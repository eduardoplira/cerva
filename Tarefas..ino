void enchetk1(int litro)
{

    byte vazant;
    if (!litro)
    {
        Serial.println("Litragem única");
    }
    else
    {
        litro = litro * 450; //fazer calculo de litragem
        Serial.println("Enchendo Tanque 1");
        digitalWrite(CV1, HIGH); //abre a valvula de entrada
        id = Alarm.timerOnce(300, errotk1);
        while (litro)
        {
            if (digitalRead(FT1))
            {
                if (!vazant)
                {
                    vazant = 1;
                }
            }
            else if (!digitalRead(FT1))
            {
                if (vazant)
                {
                    vazant = 0;
                    litro--;
                    Serial.println(litro);
                }
            }
            Alarm.delay(0);
        }
        Alarm.free(id);
        id = dtINVALID_ALARM_ID;
        Serial.println("Cheio");
        digitalWrite(CV1, LOW);
    }
}

void aquecetk1(byte t)
{
    int timer = 300;
    Tset[1] = t;
    while (temp[1] <= Tset[1])
    {
        //controlatemp();
        Alarm.delay(1000);
        if (timer)
            timer--;
        else
            printaerro(4, 3);
    }
    Serial.println("Temperatura atingida");
}

void transferetk1()
{
    int timer = 3000;
    byte t;
    Tset[1] = 0; //Desliga TK1
    Serial.println("Transferindo TK1>TK2");
    digitalWrite(CV2, HIGH);
    digitalWrite(CV3, HIGH);
    for (t = 5; t > 0; t--)
    { // espera 5s para encher a tubulação
        Alarm.delay(1000);
    }
    digitalWrite(B1, HIGH);
    while (digitalRead(PT1))
    {
        Alarm.delay(100);
        if (timer)
            timer--;
        else
            printaerro(3, 3);
    }
    digitalWrite(CV2, LOW);
    digitalWrite(B1, LOW);
    digitalWrite(CV3, LOW);
    Serial.println("Transferencia Completa");
}

void aquecetk2() //Colocar erro de timeout
{
    byte c;
    byte t;
    int timer;
    Serial.println("Brassagem");
    digitalWrite(CV4, HIGH); //abre saída TK2
    digitalWrite(CV3, HIGH); //abre entrada TK2
    for (t = 5; t > 0; t--)
    { // espera 5s para encher a tubulação
        Alarm.delay(1000);
    }
    digitalWrite(B1, HIGH); //liga bomba
    Tset[2] = Temperatura[1];
    while (temp[2] < Tset[2])
        Alarm.delay(1000); //Espera normalizar a temperatura
    digitalWrite(B1, LOW); //Desliga Bomba
    timer = Tempocoz[1] * 60;
    while (timer)
    {
        Alarm.delay(1000);
        timer--;
    }
    for (c = 2; c < 5; c++)
    {
        digitalWrite(B1, HIGH); //liga bomba
        byte tfinal = Temperatura[c];
        while (Tset[2] < tfinal)
        {
            for (timer = 60; timer = 0; timer--)
            {
                Alarm.delay(1000);
            }
            Tset[2]++;
        }
        digitalWrite(B1, LOW);
        Serial.print("Temperatura ");
        Serial.print(c);
        Serial.println("Atingida");
        timer = Tempocoz[c] * 60;
        int timer2 = timer / 2;
        while (timer)
        {
            Alarm.delay(1000);
            timer--;
            if (timer == timer2) //Mexe misturador 5m na metade do Tempo
            {
                if (c == 5)
                    Tset[1] = Temperatura[4]; //Aquece segunda litragem
                digitalWrite(M1, HIGH);
                for (timer2 = 300; timer2 = 0; timer2--)
                {
                    timer--;
                    if (!timer)
                        break;
                    Alarm.delay(1000);
                }
                digitalWrite(M1, LOW);
            }
        }
    }
    Serial.println("Fim do primeiro cozimento");
    Tset[2] = 0; //Desliga aquecimento
    Alarm.delay(1);
}

void transferetk2()
{
    int timer = 3000;
    byte t;
    Tset[2] = 0; //Desliga TK2
    Serial.println("Transferindo TK2>TK3");
    digitalWrite(CV3, HIGH); //abre retorno TK2
    digitalWrite(CV5, HIGH); //abre retorno TK3      Reduz perda no retorno ao trocar de tanque
    for (t = 5; t > 0; t--)
    { // espera 5s para encher a tubulação
        Alarm.delay(1000);
    }
    digitalWrite(CV3, LOW);
    digitalWrite(CV4, HIGH);
    digitalWrite(B1, HIGH);
    while (digitalRead(PT1))
    {
        Alarm.delay(100);
        if (timer)
            timer--;
        else
            printaerro(3, 3);
    }
    digitalWrite(CV4, LOW);
    digitalWrite(B1, LOW);
    digitalWrite(CV5, LOW);
    Serial.println("Transferencia Completa");
}

void fervura() //Colocar erro de timeout
{
    byte c;
    byte t;
    Serial.println("Fervura");
    digitalWrite(CV5, HIGH); //abre saída TK3
    digitalWrite(CV6, HIGH); //abre entrada TK3
    for (t = 5; t > 0; t--)
    { // espera 5s para encher a tubulação
        Alarm.delay(1000);
    }
    digitalWrite(B1, HIGH); //liga bomba
    Tset[3] = Temperaturafer;
    digitalWrite(B1, LOW);  //Desliga Bomba
    digitalWrite(CV6, LOW); //Fecha saída TK2
    digitalWrite(CV5, LOW); //Fecha entrada TK2
    while (temp[3] < Tset[3])
        Alarm.delay(1000); //Espera ferver
    int e= Tempoferv *60;
    for (c = 1; c < 3; c++)
    {
        if (!Tempolup[c])
            break;
        int timer;
        for (timer = Tempolup[c] * 60; timer = 0; timer--)
        {
            Alarm.delay(1000);
            e--;
        }
        Serial.print("Lupulo ");
        Serial.print(c);
        bipa(1);
    }
    while(!e)
    {
        Alarm.delay(1000);
        e--;
    }
    Serial.println("Fim da fervura");
    Tset[3] = 0; //Desliga aquecimento
    Alarm.delay(1);
}

void bipa(byte u)
{
    byte c;
    for (c = u; c = 0; c--)
    {
        digitalWrite(Buz, HIGH);
        Alarm.delay(1000);
        digitalWrite(Buz, LOW);
        Alarm.delay(1000);
    }
}

void resfriamento()
{
    byte t;
    Serial.println("Iniciando resfriamento");
    digitalWrite(CV5, HIGH); //abre saída TK3
    digitalWrite(CV6, HIGH); //abre entrada TK3
    for (t = 5; t > 0; t--)
    { // espera 5s para encher a tubulação
        Alarm.delay(1000);
    }
    digitalWrite(B1, HIGH);  //liga bomba
    digitalWrite(CV8, HIGH); //abre entrada de agua para resfriamento
    while (Tset[3] > Tempferm)
    {
        Alarm.delay(1000);
    }
    Serial.println("Temperatura adequada para adição de fermento");
    digitalWrite(CV8, LOW);
    digitalWrite(B1, LOW);
    digitalWrite(CV6, LOW);
    digitalWrite(CV5, LOW);
}

void saida()
{
    byte t;
    int timer = 3000;
    Serial.println("Iniciando saida");
    digitalWrite(CV6, HIGH); //abre saída TK3
    digitalWrite(CV7, HIGH); //abre entrada TK3
    for (t = 5; t > 0; t--)
    { // espera 5s para encher a tubulação
        Alarm.delay(1000);
    }
    digitalWrite(B1, HIGH);
    Alarm.delay(1000);
    while (digitalRead(PT1))
    {
        Alarm.delay(100);
        if (timer)
            timer--;
        else
            printaerro(3, 3);
    }
    digitalWrite(B1, LOW);
    digitalWrite(CV6, LOW);
    digitalWrite(CV5, HIGH);
    for (t = 20; t > 0; t--) //espera 20s para esvazia a mangueira
    {
        Alarm.delay(1000);
    }
    digitalWrite(CV5, LOW);
    digitalWrite(CV7, LOW);
    digitalWrite(Buz, HIGH);
    for (t = 3; t > 0; t--) //Bipa por 3s
    {
        Alarm.delay(1000);
    }
    digitalWrite(Buz, LOW);
}
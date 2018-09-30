void recebedados()
{
    int h = 1;
    /*Serial.println("Receber dados");
    while (!Serial.available());
    delay(1000);
    Serial.println("Vai");
    for (h = 1; h < 3; h++)
    {
        litra[h] = Serial.parseInt();
        delay(100);
    }
    Serial.println("sqn");
    for (h = 1; h < 6; h++)
    {
        Temperatura[h] = Serial.parseInt();
        delay(100);
    }
    Serial.println(litra[1]);
    for (h = 1; h < 6; h++)
    {
        Tempocoz[h] = Serial.parseInt();
        delay(100);
    }
    Serial.println(litra[1]);
    for (h = 1; h < 4; h++)
    {
        Tempolup[h] = Serial.parseInt();
        delay(100);
    }
    Serial.println(litra[1]);
    Tempoferv = Serial.parseInt();
    Serial.println(litra[1]);
    Temperaturafer = Serial.parseInt();
    Serial.println(litra[1]);
    Tempferm = Serial.parseInt();*/
    Serial.print("Litragem 1: ");
    Serial.println(litra[0]);
    Serial.print("Litragem 2: ");
    Serial.println(litra[1]);
    for (h = 1; h < 6; h++)
    {
        Serial.print("Temperatura ");
        Serial.print(h);
        Serial.print(" : ");
        Serial.println(Temperatura[h-1]);
    }
    for (h = 1; h < 6; h++)
    {
        Serial.print("Tempo de Cozimento ");
        Serial.print(h);
        Serial.print(" : ");
        Serial.println(Tempocoz[h-1]);
    }
    for (h = 1; h < 4; h++)
    {
        Serial.print("Tempo de Lupulagem ");
        Serial.print(h);
        Serial.print(" : ");
        Serial.println(Tempolup[h-1]);
    }
    Serial.print("Tempo de Fervura: ");
    Serial.println(Tempoferv);
    Serial.print("Temperatura de Fervura: ");
    Serial.println(Temperaturafer);
    Serial.print("Temperatura de Fermentaçao: ");
    Serial.println(Tempferm);
    delay(1000);
}
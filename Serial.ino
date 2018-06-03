void recebedados()
{
    byte h;
    Serial.print("Receber dados");
    while (!Serial.available())
        ;
    litragem1 = Serial.parseInt();
    litragem2 = Serial.parseInt();
    for (h = 1; h < 6; h++)
    {
        Temperatura[h] = Serial.parseInt();
    }
    for (h = 1; h < 6; h++)
    {
        Tempocoz[h] = Serial.parseInt();
    }
    for (h = 1; h < 4; h++)
    {
        Tempolup[h] = Serial.parseInt();
    }
    Tempoferv = Serial.parseInt();
    Temperaturafer = Serial.parseInt();
    Tempferm = Serial.parseInt();
    Serial.print("Litragem 1: ");
    Serial.println(litragem1);
    Serial.print("Litragem 2: ");
    Serial.println(litragem2);
    for (h = 1; h < 6; h++)
    {
        Serial.print("Temperatura ");
        Serial.print(h);
        Serial.print(" : ");
        Serial.println(Temperatura[h]);
    }
    for (h = 1; h < 6; h++)
    {
        Serial.print("Tempo de Cozimento ");
        Serial.print(h);
        Serial.print(" : ");
        Serial.println(Tempocoz[h]);
    }
    for (h = 1; h < 4; h++)
    {
        Serial.print("Tempo de Lupulagem ");
        Serial.print(h);
        Serial.print(" : ");
        Serial.println(Tempolup[h]);
    }
    Serial.print("Tempo de Fervura: ");
    Serial.println(Tempoferv);
    Serial.print("Temperatura de Fervura: ");
    Serial.println(Temperaturafer);
    Serial.print("Temperatura de Fermentaçao: ");
    Serial.println(Tempferm);
}
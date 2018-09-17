void controlatemp()
{
  byte z;
  for (z = 1; z < 4; z++)
  {
    if (temp[z] <= Tset[z])
    {
      switch (z)
      {
      case 1:
        digitalWrite(Q1, HIGH);
        break;

      case 2:
        digitalWrite(Q2, HIGH);
        break;

      case 3:
        digitalWrite(Q3, HIGH);
        break;
      }
      Serial.print("liga aquecedor ");
    }
    else
    {
      Serial.print("desliga aquecedor ");
      switch (z)
      {
      case 1:
        digitalWrite(Q1, LOW);
        break;

      case 2:
        digitalWrite(Q2, LOW);
        break;

      case 3:
        digitalWrite(Q3, LOW);
        break;
      }
    }

    Serial.println(z);
  }
  delay(1000);
  letemp(1);
  delay(1000);
  letemp(2);
  delay(1000);
  letemp(3);
}

void letemp(byte l)
{
  byte data[12];
  byte i;
  ds.reset();
  switch (l)
  {
  case 1:
    ds.select(Ts1addr);
    break;

  case 2:
    ds.select(Ts2addr);
    break;

  case 3:
    ds.select(Ts3addr);
    break;
  }
  ds.write(0xBE);
  for (i = 0; i < 9; i++)
  { // we need 9 bytes
    data[i] = ds.read();
    //Serial.print(data[i], HEX);
  }
  Serial.print(" ");
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s)
  {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10)
    {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  }
  else
  {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00)
      raw = raw & ~7; // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20)
      raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40)
      raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  Serial.print("Temperatura TK ");
  Serial.print(l);
  Serial.println();
  temp[l] = (float)raw / 16.0;
  Serial.println(temp[l]);
  ds.reset();
  switch (l) //Seleciona próxima leitura
  {
  case 1:
    ds.select(Ts2addr);
    break;

  case 2:
    ds.select(Ts3addr);
    break;

  case 3:
    ds.select(Ts1addr);
    break;
  }
  ds.write(0x44, 1);
}

byte *leaddr(byte a) //Lê endereço dos sensores e registra na variável correspondente no setup
{
  byte i;
  byte addr[8];

  if (!ds.search(addr))
  { //Se não retornar valor, mostra mensagem
    Serial.print("Erro Sem Sensor ");
    Serial.print(a);
    Serial.println();
    return;
  }

  Serial.print("ROM =");
  for (i = 0; i < 8; i++)
  {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }
  Serial.println();

  if (OneWire::crc8(addr, 7) != addr[7])
  {
    Serial.println("Falha na Comunicação com sensor");
    return;
  }
  if (addr[0] == 0x28)
    type_s = 0;
  else if (addr[0] == 0x10)
  {
    type_s = 1;
  }
  else
  {
    Serial.print("Thermistor não suportado");
    return;
  }

  return addr;
}

void registrads()
{
  byte z;
  byte *a;
  a = leaddr(1);
  for (z = 0; z < 8; z++)
  {
    Ts1addr[z] = *(a + z);
  }
  a = leaddr(2);
  for (z = 0; z < 8; z++)
  {
    Ts2addr[z] = *(a + z);
  }
  a = leaddr(3);
  for (z = 0; z < 8; z++)
  {
    Ts3addr[z] = *(a + z);
  }
  Serial.println("Leitura pronta");
}

void printaddr(void)
{
  byte x;
  for (x = 0; x < 8; x++)
  {
    Serial.print(' ');
    Serial.print(Ts1addr[x], HEX);
  }
  Serial.println();
  for (x = 0; x < 8; x++)
  {
    Serial.print(' ');
    Serial.print(Ts2addr[x], HEX);
  }
  Serial.println();
  for (x = 0; x < 8; x++)
  {
    Serial.print(' ');
    Serial.print(Ts3addr[x], HEX);
  }
  Serial.println();
}

/* Serial.println();









  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end

  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);         // Read Scratchpad

  Serial.print("P=");
  Serial.print(present,HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print( OneWire::crc8( data, 8), HEX);
  Serial.println();
  }
  }
  //for (a=0; a<3; a++){
*/

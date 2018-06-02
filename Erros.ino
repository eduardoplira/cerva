void printaerro(byte er, byte cp) {
  Serial.println("Erro fatal:");
  switch (er) {
    case 1:
      Serial.print("Falta sensor ");
      Serial.print('cp');
      break;
    case 2:
      Serial.println("Tempo excedido enchendo TK1");
      break;
    case 3:
      Serial.println("Tempo excedido transferindo TK1 > TK2");
      break;
    case 4:
      Serial.println("Tempo excedido aquecendo TK1");
      break;
    default:
    Serial.println("Outro");
      break;
  }
  while (1);
}

void errotk1(void){      //Chama erro tk1 falta água.
  printaerro(2,1);
}
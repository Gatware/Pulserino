void menu()
{
lcd.clear();
while(!(PIND&0x20)){delay(300);} // Attende che venga lasciato il pulsante
lcd.print("Incremento");
while(PIND&0x20) // Continua a leggere l'encoder finché non premo
  {
  encoder();
  if(E!=0) {cv+=E; E=0; t1=millis(); delay(20);}
  if(inc>5) {noTone(7); inc=5;}
  if(inc<1) {noTone(7); inc=1;}
  lcd.setCursor(0,1);
  switch(inc)
    {
    case 1: lcd.print("+/-1"); break;
    case 2: lcd.print("+/-10"); break;
    case 3: lcd.print("+/-100"); break;
    case 4: lcd.print("x/:2"); break;
    case 5: lcd.print("x/:10"); break;
    }
}


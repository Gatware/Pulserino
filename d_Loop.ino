void loop()
{ // PIND&0x20)>>5 è come dire digitalRead(5).
P=(PIND&0x20)>>5; // Legge il pulsante dell'encoder (0=Premuto)
if(Po==1 && P==0) {t1=millis(); Po=0; menu(); while(!(PIND&0x20)){delay(300);}} // Quando viene premuto il pulsante salta al menu.
if(Po==0 && P==0) // Se era ed è premuto per almeno 1 secondo
  {
  if(millis()-t1>999) 
    {
    Po=1; Bip();
   
    while(!(PIND&0x20)) 
    delay(200);
    }
  } // END premuto per almeno 1 secondo
encoder();
if(E!=0)
  {
  if(inc==1) cpm+=E;
  else if(inc==2) cpm+=10*E;
  else if(inc==3) cpm+=100*E;
  else if(inc==4) {if(E==1) cpm<<1; else cpm>>1;}
  else if(inc==5) {if(E==1) cpm*=10; else cpm/=10;}
  E=0;
  // T=60000000/cpm;
  }
  
PORTD|=00001000;
delayMicroseconds(10);
PORTD&=11110111;
if(cpm<601) delay(int(60000/cpm+0.5))

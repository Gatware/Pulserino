void loop()
{ // PIND&0x20)>>5 è come dire digitalRead(5).
P=(PIND&0x20)>>5; // Legge il pulsante dell'encoder (0=Premuto)
if(Po==1 && P==0)// Quando viene premuto il pulsante salta al menu.
  {
  t1=millis(); Po=0;
  menu();
  lcd.setCursor(0,0); lcd.print("          Vel.  ");
  visualcpm();
  while(!(PIND&0x20))
    {delay(100);}
  } 
if(Po==0 && P==0) // Se era ed è premuto per almeno 1 secondo
  {
  if(millis()-t1>999) 
    {
    Po=1; Bip();  
    while(!(PIND&0x20)) 
      {delay(100);}
    }
  } // END premuto per almeno 1 secondo
encoder();
if(E!=0)
  {
  if(inc==1) cpm+=E;
  else if(inc==2) cpm+=10*E;
  else if(inc==3) cpm+=100*E;
  else if(inc==4) cpm+=1000*E;
  else if(inc==5) cpm+=10000*E;
  else if(inc==6) cpm+=100000*E;  
  else if(inc==7) {if(E==1) cpm*=2; else cpm/=2;}
  else if(inc==8) {if(E==1) cpm*=10; else cpm/=10;}
  if(cpm<60) cpm=60;
  if(cpm>1000000) cpm=1000000;
  visualcpm();
  E=0;
  calc();
  }
cont+=1;
if(cont>T)
  {
  cont=0;
  PORTD|=B10000000;
  delayMicroseconds(10);
  PORTD&=B01111111;
  }
}

void calc()
{
T=8280000/cpm+2; // T in cicli di circa 7,353uS (Loop: circa 7,353uS).
     if(cpm>150000)T/=1.1;
else if(cpm>99000)T/=1.05;
else if(cpm>59999)T*=0.98;
  
  
}


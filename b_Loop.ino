// PIND&0x20)>>5 è come dire digitalRead(5).
void loop()
{ 
P=(PIND&0x20)>>5; // Legge il pulsante dell'encoder (0=Premuto)
if(P==0 && Po==1)// Quando viene premuto il pulsante salta al menu.
  {
  t1=millis(); Po=0;
  menu();
  lcd.setCursor(0,0); lcd.print("          Vel.  ");
  visualcpm();
  while(!(PIND&0x20))
    {delay(100);}
  } 

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

void visualcpm()
{
lcd.setCursor(6,1);
if(cpm<100) lcd.print("     ");
else if(cpm<1000) lcd.print("    ");
else if(cpm<10000) lcd.print("   ");
else if(cpm<100000) lcd.print("  ");
else if(cpm<1000000) lcd.print(" ");

lcd.print(cpm);
}

void encoder()
{
//S=3-(PIND>>3)&B00000011; Serviva per l'encoder su PD3 e PD4.
           // PD 76543210
S=3-PIND&B00000011; // Gli I/O 0 e 1 sono PD0 e PD1, perciò non devo scorrere a destra. 
// Il valore binario di S rappresenta A e B. Il centrale dell'encoder è a massa,
                    // quindi faccio complemento a 3 (11)  
S^=S>>1; // Faccio XOR (^) fra S (gray) e il suo bit 1, facendolo scorrere a Dx: AB XOR A,
         // ottenendo un binario che per ogni scatto fa 0-1-2-3-0 oppure 0-3-2-1-0.
if (S!=So && S==0) X=0;
if (X==0)
  {
  if (So==1&&S==2)
    {E=1; X=1; Bip();}
  if (So==3&&S==2)
    {E=-1; X=1; Bip();}
  if (S==0)
    {E=0; X=0;}
  So=S;  
  }
}

void Bip()   {tone(6,1000,15);}

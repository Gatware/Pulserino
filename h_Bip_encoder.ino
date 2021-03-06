void Bip()   {tone(6,1000,15);}

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

void mask()
{
lcd.setCursor(0,0); lcd.print("          Vel.  ");
lcd.setCursor(0,1); lcd.print("+/-1"); visualcpm();
lcd.setCursor(13,1); lcd.print("cpm");
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


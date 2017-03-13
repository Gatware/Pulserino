// while(!(PIND&0x20)) è come scrivere: while(digitalRead(5)=LOW)
// while( (PIND&0x20)) è come scrivere: digitalRead(5)=HIGH

void setup()
{
lcd.begin(16,2);
pinMode(0,INPUT); // Encoder - A
pinMode(0,INPUT_PULLUP);
pinMode(1,INPUT); // Encoder - B
pinMode(1,INPUT_PULLUP);
pinMode(5,INPUT); // Encoder - Pulsante.
pinMode(5,INPUT_PULLUP);
pinMode(6,OUTPUT); // Capsula piezo
pinMode(7,OUTPUT); // Uscita
pinMode(A0,OUTPUT); // Retroilluminazione (0:accesa).
calc();

lcd.print("   PULSERINO    ");
delay(1000);
lcd.clear();
mask();
} // END setup



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

pinMode(3,OUTPUT); // Uscita
pinMode(7,OUTPUT); // Capsula piezo

T=60000000/cpm; // in uS.
} // END setup



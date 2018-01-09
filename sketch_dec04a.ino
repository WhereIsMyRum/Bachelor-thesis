boolean toggle1 = 0;
unsigned long t = 0;
String str;
int currentMicros = 0;
int previousMicros = 0;

void setup() {
  
  cli();
  Serial.begin(4000000);
  pinMode(9,OUTPUT);
  
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 249;// = (16*10^6) / (1000*64) - 1 (must be <65536)
  // turn on CTC (Clear timer on compare) mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  sei();

}

ISR(TIMER1_COMPA_vect){
  
      float voltage1 = analogRead(A0);
      voltage1 = voltage1 * (5.0 / 1023.0);
      String str1 = String(voltage1,DEC);
      if(str1.length() > 6) str1.remove(str1.indexOf('.')+3, str1.length() - str1.indexOf('.')+2);
      str1 = str1 + "d";
      
      float voltage2 = analogRead(A1);
      voltage2 = voltage2 * (5.0 / 1023.0);
      String str2 = String(voltage2,DEC);
      if(str2.length() > 6) str2.remove(str2.indexOf('.')+3, str2.length() - str2.indexOf('.')+2);
      str2 = str2 + "r";

      //Serial.println(str1);
      Serial.println(str2);

      if(t == 1000)
      {
        digitalWrite(9,HIGH);
      }
      if(t == 2000)
      {
        digitalWrite(9,LOW);
        t = 0;
      }
      t++;
 
}

void loop() {
}

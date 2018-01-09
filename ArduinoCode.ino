float i = 0;
float j = 500.00;

bool dir = true;

unsigned long previousMicros = 0;
const long interval = 1000;

void setup()
{
    Serial.begin(115200);
}
  
void loop()
{
    unsigned long currentMicros = micros();
    if(currentMicros-previousMicros >= interval)
    {
      String str3 = String(currentMicros,DEC) +"t";
      
      float voltage1 = analogRead(A0);
      voltage1 = voltage1 * (5.0 / 1023.0);
      String str1 = String(voltage1,DEC);
      if(str1.length() > 6) str1.remove(str1.indexOf('.')+3, str1.length() - str1.indexOf('.')+2);
      str1 = str1 + "d";
      
      float voltage2 = analogRead(A2);
      voltage2 = voltage2 * (5.0 / 1023.0);
      String str2 = String(voltage2,DEC);
      if(str2.length() > 6) str2.remove(str2.indexOf('.')+3, str2.length() - str2.indexOf('.')+2);
      str2 = str2 + "r";
      
      //String str1 = String(i,DEC);
      //if(str1.length() > 6) str1.remove(str1.indexOf('.')+3, str1.length() - str1.indexOf('.')+2);
      //str1 = str1 + "d";
      
      //String str2 = String(j,DEC);
      //if(str2.length() > 6) str2.remove(str2.indexOf('.')+3, str2.length() - str2.indexOf('.')+2);
      //str2 = str2 + "r";
      
      Serial.println(str1);
      Serial.println(str2);
      Serial.println(str3);
      previousMicros = currentMicros;
      i++;
      j++;
      if(j == 999) j=0;
      if(i == 999) i=0;
      //delayMicroseconds(500);
    }
   
}

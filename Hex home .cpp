#include<SoftwareSerial.h>
#include<TimeLib.h>
int Motorfeeder=8;
int heater=9 ;
int cooler =6;
int tempsensor = A0;
int feedsensor =A1;
SoftwareSerial gsmModule(0,1);

void setup() {

Serial.begin(9600);
pinMode(Motorfeeder,OUTPUT);
gsmModule.begin(9600);
sendATCommand("AT");
sendATCommand("AT+CMGF=1");
}

void loop() {
int sensorValue=analogRead(tempsensor);
int feedsValue=analogRead(feedsensor);

float voltemp = (feedsValue/1023.0)*5.0;
float temp = (voltemp-0.5)*100.0;
float feedsvalltemp = (sensorValue/1023.0)*5.0;
int feeds;
int time;
if(feeds<=20)
{
  sendMessage("+256709492182","Hello this is Smart Bird home system/n the feeds are less of about %d Your please reminded to Reload");
}
if(temp<=19)
{

  digitalWrite(heater,HIGH);
  delay(5000);
}
else
{
    digitalWrite(heater,LOW);
  delay(500);
}
if(temp>=21)
{

  digitalWrite(cooler,HIGH);
  delay(5000);
}
else
{
    digitalWrite(cooler,LOW);
  delay(500);
}
if(hour()== 8 && minute()==0)
{

  digitalWrite(Motorfeeder,HIGH);
  delay(500);
}
else
{
    digitalWrite(Motorfeeder,LOW);
  delay(500);
}
}
void sendMessage(const char* phoneNumber, const char* message)
{
  gsmModule.println("AT+CMGS=\""+ String(phoneNumber)+"\"");
  delay(1000);
  gsmModule.println(message);
   delay(1000);
     gsmModule.write(26);
     delay(1000);

}

void sendATCommand(char* command)
{
  gsmModule.println("command");
  delay(1000);
  while (gsmModule.available());
{
  Serial.write(gsmModule.read());
}
}

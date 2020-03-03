#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include "checkrain.h"

//define pins
// for led 
// for relay
//define variables
int RedLedPin=4,GreenLedPin=5,RelayPin=6;

int t=0,tH=0,tM=0; //time variables
boolean rainF=false;



WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void setup (){
Serial.begin(115200);
WiFi.begin(ssid, password); 

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();

}
void loop(){
t=timestamp();
// grab timestamp
//check 
if (t > 000 and t <006){ //five minutes after midnight it grabs owm info

rainF=IsItRain();  
if (rainF ==true) {
stopwatering;}
else {startwatering;}

}
for (int TimeWait=0; TimeWait==2999; TimeWait++){ //five minutes of wait
delay(1000);//wait for 1 second
}

}//loop end

int timestamp(){
   timeClient.update();
  tH=timeClient.getHours();
  tM=timeClient.getMinutes();
  return ((tH* 100) + tM); 
}
void stopwatering(){
digitalWrite(RelayPin,HIGH);
digitalWrite(RedLedPin,HIGH);
digitalWrite(GreenLedPin,LOW);
  //switch off the relay
//turn on red led, turn off green led
}
void startwatering(){
digitalWrite(RelayPin,LOW);
digitalWrite(RedLedPin,LOW);
digitalWrite(GreenLedPin,HIGH);
}


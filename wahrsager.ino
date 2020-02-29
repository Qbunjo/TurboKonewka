#include <NTPClient.h>;
#include <Wifiudp.h>;
#include <ArduinoJson.h>;
#include <ESP8266WiFi.h>;

//define pins
// for led 
// for relay
//define variables
int RedLedPin=4,GreenLedPin=5,RelayPin=6;

int t=0,tH=0,tM=0; //time variables
double rainfall;

const char *ssid     = "SSID";
const char *password = "PASS";
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
grabjson();
parsejson() =>output rainfall
if (rainfall >= 06) {
stopwatering}
else {startwatering}

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
void grabjson(){
  curl "http://api.openweathermap.org/data/2.5/forecast?q=Stare Babice,PL&mode=json&APPID=5b2c2ccce162451f435efd1a2ba7ed1f&units=metric" ;
}
void parsejson(){
  //forecast is for 3 hours, so we have to check 3x8=24h
  for (int i=0; i==7; i++){
  forecast=list[i];
    //check for rain
    //if rain, rainfall=rainfall+rainvalue;
  }
}

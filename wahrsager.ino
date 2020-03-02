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

#define max_readings 8

Forecast_record_type  WxConditions[1];
Forecast_record_type  WxForecast[max_readings];

#include "common.h"

float rain_readings[max_readings]        = {0};


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
rainfall=parsejson();
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
   byte Attempts = 1;
  while ((RxForecast == false) && Attempts <= 2) { // Try up-to twice for Forecast data
              if (RxForecast == false) RxForecast = obtain_wx_data(client, "forecast");
        Attempts++;
      }
}
float parseJson(){
  do {   
     rain_readings[r]     = WxForecast[r].Rainfall;
     float rainFall=rainFall+rain_readings[r];
    r++;
  } while (r <= max_readings);
return rainFall;}
  }
}

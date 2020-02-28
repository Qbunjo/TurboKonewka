//TODO
#include NTP;
#include NTPUDP;
#include json;
#include WIFI8266;

//define pins
// for led 
// for relay
//define variables

int t=0,tH=0 tM=0; //time variables

const char *ssid     = "SSID";
const char *password = "PASS";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", hour, 60000);

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
grabjson
parsejson =>output rainfall
if (rainfall >= 06) {
stopwatering}
else {startwatering}

}
for (TimeWait=0, TimeWait==3000, TimeWait+2){ //five minutes of wait
delay(1000);//wait for 1 second
ClockLed LOW;
delay(1000);//wait for 1 second
ClockLed HIGH;
}

}//loop end

int timestamp(){
   timeClient.update();
  tH=timeClient.getHours();
  tM=timeClient.getMinutes();
  return ((tH* 100) + tM); 
}
void stopwatering(){
//switch off the relay
//turn on red led, turn off green led
}
void startwatering(){
//switch on the relay, turn off red led, turn on green led
}
void grabjson(){
}
void parsejson(){
}


#include "owm_credentials.h"   // See 'owm_credentials' tab and enter your OWM API key and set the Wifi SSID and PASSWORD
#include <ArduinoJson.h>       // https://github.com/bblanchon/ArduinoJson
#include <WiFi.h>              // Built-in
#include "forecast_record.h"

//################ VARIABLES ###########################

String  Time_str, Date_str, rxtext; // strings to hold time and received weather data;
int     StartTime, CurrentHour = 0, CurrentMin = 0, CurrentSec = 0;
float rainFall;

//################ PROGRAM VARIABLES and OBJECTS ################

#define max_readings 8

Forecast_record_type  WxConditions[1];
Forecast_record_type  WxForecast[max_readings];

#include "common.h"

float rain_readings[max_readings]        = {0};

long SleepDuration = 30; // Sleep time in minutes, aligned to minute boundary, so if 30 will always update at 00 or 30 past the hour
int  WakeupTime    = 7;  // Don't wakeup until after 07:00 to save battery power
int  SleepTime     = 23; // Sleep after (23+1) 00:00 to save battery power

//#########################################################################################
void setup() {
  StartTime = millis();
  Serial.begin(115200);
  if (StartWiFi() == WL_CONNECTED && SetupTime() == true) {
    if ((CurrentHour >= WakeupTime && CurrentHour <= SleepTime)) {
          byte Attempts = 1;
      WiFiClient client;   // wifi client object
      while ((RxForecast == false) && Attempts <= 2) { // Try up-to twice for Forecast data
              if (RxForecast == false) RxForecast = obtain_wx_data(client, "forecast");
        Attempts++;
      }
      if (RxForecast) { // If received Forecast data then proceed, report later if failed
        StopWiFi(); // Reduces power consumption
       
      
      }
    }
   }
}
//#########################################################################################
void loop() { // this will never run!
}


//#########################################################################################
void DisplayForecastSection(int x, int y) {
  
  int r = 1;
  do {   
     rain_readings[r]     = WxForecast[r].Rainfall;
     rainFall=rainFall+rain_readings[r];
    r++;
  } while (r <= max_readings);
}

//#########################################################################################
uint8_t StartWiFi() {
  Serial.print(F("\r\nConnecting to: ")); Serial.println(String(ssid));
  IPAddress dns(8, 8, 8, 8); // Google DNS
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  unsigned long start = millis();
  uint8_t connectionStatus;
  bool AttemptConnection = true;
  while (AttemptConnection) {
    connectionStatus = WiFi.status();
    if (millis() > start + 15000) { // Wait 15-secs maximum
      AttemptConnection = false;
    }
    if (connectionStatus == WL_CONNECTED || connectionStatus == WL_CONNECT_FAILED) {
      AttemptConnection = false;
    }
    delay(100);
  }
  if (connectionStatus == WL_CONNECTED) {
    Serial.println("WiFi connected at: " + WiFi.localIP().toString());
  }
  else Serial.println("WiFi connection *** FAILED ***");
  return connectionStatus;
}
//#########################################################################################
void StopWiFi() {
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
}
//#########################################################################################
boolean SetupTime() {
  configTime(0, 0, "0.europe.pool.ntp.org", "time.nist.gov");
  setenv("TZ", Timezone, 1);
  tzset(); // Set the TZ environment variable
  delay(100);
  bool TimeStatus = UpdateLocalTime();
  return TimeStatus;
}
//#########################################################################################
boolean UpdateLocalTime() {
  struct tm timeinfo;
  char output[30], day_output[30];
  while (!getLocalTime(&timeinfo, 5000)) { // Wait for 5-sec for time to synchronise
    Serial.println(F("Failed to obtain time"));
    return false;
  }
  strftime(output, 30, "%H", &timeinfo);
  CurrentHour = timeinfo.tm_hour;
  CurrentMin  = timeinfo.tm_min;
  CurrentSec  = timeinfo.tm_sec;
  //See http://www.cplusplus.com/reference/ctime/strftime/
  //Serial.println(&timeinfo, "%a %b %d %Y   %H:%M:%S"); // Displays: Saturday, June 24 2017 14:05:49
  Serial.println(&timeinfo, "%H:%M:%S");                 // Displays: 14:05:49
  if (Units == "M") {
    strftime(day_output, 30, "%d-%b-%y", &timeinfo);     // Displays: 24-Jun-17
    strftime(output, 30, "%H:%M", &timeinfo);            // Creates: '14:05'
  }
  else {
    strftime(day_output, 30, "%b-%d-%y", &timeinfo);     // Creates: Jun-24-17
    strftime(output, 30, "%I:%M%p", &timeinfo);          // Creates: '2:05pm'
  }
  Date_str = day_output;
  Time_str = output;
  return true;
}



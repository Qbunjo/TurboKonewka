#include <Arduino.h>
#include <JsonListener.h>
#include <time.h>
#include "OpenWeatherMapForecast.h"
float rain=0;
float rainTreshold=0.4;
boolean isitgonnarain=false;

// initiate the client
OpenWeatherMapForecast client;

// See https://docs.thingpulse.com/how-tos/openweathermap-key/
String OPEN_WEATHER_MAP_APP_ID = "XXX";
/*
Go to https://openweathermap.org/find?q= and search for a location. Go through the
result set and select the entry closest to the actual location you want to display 
data for. It'll be a URL like https://openweathermap.org/city/2657896. The number
at the end is what you assign to the constant below.
 */
String OPEN_WEATHER_MAP_LOCATION_ID = "758343";

String OPEN_WEATHER_MAP_LANGUAGE = "pl";
boolean IS_METRIC = true;
uint8_t MAX_FORECASTS = 8;

 
boolean IsItRain() {
  Serial.begin(115200);
 
  Serial.println();
  Serial.println("\n\nNext Loop-Step: " + String(millis()) + ":");

  OpenWeatherMapForecastData data[MAX_FORECASTS];
  client.setMetric(IS_METRIC);
  client.setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  uint8_t allowedHours[] = {0,12};
  client.setAllowedHours(allowedHours, 2);
  uint8_t foundForecasts = client.updateForecastsById(data, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION_ID, MAX_FORECASTS);
  Serial.printf("Found %d forecasts in this call\n", foundForecasts);
  Serial.println("------------------------------------");
  time_t time;
  for (uint8_t i = 0; i < foundForecasts; i++) {
    Serial.printf("---\nForecast number: %d\n", i);
    // {"dt":1527066000, uint32_t observationTime;
    time = data[i].observationTime;
    Serial.printf("observationTime: %d, full date: %s", data[i].observationTime, ctime(&time));
    // "main":{
    //   "temp":17.35, float temp;
    Serial.printf("temp: %f\n", data[i].temp);
    //   "temp_min":16.89, float tempMin;
    Serial.printf("tempMin: %f\n", data[i].tempMin);
    //   "temp_max":17.35, float tempMax;
    Serial.printf("tempMax: %f\n", data[i].tempMax);
    //   "pressure":970.8, float pressure;
    Serial.printf("pressure: %f\n", data[i].pressure);
    //   "sea_level":1030.62, float pressureSeaLevel;
    Serial.printf("pressureSeaLevel: %f\n", data[i].pressureSeaLevel);
    //   "grnd_level":970.8, float pressureGroundLevel;
    Serial.printf("pressureGroundLevel: %f\n", data[i].pressureGroundLevel);
    //   "humidity":97, uint8_t humidity;
    Serial.printf("humidity: %d\n", data[i].humidity);
    //   "temp_kf":0.46
    // },"weather":[{
    //   "id":802, uint16_t weatherId;
    Serial.printf("weatherId: %d\n", data[i].weatherId);
    //   "main":"Clouds", String main;
    Serial.printf("main: %s\n", data[i].main.c_str());
    //   "description":"scattered clouds", String description;
    Serial.printf("description: %s\n", data[i].description.c_str());
    //   "icon":"03d" String icon; String iconMeteoCon;
    Serial.printf("icon: %s\n", data[i].icon.c_str());
    Serial.printf("iconMeteoCon: %s\n", data[i].iconMeteoCon.c_str());
    // }],"clouds":{"all":44}, uint8_t clouds;
    Serial.printf("clouds: %d\n", data[i].clouds);
    // "wind":{
    //   "speed":1.77, float windSpeed;
    Serial.printf("windSpeed: %f\n", data[i].windSpeed);
    //   "deg":207.501 float windDeg;
    Serial.printf("windDeg: %f\n", data[i].windDeg);
    // rain: {3h: 0.055}, float rain;
    Serial.printf("rain: %f\n", data[i].rain); //HEREHEREHERE!!!
   rain=rain+data[i].rain;
    // },"sys":{"pod":"d"}
    // dt_txt: "2018-05-23 09:00:00"   String observationTimeText;
    Serial.printf("observationTimeText: %s\n", data[i].observationTimeText.c_str());
  }
 if(rain>=rainTreshold){isitgonnarain=true;} else {isitgonnarain=false};
 
 }
  Serial.println();
  Serial.println("---------------------------------------------------/\n");

}
return isitgonnarain();


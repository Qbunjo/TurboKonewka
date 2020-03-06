# TurboKonewka
TurboKonewka is a virtual rain sensor based on OpenWeatherMap predictions.
It works on ESP8266 module with single relay, imitating the rain sensor connected to the sprinkles driver.

TurboKonewka checks predicted amount of rain in next 24 hours (as OWM weather is every 3 hours). The day sum of rain is then compared to set threshold. If it exceeds threshold, the relay is actuated and it breaks the sprinkles circuit.

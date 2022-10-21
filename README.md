# TurboKonewka
TurboKonewka is a virtual rain sensor based on OpenWeatherMap predictions.
It works on ESP8266 module with single relay, imitating the rain sensor connected to the sprinkles driver.

TurboKonewka checks predicted amount of rain in next 24 hours (as OWM weather is every 3 hours). The day sum of rain is then compared to set threshold. If it exceeds threshold, the relay is actuated and it breaks the sprinkles circuit.

The only thing you need is ESP8266 (can be even ESP-01 version) and simple relay. It just works as an emulator of rain sensor.
If you ask me how the real rain sensor works, it's dead simple device. Inside of a plastic pipe there is an electric switch and cardboard rings. When rain falls, the rings gets wet and soak with water. Then they break the circuit. Our device does the same, but basing on internet data.

What you have to set is rainfall threshold.
'float rainThreshold = 1.2;'

# sonoff-switch-firmware
Custom firmware to hook the "Sonoff ITEAD Smart Home WLAN Wireless Switch Basic" up to a MQTT broker.

## Important Links

This firmware is the product of certain helpful blog posts and code examples:

* [Flashing a Custom Firmware to Sonoff wifi switch with Arduino IDE](https://medium.com/@jeffreyroshan/flashing-a-custom-firmware-to-sonoff-wifi-switch-with-arduino-ide-402e5a2f77b) by Jeffrey Roshan
* [Sonoff Basic PIN configuration](https://github.com/arendst/Sonoff-Tasmota/wiki/Sonoff-Basic) by the Tasmota documentation
* [MQTT - Basic ESP8266 MQTT example](http://www.s6z.de/cms/index.php/homeautomation-homecontrol/hardwareplattformen/esp8266/113-mqtt-basic-esp8266-mqtt-example) by Marco Pfannenstiel

We used the hack hinted on in the second post (connect the RED pin of the LED) to GPIO 14.


## Setup

1. Install latest Arduino IDE.
2. Install ESP8266 support as described [here](https://github.com/esp8266/Arduino).
3. Install following additional libraries (Sketch -> Include Library -> Manage Libraries): ESP8266WiFi, PubSubClient.
4. Copy `config.dist.h` to `config.h` and fill out the placeholders.
5. I had to select "Generic ESP8285 Module" for the code to run correctly, despite the switch containing a ESP8266.
6. Press button of switch before connecting it to the flasher, then connect, and let button go after 2-3 seconds to enter flash mode. Compile and flash via Arduino IDE.


## Usage

* Write a '1' into the configured MQTT topic to switch on
* Write a '0' into the confiugred MQTT topic to switch off
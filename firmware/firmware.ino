#include "config.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


// pin config
const int BUTTON = 0;
const int RELAY = 12;
const int LED_GREEN = 13;
const int LED_RED = 14;


void led_red() {
  // switch LED to red
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
}

void led_green() {
  // switch LED to green
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
}

void led_off() {
  // switch LED off
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
}

void switch_off() {
  // switch off power
  digitalWrite(RELAY, LOW);
}

void switch_on() {
  // switch on power
  digitalWrite(RELAY, HIGH);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  // called whenever a MQTT message arrives
  // we expect:
  // ASCII '1' to turn on the switch
  // ASCII '0' to turn off the switch
  if ((char)payload[0] == '1') {
    led_green();
    switch_on();
  } else {
    led_red();
    switch_off();
  }
  delay(100);
  led_off();
}

WiFiClient wifi_client;
PubSubClient mqtt_client(MQTT_BROKER, MQTT_PORT, mqtt_callback, wifi_client);

void mqtt_reconnect() {
  // ensures the MQTT client is connected
  led_red();
  while (!mqtt_client.connected()) {
    if (mqtt_client.connect(MQTT_CLIENT_ID)) {
      mqtt_client.subscribe(MQTT_TOPIC);
      led_green();
      delay(500);
      led_off();
    } else {
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  led_off();
  switch_off();

  // WLAN
  led_red();
  WiFi.begin(WLAN_SSID, WLAN_PW);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  led_green();
  delay(500);
  led_off();
}

void loop() {
  if (!mqtt_client.connected()) {
    mqtt_reconnect();
  }
  mqtt_client.loop();
}

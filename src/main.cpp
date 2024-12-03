#include <Arduino.h>
#include <HTTPClient.h>
#include <SoftTimer.h>
// #include <soc/soc.h>
// #include "soc/rtc_cntl_reg.h"

#include "EthManager.h"
#include "ApiClient.h"
#include "DHT11.h"

// Static IP configuration
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(10, 40, 10, 6);
IPAddress gateway(10, 40, 10, 255);
IPAddress subnet(255, 255, 255, 0);
HTTPClient http;

// API URL
String hostUrl = "http://10.40.10.5:3000/api/graphql";

// Pin
uint8_t s0Pin = IO4;

EthManager eth(mac, ip, gateway, subnet);
ApiClient db(hostUrl);
DHT111 s0(s0Pin, "0013a20040050000");

void testSensor(Task *me);
Task tsk0(3000, testSensor);

void setup()
{
  // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector

  Serial.begin(115200);
  while (!Serial && millis() < 5000)
    ;
  delay(200);

  pinMode(s0Pin, INPUT_PULLUP);

  eth.initialize();
  s0.initialize();

  SoftTimer.add(&tsk0);
}

void testSensor(Task* me)
{
  Serial.println("Reading sensor data...");
  float temperature = s0.getTemperature();
  float humidity = s0.getHumidity();

  Serial.println("Temperature: " + String(temperature) + " °C");
  Serial.println("Humidity: " + String(humidity) + " %");
}
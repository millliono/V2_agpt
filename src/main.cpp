#include <Arduino.h>
#include <HTTPClient.h>
#include <SoftTimer.h>

#include "EthManager.h"
#include "ApiClient.h"
#include "DHT11.h"
#include "AHT10.h"

// Choose sensor type
#define SENSOR_TYPE_DHT11
#define SENSOR_TYPE_AHT10

// Static IP configuration
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// IPAddress ip(10, 40, 10, 6);
IPAddress ip(192, 168, 1, 9);

// IPAddress gateway(10, 40, 10, 255);
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 255, 0);
HTTPClient http;

// String hostUrl = "http://10.40.10.5:3000/api/graphql";
String hostUrl = "http://192.168.1.7:3000/graphql";

#ifdef SENSOR_TYPE_DHT11
uint8_t pin = IO4;
DHT111 sensorDHT(pin, "0013a20040050001");
#endif

#if defined(SENSOR_TYPE_AHT10)
uint8_t i2cSDA = IO14;
uint8_t i2cSCL = IO15;
AHT10 sensorATH("0013a20040050002");
#endif

EthManager eth(mac, ip, gateway, subnet);
ApiClient api(hostUrl);

void testSensor(Task *me);
void postDb(Task *me);
Task tsk0(3000, testSensor);
Task tsk1(60000, postDb);

void setup()
{
  // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector

  Serial.begin(115200);
  while (!Serial && millis() < 5000)
    ;
  delay(200);

  // eth.initialize();

// Initialize pins
#ifdef SENSOR_TYPE_DHT11
  pinMode(pin, INPUT);
  sensorDHT.initialize();
#endif

#ifdef SENSOR_TYPE_AHT10
  Wire.begin(i2cSDA, i2cSCL);
  sensorATH.initialize();
#endif

  SoftTimer.add(&tsk0);
  // SoftTimer.add(&tsk1);
}

void testSensor(Task *me)
{
  Serial.println("Reading sensor data...");

#ifdef SENSOR_TYPE_DHT11
  sensorDHT.debug();
#endif

#ifdef SENSOR_TYPE_AHT10
  sensorATH.debug();
#endif
}

void postDb(Task *me)
{
#ifdef SENSOR_TYPE_DHT11
  api.postJson(sensorDHT.createJsonDoc(4, sensorDHT.getTemperature()));
  api.postJson(sensorDHT.createJsonDoc(5, sensorDHT.getHumidity()));
#endif

#ifdef SENSOR_TYPE_AHT10
  api.postJson(sensorATH.createJsonDoc(4, sensorATH.getTemperature()));
  api.postJson(sensorATH.createJsonDoc(5, sensorATH.getHumidity()));
#endif
}
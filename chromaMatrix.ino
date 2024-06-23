#include <Adafruit_NeoPixel.h>
#include <ArduinoBLE.h>

#define PIN            6
#define ROWS           10
#define COLUMNS        15
#define NUMPIXELS      ROWS * COLUMNS

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLEStringCharacteristic labelCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, 20);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("STARTING");
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  BLE.setLocalName("RSWM_ChromaMatrix");
  BLE.setAdvertisedService(ledService);
  ledService.addCharacteristic(labelCharacteristic);
  BLE.addService(ledService);
  BLE.advertise();
  strip.begin();
  strip.setBrightness(50);
  strip.show();
}

void loop() {
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    while (central.connected()) {
      if (labelCharacteristic.written()) {
        String label = labelCharacteristic.value();
        Serial.println(label);
        fillMatrixWithColor(label);
      }
    }
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}

void fillMatrixWithColor(String label) {
  uint32_t color;
  if (label == "Red") {
    color = strip.Color(255, 0, 0);
  } else if (label == "Green") {
    color = strip.Color(0, 255, 0);
  } else if (label == "Blue") {
    color = strip.Color(0, 0, 255);
  } else if (label == "White") {
    color = strip.Color(255, 255, 255);
  } else if (label == "Yellow") {
    color = strip.Color(255, 255, 0);
  } else if (label == "Orange") {
    color = strip.Color(255, 165, 0);
  } else {
    return;
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

#include <FastLED.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define LED_PIN     5
#define NUM_LEDS    150 // 10 rows * 15 columns
#define BRIGHTNESS  50
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

// BLE characteristics
BLEServer *pServer = nullptr;
BLECharacteristic *pCharacteristic = nullptr;
bool deviceConnected = false;

// Service and Characteristic UUIDs
#define SERVICE_UUID        "19b10000-e8f2-537e-4f6c-d104768a1214"
#define CHARACTERISTIC_UUID "19b10001-e8f2-537e-4f6c-d104768a1214"

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  // Initialize BLE Device
  BLEDevice::init("ESP32_BLE");
  pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::createAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  // Handle BLE device connection
  FastLED.show();
  delay(100);
}

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
        
        // Handle the incoming data to control the LED matrix
        handleLEDMatrix(value); // Update LEDs based on the command
      }
    }
};

void handleLEDMatrix(std::string command) {
  // Clear the display
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  if (command == "Red") {
    fill_solid(leds, NUM_LEDS, CRGB::Red);
  } else if (command == "Green") {
    fill_solid(leds, NUM_LEDS, CRGB::Green);
  } else if (command == "Blue") {
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
  } else if (command == "White") {
    fill_solid(leds, NUM_LEDS, CRGB::White);
  } else if (command == "Yellow") {
    fill_solid(leds, NUM_LEDS, CRGB::Yellow);
  } else if (command == "Orange") {
    fill_solid(leds, NUM_LEDS, CRGB::Orange);
  } else {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
  }
}

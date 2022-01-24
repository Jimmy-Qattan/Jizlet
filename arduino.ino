#include <ArduinoBLE.h>

BLEService service("c0a6acdd-955d-4fff-8e03-0bd30140cdcf");
BLECharCharacteristic characteristic("7057d88f-9765-456f-9352-b8f02d7c6b76", BLENotify | BLERead);

BLEStringCharacteristic ledCharacteristic("c7112802-6856-47c7-82f4-736f828f4f68", BLERead | BLEWrite | BLENotify, 20);

unsigned long timeStamp;

void setup()
{
  Serial.begin(9600);


  service.addCharacteristic(characteristic);
  service.addCharacteristic(ledCharacteristic);

  if (!BLE.begin()) {
    Serial.println("Connect NOW!");

  }

  BLE.setLocalName("Game Controller 1");
  BLE.setDeviceName("Game Controller 1");


  BLE.addService(service);

  BLE.setAdvertisedService(service);

  BLE.advertise();

  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

}

void loop()
{


  

  if (digitalRead(2) == HIGH) {
    Serial.println("D");


    if (BLE.connected()) {
      characteristic.writeValue('D');
    }
  } 
  if (digitalRead(3) == HIGH) {
    Serial.println("B");

    if (BLE.connected()) {
      characteristic.writeValue('B');
    }
  } 
  if (digitalRead(4) == HIGH) {
    Serial.println("C");

    if (BLE.connected()) {
      characteristic.writeValue('C');
    }
  } 
  if (digitalRead(5) == HIGH) {
    Serial.println("A");

    if (BLE.connected()) {
      characteristic.writeValue('A');
      Serial.println("YESSS");
    }
  }

  if (BLE.connected()) {
    if (ledCharacteristic.written()) {
      if (String(ledCharacteristic.value()) == "correct") {
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
      } else if (String(ledCharacteristic.value()) == "incorrect") {
        digitalWrite(9, LOW);
        digitalWrite(10, HIGH);
      } else if (String(ledCharacteristic.value()) == "reset") {
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
      }
    }
  }
  

  delay(50);
}

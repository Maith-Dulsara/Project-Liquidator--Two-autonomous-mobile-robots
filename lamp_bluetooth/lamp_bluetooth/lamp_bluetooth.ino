#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <FastLED.h>

#define DATA_PIN1 4 //(0-7)
#define DATA_PIN2 5 //(8-14)
#define DATA_PIN3 18 //(15-20)

#define COLOR_ORDER GRB
#define LED_TYPE WS2812B

#define NUM_LEDS    200

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];

const char* SERVICE_UUID = "6e400001-b5a3-f393-e0a9-e50e24dcca9e";
const char* CHARACTERISTIC_UUID = "6e400002-b5a3-f393-e0a9-e50e24dcca9e";


void lmp1();
void lmp2();
void lmp3();
void lmp4();
void lmp5();
void lmp6();
void lmp7();
void lmp8();
void lmp9();
void lmp10();
void lmp11();
void lmp12();
void lmp13();
void lmp14();
void lmp15();
void lmp16();
void lmp17();
void lmp18();
void lmp19();
void lmp20();

void offLmp();

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
      String val = "";
      String preVaal = "";
      Serial.print("Received value: ");
      for (int i = 0; i < value.length(); i++) {
        val = preVaal + value[i];
        preVaal = val;
      }
      if (val == "*") {
        offLmp();
        }
      if (val == "1") {
        lmp1();
        }
      if (val == "2") {
        lmp2();
        }
       if (val == "3") {
        lmp3();
        }
       if (val == "4") {
        lmp4();
        }
       if (val == "5") {
        lmp5();
        }
       if (val == "6") {
        lmp6();
        }
       if (val == "7") {
        lmp7();
        }
       if (val == "8") {
        lmp8();
        }
       if (val == "9") {
        lmp9();
        }
       if (val == "10") {
        lmp10();
        }
       if (val == "11") {
        lmp11();
        }
       if (val == "12") {
       lmp12();
        }
       if (val == "13") {
        lmp13();
        }
       if (val == "14") {
        lmp14();
        }
       if (val == "15") {
        lmp15();
        }
       if (val == "16") {
       lmp16();
        }
       if (val == "17") {
        lmp17();
        }
       if (val == "18") {
        lmp18();
        }
       if (val == "19") {
       lmp19();
        }
       if (val == "20") {
        lmp20();
        }
      Serial.println(val);
    }
  }
};

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    Serial.println("Client connected");
  }

  void onDisconnect(BLEServer* pServer) {
    Serial.println("Client disconnected");
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE...");

  BLEDevice::init("ESP32_BLE");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );

  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

  pServer->setCallbacks(new MyServerCallbacks());

  Serial.println("BLE server is ready");
  FastLED.addLeds<LED_TYPE, DATA_PIN1, RGB>(leds1, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_PIN2, RGB>(leds2, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_PIN3, RGB>(leds3, NUM_LEDS);  
}

void loop() {
}

void offLmp() {
  for (int i = 45; i <= 49 ; i++) {
    leds1[i] = CRGB::Black;
  }
  for (int i = 56; i <= 60 ; i++) {
    leds1[i] = CRGB::Black;
  }
  for (int i = 66; i <= 70 ; i++) {
    leds1[i] = CRGB::Black;
  }
  for (int i = 81; i <= 85 ; i++) {
    leds1[i] = CRGB::Black;
  }
  for (int i = 104; i <= 108 ; i++) {
    leds1[i] = CRGB::Black;
  }
  for (int i = 118; i <= 122 ; i++) {
    leds1[i] = CRGB::Black;
  }
  for (int i = 130; i <= 134 ; i++) {
    leds1[i] = CRGB::Black;
  }
  for (int i = 35; i <= 39 ; i++) {
    leds2[i] = CRGB::Black;
  }
  for (int i = 47; i <= 51 ; i++) {
    leds2[i] = CRGB::Black;
  }
  for (int i = 60; i <= 64 ; i++) {
    leds2[i] = CRGB::Black;
  }
  for (int i = 65; i <= 69 ; i++) {
    leds2[i] = CRGB::Black;
  }
  for (int i = 90; i <= 94 ; i++) {
    leds2[i] = CRGB::Black;
  }
  for (int i = 104; i <= 108 ; i++) {
    leds2[i] = CRGB::Black;
  }
  for (int i = 113; i <= 117 ; i++) {
    leds2[i] = CRGB::Black;
  }
  for (int i = 55; i <= 59 ; i++) {
    leds3[i] = CRGB::Black;
  }
  for (int i = 69; i <= 73 ; i++) {
    leds3[i] = CRGB::Black;
  }
  for (int i = 78; i <= 82 ; i++) {
    leds3[i] = CRGB::Black;
  }
  for (int i = 88; i <= 92 ; i++) {
    leds3[i] = CRGB::Black;
  }
  for (int i = 107; i <= 111 ; i++) {
    leds3[i] = CRGB::Black;
  }
  for (int i = 120; i <= 124 ; i++) {
    leds3[i] = CRGB::Black;
  }
  FastLED.show();
  }
//Lamp 1
void lmp1(){
  for (int i = 0; i < 45 ; i++) {
    leds1[i] = CRGB::Red;
 
    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  }
 
  FastLED.show();
//lamp 5 
  leds1[45] = CRGB::Red;
  leds1[46] = CRGB::Red;
  leds1[47] = CRGB::Red;
  leds1[48] = CRGB::Red;
  leds1[49] = CRGB::Red;


FastLED.show();

}

//lamp 2
void lmp2(){
    for (int i = 0; i < 45 ; i++) {
    leds1[i] = CRGB::Blue;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  }
 
  FastLED.show();
  for (int i = 50; i < 56 ; i++) {
    leds1[i] = CRGB::Blue;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  } 


// lamp 2 set
  leds1[56] = CRGB::Blue;
  leds1[57] = CRGB::Blue;
  leds1[58] = CRGB::Blue;
  leds1[59] = CRGB::Blue;
  leds1[60] = CRGB::Blue;
FastLED.show();
}


void lmp3(){
    for (int i = 0; i < 42 ; i++) {
    leds1[i] = CRGB::Yellow ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  }
  for (int i = 50; i < 55 ; i++) {
    leds1[i] = CRGB::Yellow ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  } 

    for (int i = 61; i < 66 ; i++) {
    leds1[i] = CRGB::Yellow ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  } 
  leds1[66] = CRGB::Blue;
  leds1[67] = CRGB::Blue;
  leds1[68] = CRGB::Blue;
  leds1[69] = CRGB::Blue;
  leds1[70] = CRGB::Blue;
FastLED.show();

}

void lmp4(){
  for (int i = 0; i < 44 ; i++) {
    leds1[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  }
  for (int i = 50; i < 55 ; i++) {
    leds1[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  } 

    for (int i = 72; i < 81 ; i++) {
    leds1[i] = CRGB::Fuchsia  ;

    FastLED.show();
    delay(50);
     leds1[i] = CRGB::Black;
    FastLED.show();
  }


    leds1[81] = CRGB::Blue;
  leds1[82] = CRGB::Blue;
  leds1[83] = CRGB::Blue;
  leds1[84] = CRGB::Blue;
  leds1[85] = CRGB::Blue;

  FastLED.show();

}

void lmp5(){
  for (int i = 0; i < 31 ; i++) {
    leds1[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  }
  for (int i = 86; i < 104 ; i++) {
    leds1[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  } 

  leds1[104] = CRGB::Blue;
  leds1[105] = CRGB::Blue;
  leds1[106] = CRGB::Blue;
  leds1[107] = CRGB::Blue;
  leds1[108] = CRGB::Blue;

  FastLED.show();

}

void lmp6(){
  for (int i = 0; i < 31 ; i++) {
    leds1[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  }
  for (int i = 86; i < 104 ; i++) {
    leds1[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  } 

  for (int i = 109; i < 118 ; i++) {
    leds1[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  } 

  leds1[118] = CRGB::Blue;
  leds1[119] = CRGB::Blue;
  leds1[120] = CRGB::Blue;
  leds1[121] = CRGB::Blue;
  leds1[122] = CRGB::Blue;

  FastLED.show();

}

void lmp7(){
  for (int i = 0; i < 31 ; i++) {
    leds1[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  }
  for (int i = 86; i < 104 ; i++) {
    leds1[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  } 

  for (int i = 109; i < 118 ; i++) {
    leds1[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  } 
    for (int i = 124; i < 130 ; i++) {
    leds1[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds1[i] = CRGB::Black;
    FastLED.show();
  } 

  leds1[130] = CRGB::Blue;
  leds1[131] = CRGB::Blue;
  leds1[132] = CRGB::Blue;
  leds1[133] = CRGB::Blue;
  leds1[134] = CRGB::Blue;

  FastLED.show();

}

void lmp8(){
  for (int i = 0; i < 35 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

  leds2[35] = CRGB::Blue;
  leds2[36] = CRGB::Blue;
  leds2[37] = CRGB::Blue;
  leds2[38] = CRGB::Blue;
  leds2[39] = CRGB::Blue;

  FastLED.show();

}

void lmp9(){
  for (int i = 0; i < 35 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

  for (int i = 40; i < 47 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

  leds2[47] = CRGB::Blue;
  leds2[48] = CRGB::Blue;
  leds2[49] = CRGB::Blue;
  leds2[50] = CRGB::Blue;
  leds2[51] = CRGB::Blue;

  FastLED.show();

}

void lmp10(){
  for (int i = 0; i < 35 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

  for (int i = 40; i < 47 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }
    for (int i = 52; i < 60 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

  leds2[60] = CRGB::Blue;
  leds2[61] = CRGB::Blue;
  leds2[62] = CRGB::Blue;
  leds2[63] = CRGB::Blue;
  leds2[64] = CRGB::Blue;

  FastLED.show();

}

void lmp11(){
  for (int i = 0; i < 34 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

  for (int i = 76; i >=70  ; i--) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }
  

  leds2[65] = CRGB::Blue;
  leds2[66] = CRGB::Blue;
  leds2[67] = CRGB::Blue;
  leds2[68] = CRGB::Blue;
  leds2[69] = CRGB::Blue;

  FastLED.show();

}

void lmp12(){
  for (int i = 0; i < 31 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

  for (int i = 77; i < 90 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

  leds2[90] = CRGB::Blue;
  leds2[91] = CRGB::Blue;
  leds2[92] = CRGB::Blue;
  leds2[93] = CRGB::Blue;
  leds2[94] = CRGB::Blue;

  FastLED.show();

}

void lmp13(){
  for (int i = 0; i < 31 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

  for (int i = 77; i < 90 ; i++) {
    leds2[i] = CRGB::Fuchsia ;
 
    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

    for (int i = 95; i < 104 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

  leds2[104] = CRGB::Blue;
  leds2[105] = CRGB::Blue;
  leds2[106] = CRGB::Blue;
  leds2[107] = CRGB::Blue;
  leds2[108] = CRGB::Blue;

  FastLED.show();

}

void lmp14(){
  for (int i = 0; i < 31 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

  for (int i = 77; i < 90 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

    for (int i = 95; i < 100 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

    for (int i = 109; i < 113 ; i++) {
    leds2[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds2[i] = CRGB::Black;
    FastLED.show();
  }

  leds2[113] = CRGB::Blue;
  leds2[114] = CRGB::Blue;
  leds2[115] = CRGB::Blue;
  leds2[116] = CRGB::Blue;
  leds2[117] = CRGB::Blue;

  FastLED.show();

}

void lmp15(){
  for (int i = 0; i < 55 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }



  leds3[55] = CRGB::Blue;
  leds3[56] = CRGB::Blue;
  leds3[57] = CRGB::Blue;
  leds3[58] = CRGB::Blue;
  leds3[59] = CRGB::Blue;

  FastLED.show();

}

void lmp16(){
  for (int i = 0; i < 55 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }

    for (int i = 60; i < 69 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }



  leds3[69] = CRGB::Blue;
  leds3[70] = CRGB::Blue;
  leds3[71] = CRGB::Blue;
  leds3[72] = CRGB::Blue;
  leds3[73] = CRGB::Blue;

  FastLED.show();

}


void lmp17(){
  for (int i = 0; i < 55 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }

    for (int i = 60; i < 69 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }

      for (int i = 74; i < 78 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }

  leds3[78] = CRGB::Blue;
  leds3[79] = CRGB::Blue;
  leds3[80] = CRGB::Blue;
  leds3[81] = CRGB::Blue;
  leds3[82] = CRGB::Blue;

  FastLED.show();

}

void lmp18(){
  for (int i = 0; i < 55 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }

    for (int i = 60; i < 63 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }

      for (int i = 83; i < 88 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }

  leds3[88] = CRGB::Blue;
  leds3[89] = CRGB::Blue;
  leds3[90] = CRGB::Blue;
  leds3[91] = CRGB::Blue;
  leds3[92] = CRGB::Blue;

  FastLED.show();

}

void lmp19(){
  for (int i = 0; i < 40 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }

    for (int i = 93; i < 107 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }
  leds3[107] = CRGB::Blue;
  leds3[108] = CRGB::Blue;
  leds3[109] = CRGB::Blue;
  leds3[110] = CRGB::Blue;
  leds3[111] = CRGB::Blue;

  FastLED.show();

}

void lmp20(){
  for (int i = 0; i < 40 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }

    for (int i = 93; i < 105 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }


      for (int i = 112; i < 120 ; i++) {
    leds3[i] = CRGB::Fuchsia ;

    FastLED.show();
    delay(50);
    leds3[i] = CRGB::Black;
    FastLED.show();
  }
  leds3[120] = CRGB::Blue;
  leds3[121] = CRGB::Blue;
  leds3[122] = CRGB::Blue;
  leds3[123] = CRGB::Blue;
  leds3[124] = CRGB::Blue;

  FastLED.show();

}

#define BLYNK_TEMPLATE_ID "xx"
#define BLYNK_TEMPLATE_NAME "LORA"
#define BLYNK_FIRMWARE_VERSION "0.0.1"

#define BLYNK_PRINT Serial
//#define BLYNK_debug_mode
///#define APP_debug_mode

/*CHANGE LOG

*/

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
#define USE_WEMOS_D1_MINI
//Connect D3 to GND to reset D1Mini

#define VPIN_RELAY1 V1
#define VPIN_RELAY2 V2
#define VPIN_RELAY3 V3
#define VPIN_RELAY4 V4
#define VPIN_LOG V5

#include "BlynkEdgent.h"
#include <TimeLib.h>
#include <SPI.h>
#include <LoRa.h>

//D1 ARDIUNO BASED
static const uint8_t D2   = 16; //SAFE TO USE? --- HIGH ON BOOT ??
static const uint8_t D10  = 15;
static const uint8_t D14  = 4;

bool R1;
bool R2;
bool R3;
bool R4;

// Pins mapping LoRa shield and wemos
#define nss D10
#define rst D14
#define dio0 D2

String status_log;

BlynkTimer timer;
int cnt = 0 ;

BLYNK_CONNECTED(){
  Blynk.virtualWrite(VPIN_RELAY1, 0);
  Blynk.virtualWrite(VPIN_RELAY2, 0);
  Blynk.virtualWrite(VPIN_RELAY3, 0);
  Blynk.virtualWrite(VPIN_RELAY4, 0);
  Blynk.virtualWrite(VPIN_LOG, "");
  Blynk.syncVirtual(VPIN_RELAY1); 
  Blynk.syncVirtual(VPIN_RELAY2); 
  Blynk.syncVirtual(VPIN_RELAY3); 
  Blynk.syncVirtual(VPIN_RELAY4); 
  Blynk.syncVirtual(VPIN_LOG); 
}

BLYNK_WRITE(VPIN_RELAY1){R1 = param.asInt();cnt = 0 ;}
BLYNK_WRITE(VPIN_RELAY2){R2 = param.asInt();cnt = 0 ;}
BLYNK_WRITE(VPIN_RELAY3){R3 = param.asInt();cnt = 0 ;}
BLYNK_WRITE(VPIN_RELAY4){R4 = param.asInt();cnt = 0 ;}

void updateValues(){ Blynk.virtualWrite(VPIN_LOG, status_log);}
 
void setup()
{
  Serial.begin(9600); 
  delay(100);
  BlynkEdgent.begin();

  //  Set loRa frequency 
  //  433E6 for Asia
  //  866E6 for Europe
  //  915E6 for North America

  while (!Serial);
  Serial.println("LoRa Gateway");
  LoRa.setPins(nss, rst, dio0);  
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  //LoRa.setTxPower(20);
  timer.setInterval(1000L, updateValues); 
}

void loop() {
  BlynkEdgent.run();
  timer.run(); 

  if (cnt <= 10){
    //send status only when event occurs
    if (R1){status_log = "R1:ON";}
    else { status_log = "R1:OFF";}
    if (R2){status_log = status_log + "#" + "R2:ON";}
    else{ status_log = status_log + "#" + "R2:OFF"; }
    if (R3){status_log = status_log + "#" + "R3:ON";}
    else{ status_log = status_log + "#" + "R3:OFF"; }
    if (R4){status_log = status_log + "#" + "R4:ON";}
    else{ status_log = status_log + "#" + "R4:OFF";}

    LoRa.beginPacket();
    LoRa.print(status_log);
    LoRa.endPacket();
    Serial.println("Sending>>" + status_log);
    cnt += 1;
  }
  else{ status_log = "";}
  
  //delay(500);
}
 

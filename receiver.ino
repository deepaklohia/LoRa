

#include <SPI.h>
#include <LoRa.h> 

#define OFF HIGH
#define ON LOW

int relay1 = 4 ;
int relay2 = 5 ;
int relay3 = 6 ;
int relay4 = 7 ;

bool r1_status;
bool r2_status;
bool r3_status;
bool r4_status;

String LoRaData = "";    // string to hold input
String LoRaData2 = "";   
String str ;
int val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);

  digitalWrite(relay1,OFF);
  digitalWrite(relay2,OFF);
  digitalWrite(relay3,OFF);
  digitalWrite(relay4,OFF);
  
   //  Set loRa frequency 
  //  433E6 for Asia
  //  866E6 for Europe
  //  915E6 for North America

  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
 
void loop(){
  // try to parse packet
  int packetSize = LoRa.parsePacket();

  if (packetSize) { 
    // read packet    
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.println("Received:" + LoRaData); 

      if (LoRaData.indexOf("R1:ON") >=0 && !r1_status){digitalWrite(relay1,ON); r1_status = true;}
      else if (LoRaData.indexOf("R1:OFF") >=0 && r1_status){ digitalWrite(relay1,OFF); r1_status = false; }

      if (LoRaData.indexOf("R2:ON") >=0 && !r2_status){ digitalWrite(relay2,ON);  r2_status = true; }
      else if (LoRaData.indexOf("R2:OFF") >=0 && r2_status){ digitalWrite(relay2,OFF);  r2_status = false; }

      if (LoRaData.indexOf("R3:ON") >=0 && !r3_status){digitalWrite(relay3,ON); r3_status = true;}
      else if (LoRaData.indexOf("R3:OFF") >=0 && r3_status){ digitalWrite(relay3,OFF); r3_status = false;}

      if (LoRaData.indexOf("R4:ON") >=0 && !r4_status){ digitalWrite(relay4,ON); r4_status = true;}
      else if (LoRaData.indexOf("R4:OFF") >=0 && r4_status){ digitalWrite(relay4,OFF);r4_status = false;}
      /*
     // print RSSI of packet
     Serial.print("' with RSSI ");
     Serial.println(LoRa.packetRssi());
     */
    }
    
  }
  //Serial.println(LoRaData);
  //delay(100);
}

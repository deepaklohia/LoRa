## &#x1F534; Problem Statement##
### we have two properties, say A & B, Property-A has good wifi , Property-B  has wifi issues. Due to which sometimes we are not able to send Relay/ motor signal to Property B. ###



## &#x1F34F;Solution ## 
We will be passing LoRa Signal from property-A to property-B ,in order to control motor relays at Property-B. Blynk is used at Property-A to ease this process.We can also Add Automations in Blynk to turn on relays at specific time or turn them on manually as well.

## Sendor: Wemos D1 R2 ##

WEMOS D1 R2 PIN CONNECTION
- LoRa DI00 >> D2
- LoRa RST >> D14/SDA
- LoRa NSS > D10 / SS
- LoRa MOSI >> D11 / MOSI
- LoRa MISO >> D12 / MISO
- LoRa SCK >> D13 / SCK

![IMG_9003](https://github.com/user-attachments/assets/2c0e27f9-2b67-4c87-8e83-96670a0347ea)

## Receiver: Arduino UNO ##
ARDUINO PIN CONNECTION
- LoRa DI00 >> 2
- LoRa RST >> 9
- LoRa NSS >> 10
- LoRa MOSI >> 11
- LoRa MISO >> 12
- LoRa SCK >> 13

![IMG_9004](https://github.com/user-attachments/assets/21ff4416-2e6b-414e-9e26-3bbc867f1e5d)

### $${\color{green}JDGJSS \space Powered \space by: Deepak  \space Lohia \space Automations}$$ ###

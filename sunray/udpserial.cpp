// Ardumower Sunray 
// Copyright (c) 2013-2020 by Alexander Grau, Grau GmbH
// Licensed GPLv3 for open source use
// or Grau GmbH Commercial License for commercial use (http://grauonline.de/cms2/?page_id=153)

#include "udpserial.h"
#include "WiFiEsp.h"
#include "WiFiEspUdp.h"

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)
UdpSerial udpSerial;
#endif

unsigned int localPort = 4211;  // local port 
IPAddress remoteIP(UDP_SERVER_PORT);


WiFiEspUDP Udp;
char packetBuffer[100];          // buffer to packet
int packetIdx = 0;
bool udpStarted = false;
bool udpActive = false;


void UdpSerial::begin(unsigned long baud){  
  SerialUSB.begin(baud);
}  

void UdpSerial::beginUDP(){  
  Udp.begin(localPort);  
  Udp.beginPacket(remoteIP, UDP_SERVER_PORT);
  // Udp.endPacket();
  udpStarted = true;  
}

size_t UdpSerial::write(uint8_t data){
  if ((udpStarted) && (!udpActive)) {
    udpActive = true;
    packetBuffer[packetIdx] = char(data);
    packetIdx++;
    if (packetIdx == 99){
      packetBuffer[packetIdx] = '\0';      
      Udp.write(packetBuffer);              
      packetIdx = 0;            
    }
    udpActive = false;
  }  
  SerialUSB.write(data);
  return 1; 
}
  
  
int UdpSerial::available(){
  return SerialUSB.available();
}


int UdpSerial::read(){
  return SerialUSB.read();
}


int UdpSerial::peek(){
  return SerialUSB.peek();
}

void UdpSerial::flush(){  
  SerialUSB.flush();    
}




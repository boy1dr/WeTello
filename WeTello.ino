
/*
 * WeTello (Tello control for Arduino Wemos )
 * Chris Mitchell 19/08/2018
 * 
 */
 
#include "ESP8266WiFi.h"
#include <WiFiUdp.h>

WiFiUDP UDP;

#define MyTelloSSID "TELLO-B68D84"
#define MyTelloPASS ""
#define tello_ip "192.168.10.1"
#define portCmd 8889
unsigned int localPort = 9000;

char packetBuffer[255]; 
char incomingPacket[255];
int inByte = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  do_wifi();
  delay(500);
}

void loop() {
  checkSerial();
  checkPacket();
}

void do_wifi(){
  WiFi.disconnect();
  delay(100);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(MyTelloSSID);
  WiFi.begin(MyTelloSSID, MyTelloPASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);
  UDP.begin(localPort);
  delay(500);
}

void udpSend( char * msg ){
  
  UDP.beginPacket(tello_ip, portCmd);
  Serial.print("TX: ");
  Serial.println(msg);
  delay(100);
  strcpy(packetBuffer,msg);
  //UDP.write(msg);
  UDP.write(packetBuffer,strlen(packetBuffer));
  delay(100);
  UDP.endPacket();
  delay(100);
}

void checkSerial(){
  if (Serial.available() > 0) {
    inByte = Serial.read();
    if(inByte==49){udpSend("takeoff"); }    //1 (keypress)
    if(inByte==50){udpSend("land");}        //2
    if(inByte==51){udpSend("speed?");}      //3
    if(inByte==52){udpSend("battery?");}    //4
    if(inByte==53){udpSend("Time?");}       //5
    if(inByte==54){udpSend("cw 3600");}     //6
    if(inByte==55){do_wifi();}              //7
    if(inByte==56){printWiFiStatus();}      //8
   }
}

void checkPacket(){
   int packetSize = UDP.parsePacket();
  if (packetSize){
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, UDP.remoteIP().toString().c_str(), UDP.remotePort());
    int len = UDP.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
  }
}

void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}



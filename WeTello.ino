
/*
 * WeTello (Tello control for Arduino Wemos )
 * Chris Mitchell 19/08/2018
 */
 
#include "ESP8266WiFi.h"
#include <WiFiUdp.h>

WiFiUDP UDP;

#define MyTelloSSID "TELLO-B68D84"
#define MyTelloPASS ""
#define tello_ip "192.168.10.1"
#define portCmd 8889
unsigned int localPort = 8889;

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
  delay(1000);
  udpSend("command");
  Serial.println("Waiting for commands");
}

void udpSend( char * msg ){
  UDP.beginPacket(tello_ip, portCmd);
  Serial.print("TX: ");
  Serial.println(msg);
  UDP.write(msg);
  UDP.endPacket();
}

void checkSerial(){
  if (Serial.available() > 0) {
    inByte = Serial.read();
    if(inByte==49){udpSend("takeoff"); }    //1 (keypress)
    if(inByte==50){udpSend("land");}        //2
    if(inByte==51){udpSend("speed?");}      //3
    if(inByte==52){udpSend("battery?");}    //4
    if(inByte==53){udpSend("Time?");}       //5
    if(inByte==54){udpSend("cw 360");}      //6

    if(inByte==55){udpSend("up 20");}      //7
    if(inByte==56){udpSend("right 20");}   //8
    if(inByte==57){udpSend("down 20");}    //9
    if(inByte==48){udpSend("left 20");}    //0
   }
}

void checkPacket(){
   int packetSize = UDP.parsePacket();
  if (packetSize){
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, UDP.remoteIP().toString().c_str(), UDP.remotePort());
    int len = UDP.read(incomingPacket, 255);
    if (len > 0){
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
  }
}

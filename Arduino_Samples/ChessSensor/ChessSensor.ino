#include <SoftwareSerial.h>

#include "MT7681.h"

void UpdateMCSValue(LC7681Wifi& wifi, char *ch_id, const char *value);

SoftwareSerial mySerial1(2, 3);
LC7681Wifi wifi(&mySerial1, &Serial);

const char ssid[] = "TO.GATHER";
const char key[] = "062221372";
const char server[] = "arduino.cc";
const int port = 80;

IPAddress serverIP;

int RST = 4;

void setup() {
  pinMode(RST, OUTPUT);
  Serial.begin(115200);
  mySerial1.begin(38400);
  
  // Waiting for serial port.
  while(!mySerial1)
  delay(100);   
  
  // reset module
  Serial.println("[log] Resetting Module...");
  
  wifi.begin(RST);
  
  // Waiting for establishing connection.
  // attempt to connect to AP
  while(true)
  {
    Serial.println("[log] Trying to connect AP...");
    if(!wifi.connectAP(ssid, key))
    {
      Serial.println("[log] Fail to connect, wait 5 secs to retry...");
      delay(5000);
      continue;
    }
  
    Serial.println("[log] Connected to AP!");
    break;
  }

  wifi.logger(NULL);
  
  IPAddress ip;
  Serial.print("[log] IP Address: ");
  do {
    ip = wifi.IP();
  } while (uint32_t(ip) == 0);
  
  Serial.println(ip);

  // lookup server ip
  IPAddress serverIP = wifi.nslookup(server);
  Serial.print("IP Address of ");
  Serial.print(server);
  Serial.print(" is ");
  Serial.println(serverIP);
  
  // connect to server
  while(true)
  {
    Serial.println("Trying to start connection to server...");
    if (!wifi.connect(serverIP, port))
    {
      Serial.println("Fail to connected to server, wait 5 secs to retry...");
      delay(3000);
      continue;
    }
  
    Serial.println("Connected to server!");
    break;
  }
  
  //Serial.println("Get arduino page ......");
  wifi.println("GET / HTTP/1.1");
  wifi.println("Host: www.arduino.cc");
  wifi.println("Connection: close");
  wifi.println();
}

void callback(int event, const uint8_t* data, int dataLen)
{
  switch(event)
  {
    case LC7681Wifi::EVENT_DATA_RECEIVED:
      Serial.print((const char*) data);
      break;
    case LC7681Wifi::EVENT_SOCKET_DISCONNECT:
      Serial.println("[log] Connection to server is closed!");
      break;
    case LC7681Wifi::EVENT_AP_DISCONNECT:
      Serial.println("[log] Connection to AP is closed!");
      break;
  }
}

void loop() 
{
  wifi.process(callback);

  //UpdateMCSValue(wifi, "chess_id", "0123456789");

}


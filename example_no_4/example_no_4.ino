/*
 * Circuits4you.com
 * mDNS example ESP8266 in Arduino IDE
 * After connecting to WiFi router enter esp8266.local in web browser
*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* wifiName = "rajendra";
const char* wifiPass = "root123456";
  
ESP8266WebServer server(80);

//Handles http request 
void handleRoot() {
  digitalWrite(2, 0);   //Blinks on board led on page request 
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(2, 1);
}


// the setup function runs once when you press reset or power the board
void setup() {
  
  Serial.begin(115200);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  
  Serial.print("Connecting to ");
  Serial.println(wifiName);

  WiFi.begin(wifiName, wifiPass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP

   if(WiFi.status() == WL_CONNECTED) //If WiFi connected to hot spot then start mDNS
  {
    if (MDNS.begin("raj")) {  //Start mDNS with name esp8266
      Serial.println("MDNS started");
    }
  }

  server.on("/", handleRoot);  //Associate handler function to path
    
  server.begin();                           //Start server
  Serial.println("HTTP server started");
}

// the loop function runs over and over again forever
void loop() {
  server.handleClient();
}\

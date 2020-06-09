
// For a connection via SPI include:
#include <SPI.h>
#include "SSD1306Spi.h"
// Initialize the OLED display using SPI:
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D2 -> DC
// D8 -> CS
SSD1306Spi display(D0, D2, D8);  // RES, DC, CS

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "LocalAccess-2.4GHz"
#define APPSK  "whosyourdaddy"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() 
{
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

// SSD1306Spi output function
void infoOutput(const char *ssid, const char *password) 
{
    
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Wi-Fi SSID: ");
    display.drawString(0, 10, ssid);
    display.drawString(0, 20, "Password: ");
    display.drawString(0, 30, password);
    
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  
  Serial.println();
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  
}

void loop() {
  server.handleClient();
  // clear the display
  display.clear();
  // draw the current method
  infoOutput(ssid, password);
  // write the buffer to the display
  display.display();
  
}

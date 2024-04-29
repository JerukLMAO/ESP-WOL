#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <CTBot.h> // Library for interacting with Telegram bot
#include <WakeOnLan.h>

WiFiUDP UDP;
TBMessage msg; // Stores Telegram message data
CTBot myBot;   // Object for interacting with Telegram bot
WakeOnLan WOL(UDP);

String ssid = "Fadgib";
String pass = "fadhligibran12";
String token = "6526441782:AAFJM0zrJW1GmXOcQazzifJE3h-oxG7k8Hg"; // Your Telegram bot token
const int id = 1221284266;                                       // Telegram chat ID where messages will be sent



void wakeMyPC()
{
  const char *MACAddress = "a0:1d:48:72:3f:33";

  WOL.sendMagicPacket(MACAddress); // Send Wake On Lan packet with the above MAC address. Default to port 9.
   // WOL.sendMagicPacket(MACAddress, 7); // Change the port number
}

void setup()
{
  WOL.setRepeat(3, 100); // Optional, repeat the packet three times with 100ms between. WARNING delay() is used between send packet function.

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  // Send a startup message to Telegram chat if connection is successful
  if (myBot.testConnection())
  {
    myBot.sendMessage(id, "Bot dinyalakan, terhubung ke " + ssid);
  }

  WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask()); // Optional  => To calculate the broadcast address, otherwise 255.255.255.255 is used (which is denied in some networks).

  wakeMyPC();
}

void loop()
{
  if (myBot.getNewMessage(msg))
  {
    // Trigger wol based on commands
    if (msg.text == "Wake")
    {
      wakeMyPC();
      myBot.sendMessage(id, "Telah mengirim Magic packet");

    }
  }
}
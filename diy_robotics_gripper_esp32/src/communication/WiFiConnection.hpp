#ifndef COMMUNICATION__WiFiConnection_HPP_
#define COMMUNICATION__WiFiConnection_HPP_

#include <Arduino.h>
#include <WiFi.h>
#include <string.h>
#include <functional>
#include <esp_pm.h>
#include <esp_wifi.h>
#include <esp_wifi_types.h>
#include <WebServer.h>
#include <SPIFFS.h>


#define FORMAT_LITTLEFS_IF_FAILED true


class WiFiConnection {
private:
  WiFiServer _wifiServer;
  bool _enable = false;
  WiFiClient _client;

  uint64_t _t_lastMessage;
  bool _clientConnected = false;
  uint32_t _receivedMessages = 0;

  std::string _ssid;
  std::string _password;
  uint8_t _port;
  std::string _clientName;

  std::function<bool (void * , size_t, void *, size_t)> _callback;

  void _initialize() {
    _wifiServer = WiFiServer(_port);
    _wifiServer.setNoDelay(true);


    IPAddress ipAddress(IP_ADDRESS);
    IPAddress gateway(GATEWAY_IP);
    IPAddress subnet(SUBNET_MASK);
    
    WiFi.config(ipAddress, gateway, subnet);

    // if (!SPIFFS.begin()) delay(10e3);
    Serial.println("Connecting\n to WiFi");

    WiFi.persistent(false);
    
    WiFi.hostname(_clientName.c_str());
    WiFi.disconnect();
    WiFi.begin(_ssid.c_str(), _password.c_str());
    WiFi.setSleep(false);// this code solves my problem

    esp_wifi_set_ps(WIFI_PS_NONE);
    
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(1000);
    }
    

    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.localIP());

    _client.stop();
    _wifiServer.close();
    _wifiServer.begin();
  }

public:
  WiFiConnection() {};

  WiFiConnection(const std::string& ssid, const std::string& password, std::function<bool (void * , size_t, void *, size_t)> callback, uint8_t socketPort, const std::string& clientName) {
    _ssid = ssid;
    _password = password;
    _port = socketPort;
    _clientName = clientName;
    _callback = callback;
    this->_initialize();
  };

  ~WiFiConnection() {
    _wifiServer.close();
    WiFi.disconnect();
  };

  void sendBinaryData(byte * pData, size_t len) {
    if (_client.connected()) {
      _client.write(pData, len);
      // _client.flush();
    }
  }
  void sendData(String data) { if (_client.connected()) _client.write((data + "\n").c_str()); }
  bool clientConnected() { return _clientConnected; }

  void loopForever(bool enable = true) {
    while(true) {

      if (WiFi.status() != WL_CONNECTED) this->_initialize();

      if (!_client.connected()) _client = _wifiServer.available();

      if (!_enable && enable) Serial.println("Enabled WiFi");
      else if (_enable && !enable) Serial.println("Disabled WiFi");

      else if (enable) {
        if (_client.connected()) {
          if (_clientConnected == false) { 
            Serial.println("Client has connected");
            _receivedMessages = 0;
          }
          
          byte receivedData[64];
          byte responseData[64];

          if (_client.available()) {
            _client.readBytes(&receivedData[0], sizeof(receivedData));

            if (_callback(&receivedData, sizeof(receivedData), &responseData, sizeof(responseData))) {
              _receivedMessages++;
              this->sendBinaryData(&responseData[0], sizeof(responseData));
            }
          }

          _clientConnected = true;

        } else {
          if (_clientConnected == true) {
            Serial.println("Client has disconnected");
          }

          _receivedMessages = 0;
          _clientConnected = false;
        }
      } 
      // _client.setNoDelay(true);
      _enable = enable;
      vTaskDelay(1);
    }
  }
};

#endif
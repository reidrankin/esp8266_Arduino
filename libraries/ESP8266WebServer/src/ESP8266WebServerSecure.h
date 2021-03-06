/*
  ESP8266WebServerSecure.h - Dead simple HTTPS web-server.
  Supports only one simultaneous client, knows how to handle GET and POST.

  Copyright (c) 2017 Earle F. Philhower, III. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef ESP8266WEBSERVERSECURE_H
#define ESP8266WEBSERVERSECURE_H

#include <ESP8266WebServer.h>
#include <WiFiServerSecure.h>

class ESP8266WebServerSecure : public ESP8266WebServer
{
public:
  ESP8266WebServerSecure(IPAddress addr, int port = 443);
  ESP8266WebServerSecure(int port = 443);
  virtual ~ESP8266WebServerSecure();

  void setServerKeyAndCert_P(const uint8_t *key, int keyLen, const uint8_t *cert, int certLen);
  void setServerKeyAndCert(const uint8_t *key, int keyLen, const uint8_t *cert, int certLen);

  WiFiClient client() override { return _currentClientSecure; }

  void begin() override;
  void handleClient() override;
  void close() override;

private:
  size_t _currentClientWrite (const char *bytes, size_t len) override { return _currentClientSecure.write((const uint8_t *)bytes, len); }
  size_t _currentClientWrite_P (PGM_P bytes, size_t len) override { return _currentClientSecure.write_P(bytes, len); }

protected:
  WiFiServerSecure _serverSecure;
  WiFiClientSecure _currentClientSecure;
};


#endif //ESP8266WEBSERVERSECURE_H

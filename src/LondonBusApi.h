/*
Copyright (c) 2017 Brian Lough. All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#ifndef LondonBusApi_h
#define LondonBusApi_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Client.h>

#define LONDONBUS_HOST "api.tfl.gov.uk/StopPoint/490015131W1/Arrivals"

struct TFLTickerResponse{
  
    responseObject.lineName = root[0]["lineName"].as<String>();
    responseObject.platformName = root[0]["platformName"].as<String>();
    responseObject.timeToStation = root[0]["timeToStation"].as<double>();
    responseObject.towards = root[0]["towards"].as<String>();
    responseObject.expectedArrival = root[0]["expectedArrival"].as<String>();
    
  String lineName;
  String platformMame;
  double timeToStation;
  String towards;
  String expectedArrival;
  
  String error;
};


class LondonBusApi
{
  public:
    LondonBusApi (Client &client);
    String SendGetToLondonBus(String command);
    TFLTickerResponse GetTickerInfo(String StopID);
    int Port = 443;

  private:
    Client *client;
};

#endif

#include "LondonBusApi.h"

LondonBusApi::LondonBusApi(Client &client)	{
  this->client = &client;
}

String LondonBusApi::SendGetToLondonBus(String command) {
  String body="";
  body.reserve(700);
  bool finishedHeaders = false;
  bool currentLineIsBlank = true;
	long now;
	bool avail;

	if (client->connect(LONDONBUS_HOST, Port)) {
		// Serial.println(".... connected to server");
		String outy= "GET " + command + " HTTP/1.1"
		display.clear();
  		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.setFont(ArialMT_Plain_10);
  		display.drawString(64, 0, F("Connected!"));
  		display.drawString(0, 0, (outy));
  		display.display();
		
		String a="";
		char c;
		int ch_count=0;
		client->println("GET " + command + " HTTP/1.1");
    client->println("Host: " LONDONBUS_HOST);
		client->println(F("User-Agent: arduino/1.0.0"));
		client->println();
		now=millis();
		avail=false;
		while (millis()-now<1500) {
			while (client->available()) {
				char c = client->read();
				//Serial.write(c);

        if(!finishedHeaders){
          if (currentLineIsBlank && c == '\n') {
            finishedHeaders = true;
          }
        } else {
          body=body+c;
          ch_count++;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        }else if (c != '\r') {
          currentLineIsBlank = false;
        }

				avail=true;
			}
			if (avail) {
				// Serial.println("Body:");
				// Serial.println(body);
				// Serial.println("END");
				break;
			}
		}
	}

  return body;
}

TFLTickerResponse LondonBusApi::GetTickerInfo() {
  String command="/StopPoint/490015131W1/Arrivals/";


  // Serial.println(command);
  String response = SendGetToLondonBus(command);
  TFLTickerResponse responseObject = TFLTickerResponse();
  DynamicJsonBuffer jsonBuffer;
	JsonArray& root = jsonBuffer.parseArray(response);
  if (root.success()) {
    responseObject.lineName = root[0]["lineName"].as<String>();
    responseObject.platformName = root[0]["platformName"].as<String>();
    responseObject.timeToStation = root[0]["timeToStation"].as<double>();
    responseObject.towards = root[0]["towards"].as<String>();
    responseObject.expectedArrival = root[0]["expectedArrival"].as<String>();
    
  } else {
    JsonObject& rootObject = jsonBuffer.parseObject(response);
    if (rootObject.containsKey("error")) {
       responseObject.error = rootObject["error"].as<String>();
    } else {
      responseObject.error = "Failed to parse JSON";
    }

    return responseObject;
  }
}

#include <Arduino.h>
#include <Preferences.h>
#include<robot.h>
#include<environment.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h> 



BluetoothSerial serialBT;
Preferences pref;
Robot robot;
const int CAPACITY = 256;
StaticJsonDocument<CAPACITY> doc;


enum COMMAND {
  WIFI_CONNECT,
  WIFI_DISCONNECT,
  SET_USERNAME,
  GET_USERNAME,
  SET_PASSWORD,
  GET_PASSWORD,
  SET_LANGUAGE,
  GET_LANGUAGE,
  SET_LOCATION,
  GET_LOCATION,
  SET_TIMEZONE,
  GET_TIMEZONE,
  SET_NOTIFICATION_PREFERENCES,
GET_NOTIFICATION_PREFERENCES
};


COMMAND getCommand(const String& commandStr) {
  if (commandStr == "WIFI_CONNECT") return WIFI_CONNECT;
  else if (commandStr == "WIFI_DISCONNECT") return WIFI_DISCONNECT;
  else if (commandStr == "SET_USERNAME") return SET_USERNAME;
  else if (commandStr == "GET_USERNAME") return GET_USERNAME;
  else if (commandStr == "SET_PASSWORD") return SET_PASSWORD;
  else if (commandStr == "GET_PASSWORD") return GET_PASSWORD;
  else if (commandStr == "SET_LANGUAGE") return SET_LANGUAGE;
  else if (commandStr == "GET_LANGUAGE") return GET_LANGUAGE;
  else if (commandStr == "SET_LOCATION") return SET_LOCATION;
  else if (commandStr == "GET_LOCATION") return GET_LOCATION;
  else if (commandStr == "SET_TIMEZONE") return SET_TIMEZONE;
  else if (commandStr == "GET_TIMEZONE") return GET_TIMEZONE;
  else if (commandStr == "SET_NOTIFICATION_PREFERENCES") return SET_NOTIFICATION_PREFERENCES;
  else if (commandStr == "GET_NOTIFICATION_PREFERENCES") return GET_NOTIFICATION_PREFERENCES;

  // Default case
  return WIFI_CONNECT; // or any other default command
}

void bootCotrix(){

  pref.begin("cortnonix", false);
  String username = pref.getString("username", "not_defined");
  if(username == "not_defined") {

      
      robot = Robot();
      robot.setCurrentState(Robot::BOOT);
      robot.setPrevState(Robot::BOOT);

  } else {

    Serial.println("Username already set: " + username);
    robot = Robot();
    robot.setCurrentState(Robot::IDLE);
    robot.setPrevState(Robot::IDLE);
  }
}

bool getDataFromBluetooth(StaticJsonDocument<CAPACITY>& targetDoc) {

  String data = serialBT.readStringUntil('\n');
  Serial.println("Received: " + data);
  DeserializationError error = deserializeJson(targetDoc, data); 

  if (error) { 
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str()); 
    return false;
  } 
  targetDoc.clear(); 
  return true;
}

void setup() {
  Serial.begin(115200);
  serialBT.begin("Cortnonix-AI", true); // Bluetooth device name
  Serial.println("Cortronix Bluetooth Turned ON");

  //Initial Contrix Setup
  Serial.println("Cortnonix AI - Initializing...");
  bootCotrix();


  pref.begin("cortnonix", false);
  pref.putString("username", "Abhishek ");

  
}

void loop() {

  if (serialBT.available()) {
    if (getDataFromBluetooth(doc)) {
      COMMAND command =  getCommand(doc["command"]);
      Serial.println("Command received: " + command);

        switch(command){

            case WIFI_CONNECT: {
              robot.setCurrentState(Robot::CONNECTING_TO_WIFI);
              String ssid = doc["ssid"];
              String password = doc["password"];
              Serial.println("Connecting to WiFi: " + ssid);
              // Add your WiFi connection logic here

              robot.setCurrentState(Robot::CONNECTED_TO_WIFI);
              robot.isConnectedToWiFi = true;




              break;
            }

        }

    }
  }

  // Add any additional logic for the robot here
  delay(100); // Adjust as necessary

  
  
}

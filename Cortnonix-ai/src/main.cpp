#include <Arduino.h>
#include <Preferences.h>
#include<robot.h>
#include<environment.h>



Preferences pref;
Robot robot;

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



void setup() {
  Serial.begin(115200);

  //Initial Contrix Setup
  Serial.println("Cortnonix AI - Initializing...");
  bootCotrix();


  pref.begin("cortnonix", false);
  pref.putString("username", "Abhishek ");


  
}

void loop() {
  
}

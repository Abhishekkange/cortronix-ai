#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define HEAD_IR_PIN 4
#define LDR_PIN 34

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

class Environment {

public:

  bool isDay() {
    int lightState = digitalRead(LDR_PIN);

    if (lightState == LOW) {
      Serial.println("🌑 It's Dark");
      return false;
    } else {
      Serial.println("☀️ It's Bright");
      return true;
    }
  }
};

class Eyes {

public:

  void blink() {
    Serial.println("Blink");
    delay(2000);
  }

  void seeLeft() {

    Serial.println("Looking Left side");
  }

  void seeRight() {

    Serial.println("Looking Right side");
  }

  void sleeping() {
    Serial.println("Sleeping...ZZZZ");
  }
};

class Robot {

public:
  enum State {
    IDLE,
    WAKE_UP,
    HAPPY,
    SLEEPY,
    LISTENING
  };

  State current_state = IDLE;
  Eyes eyes;

  //action functions
  void wake_up() {
    Serial.print("ROBOT SUDDENLY waked up !!");
  }

  void blink_eyes() {

    eyes.blink();
  }

  void smiling() {

    Serial.print("EMO is smiling");
  }

  //sensory functions
  bool is_head_touched() {
    int IR_VALUE = digitalRead(HEAD_IR_PIN);
    Serial.println(IR_VALUE);
    if (IR_VALUE == LOW) {
      Serial.println("OBJECT YES");
      return false;
    } else {

      Serial.println("OBJECT No");
      return true;
    }
  }
};

//creating robot and environment
Robot emo;
Environment env;



void setup() {
  Serial.begin(9600);  // Start serial communication
  pinMode(HEAD_IR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);

  Wire.begin(21, 22);                         // SDA, SCL
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Most OLEDs use 0x3C


  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Hello from ESP32!");
  display.display();
}

void loop() {
  // int ir_value = digitalRead(IR_SENSOR_PIN);

  // if(ir_value == LOW) {IDLE
  //   Serial.println("Object detected!");
  // } else {
  //   Serial.println("Object not detected!");
  // }

  // delay(200); // Optional: slow down the serial output a bit

  //switch_case
  switch (emo.current_state) {

    case Robot::IDLE:
      emo.blink_eyes();
      if (emo.is_head_touched()) {
        emo.current_state = Robot::HAPPY;
      }
      if(!env.isDay() && !emo.is_head_touched())
      {
        emo.current_state = Robot ::SLEEPY;
      }
      break;
    case Robot::HAPPY:
      emo.smiling();
      delay(1000);
      emo.current_state = Robot::IDLE;
      break;
    case Robot::SLEEPY:
      emo.eyes.sleeping();
      if(env.isDay())
      {
        emo.current_state = IDLE;
      }
      break;

    case Robot::LISTENING:

      break;

    case Robot::ANGRY:

      break;
    
    case Robot::DEEP_SLEEP:

      break;


      


  }

  delay(200);
}

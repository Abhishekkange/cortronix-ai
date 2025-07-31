# 🤖 Cortronix - AI Desktop  Toy


![Cortrnonix](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEg8xj20sYuGYddVdUCq-SXgW5_u-KiQzqSFoJj_VONO2DoWlOY8VT6WlwSjDSJ9a6KdCro5FLHQwu4mS14PgbetdkaLGrCONxxhv8r6GkVeuv7zPmhJ27Wb9_671AgGl6sACEtF9JQXMqtEpHjR6ZVBtaja8HZBuzqhJApMONHgZxPh1-ppDKsWBoSfwHo/s320/ChatGPT%20Image%20Aug%201,%202025,%2001_08_22%20AM.png)

**Cortronix** is a smart, emotionally expressive desktop robot toy designed to interact with humans through sensors, sounds, and animations. It reacts to light, sound, and touch, simulating behaviors similar to a robotic pet or companion. Built with an ESP32, this robot features Wi-Fi, Bluetooth, animated eyes, and playful movements.

---

## 📌 Features

1. **Touch Interaction**
   - Head touch sensor (IR-based) triggers emotional reactions (like happy, curious).
   
2. **Ambient Light Detection**
   - LDR detects day or night; Cortronix goes to sleep in the dark.

3. **Sound Detection**
   - Uses sound sensor to detect claps or nearby sound. Turns to the side when noise is detected.

4. **Eye Animation**
   - OLED/LED display for eyes with animations: blink, look left/right, excited, sleepy.

5. **Vibration Feedback**
   - Small vibration motor provides haptic feedback on touch or reactions.

6. **Idle Behaviors**
   - When inactive, Cortronix blinks randomly, hums, or looks around occasionally.

7. **Voice & Sound Reactions**
   - Plays custom pet-like or robot-like sounds to simulate emotional states.

---

## 🧠 Robot Behavior (State Machine)

| State         | Trigger                                 | Action                                                           |
|---------------|------------------------------------------|------------------------------------------------------------------|
| Idle          | Default / no input                       | Occasional blink, random eye movement                            |
| Sleep         | Dark detected via LDR                    | Eyes closed, no animation or interaction                         |
| Wake Up       | Light detected                           | Wake up sound + eye opening animation                            |
| Touched       | IR sensor on head touched                | Eye sparkles, plays happy sound, short vibration                 |
| Listening     | Sound detected via microphone            | Eye looks toward sound direction, plays curious sound            |
| Blink         | Random interval                          | Quick blink animation                                            |
| Sad           | No interaction for long time             | Eyes downcast, plays low tone                                    |
| React Sound   | Sudden loud noise                        | Surprised eye + vibration + turns                                |

---

## 🧱 Design Architecture

### Hardware Components

| Component                | Description                             |
|--------------------------|-----------------------------------------|
| **ESP32 Dev Board**      | Main controller with Wi-Fi & Bluetooth |
| **LDR Sensor**           | Detects light/dark environment          |
| **IR Sensor (KY-033)**   | Detects head touch                      |
| **Sound Sensor (KY-038)**| Detects sound / claps                   |
| **OLED Display (SSD1306)**| For expressive eye animations         |
| **Vibration Motor**      | Tactile feedback for interaction        |
| **Li-ion Battery (3.7V 1000–2000mAh)** | Rechargeable power source |
| **Speaker (Optional)**   | For sound playback                      |
| **3D Printed Shell**     | Toy casing with face and body           |

---

### Software Architecture

- `main.ino`: Arduino sketch running on ESP32.
- `states.h`: Contains enum and logic for various states.
- `display.cpp`: Eye animation code using Adafruit SSD1306 library.
- `sound.cpp`: Tone/music generation and playback.
- `sensor.cpp`: Abstraction for IR, LDR, and sound sensors.
- `motor.cpp`: Control for vibration motor.

---

## 💻 Functional Flow

```mermaid
graph TD
    A[Start] --> B{Is it Dark?}
    B -- Yes --> C[Go to Sleep]
    B -- No --> D[Idle State]
    D --> E{Touch Detected?}
    E -- Yes --> F[React Happy]
    E -- No --> G{Sound Detected?}
    G -- Yes --> H[Look + Curious Sound]
    G -- No --> I{Idle Time > 30s?}
    I -- Yes --> J[Act Sad]
    I -- No --> D
    F --> D
    H --> D
    J --> D

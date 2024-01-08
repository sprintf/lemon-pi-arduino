int motor1Down = 12;
int motor1Up = 13;

int ACTION_TIME = 2000;


void setup() {
  Serial.begin(115200);
  pinMode(motor1Down, OUTPUT);
  pinMode(motor1Up, OUTPUT);
 // important that this text appears exactly as the first thing emitted, as Lemon-Pi
 // uses this text string to determine the presence of an Arduino
  Serial.print("setup complete\n");
}

boolean down = false;
unsigned long action_end_time = 0;
int action_pin = 0;

void loop() {
  // put your main code here, to run repeatedly:
   // Serial.print("looping\n");
  if (Serial.available() > 0) {
    String x = Serial.readStringUntil('\n');
    Serial.print("received '" + x + "' on input\n");
    if (x == "help") {
      Serial.print("you are on your own\n");
    } else if (x == "down") {
      if (!down) {
        Serial.print("going down\n");
        fire_motor(motor1Down, ACTION_TIME);
        down = true;
      } else {
        Serial.print("already down\n");
      }
    } else if (x == "up") {
      if (down) {
        Serial.print("going back up\n");
        fire_motor(motor1Up, ACTION_TIME);
        down = false;
      } else {
        Serial.print("already up\n");
      }
    } else {
      Serial.print("dunno that command\n");
    }
  }

  // detect when the end of an action is complete and set the pin low
  if (action_end_time > 0L && millis() > action_end_time) {
    digitalWrite(action_pin, LOW);
    action_end_time = 0L;
    action_pin = 0;
    Serial.print("action complete\n");
  }
}

void fire_motor(int targetPin, int duration) {
    // if we are in the middle of an action then stop it
    if (action_pin > 0 && action_end_time > millis()) {
      Serial.print("interrupted action\n");
      digitalWrite(action_pin, LOW);
    }
    digitalWrite(targetPin, HIGH);
    action_pin = targetPin;
    action_end_time = millis() + (unsigned long)duration;
}


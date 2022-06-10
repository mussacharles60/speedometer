const int IN_D0 = D5;
const int BUTTON = D6;

int pulse = 0;
int pulseChange = 0;
double counter = 0.0;
boolean should_send = false;

unsigned long current_time;
unsigned long btn_click_time;

String data = "";

void setup() {
  Serial.begin(9600);
  pinMode(IN_D0, INPUT);
  pinMode(D6, INPUT_PULLUP);
}

void loop() {
  while (Serial.available() > 0) {
   char c = Serial.read();
   data += c;
   delay(10);
  }

  if (data.length() > 0) {
    // Serial.println(data);
    if (data.indexOf("start") >= 0) {
      should_send = true;
    } else if (data.indexOf("stop") >= 0) {
      counter = 0.0;
      should_send = false;
    }
    data = "";
  }
  
  if (should_send) {
    pulse = digitalRead(IN_D0);
    if (pulse != pulseChange) {
      counter = counter + 1;
      pulseChange = pulse;
    }
    else {
      pulseChange = pulse;
    }
    Serial.println(counter);
  } else {
    counter = 0.0;
  }
}
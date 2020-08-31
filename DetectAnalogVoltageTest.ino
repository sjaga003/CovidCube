// This file is a unit test to check that we are able to detect 5 different voltage levels from 0V-5V

//----- INPUTS -----
// Hook up a potentionmeter whose output is connected to pin A5
// Hook up 5 LEDs in pins 9-13
// Change voltage ranges as needed below

//----- EXPECTED OUTPUT -----
// LEDs will light up one at a time based on the voltage ranges for detection

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);

  if (voltage >= 0.0 && voltage <= 1.0){
    digitalWrite(9, HIGH);
  }
  else if (voltage > 1.0 && voltage <= 2.0){
    digitalWrite(10, HIGH);
  }
  else if (voltage > 2.0 && voltage <= 3.0){
    digitalWrite(11, HIGH);
  }
  else if (voltage > 3.0 && voltage <= 4.0){
    digitalWrite(12, HIGH);
  }
  else if (voltage > 4.0 && voltage <= 5.0){
    digitalWrite(13, HIGH);
  }
  
  Serial.println(voltage);
}

int WireMatchCount;
int EndSignal;

void setup() {
  WireMatchCount = 0;
  EndSignal = 0;
  Serial.begin(2);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);

  float aVoltage_1 = analogRead(A1) * (5 / 1023.0);
  float aVoltage_2 = analogRead(A2) * (5 / 1023.0);
  float aVoltage_3 = analogRead(A3) * (5 / 1023.0);
  float aVoltage_4 = analogRead(A4) * (5 / 1023.0);
  float aVoltage_5 = analogRead(A5) * (5 / 1023.0);

  float flag = 420.00;
  float flag2 = 0.00;

  if (aVoltage_1 >= 0.01 && aVoltage_1 < 1.00){
    ++WireMatchCount;
    digitalWrite(6, HIGH);
  }
  if (aVoltage_2 >= 1.00 && aVoltage_2 < 2.00){
    ++WireMatchCount;
    digitalWrite(7, HIGH);
  }
  if (aVoltage_3 >= 2.00 && aVoltage_3 < 3.00){
    ++WireMatchCount;
    digitalWrite(8, HIGH);
  }
  if (aVoltage_4 >= 3.00 && aVoltage_4 < 4.00){
    ++WireMatchCount;
    digitalWrite(9, HIGH);
  }
  if (aVoltage_5 >= 4.00 && aVoltage_5 <= 5.00){
    ++WireMatchCount;
    digitalWrite(10, HIGH);
  }

  if (WireMatchCount == 5){
    EndSignal = 1;
    Serial.println(flag);
    WireMatchCount = 0;
  }
  else if (WireMatchCount < 5){
    WireMatchCount = 0;
    Serial.println(flag2);
  }
}

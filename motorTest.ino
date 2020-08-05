int motorPin = 12;
int motorIn = 11;
const int puzLength = 6;
int pattern[puzLength];
int correctLen = 0;
int curpatterncorrect = 0;
int puzzleOn = 0;
int state = 0;


void setup() {
  Serial.begin(9600);
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  pinMode(motorPin, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  for(int i =0; i<puzLength;i++){
    pattern[i] = int(random(0,4));
    Serial.print(pattern[i]); 
  }
  Serial.print(" original pattern\n");
    for(int i =0; i<puzLength;i++){
    Serial.print(4-pattern[i]); 
  }
  Serial.print(" solution pattern\n");
}

void loop() {
  
  // put your main code here, to run repeatedly:
  if(puzzleOn == 2){
    switch(state){
    case 0:
      for(int i =0; i<=correctLen; i++){
        digitalWrite(pattern[i], HIGH);
        delay(1500);
        digitalWrite(pattern[i], LOW);
      }
      state = 1;
    break;

    case 1:
      //if()
    break;
    //need to get input without delay
  }
  }
  else{
    if(digitalRead(13) == HIGH){
      digitalWrite(motorPin, HIGH);
      delay(1000);
      digitalWrite(motorPin,LOW);
      puzzleOn ++;
    }
  }
}

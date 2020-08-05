int motorPin = 12;
int motorIn = 11;
const int puzLength = 6;
int pattern[puzLength];
int solution[puzLength];
int correctLen = 0;
int correct = 0;
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
  for(int i =0; i<puzLength;i++){//creating puzzle and solution
    pattern[i] = int(random(0,4));
    Serial.print(pattern[i]); 
    solution[i] = 4-pattern[i]+5;
  }
}

void loop() {
  if(puzzleOn == 2){ // if we have used the motor twice we will start puzzle 3
    switch(state){
    case 0:
      for(int i =0; i<=correctLen; i++){//turning on the lights in sequence 
        digitalWrite(pattern[i], HIGH);
        delay(1500);
        digitalWrite(pattern[i], LOW);
      }
      state = 1;
    break;
    
    case 1:
      if(digitalRead(solution[correct]){
        correct++;
        delay(100);
      }
      else if(checkOtherInputs(solution[correct]){
        state = 0;
        delay(500);
      }
      if(correct == correctLen){
        correct =0;
        if(correctLen >= puzLength){
          state = 11;
        }
        else {
          correctLen ++;
          state =0;
        }
      }
    break;
    default: 
    break;
  }
  }
  else{
    if(digitalRead(13)){
      digitalWrite(motorPin, HIGH);
      delay(1000);
      digitalWrite(motorPin,LOW);
      puzzleOn ++;
    }
  }
}

int checkOtherInputs(int except){
  for(int i=0; i < 4; i++){
    if(digitalRead(i) && i != solution[except){
      return 1;
    }
  }
  return 0;
}

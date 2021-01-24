int motorPin = 13;
int motorIn = 7;
const int puzLength = 5;
int pattern[puzLength];
int solution[puzLength];
int correctLen = 1;
int correct = 0;
int puzzleOn = 1;
int state = 0;
int count =0;



void setup() {
  Serial.begin(9600);
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  pinMode(motorPin, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(13, OUTPUT);
  for(int i =0; i<puzLength;i++){//creating puzzle and solution
    pattern[i] = int(random(2,6));
    solution[i] = 14-pattern[i];
    Serial.print(solution[i]);
  }
  Serial.print("\n");
        digitalWrite(13,HIGH);
      delay(300);
      Serial.print(digitalRead(13));
      digitalWrite(13,LOW);
}

void loop() {

  if(puzzleOn == 1){ // if we have used the motor twice we will start puzzle 3
    switch(state){
    case 0:
      for(int i =0; i<correctLen; i++){//turning on the lights in sequence 
        digitalWrite(pattern[i], HIGH);
        delay(1000);
        digitalWrite(pattern[i], LOW);
        Serial.print(solution[i]);
        delay(500);
      }
      Serial.print("\n");
      state = 1;
    break;
    
    case 1:
      if(checkOtherInputs(solution[correct])){
        state = 0;
        delay(200);
      }
      else if(digitalRead(solution[correct])){
        Serial.print(solution[correct]);
        correct++;
        digitalWrite(solution[correct], LOW);
        delay(200);
      }
      if(correct == correctLen){
        correct =0;
        if(correctLen >= puzLength){
          state = 10;
          Serial.print("done");
          
        }
        else {
          correctLen++;
          state =0;
        }
      }
    break;

    case 10:
    count++;
    for(int i =2; i<7; i++){
      digitalWrite(i, HIGH);
     }
     delay(1000);
    for(int i =2; i<7; i++){
      digitalWrite(i, LOW);
    }
    delay(1000);
    if(count == 4){
      state=0;
      puzzleOn++;
      digitalWrite(13,HIGH);
      delay(300);
      digitalWrite(13,LOW);
    }
    break;
    default: 
    break;
  }
  }
  else{
    if(digitalRead(7)){
      puzzleOn = 1;
    }
  }
}

int checkOtherInputs(int except){
  for(int i=8; i < 13; i++){
    if(digitalRead(i) == 1 && i != except){
      //Serial.print("bad input ");
      delay(1000);
      Serial.print("(");
      Serial.print(i);
      Serial.print(" != ");
      Serial.print(except);
      Serial.print(")\n");
      
      return 1;
    }
  }
  return 0;
}

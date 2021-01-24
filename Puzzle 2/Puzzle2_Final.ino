#include <LiquidCrystal.h>

char *RNA_Sequences[] = {
  "AAUCU",  // This one is the correct one. I think.
  "AUCAU",
  "UACUC",
  "CUCAU",
  "UCAUC"
};

char *DNA_Sequences[] = {
  "AGATT",  // This one is the correct one. Promise :3
  "TAGTG",
  "ATGTG",
  "GAGTA",
  "AGTAG"
};

char *Messages[] = {
  "Not Quite...    ",
  "Close! Or is it?",
  "Nice Try        ",
  "Try Again       ",
  "Hmmm...         ",
  "Coughs in Covid ",
  "Need a Hint?    ",
  "not WHO approved",
  "Bailey not a fan",
  "\"Inconclusive\"  ",
  "404: No Vaccine "
};

int i_RNA = 0;
int i_DNA = 0;
int i_Message = 0;  //Apple inc. has entered the chat 0_0

enum Puzzle_State {WaitStart, SequenceMatching, WireMatching, EndPuzzle, EndForever} puzzle;
enum SeqM_States {InitialSM, Wait_Input, Update_Left, Update_Right, Check, EndSM} SeqM_state;
enum WireM_States {InitialWM, Matching, EndWM} WireM_state;

int WireMatchCount;

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Waiting To Start");
  puzzle = WaitStart;
  SeqM_state = InitialSM;
  WireM_state = InitialWM;
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  WireMatchCount = 0;
}

void SequenceSM(){
  switch(SeqM_state) {
    case InitialSM:
      lcd.clear();
      lcd.print("L:");
      
      lcd.setCursor(2,0);
      lcd.print(RNA_Sequences[0]);
      
      lcd.setCursor(9,0);
      lcd.print("R:");
      
      lcd.setCursor(11,0);
      lcd.print(DNA_Sequences[0]);

      lcd.setCursor(0,1);
      lcd.print("Press to Verify");

      SeqM_state = Wait_Input;
      break;
     
     case Wait_Input:
      if (digitalRead(5) == HIGH){
        SeqM_state = Update_Left;
        break;
      }
      else if (digitalRead(6) == HIGH){
        SeqM_state = Update_Right;
        break;
      }
      else if (digitalRead(7) == HIGH){
        SeqM_state = Check;
        break;
      }
      else {
        SeqM_state = Wait_Input;
        break;
      }
      break;

     case Update_Left:
      break;

     case Update_Right:
      SeqM_state = Update_Right;
      break;

     case Check:
      break;

     case EndSM:
      lcd.clear();
      lcd.print("Congratulations!");
      delay(2000);

      lcd.clear();
      lcd.print("Moving On...    ");
      delay(2000);

      SeqM_state = InitialSM;
      puzzle = WireMatching;
      break;
     
     default:
      SeqM_state = Wait_Input;
      break;
  }

  switch(SeqM_state) {
    case InitialWM:
     SeqM_state = Wait_Input;
     break;
    
    case Wait_Input:
     break;

    case Update_Left:
      if (digitalRead(5) == HIGH){
        SeqM_state = Update_Left;
        break;
      }
      else if (digitalRead(5) == LOW){
        lcd.setCursor(2,0);
        if (i_RNA < 4){
          ++i_RNA;
        }
        else if (i_RNA == 4){
          i_RNA = 0;
        }
        lcd.print(RNA_Sequences[i_RNA]);
        SeqM_state = Wait_Input;
        break;
      }
      break;

    case Update_Right:
      if (digitalRead(6) == HIGH){
        SeqM_state = Update_Right;
        break;
      }
      else if (digitalRead(6) == LOW){
        lcd.setCursor(11,0);
        if (i_DNA < 4){
          ++i_DNA;
        }
        else if (i_DNA == 4){
          i_DNA = 0;
        }
        lcd.print(DNA_Sequences[i_DNA]);
        SeqM_state = Wait_Input;
        break;
      }
      break;

    case Check:
      if (digitalRead(7) == HIGH){
        SeqM_state = Check;
        break;
      }
      else if (digitalRead(7) == LOW){
        if (i_RNA == 0 && i_DNA == 0){
          SeqM_state = EndSM;
          break;
        }
        else if (i_RNA != 0 || i_DNA !=0){
          lcd.setCursor(0,1);
          lcd.print(Messages[i_Message++]);
          i_Message %= 11;
          SeqM_state = Wait_Input;
          break;
        }
      }
      break;

     case EndSM:
      break;
    
    default:
     SeqM_state = Wait_Input;
     break;
  }
}

void WireMatchingSM(){
  switch(WireM_state){
    case InitialWM:
      lcd.clear();
      lcd.print("Begin Wiring!");
      delay(2000);

      lcd.clear();
      lcd.print("Matches:0 of 5 ");
      break;
    case Matching:
      float aVoltage_5 = analogRead(A1) * (5 / 1023.0);
      float aVoltage_4 = analogRead(A2) * (5 / 1023.0);
      float aVoltage_3 = analogRead(A3) * (5 / 1023.0);
      float aVoltage_2 = analogRead(A4) * (5 / 1023.0);
      float aVoltage_1 = analogRead(A5) * (5 / 1023.0);
      float aTester_0 = analogRead(A0) * (5 / 1023.0);

      if (aVoltage_1 >= 0.5 && aVoltage_1 < 1.00){
        ++WireMatchCount;
      }
      if (aVoltage_2 >= 1.00 && aVoltage_2 < 2.00){
        ++WireMatchCount;
      }
      if (aVoltage_3 >= 2.00 && aVoltage_3 < 3.00){
        ++WireMatchCount;
      }
      if (aVoltage_4 >= 3.00 && aVoltage_4 < 4.00){
        ++WireMatchCount;
      }
      if (aVoltage_5 >= 4.00 && aVoltage_5 <= 5.00){
        ++WireMatchCount;
      }
      //Serial.println(aTester_0);
      break;

    case EndWM:
      break;
  }

  switch(WireM_state){
    case InitialWM:
      WireM_state = Matching;
      break;
    case Matching:
      if (WireMatchCount == 5){
        WireM_state = EndWM;
        break;
      }
      else if (WireMatchCount < 5){
        lcd.setCursor(8,0);
        lcd.print(WireMatchCount);
        WireMatchCount = 0;
        WireM_state = Matching;
        break;
      }
      break;
    case EndWM:
      lcd.clear();
      lcd.print("Done!");
      puzzle = EndPuzzle;
      break;
  }
}

void EndPuzzleSM(){
  lcd.print("Still here?");
  lcd.setCursor(16, 2);
  digitalWrite(3, HIGH);
  delay(200);
  digitalWrite(3, LOW);
  delay(2000);
  puzzle = EndForever;
}

void loop() {
  switch(puzzle){
    case WaitStart:
      if (digitalRead(4) == HIGH){
        puzzle = SequenceMatching;
        break;
      }
      else {
        puzzle = WaitStart;
        break;
      }
    case SequenceMatching:
      SequenceSM();
      break;
    case WireMatching:
      WireMatchingSM();
      break;
     case EndPuzzle:
      EndPuzzleSM();
      break;
     case EndForever:
      break;
  }
}

/*  Wanita dhijen test n 2 7seg ik 2 ShiftReg 
 *  Itatafd nomro zi Serial inatarith dhi digits wis 1
 *  Itatafd nomro wis 2 inatarith dhi seg wis 1 
 *  theni togha dhi wis 1 ghawmazwa dakwar dhi wis 2
 *  gijen moda n 3s
 */
#define DataPin 13
#define LatchPin 12
#define ClockPin 7
#define Output 6


/* anekhdhem s LSBFIRST                                    ___
 11001101 LSB ->    1  1  0  0  1  1  0  1                | a |b
  remember that we have Qa Qb Qc Qd Qe Qf Qg Qh          f|___|
 kifkif ik Seg                                            | g |c
 ghanagh                                                 e|___|
                                                            d
*/

byte Digits[] = { 0b00000011,
                  0b10011111,
                  0b00100101,
                  0b00001101,
                  0b10011001,
                  0b01001001,
                  0b01000001,
                  0b00011111,
                  0b00000001,
                  0b00001001
                };
int D1 = 0;
int D2 = 0;
unsigned long Start, Old;
int count = 0;
void setup() {
  pinMode(DataPin, OUTPUT);
  pinMode(LatchPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  pinMode(Output, OUTPUT);
  digitalWrite(Output, LOW); //desactivate Outputs
  Serial.begin(9600);
  Standby();
  Old = 0;



}


void loop() {



  Start = millis();
  if ( Start - Old >= 3000)Standby();
  if (Serial.available()) {
    Serial.setTimeout(10);
    int test = Serial.parseInt();
    //   for (unsigned long rekho = Start; rekho - Start <= 2000; rekho = millis()){


    if (count < 2) {
      if (test <= 9 ) {
        Serial.println("Ok!");
        D1 = D2 ;
        D2 = test;
        Start = millis();
        PrintDig(D1, D2);
        //         count++;

      }
      else
        Serial.println("It's Not A valid number! ");


    }
  }
}


void PrintDig(int d1 , int d2) {
  digitalWrite(LatchPin, LOW);
  shiftOut(DataPin, ClockPin, LSBFIRST, Digits[d1]);
  shiftOut(DataPin, ClockPin, LSBFIRST, Digits[d2]);
  digitalWrite(LatchPin, HIGH);
  // digitalWrite(Output,LOW);
  Old = Start;
  count++;
}

void Standby() {
  digitalWrite(LatchPin, LOW);
  shiftOut(DataPin, ClockPin, LSBFIRST, 0b11111101);
  shiftOut(DataPin, ClockPin, LSBFIRST, 0b11111101);
  digitalWrite(LatchPin, HIGH);
  D1 = 0;
  D2 = 0;
  count = 0;
}

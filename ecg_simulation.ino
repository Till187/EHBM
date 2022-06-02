#include <LiquidCrystal.h> 


const int RS = 12, E = 11, D4 = 5, D5 = 4, D6 = 7, D7 = 6;
const int analogInPin = A3;
int sensorValue = 0;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
int threshold = 775;
double TimeArray[2] = {};
const int BPMARRAYLEN = 10;
double BPMArray[10] = {};
double SumBPM = 0;
double BPMAvg = 0;
double Deltat = 0;
double temp = 0;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); 
  pinMode(LED_BUILTIN, OUTPUT);
  TimeArray[0] = 0;
}

void loop() {
  
sensorValue = analogRead(analogInPin);
lcd.setCursor(0,0);
lcd.clear();
// Serial.print(sensorValue);
//Serial.println();
digitalWrite(LED_BUILTIN, LOW); 


// turn the LED off by making the voltage LOW
if (sensorValue > threshold){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  
  if (TimeArray[0] == 0){
  TimeArray[1] = millis();
  TimeArray[0] = TimeArray[1];
  }

  else {
  digitalWrite(LED_BUILTIN, HIGH);
  TimeArray[1] = TimeArray[0];
  TimeArray[0] = millis();
  delay(20);

Serial.println(TimeArray[0]);
Serial.println(TimeArray[1]);
Serial.print(TimeArray[0]-TimeArray[1]); 
Deltat = TimeArray[0]-TimeArray[1];
temp = 60000/Deltat; /////////////////////////////////////////////// IF YOU WRITE 60*1000 ON THE DENOMINATOR IT DOES NOT WORK
Serial.println((1000/Deltat)*60);

    for (int i= 0;i<BPMARRAYLEN-1;i++){
     BPMArray[BPMARRAYLEN-i-1] = BPMArray[BPMARRAYLEN-i-2];
  }
  Deltat = TimeArray[0]-TimeArray[1];
  BPMArray[0] = 60*1000/(Deltat);
 /* 
 Serial.println(BPMArray[0]);
 Serial.println(BPMArray[1]);
 Serial.println();
*/
 
  }
}



  for (int i= 0;i<BPMARRAYLEN;i++){
  SumBPM = SumBPM + BPMArray[i];
  }
  BPMAvg = SumBPM/BPMARRAYLEN;
  //Serial.print(BPMAvg);
}

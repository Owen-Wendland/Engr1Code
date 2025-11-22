//Include lcd screen
#include <LiquidCrystal.h>

// Sensor pins
#define waterPower 7
#define waterPin A1

//define lcd pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buzzer = 8; //buzzer to arduino pin 8
const String notes[] = {"c", "c#", "d", "d#", "e", "f", "f#", "g","g#", "a", "a#", "b"};

//lcd contrast pin
const int contrast = 13; 

// Value for storing water level
int waterLevel = 0;

int timer = 0;

void setup() {
  analogWrite(contrast, 130); 
  //setup size of lcd
  lcd.begin(16, 2);

  // Set D7 as an OUTPUT
  pinMode(waterPower, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Set to LOW so no power flows through the sensor
  digitalWrite(waterPower, LOW);

  lcd.clear();
  Serial.println("\n\n\n\n\n\n\n");
  Serial.begin(9600);
}

void loop() {
  //get the reading from the function below and print it
  int waterLevel = readSensor();

  //Serial.print("Water level: ");
  //Serial.println((String)waterLevel + "%");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print((waterLevel));
  lcd.setCursor(0, 1);
  Serial.println(timer);
  if(waterLevel >= 70){
    lcd.print("Watered");
  }
  else if(waterLevel >= 40){
    lcd.print("Moist");
  }
  else if(waterLevel >= 10){
    lcd.print("drying");
    
  }
  else{
    lcd.print("dry");
    if(timer<60){
      timer++;
    }
    else if(timer>=60){
      timer = 0;
      littleLamb();
    }
    lcd.setCursor(14, 1);
    lcd.print((timer));
  }
  //lcd.setCursor(2, 0);
  //lcd.print(noteToHz("C", 4));
  //-----------------------DELAY IS HERE------------
  delay(1000);
  //reset lcd
  lcd.setCursor(0, 0);
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(waterPower, HIGH);  // Turn the sensor ON
  delay(1000);                        // wait 10 milliseconds
  int val = analogRead(waterPin);      // Read the analog value form sensor
  //val = (((0.58)*val)/(157.66 - val));
  //int outt = int(val)*10;
  int outt = analogRead(waterPin); 
  digitalWrite(waterPower, LOW);   // Turn the sensor OFF

  //if(outt > 100){
    //outt = 100;
  //}
  //else if(outt < 0){
    //outt = 0;
  //}

  //outt = (50.16703 * log(outt)) + 49.68079;
  outt = pow(10, (outt-49.68079)/50.16703);

  return outt;                       // send current reading
}

double noteToHz(String note, int octave){
  int noteID = 0;
  note.toLowerCase();
  for (int i=0; i<12; i++) {
    if (note == notes[i]) {
      noteID = i+1;
      break;
    }
  } 
  double x = noteID + (octave * 12);
  
  double hz = 15.43422 * pow(2, x/12);
  return hz;
}

void littleLamb(){
  tone(buzzer, noteToHz("e", 4));
  delay(100);
  noTone(buzzer);
  delay(100);
  tone(buzzer, noteToHz("d", 4));
  delay(100);
  noTone(buzzer);
  delay(100);
  tone(buzzer, noteToHz("c", 4));
  delay(100);
  noTone(buzzer);
  delay(100);
  tone(buzzer, noteToHz("d", 4));
  delay(100);
  noTone(buzzer);
  delay(100);
  tone(buzzer, noteToHz("e", 4));
  delay(100);
  noTone(buzzer);
  delay(100);
  tone(buzzer, noteToHz("e", 4));
  delay(100);
  noTone(buzzer);
  delay(100);
  tone(buzzer, noteToHz("e", 4));
  delay(200);
  noTone(buzzer);
  delay(100);
}
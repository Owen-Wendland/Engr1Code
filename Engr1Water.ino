//Include lcd screen
#include <LiquidCrystal.h>

// Sensor pins
#define waterPower 7
#define waterPin A0

//define lcd pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Value for storing water level
int waterLevel = 0;

void setup() {
  //setup size of lcd
  lcd.begin(16, 2);

  // Set D7 as an OUTPUT
  pinMode(waterPower, OUTPUT);

  // Set to LOW so no power flows through the sensor
  digitalWrite(waterPower, LOW);

  lcd.clear();
  Serial.begin(9600);
}

void loop() {
  //get the reading from the function below and print it
  int waterLevel = readSensor();

  Serial.print("Water level: ");
  Serial.println((String)waterLevel + "%");
  lcd.print(waterLevel);

  //-----------------------DELAY IS HERE------------
  delay(1000);

  //reset lcd
  lcd.clear();
  lcd.setCursor(0, 1);
}

//This is a function used to get the reading
int readSensor() {
  int out;
  digitalWrite(waterPower, HIGH);  // Turn the sensor ON
  delay(1000);                        // wait 10 milliseconds
  int val = analogRead(waterPin);      // Read the analog value form sensor
  Serial.print("Water level: ");
  Serial.println(val);
  val = (((0.58)*val)/(157.66 - val));
  int outt = int(val)*10;
  digitalWrite(waterPower, LOW);   // Turn the sensor OFF

  if(outt > 100){
    outt = 100;
  }
  else if(outt < 0){
    outt = 0;
  }

  return outt;                       // send current reading
}
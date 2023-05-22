#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

/// Define Pins ///
/*
 * define servoA_pin 2
 * define trigA_pin 3
 * define echoA_pin 4
 * define servoB_pin 5
 * define trigB_pin 6
 * define echoB_pin 7
 * define servoC_pin 8
 * define trigC_pin 9
 * define echoC_pin 10
 * define servoD_pin 11
 * define trigD_pin 12
 * define echoD_pin 13
 * A button for Type 1 Waste
 * B button for Type 2 Waste
 * C button for Type 3 Waste
 * D button for Type 4 Waste
 * * button for reset value
 */
 
/// Counter for times open of each waste ///
int a_count = 0;
int b_count = 0;
int c_count = 0;
int d_count = 0;

/// Setting Value for open each type bin ///
int a_set = 0;
int b_set = 0;
int c_set = 0;
int d_set = 0;

/// Keypad ///
byte colPins[4] = {33,32,31,30};
byte rowPins[4] = {34,35,36,37};

char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

/// Servo ///
int duration, distance;
Servo servoA;
int const trigAPin = 3;
int const echoAPin = 4;
Servo servoB;
int const trigBPin = 6;
int const echoBPin = 7;
Servo servoC;
int const trigCPin = 9;
int const echoCPin = 10;
Servo servoD;
int const trigDPin = 12;
int const echoDPin = 13;

/// LCD ///
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting");

  // Servo //
  pinMode(trigAPin, OUTPUT); 
  pinMode(echoAPin, INPUT);     
  servoA.attach(2);
  pinMode(trigBPin, OUTPUT); 
  pinMode(echoBPin, INPUT);     
  servoB.attach(5);
  pinMode(trigCPin, OUTPUT); 
  pinMode(echoCPin, INPUT);     
  servoC.attach(8);
  pinMode(trigDPin, OUTPUT); 
  pinMode(echoDPin, INPUT);     
  servoD.attach(11);

  // LCD Boot //
  lcd.init();
  lcd.backlight();

  // Welcome Text ///
  lcd.setCursor(0,0);
  lcd.print("Smart Bin");
  lcd.setCursor(0,1);
  lcd.print("Select Type:");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A-TypeA  B-TypeB");
  lcd.setCursor(0,1);
  lcd.print("C-TypeC  D-TypeD");
}

void loop()
{
  // Keypad Input //
  char key = keypad.getKey();
  if (key != NO_KEY) {
  }
  // Test Key A - General //
  if (key == 'A') {
    a_count += 1;
    a_set = 1;
    b_set = 0;
    c_set = 0;
    d_set = 0;
    Serial.print("Counter Waste Type A:");
    Serial.println(a_count);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("A-General");
    lcd.setCursor(0,1);
    lcd.print("Type A: ");
    lcd.setCursor(8,1);
    lcd.print(a_count);
  }
  if (key == 'B') {
    b_count += 1;
    a_set = 0;
    b_set = 1;
    c_set = 0;
    d_set = 0;
    Serial.print("Counter Waste Type B:");
    Serial.println(b_count);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("B-Recycle");
    lcd.setCursor(0,1);
    lcd.print("Type B: ");
    lcd.setCursor(8,1);
    lcd.print(b_count);
  }
  if (key == 'C') {
    c_count += 1;
    a_set = 0;
    b_set = 0;
    c_set = 1;
    d_set = 0;
    Serial.print("Counter Waste Type C:");
    Serial.println(c_count);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("C-Infection");
    lcd.setCursor(0,1);
    lcd.print("Type C: ");
    lcd.setCursor(8,1);
    lcd.print(c_count);
  }
  if (key == 'D') {
    d_count += 1;
    a_set = 0;
    b_set = 0;
    c_set = 0;
    d_set = 1;
    Serial.print("Counter Waste Type D:");
    Serial.println(d_count);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("D-Hazardous");
    lcd.setCursor(0,1);
    lcd.print("Type D: ");
    lcd.setCursor(8,1);
    lcd.print(d_count);
  }
  if (key == '*') {
    a_count = 0;
    b_count = 0;
    c_count = 0;
    d_count = 0;
    a_set = 0;
    b_set = 0;
    c_set = 0;
    d_set = 0;
    Serial.println("Reset Counter");
    Serial.print("Counter Waste Type A:");
    Serial.println(a_count);
    Serial.print("Counter Waste Type B:");
    Serial.println(b_count);
    Serial.print("Counter Waste Type C:");
    Serial.println(c_count);
    Serial.print("Counter Waste Type D:");
    Serial.println(d_count);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Reset Counter");
  }

  /*
  //// Servo ///
  float duration,distance;
  digitalWrite(trig_pin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig_pin,LOW);
  distance = (duration/2)/29;
  Serial.print(distance);
  Serial.println(" cm");
  time = time + inter_time;
  delay(inter_time);
  if (distance < 10) {
    for (int i = 1500; i >= 1100 ; i -= 25) {
      myservo.writeMicroseconds(i);
      Serial.printlm("2");
      delay(100);
    }
    delay(1000);
    for (int i = 1100; i <= 1500; i += 25) {
      myservo.writeMicroseconds(i);
      Serial.printlm("1");
      delay(100);
    }
  }
  */

  /// Setting open each bin ///
  if(a_set == 1) {
    digitalWrite(trigBPin, LOW); 
    digitalWrite(trigCPin, LOW); 
    digitalWrite(trigDPin, LOW); 
    
    digitalWrite(trigAPin, HIGH); 
    //delay(500);
    digitalWrite(trigAPin, LOW);// Measure the pulse input in echo pin
    duration = pulseIn(echoAPin, HIGH);// Distance is half the duration devided by 29.1 (from datasheet)
    distance = (duration/2) / 29.1;// if distance less than 0.5 meter and more than 0 (0 or less means over range) 
    if (distance <= 10) {  
      servoA.write(50);    
      delay(500);
    } 
    else {   
      servoA.write(160);
    }
  }
  if(b_set == 1) {
    digitalWrite(trigAPin, LOW); 
    digitalWrite(trigCPin, LOW); 
    digitalWrite(trigDPin, LOW);
    
    /*
    digitalWrite(trigBPin, HIGH); 
    //delay(500);
    digitalWrite(trigBPin, LOW);// Measure the pulse input in echo pin
    duration = pulseIn(echoPin, HIGH);// Distance is half the duration devided by 29.1 (from datasheet)
    distance = (duration/2) / 29.1;// if distance less than 0.5 meter and more than 0 (0 or less means over range) 
    if (distance <= 10) {  
      servoB.write(50);    
      delay(500);
    } 
    else {   
      servoB.write(160);
    }
    */
  }
  /*
  if(c_set == 1) {
    digitalWrite(trigAPin, LOW); 
    digitalWrite(trigBPin, LOW); 
    digitalWrite(trigDPin, LOW); 
  
    digitalWrite(trigCPin, HIGH); 
    //delay(500);
    digitalWrite(trigCPin, LOW);// Measure the pulse input in echo pin
    duration = pulseIn(echoPin, HIGH);// Distance is half the duration devided by 29.1 (from datasheet)
    distance = (duration/2) / 29.1;// if distance less than 0.5 meter and more than 0 (0 or less means over range) 
    if (distance <= 10) {  
      servoC.write(50);    
      delay(500);
    } 
    else {   
      servoC.write(160);
    }
  }
  if(d_set == 1) {
    digitalWrite(trigAPin, LOW); 
    digitalWrite(trigBPin, LOW); 
    digitalWrite(trigCPin, LOW); 
    
    digitalWrite(trigDPin, HIGH); 
    //delay(500);
    digitalWrite(trigDPin, LOW);// Measure the pulse input in echo pin
    duration = pulseIn(echoPin, HIGH);// Distance is half the duration devided by 29.1 (from datasheet)
    distance = (duration/2) / 29.1;// if distance less than 0.5 meter and more than 0 (0 or less means over range) 
    if (distance <= 10) {  
      servoD.write(50);    
      delay(500);
    } 
    else {   
      servoD.write(160);
    }
  }
  */
}

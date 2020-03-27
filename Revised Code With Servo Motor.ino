#include<LiquidCrystal.h>  //GLCD library
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //interfacing auduino datapins with graphic lcd

#define triggerPin 1  //setting TX for ultarsonic trigger
#define echoPin 0  //setting RX for ultrasonic echo
#define buzzer 8 //setting D12 for Piezo buzzer
#define led1 13
#define led2 12
#define led3 11

void setup()
{
  Serial.begin(9600);  //Setting baud rate for Serial communication
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, LOW);  //The ultrasonic trigger should be low at the beginning for accuracy
  lcd.begin(16, 2); //Setting up glcd. Values inside () are pixel sizes
  lcd.print("HELLO ARDUINO");
  delay(1000);
  lcd.clear();
}

void loop()
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(10);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  /*
     This will activate the trigger once to create a single wave which will reflect on the collision object.
    Adjust the delayMicroseconds according to wavelength of trigger used and range of collision detection. Range of delay:(2,10)
  */

  float timeO = pulseIn(echoPin, HIGH);  //Sensing the reflected wave

  float distance = 344 * timeO;
  /*
     speed=distance*time
     speed of trigger sound is about 344m/s at room temperature and my very with temperature
  */

  if (distance <= 500 && distance >= 300)
  {
    lcd.clear();  //clears any output on glcd
    lcd.setCursor(1, 1); //Sets cursor to print a statement on glcd to 1st column in the 1st row
    lcd.print("GO SLOW");
    lcd.setCursor(2, 1); //Sets cursor to print a statement on glcd to 1st column in the 2nd row
    lcd.println(distance);  //prints value of distance on glcd at selected location
    Serial.print("GO SLOW ");
    Serial.println(distance);  //prints distance on Serial Monitor
    digitalWrite(led1, HIGH);
    tone(buzzer, 1000);
    delay(300);
    noTone(buzzer);
    delay(300);
    tone(buzzer, 1000);  //this will synchronously tone the buzzer on and off
  }

  if (distance > 300 && distance <= 100)
  {
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("GO SLOW");
    lcd.setCursor(2, 1);
    lcd.println(distance);
    Serial.print("GO SLOW ");
    Serial.println(distance);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    tone(buzzer, 2000);
    delay(150);
    noTone(buzzer);
    delay(150);
    tone(buzzer, 2000);
  }

  if (distance > 100 && distance <= 10)
  {
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("GO SLOW");
    lcd.setCursor(2, 1);
    lcd.println(distance);
    Serial.print("STOP ");
    Serial.println(distance);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    tone(buzzer, 3000);  //continuous buzzing of buzzer
    /*You can add any code for reacting to this condition here*/
  }
}

#include <dht.h>
// include the library code:
#include <LiquidCrystal.h>


#include <Wire.h> 
#include <Servo.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define dht_apin A1 // Analog Pin sensor is connected to
 
dht DHT;

Servo myservo;
int pos = 0;
int sensorvalue;

 
void setup(){
 
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
  lcd.begin(16, 2);

  myservo.attach(9);
  myservo.write(pos);
  
  pinMode(13, OUTPUT); // Red
  pinMode(12, OUTPUT); // Green
 
}//end "setup()"
 
void loop(){
  //Start of Program 
    delay(1000);     

    DHT.read11(dht_apin);
    lcd.setCursor(0, 0);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    lcd.print("Hum : ");
    lcd.print(DHT.humidity);
    lcd.print("%");
    Serial.print("Current temperature = ");
    lcd.setCursor(0, 1);
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    lcd.print("Temp : ");
    lcd.print(DHT.temperature);
    lcd.print("C");


    sensorvalue=analogRead(A0);
    Serial.print("brightness level:");
    Serial.println(sensorvalue);
    delay(250);
    
    for (pos = 30; pos <= 150; pos += 1) { // goes from 0 degrees to 180 degrees
      //analogRead(A0);
        if(analogRead(A0) < 70)
        {
          digitalWrite(12, LOW);
          digitalWrite(13, HIGH);
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(20); // waits 20ms for the servo to reach the position
        }
        if(analogRead(A0) > 70)
        {
          digitalWrite(12, HIGH);
          digitalWrite(13, LOW);
          delay(100);  // waits 100ms for the servo to reach the position
        }
      }
      for (pos = 150; pos >= 30; pos -= 1) {
        // goes from 180 degrees to 0 degrees
        if(analogRead(A0) < 70)
        {
          digitalWrite(12, LOW);
          digitalWrite(13, HIGH);
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(20); 
        } 
        if(analogRead(A0) > 70)
        {
          digitalWrite(12, HIGH);
          digitalWrite(13, LOW); 
          delay(100);  // waits 100ms for the servo to reach the position 
        }
      }
    delay(600);
    //Fastest should be once every two seconds.
 
}// end loop

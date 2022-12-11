#include<Servo.h>
#include<MFRC522.h>

// rfid Pin
#define RST_PIN 5
#define SS_PIN 53

MFRC522 mfrc(SS_PIN, RST_PIN);
// servo motor
Servo myServo;
int servoPin = 9;

//PIR
int PIN_PIR = 8;

int button = 7; 
int LED = 2;
boolean buzzer = 0;
boolean tagging = 0;
int bus_speed = 0;


void setup() {
 Serial.begin(9600);
 SPI.begin(); // SPI 통신

 myServo.attach(servoPin);
 pinMode(button, INPUT_PULLUP);
 pinMode(LED, OUTPUT);
 pinMode(PIN_PIR, INPUT);
}

void loop() {
  int angle;
  // button
  while(buzzer == 0)
  {
    if(!digitalRead(7)) 
    {
      buzzer = 1;
      digitalWrite(LED, HIGH);
      Serial.println("Boozer on");
     }
   }

   // Tagging
   while(tagging == 0)
   {  

      if(!mfrc.PICC_IsNewCardPresent()||!mfrc.PICC_ReadCardSerial()) // 태그 접촉 여부 , ID 읽기 여부 false가 부정임
      {
        delay(500);
        return;
      }
      
      // tag가 정상적으로 찍혔다면
      if(mfrc.uid.uidByte[0] == 138 && mfrc.uid.uidByte[1] == 139 && mfrc.uid.uidByte[2] == 162 && mfrc.uid.uidByte[3] == 14)
      {
        tagging = 1;
        Serial.println("Tagging complete");
        
        }
    }

    // 출구 개방
    if (buzzer == 1 && tagging == 1 && bus_speed == 0)
    {
      Serial.println("Open door");

      myServo.write(100);
      delay(800);
      myServo.write(90);
      
    }

      // boozer 초기화
      digitalWrite(LED, LOW);

      // 5초 뒤
      delay(5000);

      while(digitalRead(8)) // 사람이 있으면 계속 열어둠
      {
        // 속도가 0 이상이면 문닫음
        if(bus_speed > 0)
        {
          Serial.println("Close door1");
          myServo.write(45);
          delay(3000);
          }
        delay(100);
      }
      
      // 출구 닫기
      if (!digitalRead(8) && tagging == 1 && buzzer == 1)
      {
          Serial.println("Close door");

          myServo.write(80);
          delay(800);
          myServo.write(90);
   
          //tagging 초기화
          tagging = 0;
          buzzer = 0;
        }
       
      
}

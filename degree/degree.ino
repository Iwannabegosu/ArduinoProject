int destination = -1;
int chairNumber = -1; // 몇 번 좌석인지

String bus[7] = {"부경대", "남천역", "금련산역", "광안역", "수영역", "수영역", "연제구청"}; // bus 객체
int bus_move = 0;


int var;

int msg;
int LED = 2;
int IsSeat=7; //3번 좌석에 앉아서 버튼을 누름
int seat[6]={8,9,10,11,12,13}; // 의자번호와 PIN 번호 매핑

int vibration = 3; // 진동모터

boolean state=0;
boolean Isarrived=false;
void setup() {
 Serial.begin(9600); // 시리얼 통신 초기화
 Serial3.begin(9600); // 블루투스 통 초기화
 pinMode(IsSeat,INPUT);
 pinMode(seat[8],OUTPUT);
 pinMode(LED, OUTPUT);
 pinMode(vibration, OUTPUT);
}
void loop() {
 Serial3.flush();
 state = digitalRead(IsSeat);
 while(state == 1)
 {
   digitalWrite(LED, HIGH);
   // 입력 받을꺼임
   if(Serial3.available())
   {
    msg = Serial3.read();
    if (var == 0)
      {
      destination = msg;
      var = 1;
      }
    else if(var == 1)
    {
      chairNumber = msg;
      var = 0;
      break;
      }
    }
 }



if(state == 1)
{
  Serial.print(destination);
  Serial.print(chairNumber);
  while(bus_move != destination)
  {
    bus_move += 1;
    delay(1000);
  }
}

// 목적지 도착시
if(bus_move == destination)
{
  destination -= 1;
  Serial.print(bus[destination]);
  Serial.print("에 도착했습니다.");

  // 진동
  chairNumber -= 1;
  for(int i = 0 ;i< 3;i++)
  { 
    Serial.println("진동"); 
    analogWrite(seat[chairNumber], 100);
     delay(1000);
     analogWrite(seat[chairNumber], 0);
     delay(1000);
  } 
  // 변수 초기화
  state = 0;
  bus_move = 0;
  destination = -1;
  chairNumber = -1;
  digitalWrite(LED, LOW);
}

 


}

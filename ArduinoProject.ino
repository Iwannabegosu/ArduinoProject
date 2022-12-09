int button = 7; 
int LED = 2;
boolean boozer = 0;

void setup() {
 Serial.begin(9600);
 pinMode(button, INPUT_PULLUP);
 pinMode(LED, OUTPUT);
}

void loop() {
  // button
  while(boozer == 0)
  {
    if(!digitalRead(7)) 
    {
      boozer = 1;
      digitalWrite(LED, HIGH);
      break; 
     }
   }

   // Tagging
   /*
   while(1)
   {
    
    }
    */
}

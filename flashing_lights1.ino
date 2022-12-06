int Led0 = 11 ;
int Led1 = 10;
int Led2 = 6;
int SW1 = 12;
int Led1State = 0;
int Led2State = 0;
unsigned long previousMillis = 0;
int PotVal ;
bool SwState ;
int brightness = 255; // brightness: duty cycle of Led0
int brightperc = 100; // set Led0 brightness = 100% (255 on analog scale)
unsigned long LedPeriod = 200 ;//bazoyme mia tixai periodo
//enalagis ton led1 led2 otan exoyme anikto diakopti
void setup()
{
  pinMode(Led0, OUTPUT);
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(SW1,INPUT);
  Serial.begin(9600); // Open serial port
}

void loop()
{
  PotVal= analogRead(A0) ; //diabasma timon toy diaireti tasis
  SwState= digitalRead(SW1);//diabasma tis katastasis toy diakopti
 // (5V/1024 = 4.88mV ,10-bit analog to digital converter, 2^10 = 1024)
 // Vout = [(Rx + R2)/(R1+Rx+R2)] * 5V
 // Rx = 0 -> min Vout = 0.454V
 // Rx = 22kΩ -> max Vout = 4.549V
 //min PotValue=93,max PotValue=931 afoy 0.454/0.00488 = 93 kai 4.549/0.00488=931
  Serial.println(SwState);//dixni tin katastasi tou switch
  
  if (SwState == 0){
    
  	brightness = map(PotVal, 93, 931, 51, 255);
    // Re-map to pot value sto duty cycle of Led0(Rmax ->255,R=0-> 51)afoy 20% toy 255 = 51
  	brightperc = map(PotVal, 93, 931,20,100);
   
    //Re-map pot value to brightperc of Led0(Rmax->100%,R=0->20%)
  	analogWrite(Led0, brightness); // Set duty cycle of Led0.
   
    Serial.print("brightness = "); Serial.print(brightperc); Serial.println("%");
    // Print brightness percentage of Led0 on Serial Monitor
    
    // check to see if it's time to change the state of the LEDs
  	unsigned long currentAMillis = millis();
 //litourgia (b)
    if((Led1State == HIGH) && (currentAMillis - previousMillis >= LedPeriod))
    {
      Led1State = LOW;  // Turn it off
      previousMillis = currentAMillis;  // Remember the time
      digitalWrite(Led1, Led1State); // Update the actual LED
      Led2State = HIGH;
      digitalWrite(Led2, Led2State);
    }
     else if ((Led1State == LOW) && (currentAMillis - previousMillis >= LedPeriod))
    {
      Led1State = HIGH;  // turn it on
      previousMillis = currentAMillis;  // Remember the time
      digitalWrite(Led1, Led1State); // Update the actual LED
      Led2State = LOW;
      digitalWrite(Led2, Led2State);
    }   
  }
  
  if (SwState == 1){
    brightness = 255;
    analogWrite(Led0,brightness);//led0 einai sinexia anikto litoyrgia (a)
    
  	LedPeriod = map(PotVal, 93, 931, 50, 150);
  //Re-Map a value from 93 to 931 to a value from 50 to 150	
  	
    // check to see if it's time to change the state of the LEDs
  unsigned long currentMillis = millis();
 
    if((Led1State == HIGH) && (currentMillis - previousMillis >= LedPeriod))
    {
      Led1State = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(Led1, Led1State); // Update the actual LED
      Led2State = HIGH;
      digitalWrite(Led2, Led2State);
    }
     else if ((Led1State == LOW) && (currentMillis - previousMillis >= LedPeriod))
    {
      Led1State = HIGH;  // turn it on
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(Led1, Led1State); // Update the actual LED
      Led2State = LOW;
      digitalWrite(Led2, Led2State);
    }
 }
}
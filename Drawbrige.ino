// Semaforo
int redLedPin = 3;
int greenLedPin = 5;
int blueLedPin = 6;

// Limit Switches
int limitSwitchOpenPin = 11;
int limitSwitchClosedPin = 10;

// Direction Switch
int CommandSwitchOpenPin = 8;
int CommandSwitchClosedPin = 12;

// Motor
int motorOpenPin = 7;
int motorClosedPin = 9;

// Bridge State
 const int up = 1;
 const int down = 2;
 const int moving = 3;
 const int unknown = 0;
int bridgeState = unknown ; 

// Switch State
 const int doOpen = 1;
 const int doClose = 2;
 const int idle = 0;
int switchState = idle;

// Action
 const int actOpen = 1;
 const int actClose = 2;
 const int actStop = 0;
int action = actStop;


void setup() {
  Serial.begin(115200);
    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(blueLedPin, OUTPUT);
    pinMode(4, OUTPUT);
    turnOff();
    pinMode(limitSwitchOpenPin, INPUT_PULLUP);
    pinMode(limitSwitchClosedPin, INPUT_PULLUP);
    pinMode(CommandSwitchOpenPin, INPUT_PULLUP);
    pinMode(CommandSwitchClosedPin, INPUT_PULLUP);
    pinMode(motorOpenPin, OUTPUT);
    digitalWrite(motorOpenPin, LOW);
    pinMode(motorClosedPin, OUTPUT);
    digitalWrite(motorClosedPin, LOW); 
    digitalWrite(4, HIGH);       
  Serial.println("started");
}

void loop() {

    Serial.println(" NEW DATA ");


    
    bridgeState = unknown;

    if (digitalRead(limitSwitchOpenPin) == LOW)
    {
     bridgeState = up;    
    }
    if (digitalRead(limitSwitchClosedPin) == LOW)
    {
      bridgeState = down;       
    }
  
    switchState = idle;
    if (digitalRead(CommandSwitchOpenPin) == LOW)
    {
      switchState = doOpen; 
    }
    if (digitalRead(CommandSwitchClosedPin) == LOW)
    {
      switchState = doClose;
    }

    action = actStop;
    switch (switchState)
    {
      case doOpen:
        action = actOpen;
        Serial.println("switch is doOpen");
        break;
      case doClose:
        action = actClose;
        Serial.println("switch is doClose");          
        break;
      case idle: 
        Serial.println("switch is idle");      
        action = actStop;
        break;        
    }
        
    switch (bridgeState)
    {
      case up:
        redLight();
        if (action == actOpen)
          action = actStop;
        Serial.println("Bridge is up"); 
        break;
      case down:
        greenLight();
        if (action == actClose)
          action = actStop;
        Serial.println("Bridge is down");    
        break;
      case unknown:
        Serial.println("Bridge is unknown"); 
        break; 
      case moving:
        Serial.println("Bridge is moving"); 
        break;        
    }
    
    switch (action)
    {
      case actOpen:
        yellowLight();
        delay(1000);
        openBridge();
        break;
      case actClose:
        yellowLight();
        delay(1000);      
        closeBridge();
        break;
      case actStop:
        turnOff();
        stopBridge();
        break; 
    }
}

void openBridge()
{


  digitalWrite(motorClosedPin, LOW);
  digitalWrite(motorOpenPin, HIGH);
  Serial.println("Opening bridge");
  
}

void closeBridge()
{

  digitalWrite(motorClosedPin, HIGH);
  digitalWrite(motorOpenPin, LOW);
  Serial.println("Closing bridge");
}

void stopBridge()
{
  digitalWrite(motorClosedPin, LOW);
  digitalWrite(motorOpenPin, LOW);
  Serial.println("stopping bridge");
}

void yellowLight ()
{
  RGB_color(150, 150, 0);
  Serial.println(" YELLOW LED On ");
}

void redLight ()
{
  RGB_color(255, 0, 0);
  Serial.println(" RED LED On ");
}

void greenLight ()
{
  RGB_color(0, 255, 0);
  Serial.println(" GREEN LED On ");
}

void turnOff ()
{
  RGB_color(0, 0, 0);
  Serial.println(" LED Off ");
}


void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(redLedPin, 255 - red_light_value);
  analogWrite(greenLedPin, 255 - green_light_value);
  analogWrite(blueLedPin, 255 - blue_light_value);
}



////       ---------- LED CONTROL  ------------------ 
//
//    if(bridgeState == up)
//    {
//     digitalWrite(redLedPin, HIGH);      
//    }
//
//    if(bridgeState == down)
//    {
//     digitalWrite(greenLedPin, HIGH);      
//    }
//
//    if(bridgeState == unknown)
//    {
//     digitalWrite(yellowLedPin, HIGH);   
//    }
//    

  

//
//void changeLights(){
//    // green off, yellow on for 3 seconds
//    digitalWrite(green, LOW);
//    digitalWrite(yellow, HIGH);
//    delay(3000);
//
//    // turn off yellow, then turn red on for 5 seconds
//    digitalWrite(yellow, LOW);
//    digitalWrite(red, HIGH);
//    delay(5000);
//
//
//    // turn off red and yellow, then turn on green
//    digitalWrite(yellow, LOW);
//    digitalWrite(red, LOW);
//    digitalWrite(green, HIGH);
//    delay(3000);
//}

/*
 Illuminating LED Pumpkin
 by Ho Yun "Bobby" Chan
 Otober 17th, 2016
 Code to control high power 12V LED strip segments using npn BJT. A button press
 changes the state of the LEDs (color and pattern).
 */

int ledR = 5;//hardware PWM //pin 0 on ATtiny85
int ledG = 6;//hardware PWM //pin 1 on ATtiny85
int ledB = 9; //hardware PWM

int ledMode = 0; //color mode to control LEDs
int pattern = 0; //pattern
int prev_FadeVal = 0;
int current_FadeVal = 0;
boolean increasing = true;

int blinkVal = 0;
boolean on = false;

const int button1Pin = 2;
boolean prev_button1State = false;
boolean current_button1State = false;

const int button2Pin = 3;
boolean prev_button2State = false;
boolean current_button2State = false;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pins as an output for LEDs
  pinMode(ledR, OUTPUT);     
  pinMode(ledG, OUTPUT);     
  pinMode(ledB, OUTPUT);
  sequenceTest();//visually initialization  
  allOFF(); //initialize LEDs with it turned off

  pinMode(button1Pin, INPUT_PULLUP); //use internal pullup resistor with button
  pinMode(button2Pin, INPUT_PULLUP); //use internal pullup resistor with button

  Serial.begin(9600);
  Serial.print("Begin Tests");
}


void loop() {

  int button1State;
  int button2State;
  /*buttonXstate
   - LOW or 0 means pressed
   - HIGH or 1 means not pressed
   */
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  //if button is pressed, it will be pulled low
  if(button1State == LOW){
    current_button1State = true; // button has been pressed once

      if(prev_button1State != current_button1State){//check to see if button is still being pressed
      ledMode = ledMode+1;//change color MODE after button has been pressed
      if(ledMode<0 || ledMode>6){
        //reset ledMode
        ledMode = 0;
        allOFF();
      }
    }
    else{//do nothing because finger is still on button
    }
    prev_button1State = current_button1State;
  }
  //button has not been pressed, it will be high
  else{
    current_button1State = false;
    prev_button1State = current_button1State;
  }

  if(button2State == LOW){
    current_button2State = true; //button has been pressed once

      if(prev_button2State != current_button2State){//check to see if button is still being pressed
      pattern=pattern+1;//change LED pattern after button has been pressed
      if(pattern<0 || pattern>3){
        //reset pattern
        pattern = 0;
      }
    }
    else{//do nothing because finger is still on button
    }
    prev_button2State = current_button2State;
  }
  //button has not been pressed, it will be high
  else{
    current_button2State = false;
    prev_button2State = current_button2State;
  }

  switch(pattern){
  case 1:
    patternON();
    break;
  case 2:
    patternFade();
    break;
  case 3:
    patternBlink();
    break;
  default:
    allOFF();
    break;
  }


}//END LOOP

/*
 ROYGBIV
 a 9V battery is not able to fully power all three LEDs simultaneously...
 MODE
 1.) red              = red[HIGH]
 .) tangerine orange = red[HIGH]+ green[50]
 2.) yellow           = red[HIGH]+ green[HIGH]
 3.) green            =          + green[HIGH]
 4.) clear blue       =          + green[HIGH] + blue[HIGH]
 5.) blue             =                        + blue[HIGH]
 6.) magenta          = red[HIGH]+             + blue[HIGH]
 .) white            = red[HIGH]+ green[HIGH] + blue[HIGH]
 */

void allOFF(){//MODE 0
  analogWrite(ledR, 0);
  analogWrite(ledG, 0);
  analogWrite(ledB, 0);
}

void redON(){//MODE 1
  analogWrite(ledR, 255);
  analogWrite(ledG, 0);
  analogWrite(ledB, 0);
}

void yellowON(){//MODE 2
  analogWrite(ledR, 255);
  analogWrite(ledG, 255);
  analogWrite(ledB, 0);
}

void greenON(){//MODE 3
  analogWrite(ledR, 0);
  analogWrite(ledG, 255);
  analogWrite(ledB, 0);
}

void clearblueON(){//MODE 4
  analogWrite(ledR, 0);
  analogWrite(ledG, 255);
  analogWrite(ledB, 255);
}

void blueON(){//MODE 5
  analogWrite(ledR, 0);
  analogWrite(ledG, 0);
  analogWrite(ledB, 255);
}

void magentaON(){//MODE 6
  analogWrite(ledR, 255);
  analogWrite(ledG, 0);
  analogWrite(ledB, 255);
}

void whiteON(){//MODE 7 //not possible using 9V battery to power all on
  analogWrite(ledR, 255);
  analogWrite(ledG, 255);
  analogWrite(ledB, 255);
}

void sequenceTest(){
  redON();
  delay(50);
  allOFF();
  delay(50);

  yellowON();
  delay(50);
  allOFF();
  delay(50);

  greenON();
  delay(50);
  allOFF();
  delay(50);

  clearblueON();
  delay(50);
  allOFF();
  delay(50);

  blueON();
  delay(50);
  allOFF();
  delay(50);

  magentaON();
  delay(50);
  allOFF();
  delay(50);

  whiteON();
  delay(50);
  allOFF();
  delay(50);

}

void patternON(){
  // button is pressed, change LED color/sequence
  switch(ledMode)
  {
  case 1:
    redON();
    break;
  case 2:
    yellowON();
    break;
  case 3:
    greenON();
    break;
  case 4:
    clearblueON();
    break;
  case 5:
    blueON();
    break;
  case 6:
    magentaON();
    break;
  default:
    allOFF();
    break;
  }//end switch
  Serial.print(ledMode);//print what the mode is set to
}

/*
//removed so Arduino can check button states between  
 //increments instead of being stuck in for loop
 void fadeR(){
 digitalWrite(ledG, LOW);
 digitalWrite(ledB, LOW);
 // fade in from min to max in increments of 5 points:
 for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
 // sets the value (range from 0 to 255):
 analogWrite(ledR, fadeValue);         
 // wait for 30 milliseconds to see the dimming effect    
 delay(30);                            
 } 
 
 // fade out from max to min in increments of 5 points:
 for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
 // sets the value (range from 0 to 255):
 analogWrite(ledR, fadeValue);         
 // wait for 30 milliseconds to see the dimming effect    
 delay(30);                            
 } 
 }*/
void patternFade(){

  switch(ledMode){
  case 1://FADE RED
    analogWrite(ledG, 0);
    analogWrite(ledB, 0);
    analogWrite(ledR, prev_FadeVal);
    break;
  case 2://FADE YELLOW
    analogWrite(ledR, prev_FadeVal);
    analogWrite(ledG, prev_FadeVal);
    analogWrite(ledB, 0);
    break;
  case 3://FADE GREEN
    analogWrite(ledR, 0);
    analogWrite(ledG, prev_FadeVal);
    analogWrite(ledB, 0);
    break;
  case 4://FADE CLEAR BLUE
    analogWrite(ledR, 0);
    analogWrite(ledG, prev_FadeVal);
    analogWrite(ledB, prev_FadeVal);
    break;
  case 5://FADE BLUE
    analogWrite(ledR, 0);
    analogWrite(ledG, 0);
    analogWrite(ledB, prev_FadeVal);
    break;
  case 6://FADE MAGENTA
    analogWrite(ledR, prev_FadeVal);
    analogWrite(ledG, 0);
    analogWrite(ledB, prev_FadeVal);
    break;
  default:
    allOFF();
    break;
  }
  delay(30);


  if(increasing == true){
    current_FadeVal += 5;
  }
  else{//decreasing
    current_FadeVal -= 5;
  }

  if(current_FadeVal>255){
    increasing = false;
    prev_FadeVal -= 5;//undo addition
    current_FadeVal = prev_FadeVal;

  }
  else if(current_FadeVal<0){
    increasing = true; 
    prev_FadeVal += 5;//unto subtraction
    current_FadeVal = prev_FadeVal;
  }

  prev_FadeVal = current_FadeVal;
}

void patternBlink(){
  switch(ledMode){
  case 1://BLINK RED
    analogWrite(ledG, 0);
    analogWrite(ledB, 0);
    analogWrite(ledR, blinkVal);
    break;
  case 2://FADE YELLOW
    analogWrite(ledR, blinkVal);
    analogWrite(ledG, blinkVal);
    analogWrite(ledB, 0);
    break;
  case 3://FADE GREEN
    analogWrite(ledR, 0);
    analogWrite(ledG, blinkVal);
    analogWrite(ledB, 0);
    break;
  case 4://FADE CLEAR BLUE
    analogWrite(ledR, 0);
    analogWrite(ledG, blinkVal);
    analogWrite(ledB, blinkVal);
    break;
    case 5://FADE BLUE
    analogWrite(ledR, 0);
    analogWrite(ledG, 0);
    analogWrite(ledB, blinkVal);
    break;
  case 6://FADE MAGENTA
    analogWrite(ledR, blinkVal);
    analogWrite(ledG, 0);
    analogWrite(ledB, blinkVal);
    break;
  default:
    allOFF();
    break;
  }
  delay(250);

  if(on == true){
    blinkVal = 0;
    on = false;
  }
  else{//it was on, so turn off
    blinkVal = 255;
    on = true;
  }
}

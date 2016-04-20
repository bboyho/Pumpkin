/*
 Illuminating LED Pumpkin
 by Ho Yun "Bobby" Chan
 Otober 24th, 2015
 Code to control high power 12V LED strip segments using npn BJT. A button press
 changes the state of the LEDs.
 */

int ledR = 5;//hardware PWM //pin 0 on ATtiny85
int ledG = 6;//hardware PWM//pin 1 on ATtiny85
int ledB = 3; //needs software PWM?

int ledMode = 0; //mode to control LEDs

const int button1Pin = 2;

boolean prev_button1State = false;
boolean current_button1State = false;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pins as an output for LEDs
  pinMode(ledR, OUTPUT);     
  pinMode(ledG, OUTPUT);     
  pinMode(ledB, OUTPUT);
  sequenceTest();//visually initialization  
  allOFF(); //initialize LEDs with it turned off

  pinMode(button1Pin, INPUT_PULLUP); //use internal pullup resistor with button

  Serial.begin(9600);
  Serial.print("Begin Tests");
}


void loop() {

  int button1State;

  button1State = digitalRead(button1Pin);
  /*button1state
   - LOW or 0 means pressed
   - HIGH or 1 means not pressed
   */

  //if button is pressed, it will be pulled low
  if(button1State == LOW){
    current_button1State = true; // button has been pressed once

      if(prev_button1State != current_button1State){//check to see if button is still being pressed
      ledMode = ledMode++;//change MODE after button has been pressed
      // button is pressed, change LED color/sequence
      if(ledMode<0 || ledMode>6){
        //reset ledMode
        ledMode = 0;
        allOFF();
      }
      else{//switch LED mode
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

        /*case 7:
          fadeR();
          break;
        */  
        default:
          allOFF();
          break;
        }//end switch
      }
      Serial.print(ledMode);//print what the mode is set to
    }
    else{
      //do nothing because finger is still on button
    }
    prev_button1State = current_button1State;
  }

  //button has not been pressed, it will be high again
  else{
    current_button1State = false;

    prev_button1State = current_button1State;
    /*if(ledMode==7){
      fadeR();
      delay(500);
    }*/
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
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
}

void redON(){//MODE 1
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
}

void yellowON(){//MODE 2
  analogWrite(ledR, 255);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, LOW);
}

void greenON(){//MODE 3
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, LOW);
}

void clearblueON(){//MODE 4
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
}

void blueON(){//MODE 5
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, HIGH);
}

void magentaON(){//MODE 6
  analogWrite(ledR, 255);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, HIGH);
}

void whiteON(){//MODE 7 //not possible using 9V battery to power all on
  analogWrite(ledR, 255);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
}
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








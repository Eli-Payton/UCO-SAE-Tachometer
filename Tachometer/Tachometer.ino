 const int number_of_LEDs = 10;        //Must Set these variables!!!
 const int starting_pin = 2;           //First digital pin with LED
 const int rpm_range = 10000;          //Max RPMs (or whatever other metric)
 const int VRy = A0;                   //Digital pin number for the Y-input of the controller
 int x1 = 0;                           //X1 is used as the global RPM value

void setup() {

   Serial.begin(9600);
   Serial.println("Starting Program");
   delay(1000);

}

 void loop() {                                          //Loop cycles through 5 times per second, uses set_x() to update x1, then prints out the values of the joystick input and x1, then RPM_check() is called
  x1 = set_x(x1);                                       //to light up the appropriate LEDs
  Serial.println(analogRead(VRy));
  Serial.println(x1);
  RPM_check(x1);
  delay(200);
 }

void RPM_check(int rpm) {                                   //This function calculates how many LEDs should be lit up and then calls the brighten_num function to brighten those LEDs
  int rpm_threshold_size = (rpm_range / number_of_LEDs);

  for (int i = 0; i < number_of_LEDs; i++){
    if (rpm > (i * rpm_threshold_size) ){       
      brighten_num(i+1);
    }
  }
}

int set_x (int x) {                                         //This function updates the value that the tachometer is displaying. If the user inputs a number to the keyboard, we return that number.
  if (Serial.available() > 0) {                             //If the user doesn't enter a new number, then we call the joystick_accelerator function to check if the user has made an input with the joystick.
     String input = Serial.readStringUntil('\n'); // Reads until Enter key is pressed
     return input.toInt();
  }
  else {
    return joystick_accelerator(x);
  }
}

void brighten_num(int x){                         //This functions takes the number of LEDs it needs to light up as an input and then brightens them while dimming all other LEDs
  for (int i = 0; i < number_of_LEDs; i++) {
      if (i < x) {
        digitalWrite(starting_pin + i, HIGH);
      } else {
        digitalWrite(starting_pin + i, LOW);
      }
    }
}

int joystick_accelerator(int x) {                 //This function takes the original RPM as an input and checks if the user has moved the joystick up or down. Depending on the user's input to the joystick       
  int yValue = analogRead(VRy);                   //the function will either return a larger, smaller, or the same RPM value. The second if statement functions as a deazone so that insignificant inputs are
  if (x < 0){                                     //not considered user inputs.
    x = 0;
  }
  if(yValue > 580 || yValue < 450){
    return ((yValue - 512) + x);
  }
  else 
  {
    return x;
  }
}
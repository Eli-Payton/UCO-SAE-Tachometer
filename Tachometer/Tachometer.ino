 const int number_of_LEDs = 10;       //Must Set these 3!!!
 const int starting_pin = 2;
 const int rpm_range = 10000;
 const int VRy = A0;  // Y-axis
 int x1 = 0;

void setup() {

   Serial.begin(9600);
   Serial.println("Hello, world!");
   delay(1000);

}

 void loop() {
  x1 = set_x(x1);
  Serial.println(analogRead(VRy));
  Serial.println(x1);
  RPM_check(x1);
  delay(200);
 }

void RPM_check(int rpm) {
  int rpm_threshold_size = (rpm_range / number_of_LEDs);

  for (int i = 0; i < number_of_LEDs; i++){
    if (rpm > (i * rpm_threshold_size) ){       //Swapping this greater than
      brighten_num(i+1);
    }
  }
}

int set_x (int x) {
  if (Serial.available() > 0) {
     String input = Serial.readStringUntil('\n'); // Reads until Enter is pressed
     return input.toInt();
}
  else {
    return joystick_accelerator(x);
  }
}

void brighten_num(int x){                         //digital write is not working with current configuration
  for (int i = 0; i < number_of_LEDs; i++) {
      if (i < x) {
        digitalWrite(starting_pin + i, HIGH);
      } else {
        digitalWrite(starting_pin + i, LOW);
      }
    }
}

int joystick_accelerator(int x) {
  int yValue = analogRead(VRy);
  if (x < 0){
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
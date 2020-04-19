/*
  Contributors:
  Nicco Rossi
  Kaiyu Hernandez
  Nathaniel Hejduk
  Adam Zawierucha
*/

// Define the LED digit patterns for 0 - F in a 2 dimensional array.
// The 2D array (an array of arrays or a matrix) has 16 arrays that each
// contain 7 values.
// Note that these patterns are for common cathode displays. For common
// anode displays, change the 1's to 0's and 0's to 1's
// 1 = LED on, 0 = LED off, in this order:
// Common Anode version
byte seven_segment_digits[16][7] = { { 0,0,0,0,0,0,1 }, // display '0'
                                     { 1,0,0,1,1,1,1 }, // display '1'
                                     { 0,0,1,0,0,1,0 }, // display '2'
                                     { 0,0,0,0,1,1,0 }, // display '3'
                                     { 1,0,0,1,1,0,0 }, // display '4'
                                     { 0,1,0,0,1,0,0 }, // display '5'
                                     { 0,1,0,0,0,0,0 }, // display '6'
                                     { 0,0,0,1,1,1,1 }, // display '7'
                                     { 0,0,0,0,0,0,0 }, // display '8'
                                     { 0,0,0,1,1,0,0 }, // display '9'
                                     { 0,0,0,1,0,0,0 }, // display 'A'
                                     { 1,1,0,0,0,0,0 }, // display 'b'
                                     { 0,1,1,0,0,0,1 }, // display 'C'
                                     { 1,0,0,0,0,1,0 }, // display 'd'
                                     { 0,1,1,0,0,0,0 }, // display 'E'
                                     { 0,1,1,1,0,0,0 }  // display 'F'
                                   };

/* Connect the pins of the display accordingly.
Only one of the VCC (Common Anode) / GND (Common Cathode) pins need to be
connected to work, but it's ok to connect both if you want.
///////////////TOP//////////////
   pin 1 : G (9)  pin 10: A (3)
   pin 2 : F (8)  pin 9 : B (4)
   pin 3 : VCC    pin 8 : VCC
   pin 4 : E (7)  pin 7 : C (5)
   pin 5 : D (6)  pin 6 : Dot (10)
/////////////BOTTOM/////////////
*/

// Initial variable values
int button_state = 1;
int last = 1;
int count = 0;
int switch_state = 0;

/* In the setup function, we set our LED pins as OUTPUT.
*/
void setup() {
  pinMode(3, OUTPUT); // set segment A as output
  pinMode(4, OUTPUT); // set segment B as output
  pinMode(5, OUTPUT); // set segment C as output
  pinMode(6, OUTPUT); // set segment D as output
  pinMode(7, OUTPUT); // set segment E as output
  pinMode(8, OUTPUT); // set segment F as output
  pinMode(9, OUTPUT); // set segment G as output
  pinMode(10, OUTPUT); // set dot as output
  for(int i = 3; i < 10; i++) { // start with segments off
    digitalWrite(i, HIGH);
  }

  //Start with dot on 7-segment display off
  digitalWrite(10, HIGH);

  //Setup the onboard switch SW1
  pinMode(31, INPUT_PULLUP);

  //Setup the tilt switch
  pinMode(11, INPUT);
}

void update_display( int count ){
  /*
    Inputs: count (integer)
    Outputs: None
    Updates 7-segment display with value of count in hex      
  */
  int pin = 3;
  for (int segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_segment_digits[count][segCount]);
    ++pin;
  }
}

/* In the loop section we will begin displaying the different numbers.
 * Add delay() or sleep() to give some time between the numbers changing.
 */
void loop() {
  // Read pin states
  button_state = digitalRead(31);
  switch_state = digitalRead(11);
  
  //Check if state indicates action needs to take place
  if (button_state != last && button_state == 0){
    // if the state is zero, we increment the count, max at 15
    if (switch_state == 0 && count < 15){
      count += 1; 
    }
    // Otherwise, we decrement the pin, min at 0
    if (switch_state == 1 && count > 0){
      count -= 1;
    }
    //Store old state
    last = button_state;
  } else if (button_state == 1){
    //Store old state
    last = button_state;
  }
  //Update display
  update_display(count);
  //Wait
  delay(1);
}

//Extra debug functions
/*
void iterate_segments(){
  //Iterates through all the segment lights: purely for debugging
  for (int cur = 3; cur < 10; cur++) {
    for (int pin = 3; pin < 10; pin++) {
      if (cur == pin) {
        digitalWrite(pin, 0);
      } else {
        digitalWrite(pin, 1);
      }
    }
    delay(1000); // this is the same as delay() but saves power
  }
}
*/

/*
void disp_all(){
  for (int count = 16; count > 0; --count) {
    int pin = 3;
    for (int segCount = 0; segCount < 7; ++segCount) {
      digitalWrite(pin, seven_segment_digits[count-1][segCount]);
      ++pin;
    }
    delay(1000); // this is the same as delay() but saves power
  }
}
*/

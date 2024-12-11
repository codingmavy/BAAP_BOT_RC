//Add or related libraries
#include<HardwareSerial.h>

const int XPIN = 32;     // Joystick X-axis pin
const int YPIN = 35;     // Joystick Y-axis pin
//const int BUTTONPIN = 34; // Joystick button pin
const int RX_PIN = 27;   // 
const int TX_PIN = 14;   //

// Use HardwareSerial on UART2 (for example)
HardwareSerial HC05(2);  // Use UART2 for HC-05

void connectToHC05() {
  Serial.println("Configuring HC-05...");
  // HC05.println("AT");  // Test HC-05 communication
  delay(100);
  if (HC05.available()) {
    Serial.println("HC-05 Ready");
  } else {
    Serial.println("HC-05 Connection Failed");
  }
}

void setup() {
  Serial.begin(9600);   // Serial monitor baud rate
   HC05.begin(38400, SERIAL_8N1, RX_PIN, TX_PIN);  // Use HardwareSerial on UART2 with custom pins
  //HC05.begin(38400);

  pinMode(XPIN, INPUT);
  pinMode(YPIN, INPUT);
  //pinMode(BUTTONPIN,INPUT_PULLUP);

  Serial.println("HC-05 Bluetooth Ready");
  connectToHC05();
}

void loop() {
  // Read joystick inputs
  int xval = analogRead(XPIN);
  int yval = analogRead(YPIN);
  //int buttonState = digitalRead(BUTTONPIN);

  // Debug print for joystick values
  Serial.printf("X: %d, Y: %d\n", xval, yval);

  // Send movement data to the HC-05
  sendMovementData(xval, yval);

  delay(100); // Reduced delay for more responsive control
}

void sendMovementData(int xval, int yval) {
  // Dynamic mapping with center deadzone
  int forwardSpeed = map(yval, 3500, 2460, 0, 255);
  int backwardSpeed = map(yval, 2500, 3200, 0, 255);
  int leftSpeed = map(xval, 2500, 2400, 0, 255);
  int rightSpeed = map(xval, 3500, 3400, 0, 255);

  // Send movement commands to the HC-05
  if (yval < 2460 && xval > 3500) {
    HC05.printf("%c",'1'); // forward
  } else if (yval > 3200 && xval < 2500) {
    HC05.printf("%c",'2'); // Backward
  }

  else if (yval < 2400 && xval < 2500) {
    HC05.printf("%c",'4'); // left
  } else if (yval > 3400 && xval > 3500) {
    HC05.printf("%c",'3'); // right
  }

  else{
    HC05.printf("%c",'5');
  }

  // if (buttonState == 0) {
  //   // HC05.print("STOP");
  //   HC05.println(0);
  // }

  delay(100);
}

//add all related libraries before compilling
#include <Wire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

char t;
SoftwareSerial BTSerial(8, 9);  //RX || TX
int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;
LiquidCrystal_I2C lcd(0x27, 16, 2);

char message[] = "THE ROBOTICS CLUB, PANTNAGAR  ";  // Message to scroll with spaces at the end
int length = sizeof(message) - 1;                   // Length of the message (excluding null terminator)

unsigned long previousMillis = 0;  // To track the last update time
const long interval = 500;         // Scroll interval (adjust as needed)


void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();  // Turn on the backlight

  // Print the fixed message to the LCD
  lcd.setCursor(3, 1);
  lcd.print("BAAP-BOT;)");
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  BTSerial.begin(38400);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Controlling speed (0  = off and 255 = max speed):
  if (BTSerial.available()) {
    t = BTSerial.read();
    Serial.println(t);
  }
  // Scroll the first line manually
  static int position = 0;  // Current scroll position
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Update the last update time

    lcd.setCursor(0, 0);                    // Set cursor to the beginning of the first line
    for (int i = 0; i < 16; i++) {          // 16 is the LCD width
      int index = (position + i) % length;  // Loop around the message length
      lcd.print(message[index]);            // Print the character
    }
    position = (position + 1) % length;  // Increment the position
  }

  switch (t) {
    case '1':  // Move forward
      forward();
      break;
    case '2':  // Move reverse
      reverse();
      break;
    case '4':  // Turn left
      left();
      break;
    case '3':  // Turn right
      right();
      break;
    case '5':  // Stop
      stop();
      break;
    default:  // Do nothing for invalid input
      stop();
      break;
  }
}
void stop() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void reverse() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

void forward() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void left() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void right() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}
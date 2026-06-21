  /* Code Written by Mridul Saha */

  #include <Servo.h> // Adding Servo Library
  #include <SoftwareSerial.h> // Adding Software Serial Library
 
  Servo myservo; // Using myservo name
  SoftwareSerial sim800l(11, 12); // Defining Sim800L RX and TX

  int pos; // Creating a variable for servo position
  boolean fire = false; // Defining fire is false in initial state

  #define Left 9 // Defining Left Flame Sensor to Arduino 0 number Digital Pin
  #define Right 10 // Defining Right Flame Sensor to Arduino 1 number Digital Pin
  #define Middle 2 // Defining Middle Flame Sensor to Arduino 2 number Digital Pin
  #define IN1 3 // Defining IN1 Motor Driver Pin to Arduino 3 number Digital Pin
  #define IN2 4 // Defining IN2 Motor Driver Pin to Arduino 4 number Digital Pin
  #define IN3 5 // Defining IN3 Motor Driver Pin to Arduino 5 number Digital Pin
  #define IN4 6 // Defining IN4 Motor Driver Pin to Arduino 6 number Digital Pin
  #define Pump 7 // Defining Pump Relay Pin to Arduino 7 number Digital Pin
  #define Gassensor 8 // Defining Gas Sensor Pin to Arduino 8 number Digital Pin

void setup() 
{

  pinMode(Left, INPUT); // Defining Pin Mode as Input
  pinMode(Right, INPUT); // Defining Pin Mode as Input
  pinMode(Middle, INPUT); // Defining Pin Mode as Input
  pinMode(Gassensor, INPUT); // Defining Pin Mode as Input 
  pinMode(IN1, OUTPUT); // Defining Pin Mode as Output 
  pinMode(IN2, OUTPUT); // Defining Pin Mode as Output 
  pinMode(IN3, OUTPUT); // Defining Pin Mode as Output 
  pinMode(IN4, OUTPUT); // Defining Pin Mode as Output 
  pinMode(Pump, OUTPUT); // Defining Pin Mode as Output 

  myservo.attach(A0); // Defining Servo Pin to Arduino A3 Number Analog Pin 
  myservo.write(90); //Defining Servo Intital State to 90 degree

  sim800l.begin(115200); // Sim800L Starts
  sim800l.println("AT\r\n"); // Sim800L Testing Command
  digitalWrite(Pump, HIGH); // Defining Pump Relay Initial stage to High

  digitalWrite(IN1, LOW); // Defining IN1 Motor Driver Pin as Low in Initial Stage
  digitalWrite(IN2, LOW); // Defining IN2 Motor Driver Pin as Low in Initial Stage
  digitalWrite(IN3, LOW); // Defining IN3 Motor Driver Pin as Low in Initial Stage
  digitalWrite(IN4, LOW); // Defining IN4 Motor Driver Pin as Low in Initial Stage

}

void fireburn() 
{

  digitalWrite(Pump, LOW); // Defining the Pump Relay to Start when fire is true
  delay(500); // Delay because pump will start first then servo will run

  for (pos = 10; pos <= 170; pos++) // Initial Position of Servo will be 20 and then with 15 millseconds delay position will increase with 1 till it becomes 160
  {
    myservo.write(pos); 
    delay(15);
  }

  for (pos = 170; pos >= 10; pos--) // Initial Position of Servo will be 160 and then with 15 millseconds delay position will decrease with 1 till it becomes 20
  {
    myservo.write(pos);
    delay(15);
  }

  myservo.write(90); // Now servo will go to its initial position of 90 degree
  delay(500); // Delay of 2500 because first Servo will stop then Pump Relay will Stop

  digitalWrite(Pump, HIGH); // Stopping the Pump Relay


  fire = false; // Now defining fire is false

}

void gassms() 
{

  sim800l.println("AT+CMGF=1\r\n"); // By this command sim800l will go to text mode
  delay(1000); // Delay Because previous command will take time
  sim800l.println("AT+CMGS=\"+919993519780\"\r\n"); // This command say that sim800l send sms to this mobile no. *please use country code while sending sms
  delay(1000); // Delay Because previous command will take time
  sim800l.print("Gas Detected!!"); // Now sim800l will send this message to the number
  delay(1000); // Delay Because previous command will take time
  sim800l.write(26);

}

void flamesms() 
{

  sim800l.println("AT+CMGF=1\r\n"); // By this command sim800l will go to text mode
  delay(1000); // Delay Because previous command will take time
  sim800l.println("AT+CMGS=\"+919993519780\"\r\n"); // This command say that sim800l send sms to this mobile no. *please use country code while sending sms
  delay(1000); // Delay Because previous command will take time
  sim800l.println("Flame Detected!!"); // Now sim800l will send this message to the number
  delay(1000); // Delay Because previous command will take time
  sim800l.write(26);

}

void flamecall() 
{

  sim800l.println("ATD+919993519780;"); // By this command sim800l will call to this no.

}


void loop() 
{

  int gasread = digitalRead(Gassensor); // Defining gasread as analogRead of Gas sensor

  if (gasread == LOW) // If gas sensor detects any gas or smoke it will run gassms method
  {
    gassms(); // Calling Gas Sms Method
  }

  myservo.write(90);

  if (digitalRead(Left) == LOW && digitalRead(Right) == LOW && digitalRead(Middle) == LOW) // If Left, Right and Middle flame sensor detects any flame then it will run code below
  {
    fire = true; // Defining fire is true
    digitalWrite(IN1, HIGH); // Defining IN1 pin as High to run left motor to forward
    digitalWrite(IN2, LOW); // Defining IN2 pin as Low
    digitalWrite(IN3, HIGH); // Defining IN3 pin as High to run Right motor to forward
    digitalWrite(IN4, LOW); // Defining IN4 pin as Low
    delay(3000); // Delay Because it motor will run for 1000 milliseconds and then run code below
    digitalWrite(IN1, LOW); // Defining IN1 pin as Low
    digitalWrite(IN2, LOW); // Defining IN2 pin as Low
    digitalWrite(IN3, LOW); // Defining IN3 pin as Low
    digitalWrite(IN4, LOW); // Defining IN4 pin as Low
  } 

  else if (digitalRead(Middle) == LOW) // If Middle flame sensor detects any flame then it will run code below
  {
    fire = true; // Defining fire is true
    digitalWrite(IN1, HIGH); // Defining IN1 pin as High to run left motor to forward
    digitalWrite(IN2, LOW); // Defining IN2 pin as Low
    digitalWrite(IN3, HIGH); // Defining IN3 pin as High to run Right motor to forward
    digitalWrite(IN4, LOW); // Defining IN4 pin as Low
    delay(3000); // Delay Because it motor will run for 1000 milliseconds and then run code below
    digitalWrite(IN1, LOW); // Defining IN1 pin as Low
    digitalWrite(IN2, LOW); // Defining IN2 pin as Low
    digitalWrite(IN3, LOW); // Defining IN3 pin as Low
    digitalWrite(IN4, LOW); // Defining IN4 pin as Low
  } 

  else if (digitalRead(Left) == LOW) // If Left flame sensor detects any flame then it will run code below
  {
    fire = true; // Defining fire is true
    digitalWrite(IN1, LOW); // Defining IN1 pin as Low
    digitalWrite(IN2, HIGH); // Defining IN2 pin as High because it will turn the vehicle to Left
    digitalWrite(IN3, HIGH); // Defining IN3 pin as High because it will turn the vehicle to Left
    digitalWrite(IN4, LOW); // Defining IN4 pin as Low
    delay(2000); // Delay Because motor will run for 500 milliseconds and then it will run code below
    digitalWrite(IN1, LOW); // Defining IN1 pin as Low 
    digitalWrite(IN2, LOW); // Defining IN2 pin as Low
    digitalWrite(IN3, LOW); // Defining IN3 pin as Low
    digitalWrite(IN4, LOW); // Defining IN4 pin as Low
  } 

  else if (digitalRead(Right) == LOW) // If Right flame sensor detects any flame then it will run code below
  {
    fire = true;  // Defining fire is true
    digitalWrite(IN1, HIGH); // Defining IN1 pin as High because it will turn the vehicle to Right
    digitalWrite(IN2, LOW); // Defining IN2 pin as Low
    digitalWrite(IN3, LOW); // Defining IN3 pin as Low
    digitalWrite(IN4, HIGH); // Defining IN4 pin as High because it will turn the vehicle to Right
    delay(2000); // Delay Because motor will run for 500 milliseconds and then it will run code below
    digitalWrite(IN1, LOW); // Defining IN1 pin as Low  
    digitalWrite(IN2, LOW); // Defining IN2 pin as Low
    digitalWrite(IN3, LOW); // Defining IN3 pin as Low
    digitalWrite(IN4, LOW); // Defining IN4 pin as Low
  }

  while (fire == true) // While fire is true it will call the methods below
  {
  fireburn(); // Calling fire burn method
  flamesms(); // Calling flame sms method
  delay(2000); // Delay because sending a sms take some time
  flamecall(); // Calling flame call method
  }

}


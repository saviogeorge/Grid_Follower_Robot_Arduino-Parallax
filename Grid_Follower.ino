//Note:
//The following program makes the robot to move on a grid (Black Track on white Background)
//In a specified Path on the grid under the section "Robo Path to specified here"
#include<Servo.h>

//Macros declared for the arduino pin 
#define SENSOR_RIGHTMOST_PIN    7
#define SENSOR_RIGHT_PIN        6
#define SENSOR_MIDDLE_PIN       5
#define SENSOR_LEFT_PIN         4
#define SENSOR_LEFTMOST_PIN     3
#define SWITCH_PIN              2

#define MOTOR_RIGHT_PIN         13
#define MOTOR_LEFT_PIN          12

//Necessary variables declared as volatile to prevent optimization
volatile int sensorRightTrackCross;                  
volatile int sensorRight;                             
volatile int sensor_Middle;                 
volatile int sensorLeft;                  
volatile int sensorLeftTrackCross;                  
volatile int Keypress;

Servo motor_left, motor_right;              //servo Motor Objects Left and Right

//Function to make the Robot to turn left
//The approach is one wheel is stopped and the other 
//rotated and wait till the middle sensor meets the track
//Turn delay is to skip the first straight track
//and later the robot turns until the middle sensor meets the 
//track perpendicular to the striaght track 
void Left()
{
    motor_right.writeMicroseconds(1450);  
    motor_left.writeMicroseconds(1500);
    delay(500);//turn delay
    //Rotate the robot until middle sensor detects black
    while(digitalRead(SENSOR_MIDDLE_PIN))
    {
      motor_right.writeMicroseconds(1450);   
      motor_left.writeMicroseconds(1500);
    }
}

//Function to make the Robot to turn right
//The approach is one wheel is stopped and the other 
//rotated and wait till the middle sensor meets the track
//Turn delay is to skip the first straight track
//and later the robot turns until the middle sensor meets the 
//track perpendicular to the striaght track 
void Right()
{
    motor_right.writeMicroseconds(1500);   
    motor_left.writeMicroseconds(1550);
    delay(500);//turn delay
    //Rotate the robot until middle sensor detects black
    while(digitalRead(SENSOR_MIDDLE_PIN))
    {
      motor_right.writeMicroseconds(1500);   
      motor_left.writeMicroseconds(1550);
    }
}

//Function to make the Robot to turn Left
//The approach is both the wheels are rotated after going a little forward
//after the junction is crossed 
//rotated and wait till the middle sensor meets the track
//Turn delay is to skip the first straight track
//and later the robot turns until the middle sensor meets the 
//track perpendicular to the striaght track 
void Left_90()
{
    motor_right.writeMicroseconds(1450);
    motor_left.writeMicroseconds(1550);
    delay(300);//Forward delay
    motor_right.writeMicroseconds(1450);  
    motor_left.writeMicroseconds(1500);
    delay(500);//turn delay
    //Rotate the robot until middle sensor detects black
    while(digitalRead(SENSOR_MIDDLE_PIN))
    {
      motor_right.writeMicroseconds(1450);   
      motor_left.writeMicroseconds(1500);
    }
}

//Function to make the Robot to turn right
//The approach is both the wheels are rotated after going a little forward
//after the junction is crossed 
//rotated and wait till the middle sensor meets the track
//Turn delay is to skip the first straight track
//and later the robot turns until the middle sensor meets the 
//track perpendicular to the striaght track 
void Right_90()
{
    motor_right.writeMicroseconds(1450);
    motor_left.writeMicroseconds(1550);
    delay(300);//Forward delay
    motor_right.writeMicroseconds(1525);   
    motor_left.writeMicroseconds(1525);
    delay(500);//turn delay
    //Rotate the robot until middle sensor detects black
    while(digitalRead(SENSOR_MIDDLE_PIN))
    {
      motor_right.writeMicroseconds(1525);   
      motor_left.writeMicroseconds(1525);
    }
}

//Function to take u turn from right
//The good amount of turn delay will make the robot to turn
//for a large time and later it turns until the middle sensor it finds the immediate
//next track 
void Uturn_Right()
{
  motor_right.writeMicroseconds(1525);   
  motor_left.writeMicroseconds(1525);
  delay(1000);//turn delay
  while(digitalRead(SENSOR_MIDDLE_PIN))
  {
    motor_right.writeMicroseconds(1525);   
    motor_left.writeMicroseconds(1525);
  }
}

//Function to take u turn from left
//The good amount of turn delay will make the robot to turn
//for a large time and later it turns until the middle sensor it finds the immediate
//next track 
void Uturn_Left()
{
  motor_right.writeMicroseconds(1475);  
  motor_left.writeMicroseconds(1475);
  delay(1000);//turn delay
  while(digitalRead(SENSOR_MIDDLE_PIN))
  {
    motor_right.writeMicroseconds(1475);  
    motor_left.writeMicroseconds(1475);
  }
}

//Function makes the robot to move forward 
//in a fixed speed
void FixedSpeed_Forward()
{
  motor_right.writeMicroseconds(1450);
  motor_left.writeMicroseconds(1550);
}
//Function makes the robot to turn Left 
//in a fixed speed
void FixedSpeed_Left()
{
  motor_right.write(1700);
  motor_left.write(1700);
}
//Function makes the robot to turn Right 
//in a fixed speed
void FixedSpeed_Right()
{
  motor_right.write(1300);
  motor_left.write(1300);
}

//To keep the robot moving on forward direction
//For function call-Forward(0) the skip track is disabled and therefore robot stops at the next junction
//immediately it detects the junction
//For function call-Forward(1) the skip track is enbled and therefore the robot stops after all
//sensors have passed the junction
//Benefit- To skip a track we do not have rely on delay function which might show little unstable behaviour depending on the 
//Battery power
//Known Limitation - if the vehicle approaches a junction too much inclined and not striaght enough
//The skip track might fail , If the tracks are very thin this effect is pronounced
//An alternate solution would be to combine the above 2 techniques skip the track and give a delay as well
//so we make sure the vehicle crosses the jucntion to be skipped and the sensors crosses the junction 
void KeepTrack_MoveForward(bool Enable_SkipTrack)
{
  while(1)
  {
    //------------------------------Keeps the Robot on track----------------------------// 
             
    sensorRightTrackCross         = digitalRead(SENSOR_RIGHTMOST_PIN);
    sensorLeft                    = digitalRead(SENSOR_LEFT_PIN);
    sensorRight                   = digitalRead(SENSOR_RIGHT_PIN);
    sensorLeftTrackCross          = digitalRead(SENSOR_LEFTMOST_PIN);

    // To keep moving forward
    if( ( 1 == sensorLeft && 1 == sensorRight )||( 0 == sensorLeft && 0 == sensorRight ) )
  
    {
      FixedSpeed_Forward();
    }
    //To tilt towards right
    else if( 0 == sensorLeft && 1 == sensorRight )
    {
      FixedSpeed_Right();
    }
    //To tilt towards left 
    else if( 0 == sensorRight && 1 == sensorLeft )
    {
      FixedSpeed_Left();
    }
    //------------------------------Keeps the Robot on track----------------------------//  
    //When a junction is encountered
    if( 0 == sensorRightTrackCross || 0 == sensorLeftTrackCross )
    {
      //If the skip track is enabled
      if(Enable_SkipTrack)
      {
        FixedSpeed_Forward();
        while((!digitalRead(SENSOR_RIGHTMOST_PIN))||(!digitalRead(SENSOR_LEFTMOST_PIN))||(!digitalRead(SENSOR_LEFT_PIN))||(!digitalRead(SENSOR_RIGHT_PIN)))
        {
          //Control stays here until all the track sensors have crossed the line
          //to be skipped 
          //All the sensors has to be checked for stability
          delay(400);//optional enable it in case if the robot does not work with skip track approach alone
        }
      }//If for enable skip track ends here
      break;
    }//if for track cross sensors ends here    
  }//while loop ends here
  return;
}//function ends here

//Function to stop the Robot 
void Stop()
{
    motor_right.writeMicroseconds(1500);
    motor_left.writeMicroseconds(1500);
}
 
 
void setup()
{
  //Setting the Pin Mode for sensors         
  pinMode(SENSOR_RIGHTMOST_PIN,INPUT);
  pinMode(SENSOR_RIGHT_PIN,INPUT);
  pinMode(SENSOR_MIDDLE_PIN,INPUT);
  pinMode(SENSOR_LEFT_PIN,INPUT);
  pinMode(SENSOR_LEFTMOST_PIN,INPUT);
  pinMode(SWITCH_PIN,INPUT_PULLUP);
  
  motor_right.attach(MOTOR_RIGHT_PIN);
  motor_left.attach(MOTOR_LEFT_PIN);
  Serial.begin(9600);

  while(1)
  {
    Keypress        = digitalRead(SWITCH_PIN);
    //The robot is stopped until a key press is detected
    if( 1 == Keypress )
    {  
      Stop();   
    }
    //Give the necessary directions to 
    //in here to move the robot in a specified track within
    //the grid once the function calls inside this are all executed
    //the robot stops and will not start until the next key press
    else if( 0 == Keypress )
    {
      //-----------------------Robo Path to specified here---------------------//
      KeepTrack_MoveForward(0);
      Right();
      KeepTrack_MoveForward(0);
      Left();
      KeepTrack_MoveForward(1);
      KeepTrack_MoveForward(0);
      Left();
      KeepTrack_MoveForward(0);
      Right();
      KeepTrack_MoveForward(1);
      KeepTrack_MoveForward(0);  
      //-----------------------Robo Path to specified here---------------------//   
    }//else if ends here  
  }//while ends here
}//set up ends here
void loop()
{}


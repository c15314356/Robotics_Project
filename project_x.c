/*
This will Be the Main Program for the project
c15314356
*/
#pragma config(Sensor, S3,     lightSensor,    sensorEV3_Color)
#pragma config(Sensor, S2,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S1,     ultraSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          Right,         tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorC,          Left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)

#define TURN 190
#define SPEED 50

//Turn left 90 degrees
void LeftTurn(void);
//Turn right 90 degrees
void RightTurn(void);
//Go Forward
void Forward(void);
//Counts number of squares passed
int Count(int count);
//Reset count
int ResetCount(int count);
//Move Forward a Square
void ForwardSQ(void);
//Move next line
void NextLineLeft(void);

task main()
{
    int count=0;
    int direction=1;
    int doubleline=0;
    int sense=0;
    
    //turn right go forward until hit double line go back half a square then turn left (You are at bottom left sq now
    while(doubleline!=2)
    {
        //traverse right and count lines
        if(direction==1)
        {
            while(count<7)
            {
                //move forward
                Forward();
                
                if(SensorValue(lightSensor)<45)
                {
                    sense=1;
                }
        
                if(SensorValue(lightSensor)>45&&sense==1)
                {
                    Count(count);
                    sense=0;
                }
                displayBigTextLine(4,"crossed %d lines",count);
            }
            
            //Switches to next line
            direction=NextLineLeft(direction);
            //Resets count
            count=ResetCount(count);
        }
        
        //traverse left and count lines
        if(direction==2)
        {
            while (count<7)
            {
                //move forward
                Forward();
                
                if(SensorValue(lightSensor)<45)
                {
                    sense=1;
                }
        
                if(SensorValue(lightSensor)>45&&sense==1)
                {
                    Count(count);
                    sense=0;
                }
                displayBigTextLine(4,"crossed %d lines",count);
            }
            
            //Switches to next line
            direction=NextLineRight(direction);
            //Resets count
            count=ResetCount(count);
        }
    }
    
}//end main()


//Turn left 90 degrees
void LeftTurn(void)
{
    //Reset Encoder
    nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
    //Turn Right
	setMotorTarget(motorB,-TURN,50);
	setMotorTarget(motorC,TURN,50);
    //Wait for program to stop
	waitUntilMotorStop(motorB);
	waitUntilMotorStop(motorC);
}

//Turn right 90 degrees
void RightTurn(void)
{
    //Reset Encoder
    nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
    //Turn Right
    setMotorTarget(motorB,TURN,50);
	setMotorTarget(motorC,-TURN,50);
    //Wait for program to stop
    waitUntilMotorStop(motorB);
    waitUntilMotorStop(motorC);
}

//Go Forward
void Forward(void)
{
    motor(motorB)=SPEED;
    motor(motorC)=SPEED;
    wait1Msec(1);
}

//Counts number of squares passed
void Count(int count)
{
    count++;
    return(count);
}

//resets the number of count
int ResetCount(int count)
{
    count=0;
    return(count);
}

//Move Forward a Square
void ForwardSQ(void)
{
	//Move Forward a Square
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
	setMotorTarget(motorB,180,50);
	setMotorTarget(motorC,180,50);
	waitUntilMotorStop(motorB);
	waitUntilMotorStop(motorC);
}

//Move next line on left
void NextLineLeft(int direction)
{
    ForwardSQ();
    LeftTurn();
    ForwardSQ();
    LeftTurn();
    direction=2;
    return(direction);
}

//Move next line on right
void NextLineRight(int direction)
{
    ForwardSQ();
    RightTurn();
    ForwardSQ();
    RightTurn();
    direction=1;
    return(direction);
}


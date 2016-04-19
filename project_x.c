/*
This will Be the Main Program for the project
TODO------------------------------------
implement ability to write to file
implement stop when double line hit x2
implement go back sq when double line hit and turn
implement x and y coords in order to go back to start
implement ability to scan for an object
-------------------------------------------
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
//Go forward
void Forward(void);
//Counts number of squares passed
int Count(int count);
//Reset count
int ResetCount(int count);
//Move forward a Square
void ForwardSQ(void);
//Move next line on left
int NextLineLeft(int direction);
//Move next line on right
int NextLineRight(int direction);

task main()
{
    int count=0;
    int direction=1;
    int doubleline=0;
    int sense=0;
    int blacksq=0;

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
                //if less 45 = black
                if(SensorValue(S3)<45)
                {
                    sense=1;
                    if(time1[T1]>200)
                    {
                        blacksq++;
                    }
                }

                //if greater 45 = white
                if(SensorValue(S3)>45&&sense==1)
                {
                    //starts timer
                    clearTimer(T1);
                    //adds one to count of lines
                    Count(count);
                    sense=0;
                }
                displayBigTextLine(4,"crossed %d lines number of black= %d",count,blacksq);
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

                if(SensorValue(S3)<45)
                {
                    sense=1;
                    if(time1[T1]>200)
                    {
                        blacksq++;
                    }
                }

                if(SensorValue(S1)>45&&sense==1)
                {
                    //starts timer
                    clearTimer(T1);
                    //adds one to count of lines
                    Count(count);
                    sense=0;
                }
                displayBigTextLine(4,"crossed %d lines number of black= %d",count,blacksq);
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
}//end LeftTurn

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
}//end RightTurn

//Go Forward
void Forward(void)
{
    motor(motorB)=SPEED;
    motor(motorC)=SPEED;
    wait1Msec(1);
}//end Forward()

//Counts number of squares passed
int Count(int count)
{
    count++;
    return(count);
}// end Count()

//resets the number of count
int ResetCount(int count)
{
    count=0;
    return(count);
}//end ResetCount()

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
}//end ForwardSQ()

//Move next line on left
int NextLineLeft(int direction)
{
    ForwardSQ();
    LeftTurn();
    ForwardSQ();
    LeftTurn();
    direction=2;
    return(direction);
}//end NextLine Left()

//Move next line on right
int NextLineRight(int direction)
{
    ForwardSQ();
    RightTurn();
    ForwardSQ();
    RightTurn();
    direction=1;
    return(direction);
}//end NextLineRight ()

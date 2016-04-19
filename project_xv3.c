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

#define LEFT 178
#define RIGHT 178
#define SPEED 30
#define DISTANCE 2152

//Turn left 90 degrees
void LeftTurn(void);
//Turn right 90 degrees
void RightTurn(void);
//Go forward
void Forward(void);
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
        	   	nMotorEncoder[motorB]=0;
							nMotorEncoder[motorC]=0;
            while(nMotorEncoder[motorB]<DISTANCE)
            {
                //move forward
                Forward();
                //if less 45 = black
                if(SensorValue(S3)<45)
                {
                    sense=1;
                    clearTimer(T1);

                }

                //if greater 45 = white
                if(SensorValue(S3)>45&&sense==1)
                {
										if(time1[T1]>500)
                    {
                        blacksq++;
                    }
                    //adds one to count of lines
                    count++;
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
        	    nMotorEncoder[motorB]=0;
							nMotorEncoder[motorC]=0;
            while (nMotorEncoder[motorB]<DISTANCE)
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

                if(SensorValue(S3)>45&&sense==1)
                {
                    //starts timer
                    clearTimer(T1);
                    //adds one to count of lines
                    count++;
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
	setMotorTarget(motorB,-LEFT,25);
	setMotorTarget(motorC,LEFT,25);
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
    setMotorTarget(motorB,RIGHT,25);
	setMotorTarget(motorC,-RIGHT,25);
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
	setMotorTarget(motorB,287,25);
	setMotorTarget(motorC,287,25);
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

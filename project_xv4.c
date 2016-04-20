/*
This will Be the Main Program for the project
TODO------------------------------------
implement ability to write to file
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

#define TURN2 1780
#define TURN 178
#define SPEED 30
#define ROW 7
#define COL 9

//global variables
int blacksq=0;
int total=0;
int pos1=0,pos2=0;
int grid[ROW][COL];//<--------------------- change all to strings and also change all intial values to 0

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
    int end=0;

    //turn right go forward until hit double line go back half a square then turn left (You are at bottom left sq now
    while(end!=6)
    {
        //traverse right and count lines
        if(direction==1)
        {
            end++;
            while(count<8)
            {
                if(SensorValue(S3)<45)
                {
                    blacksq++;
                    //store position to array
                    grid[pos1][pos2]=1;
                }
                //increment counters
                count++;
                total++;
                displayBigTextLine(2,"Black:%d",blacksq);
                displayBigTextLine(5,"Count:%d ",count);
                displayBigTextLine(8,"Total:%d",total);
                //move forward one square
                Forward();
                pos2++;
            }

            //Switches to next line
            if(end!=6)
            {
                direction=NextLineLeft(direction);
                //Resets count
                count=ResetCount(count);
                pos2=0;
                pos1++;
            }
        }
        if(direction==2)
        {
            end++;
            while(count<8)
            {
                if(SensorValue(S1)<45)
                {
                    blacksq++;
                    //store position to array
                    grid[pos1][pos2]=1;
                }
                //increment counters
                count++;
                total++;
                displayBigTextLine(2,"Black:%d",blacksq);
                displayBigTextLine(5,"Count:%d ",count);
                displayBigTextLine(8,"Total:%d",total);
                //move forward one square
                Forward();
                pos2++;
            }
            //Switches to next line
            if(end!=6)
            {
                //Switches to next line
                direction=NextLineRight(direction);
                //Resets count
                count=ResetCount(count);
                pos2=0;
                pos1++;
            }
        }//end if()
        //go back 7 suares and take away distance from bottom col from start from 7 and go to start
    }//end while()
}//end main()


//Turn left 90 degrees
void LeftTurn(void)
{
	motor[motorB]=-10;
	motor[motorC]=10;
	wait1Msec(TURN2);
}//end LeftTurn

//Turn right 90 degrees
void RightTurn(void)
{
	motor[motorB]=10;
	motor[motorC]=-10;
	wait1Msec(TURN2);
}//end RightTurn

//Go Forward
void Forward(void)
{
    motor(motorB)=SPEED;
    motor(motorC)=SPEED;
    wait1Msec(900);
}//end Forward()

//resets the number of count
int ResetCount(int count)
{
    count=0;
    return(count);
}//end ResetCount()

//Move Forward a Square
void ForwardSQ(void)//<--------------------------------------------------change distance forward
{
	//Move Forward a Square
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
	setMotorTarget(motorB,220,20);
	setMotorTarget(motorC,220,20);
	waitUntilMotorStop(motorB);
	waitUntilMotorStop(motorC);
}//end ForwardSQ()

//Move next line on left
int NextLineLeft(int direction)
{
    if(SensorValue(S1)<45)
    {
        blacksq++;
        //store position to array
        grid[pos1][pos2]=1;
    }
    //increment total
    total++;
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
    if(SensorValue(S1)<45)
    {
        blacksq++;
        //store position to array
        grid[pos1][pos2]=1;
    }
    total++;
    ForwardSQ();
    RightTurn();
    ForwardSQ();
    RightTurn();
    direction=1;
    return(direction);
}//end NextLineRight ()

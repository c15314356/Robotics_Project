/*
This will Be the Main Program for the project
TODO------------------------------------
implement write start
-------------------------------------------
c15314356
*/
#pragma config(Sensor, S3,     lightSensor,    sensorEV3_Color)
#pragma config(Sensor, S2,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S1,     ultraSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          Right,         tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorC,          Left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)

#define TURN2 1770
#define TURN 150
#define SPEED 30
#define ROW 7
#define COL 9
#define STARTNUM 6;

//global variables
int blacksq=0;
int total=0;
int pos1=0,pos2=0;
string onwhite="Your are on White";
string onblack="Your are on Black";
int colour=0;
int temp;
int startpos=0;
char grid[ROW][COL]=
{
{'0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0'}};
//file handle
long fileHandle;
string filename="MappedGrid";

long fileHandle2;
string filename2="MappedGrid2";


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
//Go to Start of grid
void GoStart(void);
//display array
void checkarray(void);

task main()
{
    int count=0;
    int direction=1;
    int end=0;
    int doubleline=0;
    int pause=0;
    string line1='\n';
		int line2=strlen(line1);
    int sizeofblack=strlen(onblack);
    int sizeofwhite=strlen(onwhite);

    //open the file to write
    fileHandle=fileOpenWrite(filename);
    fileHandle2=fileOpenWrite(filename2);
    //turn right go forward until hit double line go back half a square then turn left (You are at bottom left sq now)
    RightTurn();
    while(pause==0)
  	{
      motor(motorB)=SPEED;
  		motor(motorC)=SPEED;
  		wait1Msec(1);
  		startpos++;

  		if(SensorValue(S3)<45&&doubleline!=1)
  		{
  			if(time1[T1]<200)
  			{
  				pause=1;
  			}
  			doubleline=1;
  	}
  		if(SensorValue(S3)>45&&doubleline==1)
  		{
  			doubleline=0;
  			clearTimer(T1);
  		}
	}
	//writes start pos to array
	startpos=(startpos/1000)+1;
	motor[motorB]=-20;
	motor[motorC]=-20;
	wait1Msec(700);
	LeftTurn();

    //start traversing grid
    while(end!=7)
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
                    grid[pos1][pos2]='1';
                }
                //increment counters
                count++;
                total++;
                displayBigTextLine(2,"Black:%d",blacksq);
                displayBigTextLine(5,"startpos=%d",startpos);
                //displayBigTextLine(5,"Count:%d ",count;
                displayBigTextLine(8,"Total:%d",total);
                //move forward one square
                Forward();
                pos2++;
            }

            //Switches to next line
            if(end!=7)
            {
                direction=NextLineLeft(direction);
                //Resets count
                count=ResetCount(count);
                pos1++;
            }
        }
        if(direction==2)
        {
            end++;
            while(count<8)
            {
                if(SensorValue(S3)<45)
                {
                    blacksq++;
                    //store position to array
                    grid[pos1][pos2]='1';
                }
                //increment counters
                count++;
                total++;
                displayBigTextLine(2,"Black:%d",blacksq);
                displayBigTextLine(5,"Count:%d ",count);
                displayBigTextLine(8,"Total:%d",total);
                //move forward one square
                Forward();
                pos2--;
            }
            //Switches to next line
            if(end!=7)
            {
                //Switches to next line
                direction=NextLineRight(direction);
                //Resets count
                count=ResetCount(count);
                pos1++;
            }
        }//end if()
    }//end while()

    //write first file
		checkarray();
    //Goes back to the start function
    GoStart();

    //THIS IS THE SECOND PART OF THE PROGRAM TO MAP THE LOCATION OF THE OBJECT
    //turn right go forward until hit double line go back half a square then turn left (You are at bottom left sq now)
    doubleline=0;
    pause=0;

    while(pause==0)
  	{
      motor(motorB)=SPEED;
  		motor(motorC)=SPEED;
  		wait1Msec(1);

  		if(SensorValue(S3)<45&&doubleline!=1)
  		{
  			if(time1[T1]<200)
  			{
  				pause=1;
  			}
  			doubleline=1;
  	}
  		if(SensorValue(S3)>45&&doubleline==1)
  		{
  			doubleline=0;
  			clearTimer(T1);
  		}
	}
	motor[motorB]=-20;
	motor[motorC]=-20;
	wait1Msec(700);
	LeftTurn();

	motor[motorB]=0;
	motor[motorC]=0;
  wait1Msec(1000);

	//start traversing through grid looking for object
    while(1==1)
    {
    	if(getTouchValue(S2)==1)
    	{
            //reset all values
            pos1=0;
            pos2=0;
            count=0;
            direction=1;
            end=0;
            while(end!=7)
            {
                //traverse right and count lines
                if(direction==1)
                {
                    end++;
                    while(count<8)
                    {
                        //check to see if there is an object
                        if(getUSDistance(S1)<20)
                        {
                        	//if on black
                            if(grid[pos1][pos2]=='1')
                            {
                                colour=1;
                            }
                            //if on white
                            if(grid[pos1][pos2]=='0')
                            {
                                colour=0;
                            }
														//change to j for object
                            grid[pos1][pos2]='J';
                            //write to file2
                            for(int h=6;h>-1;h--)
                            {
                                for(int j=0;j<9;j++)
                                {
                                    fileWriteChar(fileHandle2,grid[h][j]);
                                }
                                //new line
                                fileWriteData(fileHandle2,line1,line2);
                            }
														//write either on black or white
                            if(colour==1)
                            {
                              fileWriteData(fileHandle2,onblack,sizeofblack);
                            }
                            if(colour==0)
                            {
                              fileWriteData(fileHandle2,onwhite,sizeofwhite);
                            }
                            fileClose(fileHandle2);

                            motor[motorB]=0;
                            motor[motorC]=0;
                            wait1Msec(1000000);
                        }
                        //increment counters
                        count++;
                        Forward();
                        pos2++;
                    }

                    //Switches to next line
                    if(end!=7)
                    {
                        direction=NextLineLeft(direction);
                        //Resets count
                        count=ResetCount(count);
                        pos1++;
                    }
                }
                if(direction==2)
                {
                    //check to see if there is an object
                    end++;
                    while(count<8)
                    {
                        if(getUSDistance(S1)<20)
                        {
                            if(grid[pos1][pos2]=='1')
                            {
                                colour=1;
                            }
                            if(grid[pos1][pos2]=='0')
                            {
                                colour=0;
                            }
                            grid[pos1][pos2]='J';
                            //write to file 2
                            for(int h=6;h>-1;h--)
                            {
                                for(int j=0;j<9;j++)
                                {
                                    fileWriteChar(fileHandle2,grid[h][j]);
                                }
                                fileWriteData(fileHandle2,line1,line2);
                            }
                            //write black or white depending on sq it is on
                            if(colour==1)
                            {
                              fileWriteData(fileHandle2,onblack,sizeofblack);
                            }

                            if(colour==0)
                            {
                              fileWriteData(fileHandle2,onwhite,sizeofwhite);
                            }
                            fileClose(fileHandle2);
                            motor[motorB]=0;
                            motor[motorC]=0;

                            wait1Msec(1000000);
                        }
                        //increment counters
                        count++;
                        //move forward one square
                        Forward();
                        pos2--;
                    }
                    //Switches to next line
                    if(end!=7)
                    {
                        //Switches to next line
                        direction=NextLineRight(direction);
                        //Resets count
                        count=ResetCount(count);
                        pos1++;
                    }
                }//end if()
            }//end while()

      }  }//end if()
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
    wait1Msec(1000);
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
        grid[pos1][pos2]='1';
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
    if(SensorValue(S3)<45)
    {
        blacksq++;
        //store position to array
        grid[pos1][pos2]='1';
    }
    total++;
    ForwardSQ();
    RightTurn();
    motor[motorB]=20;
    motor[motorC]=20;
    wait1Msec(2200);
    RightTurn();
    direction=1;
    return(direction);
}//end NextLineRight ()

//Go to the start
void GoStart(void)
{
    int count=0;
    //turn left twice
    LeftTurn();
    LeftTurn();
    //go back 8 squares
    while(count<8)
    {
        //increment counters
        count++;
        Forward();
    }
    //reset current count back to zero
    count=0;
    //turn left
    LeftTurn();
    //go forward 3 squares you are at start
    temp=7-startpos;
    while(count<temp)
    {
        //increment counters
        count++;
        Forward();
    }
     	motor[motorB]=0;
			motor[motorC]=0;
      wait1Msec(1000);
}

//displays the array and writes to a file
void checkarray(void)
{
	string line1='\n';
	int line2=strlen(line1);

	displayTextLine(2,"%c,%c,%c,%c,%c,%c,%c,%c,%c",grid[6][0],grid[6][1],grid[6][2],grid[6][3],grid[6][4],grid[6][5],grid[6][6],grid[6][7],grid[6][8]);
	displayTextLine(3,"%c,%c,%c,%c,%c,%c,%c,%c,%c",grid[5][0],grid[5][1],grid[5][2],grid[5][3],grid[5][4],grid[5][5],grid[5][6],grid[5][7],grid[5][8]);
	displayTextLine(4,"%c,%c,%c,%c,%c,%c,%c,%c,%c",grid[4][0],grid[4][1],grid[4][2],grid[4][3],grid[4][4],grid[4][5],grid[4][6],grid[4][7],grid[4][8]);
	displayTextLine(5,"%c,%c,%c,%c,%c,%c,%c,%c,%c",grid[3][0],grid[3][1],grid[3][2],grid[3][3],grid[3][4],grid[3][5],grid[3][6],grid[3][7],grid[3][8]);
	displayTextLine(6,"%c,%c,%c,%c,%c,%c,%c,%c,%c",grid[2][0],grid[2][1],grid[2][2],grid[2][3],grid[2][4],grid[2][5],grid[2][6],grid[2][7],grid[2][8]);
	displayTextLine(7,"%c,%c,%c,%c,%c,%c,%c,%c,%c",grid[1][0],grid[1][1],grid[1][2],grid[1][3],grid[1][4],grid[1][5],grid[1][6],grid[1][7],grid[1][8]);
	displayTextLine(8,"%c,%c,%c,%c,%c,%c,%c,%c,%c",grid[0][0],grid[0][1],grid[0][2],grid[0][3],grid[0][4],grid[0][5],grid[0][6],grid[0][7],grid[0][8]);
	motor[motorB]=0;
	motor[motorC]=0;
	wait1Msec(1000);

	//write to file
	grid[startpos-1][0]='S';

	for(int h=6;h>-1;h--)
	{
		for(int j=0;j<9;j++)
		{
            fileWriteChar(fileHandle,grid[h][j]);
		}
		fileWriteData(fileHandle,line1,line2);
	}
	fileClose(fileHandle);
}//end check array()

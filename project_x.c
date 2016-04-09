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

//Turn left 90 degrees
void LeftTurn(void);
//Turn right 90 degrees
void RightTurn(void);
//Go Forward
void Forward(void);
//Counts number of squares passed
void Count(void);

task main()
{
    
}


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

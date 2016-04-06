#pragma config(Sensor, S3,     lightSensor,    sensorEV3_Color)
#define TURN 190
task main()
{
int lines=0;
int sense=0;

while(lines<7)
	{
		nMotorEncoder[motorB]=0;
		nMotorEncoder[motorC]=0;
		setMotorTarget(motorB,2415,50);
		setMotorTarget(motorC,2415,50);
		waitUntilMotorStop(motorB);
		waitUntilMotorStop(motorC);

		if(SensorValue(lightSensor)<45)
		{
			sense=1;
		}

		if(SensorValue(lightSensor)>45&&sense==1)
		{
			lines++;
			sense=0;
		}
			displayBigTextLine(4,"crossed %d lines",lines);
	}

	//Move Forward
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
	setMotorTarget(motorB,180,50);
	setMotorTarget(motorC,180,50);
	waitUntilMotorStop(motorB);
	waitUntilMotorStop(motorC);

	//turn left
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
	setMotorTarget(motorB,-TURN,50);
	setMotorTarget(motorC,TURN,50);
	waitUntilMotorStop(motorB);
	waitUntilMotorStop(motorC);

		//Move Forward
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
	setMotorTarget(motorB,180,50);
	setMotorTarget(motorC,180,50);
	waitUntilMotorStop(motorB);
	waitUntilMotorStop(motorC);

	//turn left
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
	setMotorTarget(motorB,-TURN,50);
	setMotorTarget(motorC,TURN,50);
	waitUntilMotorStop(motorB);
	waitUntilMotorStop(motorC);

	lines=0;

	while(lines<7)
	{
		nMotorEncoder[motorB]=0;
		nMotorEncoder[motorC]=0;
		setMotorTarget(motorB,3,50);
		setMotorTarget(motorC,3,50);
		waitUntilMotorStop(motorB);
		waitUntilMotorStop(motorC);

		if(SensorValue(lightSensor)<45)
		{
			sense=1;
		}

		if(SensorValue(lightSensor)>45&&sense==1)
		{
			lines++;
			sense=0;
		}
			displayBigTextLine(4,"crossed %d lines",lines);
	}


}

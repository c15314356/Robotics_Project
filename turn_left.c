#define TURN 190
task main()
{
	//turn left
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
	setMotorTarget(motorB,-TURN,50);
	setMotorTarget(motorC,TURN,50);
	waitUntilMotorStop(motorB);
	waitUntilMotorStop(motorC);


}

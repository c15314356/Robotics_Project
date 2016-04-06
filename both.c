#define TURN 190
task main()
{

	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;

	//right
	setMotorTarget(motorB,TURN,50);
	setMotorTarget(motorC,-TURN,50);

	waitUntilMotorStop(motorB);
	waitUntilMotorStop(motorC);

	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;

	//left
	setMotorTarget(motorB,-TURN,50);
	setMotorTarget(motorC,TURN,50);

		waitUntilMotorStop(motorB);
		waitUntilMotorStop(motorC);


}

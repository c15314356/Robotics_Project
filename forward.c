
task main()
{
	//Move Forward
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
	setMotorTarget(motorB,360,50);
	setMotorTarget(motorC,360,50);
	waitUntilMotorStop(motorB);
	waitUntilMotorStop(motorC);


}

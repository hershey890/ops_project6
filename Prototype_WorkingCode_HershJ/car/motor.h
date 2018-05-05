#ifndef MOTOR_H
#define MOTOR_H

//define the PWM pins that are used - refers to IN from the datasheet
#define PWM1 9
#define PWM2 3
#define PWM3 5
#define PWM4 10

//Digital pins that the EN pins are connected to
#define EN1 6
#define EN2 2

class motor {
public:
	//=========================================================
	//RIGHT MOTOR
	//=========================================================
	void rightForward(signed char value); // Moves the 'right' motor forward by a value 0 - 255
	void rightBackward(signed char value); 	//Moves the 'right' motor backward by a value 0-255
	void rightCoast(); //Makes the right motor 'coast' or unabruptly slow to a stop
	void rightStop(); //forces the right motor to stop

	//=========================================================
	//LEFT MOTOR
	//=========================================================
	void leftForward(signed char value);
	void leftBackward(signed char value);
	void leftCoast();
	void leftStop();
};

#endif

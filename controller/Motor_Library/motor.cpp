#include "motor.h"
#include "arduino.h"

//==================================================
//RIGHT MOTOR
//==================================================
void motor::rightForward(signed char value) {
	digitalWrite(EN2, HIGH);
	analogWrite(PWM3, LOW);
	analogWrite(PWM4, value);
}

void motor::rightBackward(signed char value) {
	digitalWrite(EN2, HIGH);
	analogWrite(PWM3, value);
	analogWrite(PWM4, LOW);
}

void motor::motor::rightCoast() {
	digitalWrite(EN2, LOW);
	analogWrite(PWM3, HIGH);
	analogWrite(PWM4, HIGH);
}

void motor::rightStop() {
	digitalWrite(EN2, HIGH);
	analogWrite(PWM3, HIGH);
	analogWrite(PWM4, HIGH);
}

//==================================================
//LEFT MOTOR
//==================================================
void motor::leftForward(signed char value) {
	digitalWrite(EN1, HIGH);
	analogWrite(PWM1, LOW);
	analogWrite(PWM2, value);
}

void motor::leftBackward(signed char value) {
	digitalWrite(EN1, HIGH);
	analogWrite(PWM1, value);
	analogWrite(PWM2, LOW);
}

void motor::leftCoast() {
	digitalWrite(EN1, LOW);
	analogWrite(PWM1, HIGH);
	analogWrite(PWM2, HIGH);
}

void motor::leftStop() {
	digitalWrite(EN1, HIGH);
	analogWrite(PWM1, HIGH);
	analogWrite(PWM2, HIGH);
}

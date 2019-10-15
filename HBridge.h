/**
 * @file HBridge.h
 * @brief Class for H-bridge control via Arduino and Mbed platforms
 * @author Dan Oates (WPI Class of 2020)
 * 
 * H-bridges are used primarily to bidirectionally drive DC motors. This class
 * controls H-bridges via three control lines:
 * 
 * - pwm: PWM output to control duty cycle (connect to enable line)
 * - fwd: Forward enable digital output
 * - rev: Reverse enable digital output
 * 
 * Braking is done by writing both the fwd and rev lines low.
 * 
 * Dependencies:
 * - Platform: https://github.com/doates625/Platform.git
 * - DigitalOut: https://github.com/doates625/DigitalOut.git
 * - PwmOut: https://github.com/doates625/PwmOut.git
 * - CppUtil: https://github.com/doates625/CppUtil.git
 * 
 * References:
 * - H-Bridges: https://en.wikipedia.org/wiki/H_bridge
 */
#pragma once
#include <PwmOut.h>
#include <DigitalOut.h>

/**
 * Class Declaration
 */
class HBridge
{
public:
	HBridge(PwmOut* pwm, DigitalOut* fwd, DigitalOut* rev, float vcc);
	void set_voltage(float v_cmd);
	void brake();
protected:
	PwmOut* pwm;
	DigitalOut* fwd;
	DigitalOut* rev;
	float vcc, vcc_inv;
};
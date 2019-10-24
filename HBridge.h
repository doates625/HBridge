/**
 * @file HBridge.h
 * @brief Class for H-bridge control for Arduino and Mbed
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <DigitalOut.h>
#include <PwmOut.h>

/**
 * Class Declaration
 */
class HBridge
{
public:
	HBridge(PwmOut* pwm, DigitalOut* fwd, DigitalOut* rev, float vcc);
	HBridge(
		Platform::pin_t pin_pwm,
		Platform::pin_t pin_fwd,
		Platform::pin_t pin_rev,
		float vcc);
	~HBridge();
	void set_voltage(float v_cmd);
	void brake();
protected:
	PwmOut* pwm;
	DigitalOut* fwd;
	DigitalOut* rev;
	float vcc, vcc_inv;
	bool dynamic_io;
};
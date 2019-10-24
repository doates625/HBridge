/**
 * @file HBridge.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "HBridge.h"
#include <CppUtil.h>
using Platform::pin_t;

/**
 * @brief Constructs H-bridge interface
 * @param pwm PWM output (wire to H-bridge enable)
 * @param fwd Forward enable output
 * @param rev Reverse enable output
 * @param vcc Supply voltage [V]
 */
HBridge::HBridge(PwmOut* pwm, DigitalOut* fwd, DigitalOut* rev, float vcc)
{
	this->pwm = pwm;
	this->fwd = fwd;
	this->rev = rev;
	this->vcc = vcc;
	this->vcc_inv = 1.0f / vcc;
	this->dynamic_io = false;
}

/**
 * @brief Constructs H-bridge interface
 * @param pin_pwm ID of pwm output pin
 * @param pin_fwd ID of forward enable output
 * @param pin_rev ID of reverse enable output
 * @param vcc Supply voltage [V]
 * 
 * This constructor dynamically allocates the IO interfaces and deletes them
 * on destruction.
 */
HBridge::HBridge(pin_t pin_pwm, pin_t pin_fwd, pin_t pin_rev, float vcc) :
HBridge(
	new PwmOut(pin_pwm),
	new DigitalOut(pin_fwd),
	new DigitalOut(pin_rev),
	vcc)
{
	this->dynamic_io = true;
}

/**
 * @brief Destructs H-bridge object
 * 
 * Deletes IO interfaces if they were created with dynamic memory.
 */
HBridge::~HBridge()
{
	if (dynamic_io)
	{
		delete pwm;
		delete fwd;
		delete rev;
	}
}

/**
 * @brief Sets H-bridge output voltage via PWM
 * @param v_cmd Voltage command in range [-vcc, +vcc]
 * 
 * Note: Commands out of range are automatically saturated.
 */
void HBridge::set_voltage(float v_cmd)
{
	v_cmd = CppUtil::clamp(v_cmd, -vcc, +vcc);
	pwm->write(fabsf(v_cmd) * vcc_inv);
	if (v_cmd > 0.0f)
	{
		fwd->write(1);
		rev->write(0);
	}
	else if (v_cmd < 0.0f)
	{
		fwd->write(0);
		rev->write(1);
	}
	else
	{
		fwd->write(0);
		rev->write(0);
	}
}

/**
 * @brief Brakes H-bridge (disconnects both sides)
 */
void HBridge::brake()
{
	pwm->write(0.0f);
	fwd->write(0);
	rev->write(0);
}
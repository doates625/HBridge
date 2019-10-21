/**
 * @file HBridge.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "HBridge.h"
#include <CppUtil.h>

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
#pragma once
#include "types.h"

// Simple Proportional-Derivative (PD) attitude controller
class AttitudeController {
public:
    AttitudeController(double kp = 0.5, double kd = 1.2); // kp ~ proportional gain (how far off), kd ~ derivative gain (how fast)
    ControlTorque compute(const AttitudeState &current, const AttitudeCommand &command) const;

private:
    double kp_; // proportional gain
    double kd_; // derivative (rate) gain
};
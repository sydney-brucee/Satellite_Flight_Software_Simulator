#include "controller.h"
#include <cmath>

namespace {
    // Wrap angle to [-pi, pi]
    double wrap_to_pi(double angle) {
        const double pi = 3.14159265358979323846;
        angle = std::fmod(angle + pi, 2.0 * pi);
        if (angle < 0) angle += 2.0 * pi;
        return angle - pi;
    }
}

AttitudeController::AttitudeController(double kp, double kd) : kp_(kp), kd_(kd) {}

ControlTorque AttitudeController::compute(const AttitudeState &current, const AttitudeCommand &command) const {
    ControlTorque torque;

    // Attitude error wrapped to shortest path [-pi, pi]
    double err_roll = wrap_to_pi(command.roll - current.roll);
    double err_pitch = wrap_to_pi(command.pitch - current.pitch);
    double err_yaw = wrap_to_pi(command.yaw - current.yaw);

    // Proportional-Derivative control: torque = Kp * error - Kd * rate
    // kp tries to correct pointing error, kd tries to dampen oscillations
    torque.roll = kp_ * err_roll - kd_ * current.roll_rate;
    torque.pitch = kp_ * err_pitch - kd_ * current.pitch_rate;
    torque.yaw = kp_ * err_yaw - kd_ * current.yaw_rate;

    // PD control: torque = kp * error - kd * rate
    torque.roll = kp_ * err_roll - kd_ * current.roll_rate;
    torque.pitch = kp_ * err_pitch - kd_ * current.pitch_rate;
    torque.yaw = kp_ * err_yaw - kd_ * current.yaw_rate;

    return torque;
}
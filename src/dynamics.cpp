#include "dynamics.h"

AttitudeDynamics::AttitudeDynamics(double Ix, double Iy, double Iz) : Ix_(Ix), Iy_(Iy), Iz_(Iz) {}

AttitudeState AttitudeDynamics::step(const AttitudeState &state, const ControlTorque &torque, double dt) {
    AttitudeState next = state;

    // Angular acceleration = torque / inertia
    double alpha_roll = torque.roll / Ix_;
    double alpha_pitch = torque.pitch / Iy_;
    double alpha_yaw = torque.yaw / Iz_;

    // Integrate steps
    next.roll_rate += alpha_roll * dt;
    next.pitch_rate += alpha_pitch * dt;
    next.yaw_rate += alpha_yaw * dt;

    // Integrate angles
    next.roll += next.roll_rate * dt;
    next.pitch += next.pitch_rate * dt;
    next.yaw += next.yaw_rate * dt;

    return next;
}
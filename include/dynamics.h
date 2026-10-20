#pragma once
#include "types.h"

// Simple rigid-body attitude dynamics (diagonal inertia,  no products of inertia)
class AttitudeDynamics {
public:
    AttitudeDynamics(double Ix = 10.0, double Iy = 12.0, double Iz = 8.0);

    // Integrating one time step (Euler integration)
    AttitudeState step(const AttitudeState &state, const ControlTorque &torque, double dt);

private:
// Principal moments of intertia
    double Ix_, Iy_, Iz_;
};
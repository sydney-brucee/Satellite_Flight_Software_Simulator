#pragma once

// Simple 3-axis attitude state (radians and radians/second)
struct AttitudeState {
    double roll;  // radians
    double pitch; // radians
    double yaw;   // radians
    double roll_rate;  // radians/second
    double pitch_rate; // radians/second
    double yaw_rate;   // radians/second
};

// Desired/commanded attitude (radians)
struct AttitudeCommand {
    double roll;
    double pitch;
    double yaw;
};

// Control output (torques in Newton * meters)
struct ControlTorque {
    double roll;
    double pitch;
    double yaw;
};
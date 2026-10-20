#include "types.h"
#include "controller.h"
#include "dynamics.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]) {
    // Default gains are set to hyperparams
    // kp=54, kd=41
    double kp = 54;
    double kd = 41;

    if (argc == 3) {
        kp = atof(argv[1]);
        kd = atof(argv[2]);
    } else {
        cout << "Using default gains: kp=" << kp << ", kd=" << kd << endl;
        cout << "To specify gains, run: ./simulator <kp> <kd>" << endl;
    }
    cout << "Using kp=" << kp << ", kd=" << kd << endl;

    AttitudeDynamics dynamics;
    AttitudeController controller(kp, kd); // Raised gains

    // Initial state (slightly off from target)
    // Test larger values (e.g. 2.5, -1.8, 3.0) to see more angle wrapping
    //AttitudeState state{0.5, -0.2, 0.1, 0.3, 1.0, 0.6};
    AttitudeState state{0.3, -0.2, 0.1, 0.0, 0.0, 0.0};

    // Desired attitude (point "straight")
    AttitudeCommand command{0.0, 0.0, 0.0};

    const double dt = 0.01; // 10ms time step
    const double sim_time = 30.0; // seconds
    const int steps = static_cast<int>(sim_time / dt);

    // Random noise generator for simulating sensor noise
    mt19937 rng(42); // Fixed seed
    normal_distribution<double> angle_noise(0.0, 0.03); // radians...started 0.01
    normal_distribution<double> rate_noise(0.0,0.015); // radians/sec...started 0.005

    ofstream log("telemetry.csv");
    log << "time,roll,pitch,yaw,roll_rate,pitch_rate,yaw_rate\n";


    for (int i = 0; i < steps; i++) {
        double time = i * dt;

        // Noisy measurements
        AttitudeState noisy_state = state;
        noisy_state.roll += angle_noise(rng);
        noisy_state.pitch += angle_noise(rng);
        noisy_state.yaw += angle_noise(rng);
        noisy_state.roll_rate += rate_noise(rng);
        noisy_state.pitch_rate += rate_noise(rng);
        noisy_state.yaw_rate += rate_noise(rng);

        // Controller sees noisy state
        ControlTorque torque = controller.compute(noisy_state, command);
        // Dynamics see true state
        state = dynamics.step(state, torque, dt);

        // Log every 0.1 seconds
        if (i % 10 == 0) {
            log << time << "," << state.roll << "," << state.pitch << "," << state.yaw << "," 
            << state.roll_rate << "," << state.pitch_rate << "," << state.yaw_rate << "\n";
        }
    }
    
    log.close();
    cout << "Simulation complete. Telemetry written to 'telemetry.csv'\n";
    cout << "Final attitude: roll=" << state.roll << "," << ", pitch=" << state.pitch << ", yaw=" << state.yaw << endl;

    return 0;
}
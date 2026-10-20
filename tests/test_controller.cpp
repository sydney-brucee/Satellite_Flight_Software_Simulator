#include "controller.h"
#include <cassert>
#include <cmath>
#include <iostream>
using namespace std;

int main() {
    AttitudeController controller(1.0, 0.5);

    AttitudeState current{0.2, 0.0, 0.0, 0.1, 0.0, 0.0};
    AttitudeCommand command {0.0, 0.0, 0.0};

    ControlTorque torque = controller.compute(current, command);

    // Expected: err_roll = wrap(0 - 0.2) = -0.2
    // torque.roll = 1.0 * (-0.2) - 0.5 * 0.1 = -0.2 - 0.05 = -0.25
    double expected_roll = -0.25;
    assert(abs(torque.roll - expected_roll) < 1e-6);
    
    std::cout << "Controller unit test passed\n";
    return 0;
}
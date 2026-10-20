""" Simple hyperparameter tuning script for the attitude controller (kp and kd). Runs the C++ simulation multiple times and scores settling performance. Requires: attitude_sim.exe already built """

import subprocess
import pandas as pd
import numpy as np
from pathlib import Path

project_root = Path(__file__).parent.parent
EXE = project_root / "attitude_sim.exe"
CSV = project_root / "telemetry.csv"

def run_simulation(kp: float, kd: float) -> float:
    """ Run the simulation with given gains and return a simple cost (lower is better) """
    result = subprocess.run([str(EXE), str(kp), str(kd)], capture_output=True, text=True)
    if result.returncode != 0:
        return 1e6 # high cost for failures

    df = pd.read_csv(CSV)
    # Cost: integral of absolute error + penalty if it doesn't settle
    error = np.abs(df["roll"]) + np.abs(df["pitch"]) + np.abs(df["yaw"])
    cost = error.sum() * 0.1 # scaling
    # Penalizing big rates (oscillation vs control)
    rate_cost = (np.abs(df["roll_rate"]) + np.abs(df["pitch_rate"]) + np.abs(df["yaw_rate"])).mean()
    cost+= 5.0 * rate_cost
    final_error = error.iloc[-1]
    if final_error > 0.05:
        cost += 100 # penalty for not settling
    return cost

def grid_search():
    kp_values = [i * 0.5 for i in range(80,150)]
    kd_values = [i * 0.5 for i in range(60,150)]

    best_cost = float('inf')
    best_params = None

    print("Running grid search over kp and kd values...")
    for kp in kp_values:
        for kd in kd_values:
            #print("Calling:", [str(EXE), str(kp), str(kd)])
            cost = run_simulation(kp, kd)
            print(f"kp={kp:.1f}, kd={kd:.1f} => cost={cost:.2f}")
            if cost < best_cost:
                best_cost = cost
                best_params = (kp, kd)
    print(f"\nBest (demo): kp={best_params[0]:.1f}, kd={best_params[1]:.1f} => cost={best_cost:.2f}")

if __name__ == "__main__":
    grid_search()
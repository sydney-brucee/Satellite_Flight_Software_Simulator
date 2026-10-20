""" Plotting the attitude simulation results. """
import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

project_root = Path(__file__).parent.parent
df = pd.read_csv(project_root / "telemetry.csv")

fig, axes = plt.subplots(2, 1, figsize =(10, 6), sharex=True)

 # Top plot for roll, pitch, and yaw
axes[0].plot(df["time"], df["roll"], label="roll", color="blue")
axes[0].plot(df["time"], df["pitch"], label="pitch", color="red")
axes[0].plot(df["time"], df["yaw"], label="yaw", color="orange")
axes[0].set_ylabel("Attitude (rad)")
axes[0].legend()
axes[0].grid(True)

# Bottom plot for angular velocities
axes[1].plot(df["time"], df["roll_rate"], label="roll_rate", color="dodgerblue")
axes[1].plot(df["time"], df["pitch_rate"], label="pitch_rate", color="salmon")
axes[1].plot(df["time"], df["yaw_rate"], label="yaw_rate", color="gold")
axes[1].set_ylabel("Rate (rad/s)")
axes[1].set_xlabel("Time (s)")
axes[1].legend()
axes[1].grid(True)

# Plotting
plt.tight_layout()
plt.savefig(project_root/"python/attitude_response.png", dpi=300)
print("Saved attitude_response.png")
plt.show()
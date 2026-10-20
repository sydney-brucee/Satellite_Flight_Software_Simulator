# Build script
g++ -std=c++17 -Iinclude src/*.cpp -o attitude_sim.exe

# Running the simulator without tuning (to run with tuning hash this and unhash tuning section)

 if ($LASTEXITCODE -eq 0) {
    Write-Host "Build successful. Running the simulator..."
    .\attitude_sim.exe
} else {
    Write-Host "Build failed. Please refer to error messages above for details."
}

# In terminal run .\build.ps1 to build and run the simulator.
#Write-Host "Running hyperparameter tuning..."
#python .\python\tune_gains.py
#if ($LASTEXITCODE -eq 0) {
#    Write-Host "Tuning finished."
#} else {
#    Write-Host "Tuning failed."
#}


# Unhash below to also run plotting script after simulator runs.
python .\python\plot_results.py
if ($LASTEXITCODE -eq 0) {
    Write-Host "Plotting successful. Png saved to plots folder."
} else {
    Write-Host "Plotting failed. Please refer to error messages above for details."
}
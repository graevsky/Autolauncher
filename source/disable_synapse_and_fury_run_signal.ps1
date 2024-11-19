try {
    Write-Host "Shutting down signal rgb"
    Get-Process -Name "SignalRgb" -ErrorAction SilentlyContinue | Stop-Process -Force

    Write-Host "Shutting down Razer Synapse and Fury ctrl"
    Get-Process -Name "Synapse" -ErrorAction SilentlyContinue | Stop-Process -Force
    Get-Process -Name "FuryControllerService" -ErrorAction SilentlyContinue | Stop-Process -Force

    Write-Host "Synapse and fury disabled, waiting 5 seconds"
    Start-Sleep -Seconds 5
    Write-Host "Starting signalrgb"
    Start-Process -FilePath "C:\Users\graev\AppData\Local\VortxEngine\SignalRgbLauncher.exe" -WorkingDirectory "C:\Users\graev\AppData\Local\VortxEngine"

    Write-Host "Signal rbg started"

} catch {
    Write-Host "Error: $($_.Exception.Message)"
}

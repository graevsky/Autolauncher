try {
    Write-Host "Shutting down all deej.exes"
    Get-Process -Name "deej" -ErrorAction SilentlyContinue | Stop-Process -Force

    $device = Get-PnpDevice -InstanceId "FTDIBUS\VID_0403+PID_6001+FTB6SPL3A\0000" # USB com 3

    if ($device) {
        Write-Host "Device found: $($device.FriendlyName)"
        Write-Host "InstanceId: $($device.InstanceId)"
        Write-Host "Status: $($device.Status)"

        if ($device.Status -eq "OK") {
            Write-Host "Shutting down device..."
            Disable-PnpDevice -InstanceId $device.InstanceId -Confirm:$false
        } else {
            Write-Host "Device already disabled"
        }

        Write-Host "Status: $($device.Status), waiting for 10 secs"
        Start-Sleep -Seconds 10

        Write-Host "Starting up"
        Enable-PnpDevice -InstanceId $device.InstanceId -Confirm:$false

        Start-Sleep -Seconds 5

        $deviceAfterEnable = Get-PnpDevice -InstanceId $device.InstanceId

        if ($deviceAfterEnable.Status -eq "OK") {
            Write-Host "Device enabled"
            Write-Host "Starting deej"
            Start-Process -FilePath "E:\deej\deej.exe" -WorkingDirectory "E:\deej"
        } else {
            Write-Host "Device cannot be enabled"
        }

        Write-Host "Done"
    } else {
        Write-Host "Device not found"
    }
} catch {
    Write-Host "Error: $($_.Exception.Message)"
}

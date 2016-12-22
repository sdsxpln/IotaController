# IotaController 

Drone controller designed to act as the simple controller in the Simplex
Architecture.

## Features
- Implement a Server for a DeadManSwitch. The DeadManSwitch is the client which
has to always answer to the pings from the IotaController. If the DeadmanSwitch, or underlying network has any issues, the IotaController deactivates the drone under control
- kills the DragonController (Bebop) if the IotaController does not detect a presence of a DeadmanSwitch response within a configured time in milliseconds
- Listens at port 8995 to replies from the DeadmanSwitch

## Configuration
The configuration is given via command line parameters
- IP address of the DeadmanSwitch
- time (in milliseconds) to wait for a reply and de-active drone under control


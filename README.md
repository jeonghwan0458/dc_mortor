# Wireless-record-with-Matrix-Creator

## **Installation Matrix Setup from packages**
```bash
curl https://apt.matrix.one/doc/apt-key.gpg | sudo apt-key add -
echo "deb https://apt.matrix.one/raspbian $(lsb_release -sc) main" | sudo tee /etc/apt/sources.list.d/matrixlabs.list

sudo apt-get update
sudo apt-get upgrade
sudo apt-get install matrixio-creator-init libmatrixio-creator-hal libmatrixio-creator-hal-dev
sudo reboot
```
- MATRIX HAL header files are installed in /usr/include/matrix_hal
- The compiled MATRIX HAL library file is installed in /usr/lib/libmatrix_creator_hal.so.


##  **i2c set up for UPS HAT**
```bash
sudo apt install i2c-tools
sudo apt install libi2c-dev

# scan an i2c bus for devices 
sudo i2cdetect -y 1 

# check an i2c bus device number
# default: /dev/i2c-1
# please change it in the server.cpp, if one has a different device number
ls -al /dev/i2c*
```

##  **Sequence diagram for TCP/IP, i2c and mic. data read**
![Sequence diagram](doc/SequenceDiagram/WirelessMicrophoneArray.png)

##  **Test setup**
1. **Server[^1]**: execute the following commands 
```bash
make clean
make server
./build/server
```
2. **Client[^2]**: change the ip-address in the code according to your server's one and execute the following commands 
```bash
make clean
make client
# When client is running, Matrix LED shows a status of battery capacity
# -m flag: record the data for 30 seconds
cd build
./client -m 30
```
3. **Client**: one should find out *.raw files under ./build/client
4. **Client**: execute the following script in the console, in order to covert *.raw to *.wav files
```bash
# install sox, when it is not installed
sudo apt install sox

chmod a+x raw2wav.sh
./raw2wav.sh
```
5. **Client**: open the created 8 *.wav files in Audacity

##  **How to execute the server program at RPi booting**
1. Execute the following commands 
```bash
cd /home/pi/.config/autostart
touch ServerMatrixCreator.desktop
```
2. Add the following texts in the above *ServerMatrixCreator.desktop* file
```bash
[Desktop Entry]
Type=Application
Name=ServerMatrixCreator
Exec= # Add a location of your executable
```
3. Reboot
```bash
sudo reboot
```
4. Check if the server is running
```bash
ps -e | grep server
```
##  **How to execute the server program at RPi booting and to re-launch at crash**
[Auto-Starting Programs on the Raspberry Pi](https://thepihut.com/blogs/raspberry-pi-tutorials/auto-starting-programs-on-the-raspberry-pi)
1. Edit the service file
```bash
sudo geany /lib/systemd/system/wirelessMatrix.service
```
2. Add the following texts in the above *wirelessMatrix.service* file
```bash
[Unit]
Description=Wireless matrix Service
After=multi-user.target

[Service]
Type=idle

User=pi
ExecStart=# Add a location of your executable

Restart=always
RestartSec=0

[Install]
WantedBy=multi-user.target
```
3. Enable it in systemctrl and Reboot
```bash
sudo chmod 644 /lib/systemd/system/wirelessMatrix.service
sudo systemctl daemon-reload
sudo systemctl enable wirelessMatrix.service
sudo reboot
```
4. Check if *wirelessMatrix.service* is running
```bash
sudo systemctl status wirelessMatrix.service
```
5. Crash it and check if it is re-launched
```bash
ps -e | grep server
kill -9 pid # pid of "server" program
ps -e | grep server
```

[^1]: server was tested in RPi3B+ with Matrix and UPS HAT
[^2]: client was tested at Ubuntu 18.04 and RPi4

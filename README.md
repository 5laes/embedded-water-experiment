Setup:
install python 3.10 or later
to establish a serial connection with esp32 you need 2 drivers (https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/establish-serial-connection.html) follow this guide 
recursive clone esp-idf repo (https://github.com/espressif/esp-idf)
execute the install.sh in the repo (. ./install.sh)
create a projects dir in esp-idf repo
clone this repo in the projects dir
cd to esp-idf
execute export.sh (. ./export.sh)
cd to this project
run idf.py build
run idf.py -p (usp-port) flash (when "connection..." shows in the terminal hold down "boot" button on board)
run idf.py monitor (when "connection..." shows in the terminal hold down "boot" button on board)

You obviously need a ESP32 board to be able to try this your self.

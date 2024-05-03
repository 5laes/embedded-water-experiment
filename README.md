Setup:

1. install python 3.10 or later.

2. to establish a serial connection with esp32 you need 2 drivers (https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/establish-serial-connection.html) follow this guide.

3. recursive clone esp-idf repo (https://github.com/espressif/esp-idf).

4. execute the install.sh in the repo (. ./install.sh) yes the "." before "./" is needed.

5. create a projects dir in esp-idf repo.

6. clone this repo in the projects dir.

7. cd to esp-idf.

8. execute export.sh (. ./export.sh (. ./install.sh) yes the "." before "./" is needed.

9. cd to this project.

10. run idf.py build.

11. run idf.py -p (usp-port) flash (when "connection..." shows in the terminal hold down "boot" button on board).

12. run idf.py monitor (when "connection..." shows in the terminal hold down "boot" button on board).

You obviously need a ESP32 board to be able to try this your self.

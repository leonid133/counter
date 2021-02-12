# counter
atmega328p decimal counter


Raspberry Pi as a programmer
OS(Raspbian)

install dependency
```
sudo apt-get install gcc-avr avr-libc avrdude
```
RPI GPIO 
```
RESET = 22
SCK   = 11
MOSI  = 10
MISO  = 9
```
MCU GPIO
```
RESET = PC6 = 1
SCK = PB5 = 19
MOSI = PB3 = 17
MISO = PB4 = 18

```

unexport gpio if busy
```
echo 17 > /sys/class/gpio/unexport
```

upload to mcu
```
make test
make build
make flash
```

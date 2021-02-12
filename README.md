# counter
atmega328p decimal counter

Raspberry Pi as a programmer
OS(Raspbian)

![schema](https://github.com/leonid133/counter/blob/main/Schematic_counter_2021-02-12_15-04-05.png?raw=true)

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
echo 22 > /sys/class/gpio/unexport
```

upload to mcu
```
make test
make build
make flash
```

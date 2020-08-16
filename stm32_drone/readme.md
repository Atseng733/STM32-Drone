I attempt to program a drone in bare-metal c++ by writing my own drivers for GPIO(blinking LEDs and external pin-change interrupts), I2C(communication between microcontroller and MPU9250 gyro/accelerometer), timers(systick and peripheral), UART(debugging and receiving data from the transmitter).

Parts Used (so far):
  Microcontroller: stm32f103c8t
  IMU: MPU9250
  Receiver: Flysky Fli14+ (data received through iBUS serial protocol)
  Transmitter: FlySky FS-i6 

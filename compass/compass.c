#include <stdio.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <time.h>
#include <stdint.h>

int32_t main()
{
  printf("**** compass test program ****\r\n");
  int32_t handle;
  int8_t *i2c_bus = "/dev/i2c-0";
  int32_t  address = 0x1E;
  uint8_t buf[10], x, y, z;
  int32_t out;
  if ((handle = open(i2c_bus, O_RDWR)) < 0) {
    printf("this did not work at all\r\n");
}
  if (ioctl(handle, I2C_SLAVE, address) < 0) {
    printf("error initializing i2c bus\r\n");
}
    buf[0] = 0x3C;
    buf[1] = 0x00;
    buf[2] = 0x70;
  if ((write(handle, buf, 3)) != 3) {
    printf("error 1: unable write to i2c slave \r\n");
}
    buf[0] = 0x3C;
    buf[1] = 0x00;
    buf[2] = 0xA0;
  if ((write(handle, buf, 3)) != 3) {
    printf("error 2: unable to write to i2c slave \r\n");
}
    buf[0] = 0x02;
    buf[1] = 0x01;
  if ((write(handle, buf, 2)) != 2) {
    printf("error 3: unable to write to i2c slave \r\n");
}
     usleep(500000);
     buf[0] = 0x03;
  if ((write(handle, buf, 1)) != 1) {
    printf("error 4: unable to write to i2c slave \r\n");
}
  if (read(handle, buf, 6) != 6) {
    printf("error 5: unable to read from slave \r\n");
}
  else {
    x = (buf[0] << 8) | buf[1];
    y = (buf[2] << 8) | buf[3];
    z = (buf[4] << 8) | buf[5];
    printf("x: %u \r\n",  x );
    printf("y: %u \r\n",  y );
    printf("z: %u \r\n",  z );
}
  return 0;
}

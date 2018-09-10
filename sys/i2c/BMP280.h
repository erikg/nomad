#ifndef BMP280
#define BMP280

int BMP280_init(int bus, uint8_t address, int mode);

float BMP280_get_temperature(int handle);
float BMP280_get_pressure(int handle);

int BMP280_shutdown(int handle);

#endif

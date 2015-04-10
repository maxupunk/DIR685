#ifndef __I2C_ALPHA__
#define __I2C_ALPHA__

#define I2C_ALPHA_IOC_MAGIC		'i'
#define I2C_ALPHA_WRITE			_IO(I2C_ALPHA_IOC_MAGIC, 0)
#define I2C_ALPHA_READ			_IO(I2C_ALPHA_IOC_MAGIC, 1)
#define I2C_ALPHA_WRITE_NO_SUBADDR	_IO(I2C_ALPHA_IOC_MAGIC, 2)
#define I2C_ALPHA_READ_NO_SUBADDR	_IO(I2C_ALPHA_IOC_MAGIC, 3)
#define I2C_ALPHA_ENABLE		_IO(I2C_ALPHA_IOC_MAGIC, 4)
#define I2C_ALPHA_DISABLE		_IO(I2C_ALPHA_IOC_MAGIC, 5) 
#define I2C_ALPHA_READ_TP_KEY	_IO(I2C_ALPHA_IOC_MAGIC, 6) 
#define I2C_ALPHA_IOC_MAXNR 10

struct i2c {
	unsigned char SlaveAddress;
	unsigned char SubAddress;
	unsigned char *Data;
	unsigned int n;
};


void gpio_setdirection(int gpio, int dir);
int gpio_read(int gpio);
void gpio_write(int gpio, int data);

int I2C_Write(unsigned char SlaveAddress, unsigned char SubAddress, unsigned char *data, unsigned int n);
int I2C_Read(unsigned char SlaveAddress, unsigned char SubAddress, unsigned char *data, unsigned int n);
int I2C_Write_NoSubAddress(unsigned char SlaveAddress, unsigned char *data, unsigned int n);
int I2C_Read_NoSubAddress(unsigned char SlaveAddress, unsigned char *data, unsigned int n);
int I2C_Device_Detect(unsigned char SlaveAddress);

#endif // __I2C_ALPHA__

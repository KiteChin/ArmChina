#include "QN8027.h"

static void i2c_start(void)
{
    Delay_us(10);
    QN8027_SCL(1);
    QN8027_SDA(1);
    Delay_us(10);
    QN8027_SDA(0);
    Delay_us(10);
    QN8027_SCL(0);
    Delay_us(10);
}
static void i2c_stop(void)
{
    QN8027_SCL(1);
    QN8027_SDA(0);
    Delay_us(10);
    QN8027_SDA(1);
    Delay_us(10);
}

//0---ack 1---nack
static uint8_t i2c_wait_ack(void)
{
    uint8_t ack = 0;
    QN8027_SDA(1); //释放SDA
    Delay_us(10);
    QN8027_SCL(1);
    Delay_us(10);
    if(QN8027_SDA_READ())
        ack = 1;
    else
        ack = 0;
    QN8027_SCL(0);
    Delay_us(10);
    return ack;
}
static void i2c_ack(void)
{
	QN8027_SDA(0);	/* CPU驱动SDA = 0 */
	Delay_us(10);
	QN8027_SCL(1);	/* CPU产生1个时钟 */
	Delay_us(10);
	QN8027_SCL(0);
	Delay_us(10);
	QN8027_SDA(1);	/* CPU释放SDA总线 */
}

static void i2c_nack(void)
{
	QN8027_SDA(1);	/* CPU驱动SDA = 1 */
	Delay_us(10);
	QN8027_SCL(1);	/* CPU产生1个时钟 */
	Delay_us(10);
	QN8027_SCL(0);
	Delay_us(10);
}


void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			QN8027_SDA(1);
		}
		else
		{
			QN8027_SDA(0);
		}
		Delay_us(10);
		QN8027_SCL(1);
		Delay_us(10);	
		QN8027_SCL(0);
		if (i == 7)
		{
			 QN8027_SDA(1); // 释放总线
		}
		_ucByte <<= 1;	/* 左移一个bit */
		Delay_us(10);
	}
}

uint8_t i2c_ReadByte(void)
{
	uint8_t i;
	uint8_t value;

	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		QN8027_SCL(1);
		Delay_us(10);
		if (QN8027_SDA_READ())
		{
			value++;
		}
		QN8027_SCL(0);
		Delay_us(10);
	}
	return value;
}

static uint8_t i2c_write_byte(uint8_t slave_addr, uint8_t reg_addr, uint8_t data)
{

    for(int i = 0; i < 10; i++)
    {
        i2c_start();
        i2c_SendByte(slave_addr);
        if(i2c_wait_ack() == 0)
            break;
        if(i == 9) return 0;
    }
    for(int i = 0; i < 10; i++)
    {
        i2c_SendByte(reg_addr);
        if(i2c_wait_ack() == 0)
            break;
        if(i == 9) return 0;
    }
    for(int i = 0; i < 10; i++)
    {
        i2c_SendByte(data);
        if(i2c_wait_ack() == 0)
            break;
        if(i == 9) return 0;       
    }
    return 1;
}

void QN8027_Init(void)
{
    i2c_write_byte(0x58, 0x00, 0x31);
    i2c_write_byte(0x58, 0x01, 0xC2);
    i2c_write_byte(0x58, 0x02, 0xB9);
    i2c_write_byte(0x58, 0x03, 0x80);
    i2c_write_byte(0x58, 0x04, 0xB2);
    i2c_write_byte(0x58, 0x10, 0x32);
    i2c_write_byte(0x58, 0x11, 0x81);
}


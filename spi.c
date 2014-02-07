#include<reg51.h>
#include<intrins.h>
#include "main.h"

sbit SCK=P2^4;
sbit SDO=P2^5;
sbit SDI=P2^6;
sbit CS =P2^7;

#define READ  0x03
#define WRITE 0x02
#define WREN  0x06
#define WRDI  0x04
#define RDSR  0x05
#define WRSR  0x01

void delay(void)
{
	_nop_();_nop_();
	_nop_();_nop_();
}

void init_SPI(void)
{
	CS=1;
	delay();
	SCK=1;
	delay();
	SDO=1;
	delay();
	SDI=1;
	delay();
}

uchar SPI_read_byte(void)
{
	uchar i;
	uchar dat=0x00;
	SCK=0;
	for(i=0;i<8;i++)
	{
		SCK=0;
		delay();
		SCK=1;
		delay();
		dat <<= 1;
		dat |= (uchar)SDI;
	}
	return(dat);
}

void SPI_write_byte(uchar dat)
{
	uchar i;
	SCK=0;
	for(i=0;i<8;i++)
	{
		SDO= (bit)(dat&0x80);
		SCK=0;
		delay();
		SCK=1;
		delay();
		dat<<=1;
	}
}

void write_SPI(uchar dat,uchar addr)
{
	SCK=0;
	CS=0;
	delay();
	SPI_write_byte(WREN);
	CS=1;
	delay();
	CS=0;
	delay();
	SPI_write_byte(WRITE);
	SPI_write_byte(addr);
	SPI_write_byte(dat);
	CS=1;
	SCK=0;
}

uchar read_SPI(uchar addr)
{
	uchar dat;
	SCK=0;
	delay();
	CS=0;
	delay();
	SPI_write_byte(READ);
	SPI_write_byte(addr);
	dat=SPI_read_byte();
	CS=1;
	delay();
	SCK=0;
	delay();
	return dat;
}

void write_SPI_SR(uchar sReg)
{
	CS=0;
	delay();
	SPI_write_byte(WREN);
	CS=1;
	delay();
	CS=0;
	delay();
	SPI_write_byte(WRSR);
	SPI_write_byte(sReg);
	CS=1;
	delay();
}

uchar read_SPI_SR(void)
{
	uchar sReg=0;
	CS=0;
	delay();
	SPI_write_byte(RDSR);
	sReg=SPI_read_byte();
	CS=1;
	delay();
	return sReg;
}

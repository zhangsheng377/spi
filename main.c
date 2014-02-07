#include <reg51.h>
#include "main.h"
#include "delay.h"
#include "spi.h"

sbit LED1=P2^0;
sbit LED2=P2^1;

#define DAT_ADDR 0x03

uchar g_ucDat;

void display(uchar dat)
{
	LED1=0;
	LED2=1;
	P0=(dat%10);
	delay_ms(1);
	LED2=0;LED1=1;
	P0=(dat/10);
	delay_ms(1);
}

void int0_init(void)
{
	EX0=1;
	IT0=1;
	EA=1;
}

void int0_inter() interrupt 0
{
	g_ucDat ++;
}

void main(void)
{
	uchar tmp=0;
	g_ucDat=0;
	int0_init();
	init_SPI();

	write_SPI_SR(0x00);
	delay_ms(10);
	tmp=read_SPI_SR();

	tmp=read_SPI(DAT_ADDR);
	if(tmp == 0xFF)
	{
		tmp=0;
		write_SPI(tmp,DAT_ADDR);
		delay_ms(10);
	}
	g_ucDat =tmp;

	while(1)
	{
		if (tmp != g_ucDat)
		{
			if(g_ucDat > 99)
			{
				g_ucDat=1;
			}
			tmp=g_ucDat;
			write_SPI(tmp,DAT_ADDR);
			delay_ms(10);
		}

		display(tmp);
	}
}

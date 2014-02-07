#ifndef _SPI_H
#define _SPI_H

#include "main.h"

void init_SPI(void);
uchar read_SPI_SR(void);
void write_SPI_SR(uchar rs);
uchar read_SPI(uchar addr);
void write_SPI(uchar dat,uchar addr);
#endif

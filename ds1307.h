/*
	@File 		ds1307.h
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		07/06/2021
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/ 

#ifndef DS1307_H_
#define DS1307_H_

//	ADDRESS
#define DS1307_SLA_W                                    0xD0
#define DS1307_SLA_R                                    0xD1

//	CLOCK
#define DS1307_SECONDS                                  0x00
#define DS1307_MINUTES                                  0x01
#define DS1307_HOURS                                    0x02
#define DS1307_DAY					0x03
#define DS1307_DATE					0x04
#define DS1307_MONTH                                    0x05
#define DS1307_YEAR					0x06
#define DS1307_24H					0x00
#define DS1307_12H					0x40
#define DS1307_AM					0x00
#define DS1307_PM					0x20

//	RAM
#define DS1307_RAM					0x08

// CONTROL
#define DS1307_CONTROL                                  0x07
#define DS1307_SQWARE_ENABLE                            0x10
#define DS1307_SQWARE_DISABLE                           0x00
#define DS1307_SQWARE_1hz                               0x00
#define DS1307_SQWARE_8192Khz                           0x01
#define DS1307_SQWARE_4096Khz                           0x02
#define DS1307_SQWARE_32768Khz                          0x03
#define DS1307_OUT_LEVEL_HIGH                           0x80
#define DS1307_OUT_LEVEL_LOW                            0x00

//	BCD
#define Hex(x)						((x / 10) << 4) | (x % 10)
#define Dec(x)						((x >> 4) * 10) + (x & 0x0F)

unsigned char DS1307_Read_Control();
unsigned char DS1307_Read_Reg(unsigned char reg);
void DS1307_Write_Reg(unsigned char reg, unsigned char value);
void DS1307_Write_Control(unsigned char data);

#endif /* DS1307_H_ */

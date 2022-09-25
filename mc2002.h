/*
	@File 		
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		20/06/21
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef MC2002_H_
#define MC2002_H_

#include <xc.h>

#define MC2002_DIO_LOW					RC0=0
#define MC2002_DIO_HIGH                                 RC0=1

#define MC2002_CLK_LOW					RC1=0
#define MC2002_CLK_HIGH					RC1=1

#define MC2002_STB_LOW					RC2=0
#define MC2002_STB_HIGH					RC2=1

void MC2002_Clear();
void MC2002_Write(unsigned char data);
void MC2002_Command(unsigned char data);
void MC2002_Data(unsigned char address, unsigned char data);
void MC2002_Diming(unsigned char pulse);
void MC2002_Init();

unsigned char MC2002_GetKey();
unsigned char MC2002_Read();

#endif /* MC2002_H_ */

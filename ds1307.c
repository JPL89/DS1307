/*
	@File 		ds1307.cpp
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		07/06/2021
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "ds1307.h"
#include "wire.h"

unsigned char DS1307_Read_Reg(unsigned char reg)
{
	Wire_Start();
	Wire_Write(DS1307_SLA_W);
	Wire_Write(reg);
	Wire_Start();
	Wire_Write(DS1307_SLA_R);
	unsigned char data = Wire_Nack();
	Wire_Stop();
        
	return (Dec(data));
}

void DS1307_Write_Reg(unsigned char reg, unsigned char value)
{
	Wire_Start();
	Wire_Write(DS1307_SLA_W);
	Wire_Write(reg);
	Wire_Write(Hex(value));
	Wire_Stop();
}

void DS1307_Write_Control(unsigned char data)
{
	Wire_Start();
	Wire_Write(DS1307_SLA_W);
	Wire_Write(DS1307_CONTROL);
	Wire_Write(data);
	Wire_Stop();
}

unsigned char DS1307_Read_Control()
{
	Wire_Start();
	Wire_Write(DS1307_SLA_W);
	Wire_Write(DS1307_CONTROL);
	Wire_Start();
	Wire_Write(DS1307_SLA_R);
	unsigned char data = Wire_Nack();
	Wire_Stop();
	
	return (data);
}

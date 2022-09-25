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

#ifndef WIRE_H
#define WIRE_H

#include <xc.h>

#define SCL_HIGH            RC3=1
#define SCL_LOW             RC3=0

#define SDA_HIGH            RC4=1
#define SDA_LOW             RC4=0

unsigned char Wire_Test(unsigned char Slave);
unsigned char Wire_Nack();
unsigned char Wire_Ack();
void ACK();
void NACK();
void Wire_Stop();
void Wire_Start();
void Wire_Write(unsigned char data);
void Wire_Init();

#endif	


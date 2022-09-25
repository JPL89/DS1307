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
#include "wire.h"

#define _NOP() __asm__ __volatile__("nop")

void Wire_Start(void)
{
    SCL_HIGH;
    _NOP();
    SDA_HIGH;
    _NOP();
    SDA_LOW;
    _NOP(); 
    SCL_LOW;
}

void Wire_Stop(void)
{
    SDA_LOW;
    _NOP();
    SCL_HIGH;
    _NOP(); 
    SDA_HIGH;
    
}

unsigned char Wire_Ack()
{
    unsigned char byte = 0;

    TRISC4 = 1;
    
    SDA_HIGH;
    
    for (unsigned char bit=0; bit<8; bit++)
    {
        SCL_HIGH;
	_NOP();
	byte <<= 1;
	if(PORTCbits.RC4 == 1) byte |= 1; 
	
	SCL_LOW;
	_NOP();
	_NOP();
    }
	
    TRISC4 = 0;

    SDA_LOW;
    _NOP();
    SCL_HIGH;
    _NOP();
    SCL_LOW;
    _NOP();
    
    return byte;
}

unsigned char Wire_Nack()
{
    unsigned char byte = 0;
    
    TRISC4 = 1;
    
    SDA_HIGH;
    
    for (unsigned char bit=0; bit<8; bit++)
    {
        SCL_HIGH;
	_NOP();
        _NOP();
        
	byte <<= 1;
	if(PORTCbits.RC4 == 1) byte |= 1; 
	
	SCL_LOW;
        _NOP();
	_NOP();
    }
	
     TRISC4 = 0;

    SDA_HIGH;
    _NOP();
    SCL_HIGH;
    _NOP();
    SCL_LOW;
    _NOP();
	
    return byte;
}

void ACK()
{
    SDA_LOW;
    _NOP();
    SCL_HIGH;
    _NOP();
    SCL_LOW;
    _NOP();
}

void NACK()
{
    SDA_HIGH;
    _NOP();
    SCL_HIGH;
    _NOP();
    SCL_LOW;
    _NOP();
}

void Wire_Write(unsigned char data)
{
    for(unsigned char bit=0; bit<8; ++bit)
    {
	if(data & 0x80) SDA_HIGH; else SDA_LOW;
	data <<= 1;
	
        SCL_HIGH;
	_NOP();
	SCL_LOW;
	_NOP();
    }
    
    // Read ACK
    TRISC4 = 1;
    
    SDA_HIGH;
    _NOP();
    SCL_HIGH;
    _NOP();
    SCL_LOW;
    _NOP();
    
    TRISC4 = 0;
}

unsigned char Wire_Test(unsigned char Slave)
{
    unsigned char ack = 0;
	
    Wire_Start();
    
    for(unsigned char bit=0; bit<8; ++bit)
    {
	if(Slave & 0x80) SDA_HIGH; else SDA_LOW;
	Slave <<= 1;
	
	SCL_HIGH;
	_NOP();
	SCL_LOW;
	_NOP();
    }
        
    // Read ACK
    TRISC4 = 1;
    
    SDA_HIGH;
    _NOP();
    SCL_HIGH;
    _NOP();
    if(PORTCbits.RC4 == 1) ack = 1; 
    SCL_LOW;
    _NOP();
    
    TRISC4 = 0;
    
    Wire_Stop();
    
    return ack;
}

void Wire_Init(void)
{
    TRISC4 = 0;
    TRISC3 = 0;
}


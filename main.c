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

// CONFIG1H
#pragma config OSC = HS         
#pragma config FCMEN = OFF      
#pragma config IESO = OFF       

// CONFIG2L
#pragma config PWRT = OFF       
#pragma config BOREN = OFF      
#pragma config BORV = 3         

// CONFIG2H
#pragma config WDT = OFF        
#pragma config WDTPS = 32768    

// CONFIG3H
#pragma config CCP2MX = PORTC   
#pragma config PBADEN = OFF     
#pragma config LPT1OSC = OFF    
#pragma config MCLRE = ON       

// CONFIG4L
#pragma config STVREN = OFF     
#pragma config LVP = OFF        
#pragma config XINST = OFF      

// CONFIG5L
#pragma config CP0 = OFF        
#pragma config CP1 = OFF        
#pragma config CP2 = OFF        
#pragma config CP3 = OFF        

// CONFIG5H
#pragma config CPB = OFF        
#pragma config CPD = OFF        

// CONFIG6L
#pragma config WRT0 = OFF       
#pragma config WRT1 = OFF       
#pragma config WRT2 = OFF       
#pragma config WRT3 = OFF       

// CONFIG6H
#pragma config WRTC = OFF       
#pragma config WRTB = OFF       
#pragma config WRTD = OFF       

// CONFIG7L
#pragma config EBTR0 = OFF      
#pragma config EBTR1 = OFF      
#pragma config EBTR2 = OFF      
#pragma config EBTR3 = OFF      

// CONFIG7H
#pragma config EBTRB = OFF     

#define _XTAL_FREQ   20000000

#include <xc.h>
#include "mc2002.h"
#include "ds1307.h"
#include "wire.h"

#define TIME(h, m) (h * 100 + m)

volatile unsigned char seconds = 0;
volatile unsigned char minutes = 0;
volatile unsigned char hours = 0;
volatile unsigned char key = 0;
static unsigned char status = 0;

static const unsigned int MC2002_FONT[] =
{
        0x003F, 
	0x0006, 
	0x085B, 
	0x084F, 
	0x0866, 
	0x086D, 
	0x087D, 
	0x0007, 
	0x087F, 
	0x086F, 
	0x0877, 
	0x087C, 
	0x0039, 
	0x085E, 
	0x0879, 
	0x0871, 
};

void Print(int n)
{
    MC2002_Data(0x00, MC2002_FONT[n/1000%10]);
    MC2002_Data(0x01, MC2002_FONT[n/1000%10] >> 8);
    
    MC2002_Data(0x02, MC2002_FONT[n/100%10]);
    MC2002_Data(0x03, MC2002_FONT[n/100%10] >> 8);
    
    MC2002_Data(0x04, MC2002_FONT[n/10%10]);
    MC2002_Data(0x05, MC2002_FONT[n/10%10] >> 8 | 0x10);    
    
    MC2002_Data(0x06, MC2002_FONT[n/1%10]);
    MC2002_Data(0x07, MC2002_FONT[n/1%10] >> 8 | 0x10);
}

int main(void) 
{
    // WAIT VCC
    __delay_ms(1000);
    
    // WIRE INIT
    Wire_Init();
    
    // DISPLAY INIT
    MC2002_Init();
    
    // DISPLAY CLEAR
    MC2002_Clear();
    
    // // SQW AS INPUT
    TRISC5 = 1;
   
    DS1307_Write_Reg(0x01, 0); 
    DS1307_Write_Reg(0x02, 0); 
    
    // CONTROL REGISTER CONFIGURATION
    unsigned char control = DS1307_OUT_LEVEL_LOW|
    DS1307_SQWARE_ENABLE|DS1307_SQWARE_1hz;

    // WRITE CONTROL REGISTER
    DS1307_Write_Control(control); 
    
    // CLEAR SECONDS TO SQWE WORKS GOOD
    DS1307_Write_Reg(0x00, 0x00);
    
    // READ MINUTES REGISTER
    minutes = DS1307_Read_Reg(0x01);
    
    // READ HOURS REGISTER
    hours = DS1307_Read_Reg(0x02);
    
    Print( TIME(hours, minutes) );
    
    // READ SECONDS REGISTER
    seconds = DS1307_Read_Reg(0x00);
    
    while(1)
    {
        if(status == 0)
        {
            // SQW AS INPUT
            TRISC5 = 1;

            if(PORTCbits.RC5 == 1)
            {
                // READ SECONDS REGISTER
                seconds = DS1307_Read_Reg(0x00);

                // SQW AS OUTPUT
                TRISC5 = 0;
            }

            if(seconds == 0)
            {
                // READ MINUTES REGISTER
                minutes = DS1307_Read_Reg(0x01);

                // READ HOURS REGISTER
                hours = DS1307_Read_Reg(0x02);

                Print( TIME(hours, minutes) );

                // READ SECONDS REGISTER
                seconds = DS1307_Read_Reg(0x00);
            }
        }
        
        if(key == 0x08)
        {
            minutes = DS1307_Read_Reg(0x01);
                
            minutes++;
                
            DS1307_Write_Reg(0x01, minutes);
                
            Print( TIME(hours, minutes) );
                
            __delay_ms(150);
        }
        
        if(key == 0x02)
        {
            hours = DS1307_Read_Reg(0x02);
                
            hours++;
    
            DS1307_Write_Reg(0x02, hours);
                
            Print( TIME(hours, minutes) );
                
            __delay_ms(150);
        }
        
        key = MC2002_GetKey();
        
        if(key == 0x01)
        {
            // stop clock
            status  ^= 1;
            
            if(status == 1)
            {
                control = DS1307_OUT_LEVEL_LOW|
                DS1307_SQWARE_DISABLE|DS1307_SQWARE_1hz;

                // WRITE CONTROL REGISTER
                DS1307_Write_Control(control); 
            }
            else
            {
                control = DS1307_OUT_LEVEL_LOW|
                DS1307_SQWARE_ENABLE|DS1307_SQWARE_1hz;

                // WRITE CONTROL REGISTER
                DS1307_Write_Control(control); 

                // CLEAR SECONDS TO SQWE WORKS GOOD
                DS1307_Write_Reg(0x00, 0x00);
            }
            
            __delay_ms(250);
        }
        
    }
    
    return 0;
}

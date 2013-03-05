/*
 * uart.c
 *
 *  Created on: 2013-01-08
 *      Author: Bryce Klippenstein
 *                Carmanah Signs inc.
 */

#include "MKL25Z4.h"
#include "math.h"
#include "uart.h"

void uart0Config(void)
{
    uint32_t BSR = 0; //what will become the baudrate divider.
    extern uint32_t DUMMYREAD;

    /* The following is hard coded for use when the processor is running at
     * 96MHz PLL, forwarded to UART0 as MCGPLLCLK / 2. (SIM_SOPT2[UART0SRC])
     * Using an over sampling rate of 24 gives us an exact match to common baud
     * rates. Tested for 9600 and 19200 baud. Other values not guarenteed to
     * work with these settings.
     *
     * BSR = (MCGPLLCLK/2)/(FBR*(OSR+1)) where:
     * BSR is UART0_BDH[SBR] and UART0_BDL[SBR]
     * MCGPLLCLK is the PLL frequency
     * FBR is the final desired baud rate
     * OSR is UART0_C4[OSR]
     *
     * See chapter 39 of the Freescale KL25 Sub-Family Reference Manual for
     * more information.
     */

    //BSR = 48000000/(baudrate*(25)); //See above.
    BSR = 100;
    //Until I work out how to divide on this processor, this will be hard coded.
    //if(BSR < 1 || BSR > 8191)
    //{
        //return -1; //Error, invalid baud rate.
    //}

    SIM_SOPT2 &= (uint32_t)~0x0C000000; //Clear UART0SRC
    SIM_SOPT2 |= (uint32_t)0x04000000; //Set UART0SRC to 0b11
    DUMMYREAD = SIM_SOPT2;

    SIM_SCGC4 |= (uint32_t)0x00000400; //Turn on clock for UART0
    DUMMYREAD = SIM_SCGC4;
    SIM_SCGC5 |= (uint32_t)0x00000200; //Turn on clock for PortA
    DUMMYREAD = SIM_SCGC5;

    PORTA_PCR1 |= (uint32_t)0x00000200; //Set Port A as UART0_RX
    DUMMYREAD = PORTA_PCR1;
    PORTA_PCR2 |= (uint32_t)0x00000200; //Set Port A as UART0_TX
    DUMMYREAD = PORTA_PCR2;

    //UART0_C4 &= (uint8_t)~(uint8_t)0x1F;
    UART0_C4 = (uint8_t)0x18; //Set OSR to 24.
    DUMMYREAD = UART0_C4;

    UART0_BDH &= (uint8_t)~0x1F;
    UART0_BDH |= (uint8_t)(BSR >> 8); //set top 5 bits of BSR
    DUMMYREAD = UART0_BDH;
    UART0_BDL = (uint8_t)(BSR & 0xFF); //set bottom 8 bits of BSR
    DUMMYREAD = UART0_BDL;

    //return 0;
}

void uart0Enable(void)
{
    extern uint32_t DUMMYREAD;
    UART0_C2 |= (uint8_t)0x0C; // set UART0_C2[TE]=1, UART0_C2[RE]=1
    DUMMYREAD = UART0_C2;
}

void uart0Disable(void)
{
    UART0_C2 &= (uint8_t)~0x0C; // set UART0_C2[TE]=0, UART0_C2[RE]=0
}

uint8_t uart0SendByte(uint8_t data)
{
    while(!((UART0_S1 & 0x80) && (UART0_S1 & 0x40))) //Wait until data is sent before returning.
        ;

    UART0_D = (uint8_t)data;
    while(!((UART0_S1 & 0x80) && (UART0_S1 & 0x40))) //Wait until data is sent before returning.
    {
        asm("NOP");
    }
    return 1;
}

uint32_t uart0Send_s(uint8_t* data, uint8_t numBytes)
{
    int i = 0;
    uint32_t bytesSent = 0;

    for (i=0; i<numBytes; i++)
    {
        bytesSent += uart0SendByte(data[i]);
    }
    return bytesSent;
}

uint32_t uart0Send_i(uint32_t data)
{
    uint8_t magnitude;
    uint8_t leadingZero = 1;
    uint32_t temp;
    uint32_t bytesSent = 0;

    if(data < 0)
    {
        return -1;
    }

    if(data == 0)
    {
        uart0SendByte((uint8_t)48); // Special case if data is 0
        return 1;
    }

    for(magnitude=10; magnitude > 0; magnitude--)
    {
        temp = data / pow(10, (magnitude-1)); //pull off most significant digit

        if (temp != 0)
        {
            leadingZero = 0;
        }

        if(!leadingZero) // Don't print leading zeros.
        {
            uart0SendByte((uint8_t)temp+48); // Convert temp number to ascii char
            bytesSent++;
        }

        data -= temp * pow(10, (magnitude-1));
    }

    return bytesSent;
}

uint32_t uart0Send_n(char* data)
{
    int i = 0;
    uint32_t bytesSent = 0;

    while(1)
    {
        if(data[i] == '\0')
            break;

        bytesSent += uart0SendByte(data[i]);
        i++;
    }
    return bytesSent;
}

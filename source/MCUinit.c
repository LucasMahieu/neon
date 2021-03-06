/*
 ** ###################################################################
 **     This code is generated by the Device Initialization Tool.
 **     It is overwritten during code generation.
 **     USER MODIFICATION ARE PRESERVED ONLY INSIDE INTERRUPT SERVICE ROUTINES
 **     OR EXPLICITLY MARKED SECTIONS
 **
 **     Project     : DeviceInitialization
 **     Processor   : MKL25Z128VLH4
 **     Version     : Component 01.000, Driver 01.04, CPU db: 3.00.000
 **     Datasheet   : KL25RM, Rev.1, Jun 2012
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2012-12-03, 16:55, # CodeGen: 0
 **     Abstract    :
 **
 **     Contents    :
 **         Function "MCU_init" initializes selected peripherals
 **
 **     Copyright : 1997 - 2012 Freescale, Inc. All Rights Reserved.
 **
 **     http      : www.freescale.com
 **     mail      : support@freescale.com
 ** ###################################################################
 */

/****************************************************************************
 * Modified by Bryce Klippenstein - Jan 2, 2013
 * Carmanah Signs Inc.
 *
 * This file was generated by Freescale's Processor Expert. It has
 * been modified to clean out all functionality that is handled by other
 * functions.
 *
 * To be more specific, the compiler used was based on Esden's
 * summon-arm-toolchain script. Available on GitHub.
 * Commit: 0570ac76c0fb8c3b841c39513ac0c908a833f401
 *
 * The toolchain was configured to use Linaro's GCC and disable Cortex-M3
 * support by default, as well as openocd, libstm32, and libopencm3.
 *
 * More details can be found on the private Carmanah Signs Inc. github repo for
 * this project.
 *
 ***************************************************************************/

/* MODULE MCUinit */

#define PE_MCUINIT

#include <MKL25Z4.h>                   /* I/O map for MKL25Z128VLH4 */
#include "MCUinit.h"
#include "interrupt.h"
#include "board.h"
#include "rtc.h"
#include "i2c.h"
#include "uart.h"
#include "time.h"

/* Interrupt vector table type definition */
typedef void (*const tIsrFunc)(void);
typedef struct {
    void * __ptr;
    tIsrFunc __fun[0x2F];
} tVectorTable;

extern const tVectorTable __vect_table;

/* User declarations and definitions */
/*   Code, declarations and definitions here will be preserved during code generation */
/* End of user declarations and definitions */

/*
 ** ===================================================================
 **     Method      :  __init_hardware (component MKL25Z128LH4)
 **
 **     Description :
 **         Initialization code for CPU core and a clock source.
 ** ===================================================================
 */
void __attribute__ ((constructor)) __init_hardware(void)
        {
    /*** ### MKL25Z128VLH4 "Cpu" init code ... ***/
    /*** PE initialization code after reset ***/


    if((uint32_t)SCB_VTOR != (uint32_t)&__vect_table)
    {
        SCB_VTOR = (uint32_t)(&__vect_table); /* Set the interrupt vector table position */
    }

    /* Disable the WDOG module */
    /* SIM_COPC: COPT=0,COPCLKS=0,COPW=0 */
    SIM_COPC = (uint32_t)0x00UL;

    /****************************************************************************
     * Begin section modified by Bryce Klippenstein - Jan 2, 2013
     * Carmanah Signs Inc.
     *
     * This file was generated by Freescale's Processor Expert. This section has
     * been modified to clean out all functionality that is handled by other
     * functions.
     ***************************************************************************/

    /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV4=1 */
    SIM_CLKDIV1 = (uint32_t)0x00010000UL; /* Update system prescalers */
    /* SIM_SOPT2: PLLFLLSEL=0 */
    SIM_SOPT2 &= (uint32_t)~0x00010000UL; /* Select FLL as a clock source for various peripherals */
    /* SIM_SOPT1: OSC32KSEL=0 */
    SIM_SOPT1 &= (uint32_t)~0x000C0000UL; /* System oscillator drives 32 kHz clock for various peripherals */


    /* MCG_SC: FCRDIV=0 */
    MCG_SC = (uint8_t)((MCG_SC & (uint8_t)~(uint8_t)0x0EU) | (uint8_t)0x00U);
    /* Switch to FEE Mode */
    /* MCG_C2: LOCRE0=0,RANGE0=0,HGO0=0,EREFS0=1,LP=0,IRCS=1 */
    MCG_C2 = (uint8_t)0x05U;
    /* OSC0_CR: ERCLKEN=1,EREFSTEN=1,SC2P=1,SC4P=0,SC8P=0,SC16P=1 */
    OSC0_CR = (uint8_t)0xA9U;
    /* MCG_C1: CLKS=0,FRDIV=0,IREFS=0,IRCLKEN=0,IREFSTEN=0 */
    MCG_C1 = (uint8_t)0x00U;
    /* MCG_C4: DMX32=1,DRST_DRS=1 */
    MCG_C4 = (uint8_t)((MCG_C4 & (uint8_t)~(uint8_t)0x40U) | (uint8_t)0xA0U);
    /* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0 */
    MCG_C5 = (uint8_t)0x00U;
    /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
    MCG_C6 = (uint8_t)0x00U;

    if (RCM_SRS0 & RCM_SRS0_WAKEUP_MASK) // If waking up from low power mode, not cold boot:
    {
        PMC_REGSC |= 0x08; // Write to the ACKISO bit to clear wake-up event. This unlocks the MCG and GIOs.
    }

    while((MCG_S & MCG_S_IREFST_MASK) != 0x00U)
    {
        ;/* Check that the source of the FLL reference clock is the external reference clock. */
    }
    while((MCG_S & 0x0CU) != 0x00U)
    {
        ;/* Wait until output of the FLL is selected */
    }

        }

/*
 ** ===================================================================
 **     Method      :  MCU_init (component MKL25Z128LH4)
 **
 **     Description :
 **         Device initialization code for selected peripherals.
 ** ===================================================================
 */
void MCU_init(void)
{
    /* Initialization of the RCM module */
    /* RCM_RPFW: RSTFLTSEL=0 */
    RCM_RPFW &= (uint8_t)~(uint8_t)0x1FU;

    /* RCM_RPFC: RSTFLTSS=0,RSTFLTSRW=0 */
    RCM_RPFC &= (uint8_t)~(uint8_t)0x07U;

    /* Initialization of the PMC module */
    /* PMC_LVDSC1: LVDACK=1,LVDIE=0,LVDRE=1,LVDV=0 */
    PMC_LVDSC1 = (uint8_t)((PMC_LVDSC1 & (uint8_t)~(uint8_t)0x23U) | (uint8_t)0x50U);
    /* PMC_LVDSC2: LVWACK=1,LVWIE=0,LVWV=0 */
    PMC_LVDSC2 = (uint8_t)((PMC_LVDSC2 & (uint8_t)~(uint8_t)0x23U) | (uint8_t)0x40U);
    /* PMC_REGSC: BGEN=0,ACKISO=0,BGBE=0 */
    PMC_REGSC &= (uint8_t)~(uint8_t)0x19U;

    /****************************************************************************
     * End section modified by Bryce Klippenstein - Jan 2, 2013
     * Carmanah Signs Inc.
     *
     * This file was generated by Freescale's Processor Expert. This section has
     * been modified to clean out all functionality that is handled by other
     * functions.
     ***************************************************************************/

} /* MCU_init */


/*
 ** ===================================================================
 **     Interrupt handler : isr_default
 **
 **     Description :
 **         User interrupt service routine.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
PE_ISR(isr_default)
{
    SIM_SCGC5 |= 0x00000400; //enable Port B clock
    PORTB_PCR18 |= (uint32_t)0x00000100; //Configure portB18 as GPIO (RED)
    GPIOB_PDDR |= (uint32_t)0x00040000; //Configure portB18 as output
    GPIOB_PCOR |= (uint32_t)0x00040000;
    while(1)
        ; // You shouldn't be here.

}
/* end of isr_default */


/*
 ** ===================================================================
 **     Interrupt handler : isrINT_NMI
 **
 **     Description :
 **     User interrupt service routine.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
PE_ISR(isrINT_NMI)
{
    SIM_SCGC5 |= 0x00000400; //enable Port B clock
    PORTB_PCR18 |= (uint32_t)0x00000100; //Configure portB18 as GPIO (RED)
    GPIOB_PDDR |= (uint32_t)0x00040000; //Configure portB18 as output
    GPIOB_PCOR |= (uint32_t)0x00040000;
    while(1)
        ; // You shouldn't be here.
}
/* end of isrINT_NMI */

PE_ISR(systick)
{
    extern volatile uint8_t systemTicked;
    uint32_t DUMMY_READ;
    DUMMY_READ = SYST_CSR; //Read the CSR register to clear the COUNTFLAG bit.
    systemTicked = 1;
}

PE_ISR(llwu)
{
    //    __init_hardware(); //Rerun all init functions upon wake-up.
    MCU_init();
    boardInit();
    extern volatile uint32_t DUMMYREAD;

    SIM_SCGC5 |= 0x00000400; //enable Port B clock
    PORTB_PCR0 |= (uint32_t)0x00000102; //Configure portB0 as GPIO with pullup.
    GPIOB_PDDR &= ~(uint32_t)0x00000001; //Configure portB0 as input.

    LLWU_F1 |= 0x20; //clear wakeup flag on WUF5
    LLWU_FILT1 |= 0x80;
    interruptPendingClear(7);
    //PMC_REGSC |= 0x08; // Write to the ACKISO bit to clear wake-up event.
    DUMMYREAD = PMC_REGSC;

    interruptPendingClear(7);
}


/*The rest of the ISRs */
PE_ISR(PORTA_ISR)
{

    extern volatile uint32_t buttonPushed;
    interruptPendingClear(30);
    PORTA_PCR12 |= 0x01000000;
    buttonPushed = 1;
}

PE_ISR(RTC_SECONDS_ISR)
{
    extern volatile uint8_t secondTicked;
    secondTicked = 1;
    interruptPendingClear(21);
}

PE_ISR(i2c)
{
    extern volatile uint32_t DUMMYREAD;
    extern uint8_t i2cData;
    extern uint8_t i2cState;
    extern uint8_t i2cRegister;
    extern volatile struct tm calTime;
    time_t currentTime;

    FGPIOD_PCOR |= (uint32_t)0x00000002;

    I2C1_S |= 0x02; // clear interrupt flag in I2C register.

    if(I2C1_S & 0x10)
    {
        //Arbitration lost.
        I2C1_S |= 0x10;
        //uart0Send_n("Lost Arbitration\n\0");

        if(!(I2C1_S & 0x40))
        {
            interruptPendingClear(25);
            FGPIOD_PSOR |= (uint32_t)0x00000002;
            return;
        }
    }

    if(I2C1_S & 0x40)// Address Transfer
    {
        if(I2C1_S & 0x04)// SRW = 1 -> data requested
        {
            I2C1_C1 |= 0x10; // Set to transmit
            DUMMYREAD = I2C1_D;

            i2cAck(1);

            currentTime = rtcGet();
            calTime = *localtime(&currentTime);

            switch (i2cRegister)
            {
            case 0:
                i2cData = calTime.tm_sec; // received seconds request
                break;

            case 1:
                i2cData = calTime.tm_min; // received minutes request
                break;

            case 2:
                i2cData = calTime.tm_hour; // received hours request
                break;

            case 3:
                i2cData = calTime.tm_mday; // received day of month request
                break;

            case 4:
                i2cData = (calTime.tm_mon + 1); // received month request
                break;

            case 5:
                i2cData = (calTime.tm_year - 70); // Stored as years since 1900, send years since 1970
                break;

            default:
                i2cData = 0;
                break;
            }

            i2cState =  0;
            I2C1_D = i2cData; //Write appropriate byte out
        }
        else
        {
            I2C1_C1 &= ~0x10; // Set to receive
            DUMMYREAD = I2C1_D; // We received our own address, throw it away.
            if(i2cState == 0)
            {
                i2cState = 1; // Move into state 1.
                interruptPendingClear(25);
                i2cAck(1);
                FGPIOD_PSOR |= (uint32_t)0x00000002;
                return;
            }
            else if(i2cState == 2)
            {
                i2cState = 3; // Move into state 3.
                interruptPendingClear(25);
                i2cAck(1);
                FGPIOD_PSOR |= (uint32_t)0x00000002;
                return;
            }
        }
    }
    else // Data Transfer
    {
        if(I2C1_C1 & 0x10)//Module set to transmit.
        {
            I2C1_C1 &= ~0x10; // Set to receive
            DUMMYREAD = I2C1_D; // Do a dummy read.
            i2cAck(1);
        }

        else
        {
            if(i2cState == 1) // If we're in state 1
            {
                i2cRegister = I2C1_D; // Read register

                i2cState = 2; // Set our state to 2

                i2cAck(1);
            }

            else if(i2cState == 3) //if we're in state 2
            {
                i2cData = I2C1_D;
                switch (i2cRegister)
                {
                case 0:
                    calTime.tm_sec = i2cData; // received seconds
                    break;

                case 1:
                    calTime.tm_min = i2cData; // received minutes
                    break;

                case 2:
                    calTime.tm_hour = i2cData; // received hours
                    break;

                case 3:
                    calTime.tm_mday = i2cData; // received day of month
                    break;

                case 4:
                    calTime.tm_mon = (i2cData-1); // received month
                    break;

                case 5:
                    calTime.tm_year = (i2cData+70); // received years since 1970. Store as years since 1900
                    break;
                }

                i2cAck(1);
                i2cState = 0; // move back to state 0
                rtcStop();
                rtcSet(mktime((struct tm*)&calTime));
                rtcStart();
            }
        }
    }

    FGPIOD_PSOR |= (uint32_t)0x00000002;
    interruptPendingClear(25);
}

#ifdef __cplusplus
extern "C" {
#endif
extern uint32_t __SP_INIT;
extern void __thumb_startup( void );
#ifdef __cplusplus
}
#endif

/* Interrupt vector table */
#ifndef UNASSIGNED_ISR
#define UNASSIGNED_ISR isr_default   /* unassigned interrupt service routine */
#endif


__attribute__ ((section (".vectortable"))) const tVectorTable __vect_table = { /* Interrupt vector table */
        &__SP_INIT,                                             /* 0 (0x00000000) (prior: -) */
    {
        (tIsrFunc)&__thumb_startup,                             /* 1 (0x00000004) (prior: -) */
        (tIsrFunc)&isrINT_NMI,                                  /* 2 (0x00000008) (prior: -2) */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 3 (0x0000000C) (prior: -1) hard fault */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 4 (0x00000010) (prior: -) */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 5 (0x00000014) (prior: -) */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 6 (0x00000018) (prior: -) */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 7 (0x0000001C) (prior: -) */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 8 (0x00000020) (prior: -) */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 9 (0x00000024) (prior: -) */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 10 (0x00000028) (prior: -) */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 11 (0x0000002C) (prior: -) supervisor call*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 12 (0x00000030) (prior: -) */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 13 (0x00000034) (prior: -) */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 14 (0x00000038) (prior: -) pendablesrvreq*/
        (tIsrFunc)&systick,                                     /* 15 (0x0000003C) (prior: -) systick*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 16 (0x00000040) (prior: -) DMA0*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 17 (0x00000044) (prior: -) DMA1*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 18 (0x00000048) (prior: -) DMA2*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 19 (0x0000004C) (prior: -) DMA3*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 20 (0x00000050) (prior: -) */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 21 (0x00000054) (prior: -) FTFA*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 22 (0x00000058) (prior: -) PMC*/
        (tIsrFunc)&llwu,                                        /* 23 (0x0000005C) (prior: -) LLWU*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 24 (0x00000060) (prior: -) I2C0*/
        (tIsrFunc)&i2c,                                         /* 25 (0x00000064) (prior: -) I2C1*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 26 (0x00000068) (prior: -) SPI0*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 27 (0x0000006C) (prior: -) SPI1*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 28 (0x00000070) (prior: -) UART0*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 29 (0x00000074) (prior: -) UART1*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 30 (0x00000078) (prior: -) UART2*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 31 (0x0000007C) (prior: -) ADC0*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 32 (0x00000080) (prior: -) CMP0*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 33 (0x00000084) (prior: -) TPM0*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 34 (0x00000088) (prior: -) TPM1*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 35 (0x0000008C) (prior: -) TPM2*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 36 (0x00000090) (prior: -) RTC ALARM*/
        (tIsrFunc)&RTC_SECONDS_ISR,                             /* 37 (0x00000094) (prior: -) RTC SECONDS*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 38 (0x00000098) (prior: -) Periodic Interrupt Timer*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 39 (0x0000009C) (prior: -) */
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 40 (0x000000A0) (prior: -) USB OTG*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 41 (0x000000A4) (prior: -) DAC0*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 42 (0x000000A8) (prior: -) TSI0*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 43 (0x000000AC) (prior: -) MCG*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 44 (0x000000B0) (prior: -) LPTMR0*/
        (tIsrFunc)&UNASSIGNED_ISR,                              /* 45 (0x000000B4) (prior: -) */
        (tIsrFunc)&PORTA_ISR,                                   /* 46 (0x000000B8) (prior: -) Port Control Module A*/
        (tIsrFunc)&UNASSIGNED_ISR                               /* 47 (0x000000BC) (prior: -) Port Control Module D*/
        }
};



/* END MCUinit */

/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.0 [05.03]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */

/****************************************************************************** 
 * File:                | hw_driver.c 
 * Author:              | MP
 * Revision:            | A2
 * Revision date:       | 2026-04-21
 * ****************************************************************************  
 * Revision history:
 * ****************************************************************************
 * Rev. | Date          | Comments
 * A1   | 2026-04-21    | Initial draft
 ******************************************************************************/

/*------ INCLUDES ------------------------------------------------------------*/
#include "hw_driver.h"


/*------ FUNCTIONS -----------------------------------------------------------*/


/****************************************************************************** 
 * Initialization
 ******************************************************************************/

void init_hw(void) {
    init_clock();
    init_bor();
    init_pins();
    init_pwm1();
}

void init_clock(void) {
    /* Clock determined by FOSC<1:0> */
    OSCCONbits.SCS = 0U;
    
    /* 16 MHz internal HF oscillator - DON'T CARE*/
    OSCCONbits.IRCF = 15U;
    
    /* PLL OFF */
    OSCCONbits.SPLLEN = 0U;
    
    /* Oscillator calibration */
    OSCTUNEbits.TUN = 0U;
 }

void init_bor(void) {
    /* Software Brown-out Reset Enable bit
     * If BOREN<1:0> in Configuration Words = 01:
     * 1 = BOR is enabled
     * 0 = BOR is disabled
     * If BOREN<1:0> in Configuration Words != 01:
     * SBOREN is read/write, but has no effect on the BOR */
    BORCONbits.SBOREN = 1U;
    
    /* Brown-out Reset Fast Start bit
     * If BOREN <1:0> = 10 (Disabled in Sleep) 
     * or BOREN<1:0> = 01 (Under software control):
     * 1 = Band gap is forced on always (covers Sleep/wake-up/operating cases)
     * 0 = Band gap operates normally and may turn off
     * If BOREN<1:0> = 11 (Always On) or BOREN<1:0> = 00 (Always Off):
     * BORFS is read/write, but has no effect on the BOR */
    BORCONbits.BORFS = 1U;
}

void init_pins(void) {
    /* LATx registers (output latch) */
    /* 0 => output driven to low */
    /* 1 => output driven to high */
    /* Only, if configured as digital output*/
    LATAbits.LATA0 = 0U;
    LATAbits.LATA1 = 0U;
    LATAbits.LATA2 = 0U;
    LATAbits.LATA4 = 0U;
    LATAbits.LATA5 = 0U;
    
    /* TRISx registers (data direction) */
    TRISAbits.TRISA0 = 1U; /* Input */ 
    TRISAbits.TRISA1 = 1U; /* Input */
    TRISAbits.TRISA2 = 1U; /* Input */
    TRISAbits.TRISA3 = 1U; /* Input */
    TRISAbits.TRISA4 = 1U; /* Input */
    TRISAbits.TRISA5 = 0U; /* Output */
    
    /* ANSELx registers (analog select) */
    ANSELAbits.ANSA0 = 0U; /* Digital I/O */
    ANSELAbits.ANSA1 = 0U; /* Digital I/O */
    ANSELAbits.ANSA2 = 0U; /* Digital I/O */
    ANSELAbits.ANSA4 = 0U; /* Digital I/O */

    /* Weak pull-ups are enabled by individual WPUx latch values */
    OPTION_REGbits.nWPUEN = 0U;
    
    /* WPUx registers (weak pull-ups) */
    WPUAbits.WPUA0 = 0U; /* Pull-up disabled */
    WPUAbits.WPUA1 = 0U; /* Pull-up disabled */ 
    WPUAbits.WPUA2 = 0U; /* Pull-up disabled */
    WPUAbits.WPUA3 = 0U; /* Pull-up disabled */
    WPUAbits.WPUA4 = 0U; /* Pull-up disabled */
    WPUAbits.WPUA5 = 0U; /* Pull-up disabled */

    /* ODx registers (Open-Drain / Push-Pull) */
    ODCONAbits.ODA0 = 0U; /* Push-pull */
    ODCONAbits.ODA1 = 0U; /* Push-pull */
    ODCONAbits.ODA2 = 0U; /* Push-pull */
    ODCONAbits.ODA4 = 0U; /* Push-pull */
    ODCONAbits.ODA5 = 0U; /* Push-pull */
   
    /* SLRCONx registers (Slew rate control) */
    SLRCONAbits.SLRA0 = 0U; /* Maximum slew rate */
    SLRCONAbits.SLRA1 = 0U; /* Maximum slew rate */
    SLRCONAbits.SLRA2 = 0U; /* Maximum slew rate */
    SLRCONAbits.SLRA4 = 0U; /* Maximum slew rate */
    SLRCONAbits.SLRA5 = 0U; /* Maximum slew rate */
    
    /* INLVLx registers (ST/TTL input) */
    INLVLAbits.INLVLA0 = 1U; /* ST input */
    INLVLAbits.INLVLA1 = 1U; /* ST input */
    INLVLAbits.INLVLA2 = 1U; /* ST input */
    INLVLAbits.INLVLA3 = 1U; /* ST input */
    INLVLAbits.INLVLA4 = 1U; /* ST input */
    INLVLAbits.INLVLA5 = 1U; /* ST input */

    /* APFCON registers (alternate pin function) */
    APFCONbits.RXDTSEL = 0U;    /* RX/DT function is on RA1 */
    APFCONbits.CWGASEL = 0U;    /* CWGOUTA function is on RA2 */
    APFCONbits.CWGBSEL = 0U;    /* CWGOUTB funcion is on RA0 */
    APFCONbits.T1GSEL = 0U;     /* T1G function is on RA4 */
    APFCONbits.TXCKSEL = 0U;    /* TX/CK function is on RA0 */
    APFCONbits.P2SEL = 0U;      /* PWM2 function is on RA0 */
    APFCONbits.P1SEL = 1U;      /* PWM1 function is on RA5 */
    
    /* IOCx registers (interrupt-on-change) */ 
    
    /* IOCAP: INTERRUPT-ON-CHANGE PORTA POSITIVE EDGE REGISTER */
    IOCAPbits.IOCAP0 = 0U; /* interrupt-On-Change is disabled for the associated pin */
    IOCAPbits.IOCAP1 = 0U; /* interrupt-On-Change is disabled for the associated pin */
    IOCAPbits.IOCAP2 = 0U; /* interrupt-On-Change is disabled for the associated pin */
    IOCAPbits.IOCAP3 = 0U; /* interrupt-On-Change is disabled for the associated pin */
    IOCAPbits.IOCAP4 = 0U; /* interrupt-On-Change is disabled for the associated pin */
    IOCAPbits.IOCAP5 = 0U; /* interrupt-On-Change is disabled for the associated pin */
            
    /* IOCAN: INTERRUPT-ON-CHANGE PORTA NEGATIVE EDGE REGISTER */
    IOCANbits.IOCAN0 = 0U; /* interrupt-On-Change is disabled for the associated pin */
    IOCANbits.IOCAN1 = 0U; /* interrupt-On-Change is disabled for the associated pin */
    IOCANbits.IOCAN2 = 0U; /* interrupt-On-Change is disabled for the associated pin */
    IOCANbits.IOCAN3 = 0U; /* interrupt-On-Change is disabled for the associated pin */
    IOCANbits.IOCAN4 = 0U; /* interrupt-On-Change is disabled for the associated pin */
    IOCANbits.IOCAN5 = 0U; /* interrupt-On-Change is disabled for the associated pin */
    
    /* IOCAF: INTERRUPT-ON-CHANGE PORTA FLAG REGISTER */
    IOCAFbits.IOCAF0 = 0U;
    IOCAFbits.IOCAF1 = 0U;
    IOCAFbits.IOCAF2 = 0U;
    IOCAFbits.IOCAF3 = 0U;
    IOCAFbits.IOCAF4 = 0U;
    IOCAFbits.IOCAF5 = 0U;
}

void init_pwm1(void) {
    /* Standard PWM mode */
    PWM1CONbits.MODE = 0U;
    
    /* PWM module enabled */
    PWM1CONbits.EN = 1U;
    
    /* PWM output active state is high */
    PWM1CONbits.POL = 0U;
    
    /* Clock Source Prescaler Select: No prescaler */
    PWM1CLKCONbits.PS = 0U;
    
    /* Clock Source Select bits: FOSC */
    PWM1CLKCONbits.CS = 0U;
    
    /* Load Buffer Armed bit */
    PWM1LDCONbits.LDA = 1U;
    
    /* Load Buffer On Trigger bit  */
    PWM1LDCONbits.LDT = 0U;
    
    /* Load Trigger Source Select bits */
    PWM1LDCONbits.LDS = 0U;
    
    /* Offset Mode Select Bits - Independent Run mode */
    PWM1OFCONbits.OFM = 0U;
    
    /* Offset Match Control bit - Bit is ignored */
    PWM1OFCONbits.OFO = 0U;
    
    /* Offset Trigger Source Select bits - reserved */
    PWM1OFCONbits.OFS = 0U;
    
    /* PWM PERIOD IN STANDARD MODE */
    /* Period = (PWMxPR+1)*Prescale/PWMxCLK; */
    /* Duty Cycle = (PWMxDC-PWMxPH)/(PWMxPR+1) */
    
    /* Phase Count High Register */
    PWM1PHH = 0U;
    
    /* Phase Count Low Register */
    PWM1PHL = 0U;
    
    /* Duty Cycle Count High Register */
    PWM1DCH = 0U;
    
    /* Duty Cycle Count Low Register */
    PWM1DCL = 209U;
    
    /* Period Count High Register */
    PWM1PRH = 1U;
    
    /* Period Count Low Register */
    PWM1PRL = 162U;
    
    /* Offset Count High Register */
    PWM1OFH = 0U;
    
    /* Offset Count Low Register */
    PWM1OFL = 0U;
    
    /* PWM output disabled */
    PWM1CONbits.OE = 0U;
    
}

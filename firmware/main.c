/****************************************************************************** 
 * File:                | main.c 
 * Author:              | MP
 * Revision:            | A1
 * Revision date:       | 2026-04-21
 * ****************************************************************************  
 * Revision history:
 * ****************************************************************************
 * Rev. | Date          | Comments
 * A1   | 2026-04-21    | Initial draft
 ******************************************************************************/

/* **************************************************************************** 
 * Pinning
 * **************************************************************************** 
 * 
 *                            --------------------                                    
 *                        1 -|VDD              VSS|- 8                                 
 *              O_NEC <-  2 -|RA5      RA0/ICSPDAT|- 7 <-> PICKIT3                                  
 *              I_SW2  -> 3 -|RA4      RA1/ICSPCLK|- 6 <-> PICKIT3                            
 *            PICKIT3 <-> 4 -|RA3/_MCLR        RA2|- 5 <-  I_SW1                             
 *                            --------------------                
 *
 * **************************************************************************** 
 * Used: VDD, VSS, _MCLR, O_NEC, I_SW1, I_SW2, ICSPDAT, ICSPCLK
 * Programming: ICSPDAT, ICSPCLK
 * **************************************************************************** 
 * RA0: AN0, DAC1OUT, C1IN+, PWM2, TX/CK, CWG1B, IOC, ICPDAT/ICDDAT
 * RA1: AN1, VREF+, C1IN0+, PWM1, RX/DT, IOC, ICSPCLK/ICDCLK
 * RA2: AN2, C1OUT, T0CKI, PWM3, CWG1FLT/CWG1A, IOC INT
 * RA3: T1G, IOC, MCLR/VPP
 * RA4: AN3, C1IN1-, T1G, PWM2, TX/CK, CWG1B, IOC, CLKOUT
 * RA5: T1CKI, PWM1, RX/DT, CWG1A, IOC, CLKIN
 * 
 ******************************************************************************
 * Peripherials used: -
 * ****************************************************************************
 * 
 * **************************************************************************** 
 * GPIOs
 * **************************************************************************** 
 * - Digital input: I_SW1 (RA2), I_SW2 (RA4) 
 * - Digital output: O_NEC (RA5)
 *
 * ****************************************************************************
 * Settings
 * ****************************************************************************
 * -
 ******************************************************************************/

#include "configuration_bits.h"
#include "hw_driver.h"
#include "nec32_protocol.h"


nec32_frame frame = {
    .address = 0U,
    .address_inv = 255U,
    .data = 0U,
    .data_inv = 255U,
    .burst = o_nec_high,
    .pause = o_nec_low
};

/* Toshiba - Remote control CT-90429 */

 /* Volume up */
#define VOL_UP() update_nec32_frame(&frame, 64U, 26U); send_nec32_frame(&frame)

/* Volume down */
#define VOL_DOWN() update_nec32_frame(&frame, 64U, 30U); send_nec32_frame (&frame) 

/* On-Off */
#define ON_OFF() update_nec32_frame(&frame, 64U, 18U); send_nec32_frame (&frame)

/* Mute */
#define MUTE() update_nec32_frame(&frame, 64U, 16U); send_nec32_frame (&frame) 


/*------ MAIN APPLICATION ----------------------------------------------------*/

int main(void)
{
    
    init_hw();    
    init_nec32_frame(&frame, 0U, 0U, burst, pause);
    
    while(1)
    {
        if (i_sw1_state()==0) { VOL_UP(); __delay_ms(200); };
        if (i_sw2_state()==0) { VOL_DOWN(); __delay_ms(200); };
    }    
}

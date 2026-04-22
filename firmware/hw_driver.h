/****************************************************************************** 
 * File:                | hw_driver.h   
 * Author:              | MP
 * Revision:            | A1
 * Revision date:       | 2025-04-21
 * ****************************************************************************  
 * Revision history:
 * ****************************************************************************
 * Rev. | Date          | Comments
 * A1   | 2026-04-21    | Initial draft
 ******************************************************************************/

#ifndef HW_DRIVER_H
#define	HW_DRIVER_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000U
#endif


/*------ INCLUDES ------------------------------------------------------------*/
#include <stdint.h>
#include <xc.h>

/*------ MACROS AND CONSTANTS ------------------------------------------------*/

/*------ GLOBAL VARIABLES ----------------------------------------------------*/

/*------ TYPE DEFINITIONS ----------------------------------------------------*/
    
/*------ FUNCTION DECLARATIONS -----------------------------------------------*/

/****************************************************************************** 
 * Initialization 
 ******************************************************************************/
void init_hw(void);

void init_clock(void);
void init_bor(void);
void init_pins(void);
void init_pwm1(void);

/****************************************************************************** 
 * GPIOs
 ******************************************************************************/
static inline void o_nec_high(void) { LATAbits.LATA5 = 1; }
static inline void o_nec_low(void)  { LATAbits.LATA5 = 0; }

static inline uint8_t i_sw1_state(void) { return PORTAbits.RA2; }
static inline uint8_t i_sw2_state(void) { return PORTAbits.RA4; }

#endif /* HW_DRIVER_H */

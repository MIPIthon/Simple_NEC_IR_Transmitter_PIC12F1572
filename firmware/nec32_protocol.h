/****************************************************************************** 
 * File:                | nec32_protocol.h   
 * Author:              | MP
 * Revision:            | A1
 * Revision date:       | 2026-04-21
 * ****************************************************************************  
 * Revision history:
 * ****************************************************************************
 * Rev. | Date          | Comments
 * A1   | 2026-04-21    | Initial draft
 ******************************************************************************/

#ifndef NEC32_PROTOCOL_H
#define	NEC32_PROTOCOL_H


#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000U
#endif


/*------ INCLUDES ------------------------------------------------------------*/
#include <stdint.h>
#include <xc.h>
#include "hw_driver.h"

/*------ MACROS AND CONSTANTS ------------------------------------------------*/
#define LEADER_BURST 9000U      /* in us */
#define LEADER_PAUSE 4500U      /* in us */

#define BIT_ZERO_BURST 562U     /* in us */
#define BIT_ZERO_PAUSE 562U     /* in us */
#define BIT_ONE_BURST 562U      /* in us */
#define BIT_ONE_PAUSE 1687U     /* in us */

#define REPEAT_PAUSE 2250U      /* in us */

#define END_OF_FRAME_BURST 562U /* in us */

/*------ GLOBAL VARIABLES ----------------------------------------------------*/

/*------ TYPE DEFINITIONS ----------------------------------------------------*/

/* Standard NEC32 protocol */
typedef struct {
    uint8_t address; 
    uint8_t address_inv;
    uint8_t data;
    uint8_t data_inv;
    void (*burst)(void);
    void (*pause)(void);
} nec32_frame;

/* Extended NEC32 protocol */
/* TBD - now functions implemented */ 
typedef struct {
    uint16_t address; 
    uint8_t data;
    uint8_t data_inv;
    void (*burst)(void);
    void (*pause)(void);
} nec32_extended_frame;


/*------ FUNCTION DECLARATIONS -----------------------------------------------*/

void burst(void);
void pause(void);

void output_leader(void (*)(void), void (*)(void));
void output_repeat(void (*)(void), void (*)(void));
void output_bit_one(void (*)(void), void (*)(void));
void output_bit_zero(void (*)(void), void (*)(void));
void output_end_of_frame(void (*)(void), void (*)(void));
void output_byte(uint8_t, void (*)(void), void (*)(void));

void init_nec32_frame(nec32_frame *, uint8_t, uint8_t, void (*)(void), void (*)(void));
void update_nec32_frame(nec32_frame *, uint8_t, uint8_t);

void send_nec32_frame(nec32_frame *);
void repeat_nec32_frame(nec32_frame *);

#endif /* NEC32_PROTOCOL_H */



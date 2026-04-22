/****************************************************************************** 
 * File:                | nec32_protocol.c  
 * Author:              | MP
 * Revision:            | A1
 * Revision date:       | 2026-04-21
 * ****************************************************************************  
 * Revision history:
 * ****************************************************************************
 * Rev. | Date          | Comments
 * A    | 2026-04-21    | Initial draft
 ******************************************************************************/

/*------ INCLUDES ------------------------------------------------------------*/
#include "nec32_protocol.h"

/*------ FUNCTIONS -----------------------------------------------------------*/

void output_leader(void (*burst)(void), void (*pause)(void)) {
    burst();
    __delay_us(LEADER_BURST);
    pause();
    __delay_us(LEADER_PAUSE);
}

void output_bit_one(void (*burst)(void), void (*pause)(void)) {
    burst();
    __delay_us(BIT_ONE_BURST);
    pause();
    __delay_us(BIT_ONE_PAUSE);
}

void output_bit_zero(void (*burst)(void), void (*pause)(void)) {
    burst();
    __delay_us(BIT_ZERO_BURST);
    pause();
    __delay_us(BIT_ZERO_PAUSE);
}

void output_end_of_frame(void (*burst)(void), void (*pause)(void)) {
    burst();
    __delay_us(END_OF_FRAME_BURST);
    pause();
}

void output_repeat(void (*burst)(void), void (*pause)(void)) {
    burst();
    __delay_us(LEADER_BURST);
    pause();
    __delay_us(REPEAT_PAUSE);
}

void output_byte(uint8_t raw, void (*burst)(void), void (*pause)(void)) {
    for (uint8_t i=0; i<8; i++) {
        if ((raw >> i) & 0x01) {
            output_bit_one(burst, pause);
        } 
        else {
            output_bit_zero(burst, pause);    
        }
    }
}

void init_nec32_frame(nec32_frame *frame, uint8_t address, uint8_t data, void (*burst)(void), void (*pause)(void)) {
    frame->address = address;
    frame->address_inv = ~address;
    frame->data = data;
    frame->data_inv = ~data;
    frame->burst = burst;
    frame->pause = pause;
}

void update_nec32_frame(nec32_frame *frame, uint8_t address, uint8_t data) {
    frame->address = address;
    frame->address_inv = ~address;
    frame->data = data;
    frame->data_inv = ~data;
}

void send_nec32_frame(nec32_frame *frame) {
    output_leader(frame->burst, frame->pause);
    output_byte(frame->address, frame->burst, frame->pause);
    output_byte(frame->address_inv, frame->burst, frame->pause);
    output_byte(frame->data, frame->burst, frame->pause);
    output_byte(frame->data_inv, frame->burst, frame->pause);
    output_end_of_frame(frame->burst, frame->pause);
}

void repeat_nec32_frame(nec32_frame *frame) {
    output_repeat(frame->burst, frame->pause);
    output_end_of_frame(frame->burst, frame->pause);
}

void burst() {
    /* PWM output enabled */
    PWM1CONbits.OE = 1U;
}

void pause() {
    /* PWM output disabled */
    PWM1CONbits.OE = 0U;
    
    /* Output forced to low */
    o_nec_low();
}
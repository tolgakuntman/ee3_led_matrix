/* 
 * File:   led_shift.h
 * Author: tolgakuntman
 *
 * Modified: March 29, 2025
 */

#ifndef LED_SHIFT_H
#define LED_SHIFT_H

#include <stdint.h>
#include "led_matrix.h"

// ==================== MATRIX 1 (Original) ====================
#define DATA1_SetHigh()     LATDbits.LATD1 = 1
#define DATA1_SetLow()      LATDbits.LATD1 = 0
#define CLOCK1_SetHigh()    LATDbits.LATD2 = 1
#define CLOCK1_SetLow()     LATDbits.LATD2 = 0
#define STROBE1_SetHigh()   LATDbits.LATD0 = 1
#define STROBE1_SetLow()    LATDbits.LATD0 = 0

#define ROW10_SetLow()      LATAbits.LATA4 = 0
#define ROW10_SetHigh()     LATAbits.LATA4 = 1
#define ROW11_SetLow()      LATAbits.LATA3 = 0
#define ROW11_SetHigh()     LATAbits.LATA3 = 1
#define ROW12_SetLow()      LATAbits.LATA2 = 0
#define ROW12_SetHigh()     LATAbits.LATA2 = 1
#define ROW13_SetLow()      LATAbits.LATA1 = 0
#define ROW13_SetHigh()     LATAbits.LATA1 = 1
#define ROW14_SetLow()      LATAbits.LATA0 = 0
#define ROW14_SetHigh()     LATAbits.LATA0 = 1

// ==================== MATRIX 2 (New) ====================
// NOTE: Update these pins to match your second matrix wiring!
#define DATA2_SetHigh()     LATDbits.LATD5 = 1
#define DATA2_SetLow()      LATDbits.LATD5 = 0
#define CLOCK2_SetHigh()    LATDbits.LATD6 = 1
#define CLOCK2_SetLow()     LATDbits.LATD6 = 0
#define STROBE2_SetHigh()   LATDbits.LATD4 = 1
#define STROBE2_SetLow()    LATDbits.LATD4 = 0

#define ROW20_SetLow()      LATBbits.LATB3 = 0
#define ROW20_SetHigh()     LATBbits.LATB3 = 1
#define ROW21_SetLow()      LATFbits.LATF4 = 0
#define ROW21_SetHigh()     LATFbits.LATF4 = 1
#define ROW22_SetLow()      LATFbits.LATF5 = 0
#define ROW22_SetHigh()     LATFbits.LATF5 = 1
#define ROW23_SetLow()      LATFbits.LATF6 = 0
#define ROW23_SetHigh()     LATFbits.LATF6 = 1
#define ROW24_SetLow()      LATFbits.LATF7 = 0
#define ROW24_SetHigh()     LATFbits.LATF7 = 1

// ==================== Function Prototypes ====================

// MATRIX 1
void SetRow_Matrix1(uint8_t row);
void LEDMatrix_TimerISR(void);
void LEDMatrix_RowController_TimerISR(void);

// MATRIX 2
void SetRow_Matrix2(uint8_t row);
void LEDMatrix2_TimerISR(void);
void LEDMatrix2_RowController_TimerISR(void);

#endif // LED_SHIFT_H

#include "led_shift.h"
#include <xc.h>
#include "mcc_generated_files/system/system.h"

// ========== MATRIX 1 ========== //
volatile uint16_t shiftData_1 = 0;
volatile uint16_t clearOutData_1 = 0xFFFF;
volatile uint8_t bitIndex_1 = 0;
volatile uint8_t state_1 = 0;
volatile uint8_t clearOff_1 = 0;

// ========== MATRIX 2 ========== //
volatile uint16_t shiftData_2 = 0;
volatile uint16_t clearOutData_2 = 0xFFFF;
volatile uint8_t bitIndex_2 = 0;
volatile uint8_t state_2 = 0;
volatile uint8_t clearOff_2 = 0;

void LEDMatrix_RowController_TimerISR(void) {
    static uint8_t row = 0;
    
    PIR3bits.TMR2IF = 0;
    TMR4_Stop();

    shiftData_1 = getRowData(row);
    shiftData_2 = getRowData_Matrix2(row);

    row = (row + 1) % MATRIX_SIZE;

    TMR2_Start();  // Start shifting both matrices
}

void LEDMatrix_TimerISR(void) {
    static uint8_t clockState = 0;
    static uint8_t currentRow = 0;

    PIR3bits.TMR2IF = 0;

    switch (state_1) {
        case 0:
            if (bitIndex_1 == 0) {
                clockState = 0;
                SetRow_Matrix1(currentRow);
                SetRow_Matrix2(currentRow);
            }

            // Set data lines
            if ((clearOff_1 ? clearOutData_1 : shiftData_1) & 0x8000)
                DATA1_SetHigh();
            else
                DATA1_SetLow();

            if ((clearOff_2 ? clearOutData_2 : shiftData_2) & 0x8000)
                DATA2_SetHigh();
            else
                DATA2_SetLow();

            state_1 = 1;
            break;

        case 1:
            if (clockState == 0) {
                CLOCK1_SetHigh();
                CLOCK2_SetHigh();
                clockState = 1;
            } else {
                CLOCK1_SetLow();
                CLOCK2_SetLow();
                clockState = 0;

                if (clearOff_1) clearOutData_1 <<= 1;
                else            shiftData_1 <<= 1;

                if (clearOff_2) clearOutData_2 <<= 1;
                else            shiftData_2 <<= 1;

                bitIndex_1++;
                if (bitIndex_1 >= 16) {
                    bitIndex_1 = 0;
                    state_1 = 2;
                } else {
                    state_1 = 0;
                }
            }
            break;

        case 2:
            STROBE1_SetHigh();
            STROBE2_SetHigh();
            state_1 = 3;
            break;

        case 3:
            STROBE1_SetLow();
            STROBE2_SetLow();

            if (clearOff_1) {
                clearOutData_1 = 0xFFFF;
                clearOutData_2 = 0xFFFF;
                currentRow = (currentRow + 1) % MATRIX_SIZE;
                clearOff_1 = 0;
                clearOff_2 = 0;
                state_1 = 0;
            } else {
                clearOff_1 = 1;
                clearOff_2 = 1;
                state_1 = 0;
                TMR2_Stop();
                TMR4_Start();
            }
            break;
    }
}


void SetRow_Matrix1(uint8_t row) {
    ROW10_SetLow(); ROW11_SetLow(); ROW12_SetLow(); ROW13_SetLow(); ROW14_SetLow();
    switch (row) {
        case 0: ROW10_SetHigh(); break;
        case 1: ROW11_SetHigh(); break;
        case 2: ROW12_SetHigh(); break;
        case 3: ROW13_SetHigh(); break;
        case 4: ROW14_SetHigh(); break;
    }
}



void LEDMatrix2_RowController_TimerISR(void){
    static uint8_t row = 0;
    PIR5bits.TMR3IF = 0;
    TMR0_Stop();
    shiftData_2 = getRowData_Matrix2(row);
    row = (row + 1) % MATRIX_SIZE;
    TMR1_Start();
}

void LEDMatrix2_TimerISR(void) {
    static uint8_t clockState = 0;
    static uint8_t currentRow = 0;
    PIR3bits.TMR1IF = 0;

    switch (state_2) {
        case 0:
            if (bitIndex_2 == 0) {
                clockState = 0;
                SetRow_Matrix2(currentRow);
            }
            if ((clearOff_2 ? clearOutData_2 : shiftData_2) & 0x8000) {
                DATA2_SetHigh();
            } else {
                DATA2_SetLow();
            }
            state_2 = 1;
            break;

        case 1:
            if (clockState == 0) {
                CLOCK2_SetHigh();
                clockState = 1;
            } else {
                CLOCK2_SetLow();
                clockState = 0;

                if (clearOff_2) clearOutData_2 <<= 1;
                else shiftData_2 <<= 1;

                bitIndex_2++;
                if (bitIndex_2 >= 16) {
                    bitIndex_2 = 0;
                    state_2 = 2;
                } else {
                    state_2 = 0;
                }
            }
            break;

        case 2:
            STROBE2_SetHigh();
            state_2 = 3;
            break;

        case 3:
            STROBE2_SetLow();
            if (clearOff_2) {
                clearOutData_2 = 0xFFFF;
                currentRow = (currentRow + 1) % MATRIX_SIZE;
                clearOff_2 = 0;
                state_2 = 0;
            } else {
                clearOff_2 = 1;
                state_2 = 0;
                TMR1_Stop();
                TMR0_Start();
            }
            break;
    }
}

void SetRow_Matrix2(uint8_t row) {
    ROW20_SetLow(); ROW21_SetLow(); ROW22_SetLow(); ROW23_SetLow(); ROW24_SetLow();
    switch (row) {
        case 0: ROW20_SetHigh(); break;
        case 1: ROW21_SetHigh(); break;
        case 2: ROW22_SetHigh(); break;
        case 3: ROW23_SetHigh(); break;
        case 4: ROW24_SetHigh(); break;
    }
}

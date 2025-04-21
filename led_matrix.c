#include <xc.h>
#include "led_matrix.h"

// Matrix 1: Original
static uint16_t ledMatrix[MATRIX_SIZE];

// Matrix 2: New
static uint16_t ledMatrix2[MATRIX_SIZE];

// ===================== MATRIX 1 =====================
uint16_t getRowData(uint8_t row) {
    return ledMatrix[row];
}

void updateLedMatrices(uint8_t* payload){
    for (uint8_t i = 0; i < MATRIX_SIZE; i++) {
        ledMatrix[i] = ((uint16_t)payload[i * 2 + 1] << 8) | payload[i * 2];
        ledMatrix2[i] = ((uint16_t)payload[MATRIX_SIZE*2 + i * 2 + 1] << 8) | payload[10 + i * 2];
    }
}

void initLEDMatrixBlue(void) {
    for (uint8_t i = 0; i < MATRIX_SIZE; i++) {
        ledMatrix[i] = 0xFFFF;  // Start with all LEDs off
        for (uint8_t j = 0; j < MATRIX_SIZE; j++) {
            ledMatrix[i] &= ~(1 << (j * 3 + 2)); // Turn ON blue (active low)
            ledMatrix[i] |=  (1 << (j * 3));     // Turn OFF red
            ledMatrix[i] |=  (1 << (j * 3 + 1)); // Turn OFF green
        }
    }
}

void setLEDToRed(uint8_t row, uint8_t column) {
    if (row >= MATRIX_SIZE || column >= MATRIX_SIZE) return;
    ledMatrix[row] |=  (1 << (column * 3 + 2)); // off blue
    ledMatrix[row] |=  (1 << (column * 3 + 1)); // off green
    ledMatrix[row] &= ~(1 << (column * 3));     // on red
}

void setLEDToGreen(uint8_t row, uint8_t column) {
    if (row >= MATRIX_SIZE || column >= MATRIX_SIZE) return;
    ledMatrix[row] |=  (1 << (column * 3 + 2)); // off blue
    ledMatrix[row] |=  (1 << (column * 3));     // off red
    ledMatrix[row] &= ~(1 << (column * 3 + 1)); // on green
}

void setLEDToBlue(uint8_t row, uint8_t column) {
    if (row >= MATRIX_SIZE || column >= MATRIX_SIZE) return;
    ledMatrix[row] &= ~(1 << (column * 3 + 2)); // on blue
    ledMatrix[row] |=  (1 << (column * 3));     // off red
    ledMatrix[row] |=  (1 << (column * 3 + 1)); // off green
}

// ===================== MATRIX 2 =====================
uint16_t getRowData_Matrix2(uint8_t row) {
    return ledMatrix2[row];
}

void initLEDMatrixBlue_Matrix2(void) {
    for (uint8_t i = 0; i < MATRIX_SIZE; i++) {
        ledMatrix2[i] = 0xFFFF;  // Start with all LEDs off
        for (uint8_t j = 0; j < MATRIX_SIZE; j++) {
            ledMatrix2[i] &= ~(1 << (j * 3 + 1)); // ON blue (bit 1)
            ledMatrix2[i] |=  (1 << (j * 3));     // OFF red (bit 0)
            ledMatrix2[i] |=  (1 << (j * 3 + 2)); // OFF green (bit 2)
        }
    }
}

void setLEDToRed_Matrix2(uint8_t row, uint8_t column) {
    if (row >= MATRIX_SIZE || column >= MATRIX_SIZE) return;
    ledMatrix2[row] |=  (1 << (column * 3 + 1)); // off blue
    ledMatrix2[row] |=  (1 << (column * 3 + 2)); // off green
    ledMatrix2[row] &= ~(1 << (column * 3));     // on red
}

void setLEDToGreen_Matrix2(uint8_t row, uint8_t column) {
    if (row >= MATRIX_SIZE || column >= MATRIX_SIZE) return;
    ledMatrix2[row] |=  (1 << (column * 3 + 1)); // off blue
    ledMatrix2[row] |=  (1 << (column * 3));     // off red
    ledMatrix2[row] &= ~(1 << (column * 3 + 2)); // on green (bit 2)
}

void setLEDToBlue_Matrix2(uint8_t row, uint8_t column) {
    if (row >= MATRIX_SIZE || column >= MATRIX_SIZE) return;
    ledMatrix2[row] &= ~(1 << (column * 3 + 1)); // on blue (bit 1)
    ledMatrix2[row] |=  (1 << (column * 3));     // off red
    ledMatrix2[row] |=  (1 << (column * 3 + 2)); // off green
}

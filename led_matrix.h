/* 
 * File:   led_matrix.h
 * Author: tolgakuntman
 *
 * Modified on March 29, 2025 to support dual LED matrices
 */

#ifndef LED_MATRIX_H
#define	LED_MATRIX_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MATRIX_SIZE 5

void updateLedMatrices(uint8_t* payload);
// ================= MATRIX 1 =================
void initLEDMatrixBlue(void);
void setLEDToRed(uint8_t row, uint8_t column);
void setLEDToGreen(uint8_t row, uint8_t column);
uint16_t getRowData(uint8_t row);

// ================= MATRIX 2 =================
void initLEDMatrixBlue_Matrix2(void);
void setLEDToRed_Matrix2(uint8_t row, uint8_t column);
void setLEDToGreen_Matrix2(uint8_t row, uint8_t column);
uint16_t getRowData_Matrix2(uint8_t row);

#ifdef	__cplusplus
}
#endif

#endif	/* LED_MATRIX_H */

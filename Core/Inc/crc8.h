/*
 * crc8.h
 *
 *  Created on: Jun 3, 2026
 *      Author: Olegd
 */

#ifndef INC_CRC8_H_
#define INC_CRC8_H_

#include "stdint.h"
#include "stddef.h"

uint8_t crc8_calculate(const uint8_t *data, size_t lenght);

#endif /* INC_CRC8_H_ */

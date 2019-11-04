/* LibreSolar charge controller firmware
 * Copyright (c) 2016-2019 Martin Jäger (www.libre.solar)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ADC_DMA_H
#define ADC_DMA_H

/** @file
 *
 * @brief Reads ADC via DMA and stores data into necessary structs
 */

#include "dcdc.h"
#include "load.h"
#include "bat_charger.h"

#define ADC_FILTER_CONST 5          // filter multiplier = 1/(2^ADC_FILTER_CONST)

/** Struct to definie upper and lower limit alerts for any ADC channel
 */
typedef struct {
    void *callback = NULL;                  ///< Function to be called when limits are exceeded
    uint16_t upper_limit = UINT16_MAX;      ///< ADC reading for upper limit
    uint16_t lower_limit = 0;               ///< ADC reading for lower limit
    uint32_t err_flag_upper = 0;            ///< Error flag to raise at upper limit
    uint32_t err_flag_lower = 0;            ///< Error flag to raise at lower limit
    int debounce_counter;                   ///< Can be used to prevent triggering at fist occurence
} AdcAlert;

/** Sets offset to actual measured value, i.e. sets zero current point.
 *
 * All input/output switches and consumers should be switched off before calling this function
 */
void calibrate_current_sensors();

/** Updates structures with data read from ADC
 */
void update_measurements();

/** Initializes registers and starts ADC timer
 */
void adc_timer_start(int freq_Hz);

/** Sets necessary ADC registers
 */
void adc_setup(void);

/** Sets necessary DMA registers
 */
void dma_setup(void);

/** Read, filter and check raw ADC readings stored by DMA controller
 */
void adc_update_value(unsigned int pos);

/** Set limits where an alert should be triggered after reading the ADC values
 */
void adc_set_alerts();

#endif /* ADC_DMA */

/*
    __dht222_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __dht222_driver.h
@brief    DHT22_2 Driver
@mainpage DHT22_2 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   DHT222
@brief      DHT22_2 Click Driver
@{

| Global Library Prefix | **DHT222** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Oct 2018.**      |
| Developer             | **Nenad Filipovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _DHT222_H_
#define _DHT222_H_

/** 
 * @macro T_DHT222_P
 * @brief Driver Abstract type 
 */
#define T_DHT222_P    const uint8_t*

/** @defgroup DHT222_COMPILE Compilation Config */              /** @{ */

//  #define   __DHT222_DRV_SPI__                            /**<     @macro __DHT222_DRV_SPI__  @brief SPI driver selector */
   #define   __DHT222_DRV_I2C__                            /**<     @macro __DHT222_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __DHT222_DRV_UART__                           /**<     @macro __DHT222_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup DHT222_VAR Variables */                           /** @{ */


extern const uint8_t _DHT222_I2C_ADDRESS;
extern const uint8_t _DHT222_HUMIDITY_DATA_REG;
extern const uint8_t _DHT222_TEMPERATURE_DATA_REG;
extern const uint8_t _DHT222_READ_REG;
extern const uint8_t _DHT222_MODEL_DATA_REG;
extern const uint8_t _DHT222_USERS_REG_1;
extern const uint8_t _DHT222_USERS_REG_2;
extern const uint8_t _DHT222_VERSION_DATA_REG;
extern const uint8_t _DHT222_ID_DATA_REG;
                                                                       /** @} */
/** @defgroup DHT222_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup DHT222_INIT Driver Initialization */              /** @{ */

#ifdef   __DHT222_DRV_SPI__
void dht222_spiDriverInit(T_DHT222_P gpioObj, T_DHT222_P spiObj);
#endif
#ifdef   __DHT222_DRV_I2C__
void dht222_i2cDriverInit(T_DHT222_P gpioObj, T_DHT222_P i2cObj, uint8_t slave);
#endif
#ifdef   __DHT222_DRV_UART__
void dht222_uartDriverInit(T_DHT222_P gpioObj, T_DHT222_P uartObj);
#endif


/** @defgroup DHT222_FUNC Driver Functions */                   /** @{ */


/**
 * @brief Generic read 8-bit data function
 *
 * @param[in] address                    8-bit address of data that has to be read
 *
 * @return response                      8-bit data from given address
 *
 * Function read 8-bit data from 8-bit register address.
 */
uint8_t dht222_readByte( uint8_t address );

/**
 * @brief Generic read 16-bit data function
 *
 * @param[in] address                    8-bit address of data that has to be read
 *
 * @return result                        16-bit data from given address
 *
 * Function read 16-bit data from 8-bit register address.
 */
uint16_t dht222_readData( uint8_t address );

/**
 * @brief Reads 32-bit value from given address
 *
 * @param[in] address                    8-bit address of data that has to be read
 *
 * @return result                        32-bit data from given address
 *
 * Function read 32-bit data from 8-bit register address.
 */
uint32_t dht222_readAllData( uint8_t address );

/**
 * @brief Reads temperature from AM2322 sensor
 *
 * @return temperature                   
 * 16-bit temperature data
 *
 * The function calculate the temperature data from sensor data reading from
 * the sensor AM2322 on the DHT22 2 Click.
 *
 * @note
 * The 16-bit temperature data should be divided by 10
 * to obtain the exact temperature value in degrees Celsius [ °C ].
 */
uint16_t dht222_getTemperature();

/**
 * @brief Reads humidity from AM2322 sensor
 *
 * @return humidity
 * 16-bit humidity data
 *
 * The function calculate the humidity data from sensor data reading from
 * the sensor AM2322 on the DHT22 2 Click.
 *
 * @note
 * The 16-bit humidity data should be divided by 10
 * to obtain the exact percentage of humidity [ % RH ].
 */
uint16_t dht222_getHumidity();
 
/**
 * @brief Get model of AM2322 sensor
 *
 * @return model                         16-bit model data
 *
 * Function read from the model register of AM2322 sensor and
 * return 16-bit model data.
 */
uint16_t dht222_getModel();

/**
 * @brief Get users register 1 of AM2322 sensor
 *
 * @return usersRegister                 16-bit users register data
 *
 * Function read from the users register 1 of AM2322 sensor and
 * return 16-bit users register 1 data.
 */
uint16_t dht222_getUsersReg1();

/**
 * @brief Get users register 2 of AM2322 sensor
 *
 * @return usersRegister                 16-bit users register data
 *
 * Function read from the users register 2 of AM2322 sensor and
 * return 16-bit users register 2 data.
 */
uint16_t dht222_getUsersReg2();
 
/**
 * @brief Get version of AM2322 sensor
 *
 * @return version                         16-bit version data
 *
 * Function read from the version register of AM2322 sensor and
 * return 16-bit version data.
 */
uint8_t dht222_getVersion();

/**
 * @brief Get ID of AM2322 sensor
 *
 * @return ID                              16-bit version data
 *
 * Function read from the ID register of AM2322 sensor and
 * return 16-bit ID data.
 */
uint32_t dht222_getId();





                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_DHT22_2_STM.c
    @example Click_DHT22_2_TIVA.c
    @example Click_DHT22_2_CEC.c
    @example Click_DHT22_2_KINETIS.c
    @example Click_DHT22_2_MSP.c
    @example Click_DHT22_2_PIC.c
    @example Click_DHT22_2_PIC32.c
    @example Click_DHT22_2_DSPIC.c
    @example Click_DHT22_2_AVR.c
    @example Click_DHT22_2_FT90x.c
    @example Click_DHT22_2_STM.mbas
    @example Click_DHT22_2_TIVA.mbas
    @example Click_DHT22_2_CEC.mbas
    @example Click_DHT22_2_KINETIS.mbas
    @example Click_DHT22_2_MSP.mbas
    @example Click_DHT22_2_PIC.mbas
    @example Click_DHT22_2_PIC32.mbas
    @example Click_DHT22_2_DSPIC.mbas
    @example Click_DHT22_2_AVR.mbas
    @example Click_DHT22_2_FT90x.mbas
    @example Click_DHT22_2_STM.mpas
    @example Click_DHT22_2_TIVA.mpas
    @example Click_DHT22_2_CEC.mpas
    @example Click_DHT22_2_KINETIS.mpas
    @example Click_DHT22_2_MSP.mpas
    @example Click_DHT22_2_PIC.mpas
    @example Click_DHT22_2_PIC32.mpas
    @example Click_DHT22_2_DSPIC.mpas
    @example Click_DHT22_2_AVR.mpas
    @example Click_DHT22_2_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __dht222_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */
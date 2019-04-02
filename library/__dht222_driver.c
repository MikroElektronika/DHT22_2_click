/*    __dht222_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__dht222_driver.h"
#include "__dht222_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __DHT222_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* I2C Address */
const uint8_t _DHT222_I2C_ADDRESS                                        = 0x5C;

/* Register Address */
const uint8_t _DHT222_HUMIDITY_DATA_REG                                  = 0x00;
const uint8_t _DHT222_TEMPERATURE_DATA_REG                               = 0x02;
const uint8_t _DHT222_READ_REG                                           = 0x03;
const uint8_t _DHT222_MODEL_DATA_REG                                     = 0x08;
const uint8_t _DHT222_USERS_REG_1                                        = 0x10;
const uint8_t _DHT222_USERS_REG_2                                        = 0x12;
const uint8_t _DHT222_VERSION_DATA_REG                                   = 0x0A;
const uint8_t _DHT222_ID_DATA_REG                                        = 0x0B;

/* Command */
const uint8_t _DHT222_WAKE_DATA_CMD                                      = 0x00;
const uint8_t _DHT222_READ_REQUEST_4_BYTE_CMD                            = 0x04;
const uint8_t _DHT222_READ_REQUEST_2_BYTE_CMD                            = 0x02;
const uint8_t _DHT222_READ_REQUEST_1_BYTE_CMD                            = 0x01;


/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static uint16_t _calculateCRC( uint8_t *ptr, uint8_t len );

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static uint16_t _calculateCRC( uint8_t *ptr, uint8_t len )
{
    uint16_t crc = 65535;
    uint8_t i;
    
    while( len-- )
    {
        crc ^= *ptr;

        ptr++;

        for( i=0; i<8; i++ )
        {
            if( crc & 0x01 )
            {
                crc >>= 1;
                crc ^= 40961;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __DHT222_DRV_SPI__

void dht222_spiDriverInit(T_DHT222_P gpioObj, T_DHT222_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __DHT222_DRV_I2C__

void dht222_i2cDriverInit(T_DHT222_P gpioObj, T_DHT222_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __DHT222_DRV_UART__

void dht222_uartDriverInit(T_DHT222_P gpioObj, T_DHT222_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif



/* ----------------------------------------------------------- IMPLEMENTATION */



/* Generic read 8-bit data function */
uint8_t dht222_readByte( uint8_t address )
{
    uint8_t wakeData[] = { _DHT222_WAKE_DATA_CMD,_DHT222_WAKE_DATA_CMD };
    uint8_t readData[ 3 ];
    uint8_t response[ 5 ];
    uint16_t result;
    readData[ 0 ] = _DHT222_READ_REG;
    readData[ 1 ] = address;
    readData[ 2 ] = _DHT222_READ_REQUEST_1_BYTE_CMD;
      
    while (1)
    {
        hal_i2cStart();
        hal_i2cWrite( _slaveAddress, wakeData, 0, END_MODE_STOP );
        
        Delay_10us();
        
        hal_i2cStart();

        if ( hal_i2cWrite( _slaveAddress, readData, 3, END_MODE_STOP ) != 0 )
        {
            Delay_10us();
            
            hal_i2cStart();
            hal_i2cWrite( _slaveAddress, wakeData, 0, END_MODE_STOP );
        }
        else
        {
            Delay_10us();
            
            hal_i2cStart();
            hal_i2cRead( _slaveAddress, response, 5, END_MODE_STOP );

            result = response[ 4 ];
            result <<= 8;
            result |= response[ 3 ];
            
            if ( _calculateCRC( response, 3 ) == result )
                break;
          }
    }
    
    return response[ 2 ];
}

/* Generic read 16-bit data function */
uint16_t dht222_readData( uint8_t address )
{
    uint8_t wakeData[] = { _DHT222_WAKE_DATA_CMD, _DHT222_WAKE_DATA_CMD };
    uint8_t readData[ 3 ];
    uint8_t response[ 6 ];
    uint16_t checkIsCorrect;
    uint16_t result;
      
    readData[ 0 ] = _DHT222_READ_REG;
    readData[ 1 ] = address;
    readData[ 2 ] = _DHT222_READ_REQUEST_2_BYTE_CMD;
      
    while ( 1 )
    {
        hal_i2cStart();
        hal_i2cWrite( _slaveAddress, wakeData, 0, END_MODE_STOP );
        
        Delay_10us();
        
        hal_i2cStart();
    
        if ( hal_i2cWrite( _slaveAddress, readData, 3, END_MODE_STOP ) != 0 )
        {
            Delay_10us();
            
            hal_i2cStart();
            hal_i2cWrite( _slaveAddress, wakeData, 0, END_MODE_STOP );
        }
        else
        {
            Delay_10us();
            
            hal_i2cStart();
            hal_i2cRead( _slaveAddress,response, 6, END_MODE_STOP );
            
            checkIsCorrect = response[ 5 ];
            checkIsCorrect <<= 8;
            checkIsCorrect |= response[ 4 ];
     
            if ( _calculateCRC( response, 4 ) == checkIsCorrect )
                break;
        }
    }
      
    result = response[ 2 ];
    result <<= 8;
    result |= response[ 3 ];
      
    return result;
}

/* Generic read 32-bit data function */
uint32_t dht222_readAllData( uint8_t address )
{
    uint8_t wakeData[] = { _DHT222_WAKE_DATA_CMD, _DHT222_WAKE_DATA_CMD };
    uint8_t readData[ 3 ];
    uint8_t response[ 8 ];
    uint16_t checkIsCorrect;
    uint16_t result;
    
    readData[ 0 ] = _DHT222_READ_REG;
    readData[ 1 ] = address;
    readData[ 2 ] = _DHT222_READ_REQUEST_4_BYTE_CMD;
      
    while (1)
    {
        hal_i2cStart();
        hal_i2cWrite( _slaveAddress, wakeData, 0, END_MODE_STOP );
        
        Delay_10us();

        hal_i2cStart();
    
        if ( hal_i2cWrite( _slaveAddress, readData, 3, END_MODE_STOP ) != 0 )
        {
            Delay_10us();
            
            hal_i2cStart();
            hal_i2cWrite( _slaveAddress, wakeData, 0, END_MODE_STOP );
        }
        else
        {
            Delay_10us();
            
            hal_i2cStart();
            hal_i2cRead( _slaveAddress, response, 8, END_MODE_STOP );

            checkIsCorrect = response[ 7 ];
            checkIsCorrect <<= 8;
            checkIsCorrect |= response[ 6 ];

            if ( _calculateCRC( response, 6 ) == checkIsCorrect )
                break;
        }
    }
    
    result = response[ 2 ];
    result <<= 8;
    result |= response[ 3 ];
    result <<= 8;
    result |= response[ 4 ];
    result <<= 8;
    result |= response[ 5 ];
    
    return result;
}

/* Reads temperature from AM2322 sensor */
uint16_t dht222_getTemperature()
{
    uint16_t temperature;
    
    temperature = dht222_readData( _DHT222_TEMPERATURE_DATA_REG );
    
    return temperature;
}

/* Reads humidity from AM2322 sensor */
uint16_t dht222_getHumidity()
{
    uint16_t humidity;

    humidity = dht222_readData( _DHT222_HUMIDITY_DATA_REG );

    return humidity;
}

/* Get model of AM2322 sensor */
uint16_t dht222_getModel()
{
    return dht222_readData( _DHT222_MODEL_DATA_REG );
}

/* Get users register 1 of AM2322 sensor */
uint16_t dht222_getUsersReg1()
{
    return dht222_readData( _DHT222_USERS_REG_1 );
}

/* Get users register 2 of AM2322 sensor */
uint16_t dht222_getUsersReg2()
{
    return dht222_readData( _DHT222_USERS_REG_2 );
}

/* Get version of AM2322 sensor */
uint8_t dht222_getVersion()
{
    return dht222_readByte( _DHT222_VERSION_DATA_REG );
}

/* Get ID of AM2322 sensor */
uint32_t dht222_getId()
{
    return dht222_readAllData( _DHT222_ID_DATA_REG );
}



/* -------------------------------------------------------------------------- */
/*
  __dht222_driver.c

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
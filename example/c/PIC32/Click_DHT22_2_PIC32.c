/*
Example for DHT22_2 Click

    Date          : Oct 2018.
    Author        : Nenad Filipovic

Test configuration PIC32 :
    
    MCU                : P32MX795F512L
    Dev. Board         : EasyPIC Fusion v7
    PIC32 Compiler ver : v4.0.0.0

---

Description :

- System Initialization - Initializes I2C and LOG structures.
- Application Initialization - Initialization driver enable's - I2C and start write log.
- Application Task - (code snippet) This is a example which demonstrates the use of DHT22 2 Click board.
     DHT22 2 Click communicates with register via I2C protocol read data from register,
     measured temperature and humidity data from the AM2322 sensor.
     Convert temperature data to degrees Celsius [ ºC ] and
     humidity data to percentarg [ % ].
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs on usb uart for aproximetly every 5 sec.

Additional Functions :

- dht222_displayTempHum() - Write log of humidity and temperature value as a two-digit number.

*/

#include "Click_DHT22_2_types.h"
#include "Click_DHT22_2_config.h"


uint16_t temperature;
uint16_t humidity;
char logText[50];

void dht222_displayTempHum()
{
    mikrobus_logWrite( "   Humidity   : ", _LOG_TEXT );
    IntToStr( humidity / 10, logText );
    ltrim( logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( ".", _LOG_TEXT );
    IntToStr( humidity % 10, logText );
    ltrim( logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( " %", _LOG_LINE );

    mikrobus_logWrite( "   Temperature: ", _LOG_TEXT );
    IntToStr( temperature / 10, logText );
    ltrim( logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( ".", _LOG_TEXT );
    IntToStr( temperature % 10, logText );
    ltrim( logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( " °C", _LOG_LINE );
    mikrobus_logWrite( "--------------------------", _LOG_LINE );
}

void systemInit()
{
    mikrobus_i2cInit( _MIKROBUS1, &_DHT222_I2C_CFG[0] );

    mikrobus_logInit( _LOG_USBUART_A, 9600 );

    Delay_ms( 100 );
}

void applicationInit()
{
    dht222_i2cDriverInit( (T_DHT222_P)&_MIKROBUS1_GPIO, (T_DHT222_P)&_MIKROBUS1_I2C, _DHT222_I2C_ADDRESS );

    Delay_ms( 500 );

    mikrobus_logWrite( "--------------------------", _LOG_LINE );
    mikrobus_logWrite( "       DHT22 2 Click      ", _LOG_LINE );
    mikrobus_logWrite( "--------------------------", _LOG_LINE );
    mikrobus_logWrite( "  Temperature & Humidity  ", _LOG_LINE );
    mikrobus_logWrite( "--------------------------", _LOG_LINE );
}

void applicationTask()
{
    temperature = dht222_getTemperature();

    Delay_1sec();

    humidity = dht222_getHumidity();

    dht222_displayTempHum();

    Delay_ms( 5000 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}
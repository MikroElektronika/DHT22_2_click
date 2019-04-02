![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# DHT22_2 Click

- **CIC Prefix**  : DHT222
- **Author**      : Nenad Filipovic
- **Verison**     : 1.0.0
- **Date**        : Oct 2018.

---


### Software Support

We provide a library for the DHT22_2 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2226/dht22-2-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library covers all the necessary functions to control DHT22 2 Click board. 
Library performs the communication with the device via I2C driver by  reading from registers.
Library have generic read function, get temperature and humidity data from register
and converts temperature data to degree Celsius [ °C ] and humidity value to percentage [ % ].

Key functions :

- ``` float dht222_getTemperature() ``` - Reads temperature data from AM2322 sensor
- ``` float dht222_getHumidity() ``` - Reads humidity data from AM2322 sensor


**Examples Description**

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


```.c

void applicationTask()
{
    temperature = dht222_getTemperature();

    Delay_1sec();

    humidity = dht222_getHumidity();

    dht222_displayTempHum();

    Delay_ms( 5000 );
}

```

Additional Functions :

- dht222_displayTempHum() - Write log of humidity and temperature value as a two-digit number.

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2226/dht22-2-click) page.

Other mikroE Libraries used in the example:

- I2C
- UART
- Conversions

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---

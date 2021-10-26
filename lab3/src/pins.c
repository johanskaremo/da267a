#include "pins.h"
#include "driver/gpio.h"
#define LED_PIN_1 12


// initialises the 4 pins
// init the 2 LEDs pins as output and the 2 buttons' pins as input
void initPins()
{
    gpio_config_t config;
    config.pin_bit_mask = (u_int64_t)1 << LED_PIN_1;
    config.mode = GPIO_MODE_OUTPUT;
    config.pull_up_en = 0;
    config.pull_down_en = 0;
    gpio_config(&config);

}

// switches LED A on if level!=0 or off if level==0
void setLED(uint8_t level)
{
    if (level)
    {
        gpio_set_level(LED_PIN_1, 1);
    }
    else
    {
        gpio_set_level(LED_PIN_1, 0);
    }
}
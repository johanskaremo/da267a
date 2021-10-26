#include "pins.h"
#include "driver/gpio.h"

#define LED_PIN_1 12
#define LED_PIN_2 14
#define BUTTON_1 26
#define BUTTON_2 27

// initialises the 4 pins
// init the 2 LEDs pins as output and the 2 buttons' pins as input
void initPins()
{
    gpio_config_t config;
    config.pin_bit_mask = (u_int64_t)1 << LED_PIN_1;
    config.pin_bit_mask |= (u_int64_t)1 << LED_PIN_2;
    config.mode = GPIO_MODE_OUTPUT;
    config.pull_up_en = 0;
    config.pull_down_en = 0;
    gpio_config(&config);

    config.pin_bit_mask = (u_int64_t)1 << BUTTON_1;
    config.pin_bit_mask |= (u_int64_t)1 << BUTTON_2;
    config.mode = GPIO_MODE_INPUT;
    config.pull_up_en = 1;
    config.pull_down_en = 0;
    gpio_config(&config);
}

// switches LED A on if level!=0 or off if level==0
void setLEDA(uint8_t level)
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

// switches LED B on if level!=0 or off if level==0
void setLEDB(uint8_t level)
{
    if (level)
    {
        gpio_set_level(LED_PIN_2, 1);
    }
    else
    {
        gpio_set_level(LED_PIN_2, 0);
    }
}

// tells if button A is currently being pressed
// read the value of button A by "gpio_get_level"
// return 1 if A is pressed, 0 otherwise
uint8_t isButtonAPressed()
{
    return !gpio_get_level(BUTTON_2);
}

// tells if button B is currently being pressed
uint8_t isButtonBPressed()
{
    return !gpio_get_level(BUTTON_1);
}
#include "sampler.h"
#include "driver/timer.h"
#include <esp_task_wdt.h>
#include <driver/dac.h>
#include <soc/dac_channel.h>
#include <esp32/rom/ets_sys.h>
#include <soc/adc_channel.h>
#include "hal/adc_types.h"
#include "driver/adc_common.h"

esp_timer_handle_t timer;
int prevSample = 0;
int counterCrossings = 0;
int voltageConst = 1050;
float samplefreq = 0;
int64_t startTime;

void startSampling(int freq)
{
    samplefreq = 0;
    counterCrossings = 0;
    //start adc
    adc_power_acquire();

    adc_gpio_init(ADC_UNIT_1, ADC1_GPIO32_CHANNEL);
    adc1_config_channel_atten(ADC1_GPIO32_CHANNEL, ADC_ATTEN_11db);     //väljer kanal samt hur hög signalen
    adc1_config_width(ADC_WIDTH_BIT_12);    //  hur många steg per V                      skall vara(ca3,9V)

    //start timer at freq (int freq)
    esp_timer_init();
    esp_timer_create_args_t config;
    config.name = "wave_timer";
    config.arg = NULL;
    config.callback = &timerCallback;               //adderar callbackMetod till timern

    esp_err_t res = esp_timer_create(&config, &timer);          //skapa timern
    ESP_ERROR_CHECK(res);

    int periodMicro = (1000000 / freq);             //period för timern och dess calback
    res = esp_timer_start_periodic(timer, periodMicro);         //starta timer

    startTime = esp_timer_get_time();               //tiden när timern skapas för senare period för freq
}

void timerCallback(void *arg)
{
    int val = adc1_get_raw(ADC1_GPIO32_CHANNEL);
    if (prevSample < voltageConst && val > voltageConst)     //else och if för att kolla crossings
    {
        counterCrossings++;
    }
    else if (prevSample > voltageConst && val < voltageConst)
    {
        counterCrossings++;
    }
    prevSample = val;               //sätter senaste värdet till previous-värdet
}

void stopSampling()
{
    esp_timer_stop(timer);                  //stäng av timer
    int64_t endtime = esp_timer_get_time();         //tar tiden när vi stänger av timern
    int64_t uSecPeriodic = (endtime - startTime);       //ny period
    printf("%d , %lld\n", counterCrossings, uSecPeriodic);
    samplefreq = (1000000 * (float)counterCrossings) / (float)(2 * uSecPeriodic);  //räkna ut frekvensen
}                                                                           //från samplern

float getFrequency()
{
    return samplefreq;
}
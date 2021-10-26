#include <esp_task_wdt.h>
#include "pins.h"
#include "random.h"

void waitMs(unsigned int millis);

void app_main()
{
    initPins();

    while (1)
    {
        int random = getRandomsecs(3000, 5000);
        uint8_t winner = 0;

        //loop switching lights "game is loading"
        for (int i = 0; i < 5; i++)
        {
            setLEDA(1);
            setLEDB(0);
            waitMs(300);
            setLEDA(0);
            setLEDB(1);
            waitMs(300);
        }

        setLEDA(0);             //turn of both
        setLEDB(0);

        waitMs(random);

        setLEDA(1);             //switch on both
        setLEDB(1);

        while (!winner)
        {

            if (isButtonAPressed())
            {
                setLEDA(1);
                setLEDB(0);
                winner = 1;
            }
            else if (isButtonBPressed())
            {
                setLEDB(1);
                setLEDA(0);
                winner = 1;
            }
        }
        waitMs(5000);
    }
}
void waitMs(unsigned int millis)
{
    TickType_t delay = millis / portTICK_PERIOD_MS;
    vTaskDelay(delay);
}
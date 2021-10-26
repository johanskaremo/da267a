#include "random.h"
#include <esp_system.h>

int getRandomsecs(int min, int max)
{
    float random = (float)esp_random() / __UINT32_MAX__;
    return (random * (max - min) + min);
}
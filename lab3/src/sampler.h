#ifndef SAMPLER_H_
#define SAMPLER_H_

void startSampling(int freq);

void stopSampling();

void timerCallback(void* arg);

float getFrequency();

#endif
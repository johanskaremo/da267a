#include <Arduino.h>
#include <stdio.h>
#define FREQ 1000
#define heartsensor_input 32
#define led_output 25

int threshhold_upper = 3900;
int threshhold_lower = 2300; //fel eller vad fan?
int theshholdcounter = 0;
bool onPeak = false;
volatile int interrupt_counter;
unsigned long myTime;
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
static uint16_t outvalue = 0; //float?
static float invalue = 0;
time_t newtime = 0;
time_t oldtime = 0;


void IRAM_ATTR onTime()
{
  portENTER_CRITICAL_ISR(&timerMux);
  interrupt_counter++;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  pinMode(heartsensor_input, INPUT_PULLUP);
  pinMode(led_output, OUTPUT);
  pinMode(GPIO_NUM_33, OUTPUT);
  Serial.begin(115200);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTime, true);

  // Sets an alarm to sound every milisec
  timerAlarmWrite(timer, 1000000/FREQ, true);
  timerAlarmEnable(timer); 
}

void loop() {

    if(interrupt_counter > 0){
        portENTER_CRITICAL(&timerMux);
        interrupt_counter--;
        portEXIT_CRITICAL(&timerMux);
        myTime = millis();

      outvalue = analogRead(heartsensor_input);
      Serial.println(outvalue);

      if(threshhold_upper < outvalue && onPeak == false){    //HUR SKA DETTA GÖRAS
      newtime = now
        digitalWrite(33, HIGH);
        onPeak = true;
        60/timenow-oldtime;
        oldtime=timenow;
      }
      if(outvalue < threshhold_lower && onPeak == true){
        digitalWrite(33, LOW);
      }
    }

}
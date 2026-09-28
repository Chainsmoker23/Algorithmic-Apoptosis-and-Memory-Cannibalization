#ifndef AOF_HANDLER_H
#define AOF_HANDLER_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

namespace AAMC {

    // RTOS Task that preempts normal operations when AOF is received
    void IRAM_ATTR AOF_Reception_Task(void *pvParameters);

    // Helper functions for peripheral suspension
    void suspendSensingADCs();
    void reallocateMemoryProxy();

}

#endif

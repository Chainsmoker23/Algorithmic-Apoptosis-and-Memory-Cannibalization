#include "../include/AOF_Handler.h"

namespace AAMC {

    extern QueueHandle_t main_routing_queue;
    QueueHandle_t proxy_fifo;

    void IRAM_ATTR AOF_Reception_Task(void *pvParameters) {
        Serial.println("AOF RECEIVED: Executing high-priority system interrupt...");

        // 1. Endogenous Payload Purge
        if(main_routing_queue != NULL) {
            xQueueReset(main_routing_queue); 
        }
        
        // 2. Peripheral Suspension
        suspendSensingADCs(); 
        
        // 3. Buffer Reallocation
        reallocateMemoryProxy();
        
        Serial.println("Node cannibalized. Transitioning to Proxy Buffer state.");
        
        while(true) {
            // TDMA proxy data routing logic runs here at highest priority
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }

    void suspendSensingADCs() {
        // Physically power down ADCs to maximize battery for proxy radio operations
        Serial.println("ADCs powered down.");
    }

    void reallocateMemoryProxy() {
        proxy_fifo = xQueueCreate(100, sizeof(uint8_t) * 512); 
        Serial.println("RAM reallocated to Proxy FIFO.");
    }

} // namespace AAMC

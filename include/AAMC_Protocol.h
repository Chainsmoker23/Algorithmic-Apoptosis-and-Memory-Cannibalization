#ifndef AAMC_PROTOCOL_H
#define AAMC_PROTOCOL_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "SurvivalDeficit.h"

namespace AAMC {

    class Protocol {
    public:
        Protocol();
        void init();
        void updateQueueOccupancy(int current_size);
        void evaluateSaturation();
        bool isNodeCannibalized();
        void setUtilityWeight(float weight);

    private:
        float ewma_saturation_rate;
        int current_queue_occupancy;
        int previous_queue_occupancy;
        int consecutive_crisis_count;
        bool proxy_mode_active;
        float node_utility_weight;

        void executeTriage();
        void transmitAOF(uint16_t target_id);
    };

} // namespace AAMC

#endif

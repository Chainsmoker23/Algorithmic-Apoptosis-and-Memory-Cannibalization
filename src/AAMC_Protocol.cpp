#include "../include/AAMC_Protocol.h"
#include "../include/SurvivalDeficit.h"

namespace AAMC {

    const float RHO_SMOOTHING = 0.125;
    const float TAU_CRISIS_SEC = 0.5;
    const int BUFFER_CAPACITY = 50;
    const int CONSECUTIVE_CRISIS_LIMIT = 3;
    const float MONITORING_INTERVAL_SEC = 0.1;

    Protocol::Protocol() : ewma_saturation_rate(0.0), current_queue_occupancy(0), 
                           previous_queue_occupancy(0), consecutive_crisis_count(0), 
                           proxy_mode_active(false), node_utility_weight(1.0) {}

    void Protocol::init() {
        Serial.println("AA-MC Protocol Initialized.");
    }

    void Protocol::updateQueueOccupancy(int current_size) {
        current_queue_occupancy = current_size;
    }

    void Protocol::evaluateSaturation() {
        float raw_saturation_rate = (current_queue_occupancy - previous_queue_occupancy) / MONITORING_INTERVAL_SEC;
        ewma_saturation_rate = (1.0 - RHO_SMOOTHING) * ewma_saturation_rate + (RHO_SMOOTHING * raw_saturation_rate);
        previous_queue_occupancy = current_queue_occupancy;

        if (ewma_saturation_rate > 0) {
            float estimated_time_to_failure = (BUFFER_CAPACITY - current_queue_occupancy) / ewma_saturation_rate;
            if (estimated_time_to_failure < TAU_CRISIS_SEC) {
                consecutive_crisis_count++;
            } else {
                consecutive_crisis_count = 0;
            }
        } else {
            consecutive_crisis_count = 0;
        }

        if (consecutive_crisis_count >= CONSECUTIVE_CRISIS_LIMIT) {
            executeTriage();
            consecutive_crisis_count = 0; // Reset after triage
        }
    }

    void Protocol::executeTriage() {
        Serial.println("CRISIS DETECTED: Initiating target acquisition...");
        uint16_t target_id = calculateHighestSDS();
        
        if (target_id != 0) {
            transmitAOF(target_id);
        } else {
            Serial.println("Triage Failed: No expendable neighbors available.");
        }
    }

    void Protocol::transmitAOF(uint16_t target_id) {
        Serial.printf("Transmitting Apoptosis Override Frame (AOF) to Node %d\n", target_id);
        // MAC layer implementation for SIFS bypass goes here
    }

    bool Protocol::isNodeCannibalized() {
        return proxy_mode_active;
    }

    void Protocol::setUtilityWeight(float weight) {
        node_utility_weight = weight;
    }

} // namespace AAMC

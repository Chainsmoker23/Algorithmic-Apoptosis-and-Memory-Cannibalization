#ifndef SURVIVAL_DEFICIT_H
#define SURVIVAL_DEFICIT_H

#include <Arduino.h>

namespace AAMC {

    struct NeighborState {
        uint16_t id;
        float residual_energy_ratio; 
        float available_buffer_ratio; 
        float utility_weight;        
    };

    // Configuration weights
    extern const float OMEGA_E;
    extern const float OMEGA_B;

    void updateNeighborState(uint16_t id, float energy, float buffer, float utility);
    uint16_t calculateHighestSDS();

} // namespace AAMC

#endif

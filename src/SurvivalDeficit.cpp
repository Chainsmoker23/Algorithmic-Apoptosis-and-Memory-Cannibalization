#include "../include/SurvivalDeficit.h"

namespace AAMC {

    const float OMEGA_E = 0.5; // Battery weight
    const float OMEGA_B = 0.5; // Buffer weight

    #define MAX_NEIGHBORS 20
    NeighborState neighborhood[MAX_NEIGHBORS];
    int num_neighbors = 0;

    void updateNeighborState(uint16_t id, float energy, float buffer, float utility) {
        for (int i = 0; i < num_neighbors; i++) {
            if (neighborhood[i].id == id) {
                neighborhood[i].residual_energy_ratio = energy;
                neighborhood[i].available_buffer_ratio = buffer;
                neighborhood[i].utility_weight = utility;
                return;
            }
        }
        if (num_neighbors < MAX_NEIGHBORS) {
            neighborhood[num_neighbors++] = {id, energy, buffer, utility};
        }
    }

    uint16_t calculateHighestSDS() {
        float max_sds = -1.0;
        uint16_t target_id = 0;

        for (int i = 0; i < num_neighbors; i++) {
            NeighborState n = neighborhood[i];
            
            // Equation: SDS = [wE*(E_res/E_init) + wB*((B-q)/B)] * (1/U)
            float sds = (OMEGA_E * n.residual_energy_ratio + OMEGA_B * n.available_buffer_ratio) * (1.0 / n.utility_weight);
            
            if (sds > max_sds) {
                max_sds = sds;
                target_id = n.id;
            }
        }
        return target_id;
    }

} // namespace AAMC

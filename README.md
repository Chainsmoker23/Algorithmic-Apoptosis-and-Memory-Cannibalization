# Algorithmic Apoptosis and Memory Cannibalization (AA-MC)

This repository contains the core conceptual implementation of the **Algorithmic Apoptosis and Memory Cannibalization (AA-MC)** hierarchical triage protocol for high-stress IoT Networks, tailored for ESP32 microcontrollers running FreeRTOS.

## Structure
- `include/`: Header files for the main protocol, queue monitoring, and the Apoptosis Override Frame (AOF) handler.
- `src/`: Core logic implementation for the Saturation Calculus and the Survival Deficit Score (SDS).

## Overview
AA-MC abandons traditional egalitarian load-balancing. When a critical relay gateway detects imminent buffer collapse during an environmental anomaly (e.g., flash flood), it calculates the Survival Deficit Score of its neighbors. 
The gateway targets a high-resource, low-utility neighbor and preempts its standard operations via an AOF, forcing the target to reallocate its RAM as a dedicated proxy FIFO buffer.

## Note
The full OMNeT++ simulation suite is available upon reasonable request to the corresponding author of the manuscript.

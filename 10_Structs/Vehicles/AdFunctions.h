
#ifndef AD_FUNCTIONS_H
#define AD_FUNCTIONS_H

#include <stdint.h>
#include <stdio.h>

#include "AdConstants.h"
#include "AdTypes.h"

void init_ego_vehicle(VehicleType *ego_vehicle);

void init_vehicles(NeighborVehiclesType *vehicles);

void print_vehicle(const VehicleType *vehicle);

void print_neighbor_vehicles(const NeighborVehiclesType *vehicles);

void print_scene(const VehicleType *vehicle, const NeighborVehiclesType *vehicles);

void handle_lateral_user_input(uint32_t *lane_idx, char lateral_action);

void handle_longitudinal_user_input(float *speed_mps, char longitudinal_action);

void get_user_input(float *speed_mps, uint32_t *lane_idx);


#endif // AD_FUNCTIONS_H

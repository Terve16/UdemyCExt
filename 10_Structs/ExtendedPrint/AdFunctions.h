
#ifndef AD_FUNCTIONS_H
#define AD_FUNCTIONS_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "AdConstants.h"
#include "AdTypes.h"

float kph_to_mps(const float kph);

void init_ego_vehicle(VehicleType *ego_vehicle);

void init_vehicle(VehicleType *vehicle,
                  const int32_t id,
                  const float speed_mps,
                  const float distance_m,
                  const LaneAssociationType lane);

void init_vehicles(NeighborVehiclesType *vehicles);

void print_vehicle(const VehicleType *vehicle);

void print_neighbor_vehicles(const NeighborVehiclesType *vehicles);

void print_scene_line(const VehicleType *vehicle, char *string);

void print_scene(const VehicleType *vehicle, const NeighborVehiclesType *vehicles);

#endif // AD_FUNCTIONS_H


#ifndef AD_FUNCTIONS_H
#define AD_FUNCTIONS_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "AdConstants.h"
#include "AdTypes.h"

float kph_to_mps(const float kph);

float mps_to_kph(const float mps);

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

void compute_future_distance(VehicleType *vehicle, const float ego_driven_distance, const float seconds);

void compute_future_state(const VehicleType *ego_vehicle, NeighborVehiclesType *vehicles, const float seconds);

void decrease_speed(VehicleType *ego_vehicle);

void longitudinal_control(const VehicleType *front_vehicle, VehicleType *ego_vehicle);

#endif // AD_FUNCTIONS_H

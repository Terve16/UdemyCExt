
#ifndef AD_TYPES_H
#define AD_TYPES_H

#include <stdint.h>

typedef enum
{
    LANE_ASSOCIATION_TYPE_NONE,
    LANE_ASSOCIATION_TYPE_RIGHT,
    LANE_ASSOCIATION_TYPE_CENTER,
    LANE_ASSOCIATION_TYPE_LEFT
} LaneAssociationType;

typedef enum
{
    LONGITUDINAL_ACTION_NONE,
    LONGITUDINAL_ACTION_INCREASE = 'w',
    LONGITUDINAL_ACTION_DECREASE = 's'
} LongitudinalAction;

typedef enum
{
    LATERAL_ACTION_NONE,
    LATERAL_ACTION_LEFT = 'a',
    LATERAL_ACTION_RIGHT = 'd'
} LateralAction;

typedef struct
{
    int32_t id;
    LaneAssociationType lane;
    float speed_mps;
    float distance_m;
} VehicleType;

typedef struct
{
    VehicleType vehicles_left_lane[NUM_VEHICLES_ON_LANE];
    VehicleType vehicles_center_lane[NUM_VEHICLES_ON_LANE];
    VehicleType vehicles_right_lane[NUM_VEHICLES_ON_LANE];
} NeighborVehiclesType;

#endif // AD_TYPES_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AdConstants.h"
#include "AdDataLoader.h"
#include "AdFunctions.h"
#include "AdTypes.h"

#include "utils.h"

static VehicleType EGO_VEHICLE_DATA;
static VehicleType VEHICLE_DATA[NUM_VEHICLES][NUM_CYCLES];

void preload_ego_vehicle_data(const char datapath[128])
{
    char file_path[128] = {'\0'};
    strncpy(file_path, datapath, 128);
    strncat(file_path, "ego_data.txt", 20);

    FILE *file_pointer = fopen(file_path, "r");

    if (file_pointer == NULL)
        return;

    EGO_VEHICLE_DATA.id = EGO_VEHICLE_ID;
    EGO_VEHICLE_DATA.distance_m = 0.0f;

    uint32_t lane_temp;
    float speed_temp;

    fscanf(file_pointer, "Lane: %d\n", &lane_temp);
    fscanf(file_pointer, "Speed: %f\n", &speed_temp);

    switch (lane_temp)
    {
    case LANE_ASSOCIATION_TYPE_RIGHT:
    {
        EGO_VEHICLE_DATA.lane = LANE_ASSOCIATION_TYPE_RIGHT;
        break;
    }
    case LANE_ASSOCIATION_TYPE_CENTER:
    {
        EGO_VEHICLE_DATA.lane = LANE_ASSOCIATION_TYPE_CENTER;
        break;
    }
    case LANE_ASSOCIATION_TYPE_LEFT:
    {
        EGO_VEHICLE_DATA.lane = LANE_ASSOCIATION_TYPE_LEFT;
        break;
    }
    case LANE_ASSOCIATION_TYPE_NONE:
    default:
    {
        EGO_VEHICLE_DATA.lane = LANE_ASSOCIATION_TYPE_NONE;
        break;
    }
    }
    EGO_VEHICLE_DATA.speed_mps = speed_temp;

    fclose(file_pointer);
}

void preload_vehicle_data(const char datapath[128])
{
    for (size_t i = 0; i < NUM_VEHICLES; i++)
    {
        char file_path[128] = {'\0'};
        strncpy(file_path, datapath, 128);
        strncat(file_path, "vehicle_", 20);

        char temp[5] = {'\0'};
        sprintf(temp, "%d", i); // snprintf

        strncat(file_path, temp, 20);
        strncat(file_path, "_data.txt", 20);

        FILE *file_pointer = fopen(file_path, "r");

        if (file_pointer == NULL)
            continue;

        uint32_t lane_temp;
        LaneAssociationType lane_temp2;
        float distance_temp;
        float speed_temp;

        fscanf(file_pointer, "Lane: %d\n", &lane_temp);
        fscanf(file_pointer, "Distance: %f\n", &distance_temp);

        switch (lane_temp)
        {
        case LANE_ASSOCIATION_TYPE_RIGHT:
        {
            lane_temp2 = LANE_ASSOCIATION_TYPE_RIGHT;
            break;
        }
        case LANE_ASSOCIATION_TYPE_CENTER:
        {
            lane_temp2 = LANE_ASSOCIATION_TYPE_CENTER;
            break;
        }
        case LANE_ASSOCIATION_TYPE_LEFT:
        {
            lane_temp2 = LANE_ASSOCIATION_TYPE_LEFT;
            break;
        }
        case LANE_ASSOCIATION_TYPE_NONE:
        default:
        {
            lane_temp2 = LANE_ASSOCIATION_TYPE_NONE;
            break;
        }
        }

        for (size_t j = 0; j < NUM_CYCLES; j++)
        {
            int32_t temp = 0u;

            fscanf(file_pointer, "Speed %d: %f\n", &temp, &speed_temp);

            assert(j == temp);

            VEHICLE_DATA[i][j].id = i;
            VEHICLE_DATA[i][j].lane = lane_temp2;
            VEHICLE_DATA[i][j].speed_mps = speed_temp;
            VEHICLE_DATA[i][j].distance_m = distance_temp;
        }

        fclose(file_pointer);
    }
}

// The functions below will be implemented in the next exercise
void init_ego_vehicle(VehicleType *ego_vehicle)
{
}

void init_vehicle(VehicleType *vehicle, const int32_t id, const uint32_t cycle)
{
}

void init_vehicles(NeighborVehiclesType *vehicles)
{
}

void load_cycle(NeighborVehiclesType *vehicles, const uint32_t cycle)
{
}

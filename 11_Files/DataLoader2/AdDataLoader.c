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

    fscanf(file_pointer, "Lane: %u\n", &lane_temp);
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
        sprintf(temp, "%lu", i); // snprintf

        strncat(file_path, temp, 20);
        strncat(file_path, "_data.txt", 20);

        FILE *file_pointer = fopen(file_path, "r");

        if (file_pointer == NULL)
            continue;

        uint32_t lane_temp;
        LaneAssociationType lane_temp2;
        float distance_temp;
        float speed_temp;

        fscanf(file_pointer, "Lane: %u\n", &lane_temp);
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
            uint32_t temp = 0u;

            fscanf(file_pointer, "Speed %u: %f\n", &temp, &speed_temp);

            assert(j == temp);

            VEHICLE_DATA[i][j].id = i;
            VEHICLE_DATA[i][j].lane = lane_temp2;
            VEHICLE_DATA[i][j].speed_mps = speed_temp;
            VEHICLE_DATA[i][j].distance_m = distance_temp;
        }

        fclose(file_pointer);
    }
}

void init_ego_vehicle(VehicleType *ego_vehicle)
{
    if (ego_vehicle == NULL)
        return;

    ego_vehicle->id = EGO_VEHICLE_DATA.id;
    ego_vehicle->lane = EGO_VEHICLE_DATA.lane;
    ego_vehicle->speed_mps = EGO_VEHICLE_DATA.speed_mps;
    ego_vehicle->distance_m = EGO_VEHICLE_DATA.distance_m;
}

void init_vehicle(VehicleType *vehicle, const int32_t id, const uint32_t cycle)
{
    if (vehicle == NULL || id < 0 || id > NUM_VEHICLES || cycle > NUM_CYCLES)
        return;

    vehicle->id = VEHICLE_DATA[id][cycle].id;
    vehicle->lane = VEHICLE_DATA[id][cycle].lane;
    vehicle->speed_mps = VEHICLE_DATA[id][cycle].speed_mps;
    vehicle->distance_m = VEHICLE_DATA[id][cycle].distance_m;
}

void init_vehicles(NeighborVehiclesType *vehicles)
{
    if (vehicles == NULL || vehicles->vehicles_left_lane == NULL || vehicles->vehicles_center_lane == NULL ||
        vehicles->vehicles_right_lane == NULL)
        return;

    uint32_t right_lane_idx = 0u;
    uint32_t center_lane_idx = 0u;
    uint32_t left_lane_idx = 0u;

    for (size_t i = 0; i < NUM_VEHICLES; i++)
    {
        switch (VEHICLE_DATA[i][0].lane)
        {
        case LANE_ASSOCIATION_TYPE_RIGHT:
        {
            if (right_lane_idx < NUM_VEHICLES_ON_LANE)
            {
                init_vehicle(&(vehicles->vehicles_right_lane[right_lane_idx]), i, 0u);
                right_lane_idx++;
            }
            break;
        }
        case LANE_ASSOCIATION_TYPE_CENTER:
        {
            if (center_lane_idx < NUM_VEHICLES_ON_LANE)
            {
                init_vehicle(&(vehicles->vehicles_center_lane[center_lane_idx]), i, 0u);
                center_lane_idx++;
            }
            break;
        }
        case LANE_ASSOCIATION_TYPE_LEFT:
        {
            if (left_lane_idx < NUM_VEHICLES_ON_LANE)
            {
                init_vehicle(&(vehicles->vehicles_left_lane[left_lane_idx]), i, 0u);
                left_lane_idx++;
            }
            break;
        }
        case LANE_ASSOCIATION_TYPE_NONE:
        default:
        {
            break;
        }
        }
    }
}

void load_cycle(NeighborVehiclesType *vehicles, const uint32_t cycle)
{
    if (vehicles == NULL || vehicles->vehicles_left_lane == NULL || vehicles->vehicles_center_lane == NULL ||
        vehicles->vehicles_right_lane == NULL || cycle > NUM_CYCLES)
        return;

    uint32_t right_lane_idx = 0u;
    uint32_t center_lane_idx = 0u;
    uint32_t left_lane_idx = 0u;

    float distance_temp = 0.0f;

    for (size_t i = 0; i < NUM_VEHICLES; i++)
    {
        switch (VEHICLE_DATA[i][cycle].lane)
        {
        case LANE_ASSOCIATION_TYPE_RIGHT:
        {
            if (right_lane_idx < NUM_VEHICLES_ON_LANE)
            {
                distance_temp = vehicles->vehicles_right_lane[right_lane_idx].distance_m;
                init_vehicle(&(vehicles->vehicles_right_lane[right_lane_idx]), i, cycle);
                vehicles->vehicles_right_lane[right_lane_idx].distance_m = distance_temp;
                right_lane_idx++;
            }
            break;
        }
        case LANE_ASSOCIATION_TYPE_CENTER:
        {
            if (center_lane_idx < NUM_VEHICLES_ON_LANE)
            {
                distance_temp = vehicles->vehicles_center_lane[center_lane_idx].distance_m;
                init_vehicle(&(vehicles->vehicles_center_lane[center_lane_idx]), i, cycle);
                vehicles->vehicles_center_lane[center_lane_idx].distance_m = distance_temp;
                center_lane_idx++;
            }
            break;
        }
        case LANE_ASSOCIATION_TYPE_LEFT:
        {
            if (left_lane_idx < NUM_VEHICLES_ON_LANE)
            {
                distance_temp = vehicles->vehicles_left_lane[left_lane_idx].distance_m;
                init_vehicle(&(vehicles->vehicles_left_lane[left_lane_idx]), i, cycle);
                vehicles->vehicles_left_lane[left_lane_idx].distance_m = distance_temp;
                left_lane_idx++;
            }
            break;
        }
        case LANE_ASSOCIATION_TYPE_NONE:
        default:
        {
            break;
        }
        }
    }
}

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

    fscanf(file_pointer, "Lane: %d\n", &(EGO_VEHICLE_DATA.lane));
    fscanf(file_pointer, "Speed: %f\n", &(EGO_VEHICLE_DATA.speed_mps));

    /*
    // obtain file size:
    fseek(file_pointer, 0, SEEK_END);
    size_t lSize = ftell(file_pointer);
    rewind(file_pointer);

    // allocate memory to contain the whole file:
    char *buffer = (char *)malloc(sizeof(char) * lSize);
    if (buffer == NULL)
    {
        fclose(file_pointer);
        return;
    }

    // copy the file into the buffer:
    size_t result = fread(buffer, 1, lSize, file_pointer);
    if (result != lSize)
    {
        fclose(file_pointer);
        free(buffer);
        return;
    }

    // the whole file is now loaded in the memory buffer.

    // terminate
    free(buffer);

*/
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
        sprintf(temp, "%d", i);

        strncat(file_path, temp, 20);
        strncat(file_path, "_data.txt", 20);

        FILE *file_pointer = fopen(file_path, "r");

        if (file_pointer == NULL)
            continue;

        VEHICLE_DATA[i][0].id = i;

        fscanf(file_pointer, "Lane: %d\n", &(VEHICLE_DATA[i][0].lane));
        fscanf(file_pointer, "Distance: %f\n", &(VEHICLE_DATA[i][0].distance_m));

        for (size_t j = 0; j < NUM_CYCLES; j++)
        {
            int32_t temp = 0u;
            fscanf(file_pointer, "Speed %d: %f\n", &temp, &(VEHICLE_DATA[i][j].speed_mps));
            assert(j == temp);
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

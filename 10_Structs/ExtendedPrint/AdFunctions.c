

#include "AdFunctions.h"

float kph_to_mps(const float kph)
{
    return kph / 3.6f;
}

void init_ego_vehicle(VehicleType *ego_vehicle)
{
    if (ego_vehicle == NULL)
        return;

    ego_vehicle->id = EGO_VEHICLE_ID;
    ego_vehicle->lane = LANE_ASSOCIATION_TYPE_CENTER;
    ego_vehicle->speed_mps = kph_to_mps(80);
    ego_vehicle->distance_m = 0;
}

void init_vehicle(VehicleType *vehicle,
                  const int32_t id,
                  const float speed_mps,
                  const float distance_m,
                  const LaneAssociationType lane)
{
    if (vehicle == NULL)
        return;

    vehicle->id = id;
    vehicle->lane = lane;
    vehicle->speed_mps = speed_mps;
    vehicle->distance_m = distance_m;
}

void init_vehicles(NeighborVehiclesType *vehicles)
{
    init_vehicle(&(vehicles->vehicles_left_lane[0]), 1, kph_to_mps(130.0f), 80.0f, LANE_ASSOCIATION_TYPE_LEFT);
    init_vehicle(&(vehicles->vehicles_left_lane[1]), 2, kph_to_mps(80.0f), -20.0f, LANE_ASSOCIATION_TYPE_LEFT);

    init_vehicle(&(vehicles->vehicles_center_lane[0]), 3, kph_to_mps(80.0f), 50.0f, LANE_ASSOCIATION_TYPE_CENTER);
    init_vehicle(&(vehicles->vehicles_center_lane[1]), 4, kph_to_mps(120.0f), -50.0f, LANE_ASSOCIATION_TYPE_CENTER);

    init_vehicle(&(vehicles->vehicles_right_lane[0]), 5, kph_to_mps(110.0f), 30.0f, LANE_ASSOCIATION_TYPE_RIGHT);
    init_vehicle(&(vehicles->vehicles_right_lane[1]), 6, kph_to_mps(90.0f), -30.0f, LANE_ASSOCIATION_TYPE_RIGHT);
}

void print_vehicle(const VehicleType *vehicle)
{
    printf("ID: %d\n", vehicle->id);
    printf("Speed (m/s): %f\n", vehicle->speed_mps);
    printf("Distance (m): %f\n", vehicle->distance_m);
    printf("Lane: %d\n", vehicle->lane);
}

void print_neighbor_vehicles(const NeighborVehiclesType *vehicles)
{
    print_vehicle(&(vehicles->vehicles_left_lane[0]));
    print_vehicle(&(vehicles->vehicles_left_lane[1]));
    print_vehicle(&(vehicles->vehicles_center_lane[0]));
    print_vehicle(&(vehicles->vehicles_center_lane[1]));
    print_vehicle(&(vehicles->vehicles_right_lane[0]));
    print_vehicle(&(vehicles->vehicles_right_lane[1]));
}

void print_scene_line(const VehicleType *vehicle, char *string)
{
    if (vehicle == NULL && string == NULL)
        return;

    char symbol = (vehicle->id == EGO_VEHICLE_ID) ? 'E' : 'V';

    switch (vehicle->lane)
    {
    case LANE_ASSOCIATION_TYPE_RIGHT:
    {
        if (strncmp(&(string[10]), " ", 1) == 0)
        {
            string[10] = symbol;
        }
        else
        {
            string[10] = 'X';
        }
        break;
    }
    case LANE_ASSOCIATION_TYPE_CENTER:
    {
        if (strncmp(&(string[6]), " ", 1) == 0)
        {
            string[6] = symbol;
        }
        else
        {
            string[6] = 'X';
        }
        break;
    }
    case LANE_ASSOCIATION_TYPE_LEFT:
    {
        if (strncmp(&(string[2]), " ", 1) == 0)
        {
            string[2] = symbol;
        }
        else
        {
            string[2] = 'X';
        }
        break;
    }
    case LANE_ASSOCIATION_TYPE_NONE:
    default:
        break;
    }
}

void print_scene(const VehicleType *vehicle, const NeighborVehiclesType *vehicles)
{
    printf("\n\t  L   C   R ");

    for (int32_t i = 100; i >= -100; i -= 20)
    {
        char string[] = "|   |   |   |";

        if (i == 0)
        {
            print_scene_line(vehicle, string);
            /*
        {
            switch (vehicle->lane)
            {
            case LANE_ASSOCIATION_TYPE_RIGHT:
            {
                right_string = " V ";
                break;
            }
            case LANE_ASSOCIATION_TYPE_CENTER:
            {
                center_string = " V ";
                break;
            }
            case LANE_ASSOCIATION_TYPE_LEFT:
            {
                left_string = " V ";
                break;
            }
            case LANE_ASSOCIATION_TYPE_NONE:
            default:
                break;
            }
            */
        }


        for (int32_t j = 0; j < NUM_VEHICLES_ON_LANE; j++)
        {
            if ((vehicles->vehicles_left_lane[j].distance_m >= i) &&
                (vehicles->vehicles_left_lane[j].distance_m < (i + 20)))
            {
                print_scene_line(&(vehicles->vehicles_left_lane[j]), string);
            }

            if ((vehicles->vehicles_center_lane[j].distance_m >= i) &&
                (vehicles->vehicles_center_lane[j].distance_m < (i + 20)))
            {
                print_scene_line(&(vehicles->vehicles_center_lane[j]), string);
            }

            if ((vehicles->vehicles_right_lane[j].distance_m >= i) &&
                (vehicles->vehicles_right_lane[j].distance_m < (i + 20)))
            {
                print_scene_line(&(vehicles->vehicles_right_lane[j]), string);
            }
        }

        printf("\n%d\t%s", i, string);
    }

    printf("\n");
    //printf("\n\nSpeed: %f\n", vehicle->speed_mps);
}

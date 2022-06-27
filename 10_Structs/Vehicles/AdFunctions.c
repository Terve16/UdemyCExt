

#include "AdFunctions.h"

float kph_to_mps(float kph)
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

void init_vehicle(VehicleType *vehicle, int32_t id, float speed_mps, LaneAssociationType lane, float distance_m)
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
    init_vehicle(&(vehicles->vehicles_left_lane[0]), 1, kph_to_mps(130.0f), LANE_ASSOCIATION_TYPE_LEFT, 80.0f);
    init_vehicle(&(vehicles->vehicles_left_lane[1]), 2, kph_to_mps(80.0f), LANE_ASSOCIATION_TYPE_LEFT, -20.0f);

    init_vehicle(&(vehicles->vehicles_center_lane[0]), 3, kph_to_mps(80.0f), LANE_ASSOCIATION_TYPE_CENTER, 50.0f);
    init_vehicle(&(vehicles->vehicles_center_lane[1]), 4, kph_to_mps(120.0f), LANE_ASSOCIATION_TYPE_CENTER, -50.0f);

    init_vehicle(&(vehicles->vehicles_right_lane[0]), 5, kph_to_mps(110.0f), LANE_ASSOCIATION_TYPE_RIGHT, 30.0f);
    init_vehicle(&(vehicles->vehicles_right_lane[1]), 6, kph_to_mps(90.0f), LANE_ASSOCIATION_TYPE_RIGHT, -30.0f);
}

void print_vehicle(const VehicleType *vehicle)
{
    printf("ID: %d\n", vehicle->id);
    printf("Speed (m/s): %f\n", vehicle->speed_mps);
    printf("Distance (m): %f\n", vehicle->distance_m);
    printf("Lane: %d\n", vehicle->lane);

    /*
    char *left_string = "   ";
    char *center_string = "   ";
    char *right_string = "   ";

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

    printf("|%s|%s|%s|", left_string, center_string, right_string);
*/
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

void print_scene(const VehicleType *vehicle, const NeighborVehiclesType *vehicles)
{
    printf("\n\t  L   C   R ");

    for (int32_t i = 100; i >= -100; i -= 20)
    {
        char *left_string = "   ";
        char *center_string = "   ";
        char *right_string = "   ";

        if (i == 0)
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
        }
        else
        {
            ;
        }

        printf("\n%d\t|%s|%s|%s|", i, left_string, center_string, right_string);
    }

    printf("\n\nSpeed: %f\n", vehicle->speed_mps);
}

void handle_lateral_user_input(uint32_t *lane_idx, char lateral_action)
{
    if (lane_idx == NULL)
        return;

    switch (lateral_action)
    {
    case LATERAL_ACTION_LEFT:
    {
        switch (*lane_idx)
        {
        case LANE_ASSOCIATION_TYPE_LEFT:
        {
            break;
        }
        case LANE_ASSOCIATION_TYPE_CENTER:
        {
            *lane_idx = LANE_ASSOCIATION_TYPE_LEFT;
            break;
        }
        case LANE_ASSOCIATION_TYPE_RIGHT:
        {
            *lane_idx = LANE_ASSOCIATION_TYPE_CENTER;
            break;
        }
        case LANE_ASSOCIATION_TYPE_NONE:
        default:
        {
            break;
        }
        }
        break;
    }
    case LATERAL_ACTION_RIGHT:
    {
        switch (*lane_idx)
        {
        case LANE_ASSOCIATION_TYPE_LEFT:
        {
            *lane_idx = LANE_ASSOCIATION_TYPE_CENTER;
            break;
        }
        case LANE_ASSOCIATION_TYPE_CENTER:
        {
            *lane_idx = LANE_ASSOCIATION_TYPE_RIGHT;
            break;
        }
        case LANE_ASSOCIATION_TYPE_RIGHT:
        {
            break;
        }
        case LANE_ASSOCIATION_TYPE_NONE:
        default:
        {
            break;
        }
        }
        break;
    }
    case LATERAL_ACTION_NONE:
    default:
    {
        break;
    }
    }
}

void handle_longitudinal_user_input(float *speed_mps, char longitudinal_action)
{
    if (speed_mps == NULL)
        return;

    float speed_diff = ((*speed_mps) * LONGITUDINAL_DIFFERENCE_PERCENTAGE);

    switch (longitudinal_action)
    {
    case LONGITUDINAL_ACTION_INCREASE:
    {
        *speed_mps += speed_diff;
        break;
    }
    case LONGITUDINAL_ACTION_DECREASE:
    {
        *speed_mps -= speed_diff;
        break;
    }
    case LONGITUDINAL_ACTION_NONE:
    default:
        break;
    }
}

void get_user_input(float *speed_mps, uint32_t *lane_idx)
{
    if (speed_mps == NULL || lane_idx == NULL)
        return;

    char longitudinal_action;
    printf("\nLongitudinal action (w=Increase, s=Decrease): ");
    scanf(" %c", &longitudinal_action);

    char lateral_action;
    printf("\nLateral action (a=Left, d=Right): ");
    scanf(" %c", &lateral_action);

    printf("\n");

    handle_longitudinal_user_input(speed_mps, longitudinal_action);
    handle_lateral_user_input(lane_idx, lateral_action);
}

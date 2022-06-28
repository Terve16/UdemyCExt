

#include "AdFunctions.h"

float kph_to_mps(const float kph)
{
    return kph / 3.6f;
}

float mps_to_kph(const float mps)
{
    return mps * 3.6f;
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

    const int32_t line_width = 10;

    for (int32_t i = 100; i >= -100; i -= line_width)
    {
        char string[] = "|   |   |   |";

        if (i == 0)
        {
            print_scene_line(vehicle, string);
        }


        for (int32_t j = 0; j < NUM_VEHICLES_ON_LANE; j++)
        {
            if ((vehicles->vehicles_left_lane[j].distance_m >= i) &&
                (vehicles->vehicles_left_lane[j].distance_m < (i + line_width)))
            {
                print_scene_line(&(vehicles->vehicles_left_lane[j]), string);
            }

            if ((vehicles->vehicles_center_lane[j].distance_m >= i) &&
                (vehicles->vehicles_center_lane[j].distance_m < (i + line_width)))
            {
                print_scene_line(&(vehicles->vehicles_center_lane[j]), string);
            }

            if ((vehicles->vehicles_right_lane[j].distance_m >= i) &&
                (vehicles->vehicles_right_lane[j].distance_m < (i + line_width)))
            {
                print_scene_line(&(vehicles->vehicles_right_lane[j]), string);
            }
        }

        printf("\n%d\t%s", i, string);
    }

    printf("\n");
}

void compute_future_distance(VehicleType *vehicle, const float ego_driven_distance, const float seconds)
{
    if (vehicle == NULL)
        return;

    const float driven_distance = (vehicle->speed_mps * seconds);

    vehicle->distance_m += (driven_distance - ego_driven_distance);
}

void compute_future_state(const VehicleType *ego_vehicle, NeighborVehiclesType *vehicles, const float seconds)
{
    if (ego_vehicle == NULL || vehicles == NULL)
        return;

    const float ego_driven_distance = (ego_vehicle->speed_mps * seconds);

    for (int32_t i = 0; i < NUM_VEHICLES_ON_LANE; i++)
    {
        compute_future_distance(&(vehicles->vehicles_left_lane[i]), ego_driven_distance, seconds);
        compute_future_distance(&(vehicles->vehicles_center_lane[i]), ego_driven_distance, seconds);
        compute_future_distance(&(vehicles->vehicles_right_lane[i]), ego_driven_distance, seconds);
    }
}

void decrease_speed(VehicleType *ego_vehicle)
{
    if (ego_vehicle == NULL)
        return;

    ego_vehicle->speed_mps -= (ego_vehicle->speed_mps * LONGITUDINAL_DIFFERENCE_PERCENTAGE);
}

void longitudinal_control(const VehicleType *front_vehicle, VehicleType *ego_vehicle)
{
    if (ego_vehicle == NULL || front_vehicle == NULL)
        return;

    const float front_distance = front_vehicle->distance_m;
    const float front_distance_min = (mps_to_kph(ego_vehicle->speed_mps) / 2);

    if (front_distance < front_distance_min)
    {
        decrease_speed(ego_vehicle);
    }
}

const VehicleType *get_vehicle_array(const LaneAssociationType ego_lane, const NeighborVehiclesType *vehicles)
{
    if (vehicles == NULL)
        return NULL;

    switch (ego_lane)
    {
    case LANE_ASSOCIATION_TYPE_LEFT:
    {
        return vehicles->vehicles_left_lane;
        break;
    }
    case LANE_ASSOCIATION_TYPE_CENTER:
    {
        return vehicles->vehicles_center_lane;
        break;
    }
    case LANE_ASSOCIATION_TYPE_RIGHT:
    {
        return vehicles->vehicles_right_lane;
        break;
    }
    case LANE_ASSOCIATION_TYPE_NONE:
    default:
        break;
    }

    return NULL;
}

LaneAssociationType get_lane_change_request(const VehicleType *ego_vehicle, NeighborVehiclesType *vehicles)
{
    if (ego_vehicle == NULL || vehicles == NULL)
        return LANE_ASSOCIATION_TYPE_NONE;

    LaneAssociationType target_lane = ego_vehicle->lane;

    const VehicleType *vehicle_array = get_vehicle_array(ego_vehicle->lane, vehicles);

    const float min_gap_size = 10.0f;
    float rear_distance = 0.0f;
    float lane_gap[2] = {0.0f};

    lane_gap[0] = vehicle_array[0].distance_m;
    lane_gap[1] = vehicle_array[1].distance_m;

    if (lane_gap[1] < lane_gap[0])
    {
        float temp = lane_gap[1];
        lane_gap[1] = lane_gap[0];
        lane_gap[0] = temp;
    }

    if (lane_gap[0] < 0.0f)
    {
        rear_distance = (lane_gap[0] * -1.0f);
    }
    else
    {
        rear_distance = 200.0f;
    }


    if (rear_distance < (min_gap_size * 2.0f))
    {

        const VehicleType *vehicles_right = NULL;
        const VehicleType *vehicles_left = NULL;

        float right_gap[2] = {0.0f};
        float left_gap[2] = {0.0f};


        switch (ego_vehicle->lane)
        {
        case LANE_ASSOCIATION_TYPE_LEFT:
        {
            vehicles_right = get_vehicle_array(LANE_ASSOCIATION_TYPE_CENTER, vehicles);
            break;
        }
        case LANE_ASSOCIATION_TYPE_CENTER:
        {
            vehicles_right = get_vehicle_array(LANE_ASSOCIATION_TYPE_RIGHT, vehicles);
            vehicles_left = get_vehicle_array(LANE_ASSOCIATION_TYPE_LEFT, vehicles);
            break;
        }
        case LANE_ASSOCIATION_TYPE_RIGHT:
        {
            vehicles_left = get_vehicle_array(LANE_ASSOCIATION_TYPE_CENTER, vehicles);
            break;
        }
        case LANE_ASSOCIATION_TYPE_NONE:
        default:
            break;
        }


        if (vehicles_right != NULL)
        {
            right_gap[0] = fabs(vehicles_right[0].distance_m);
            right_gap[1] = fabs(vehicles_right[1].distance_m);

            if (right_gap[1] < right_gap[0])
            {
                float temp = right_gap[1];
                right_gap[1] = right_gap[0];
                right_gap[0] = temp;
            }
        }
        if (vehicles_left != NULL)
        {
            left_gap[0] = fabs(vehicles_left[0].distance_m);
            left_gap[1] = fabs(vehicles_left[1].distance_m);

            if (left_gap[1] < left_gap[0])
            {
                float temp = left_gap[1];
                left_gap[1] = left_gap[0];
                left_gap[0] = temp;
            }
        }


        switch (ego_vehicle->lane)
        {
        case LANE_ASSOCIATION_TYPE_LEFT:
        {
            if (right_gap[0] > min_gap_size)
            {
                target_lane = LANE_ASSOCIATION_TYPE_CENTER;
            }
            break;
        }
        case LANE_ASSOCIATION_TYPE_CENTER:
        {
            if (right_gap[0] > min_gap_size)
            {
                target_lane = LANE_ASSOCIATION_TYPE_RIGHT;
            }
            else if (left_gap[0] > min_gap_size)
            {
                target_lane = LANE_ASSOCIATION_TYPE_LEFT;
            }
            break;
        }
        case LANE_ASSOCIATION_TYPE_RIGHT:
        {
            if (left_gap[0] > min_gap_size)
            {
                target_lane = LANE_ASSOCIATION_TYPE_CENTER;
            }
            break;
        }
        case LANE_ASSOCIATION_TYPE_NONE:
        default:
            break;
        }
    }

    return target_lane;
}

bool lateral_control(const LaneAssociationType lane_change_request, VehicleType *ego_vehicle)
{
    if (ego_vehicle == NULL)
        return false;

    if (ego_vehicle->lane != lane_change_request)
    {
        ego_vehicle->lane = lane_change_request;
        return true;
    }

    return false;
}



#include "AdFunctions.h"

void print_scene(float speed_mps, uint32_t lane_idx)
{
    printf("\n       L C R\n      ");

    switch (lane_idx)
    {
    case LANE_ASSOCIATION_TYPE_RIGHT:
    {
        printf("| | |v|");
        break;
    }
    case LANE_ASSOCIATION_TYPE_CENTER:
    {
        printf("| |v| |");
        break;
    }
    case LANE_ASSOCIATION_TYPE_LEFT:
    {
        printf("|v| | |");
        break;
    }
    case LANE_ASSOCIATION_TYPE_NONE:
    default:
        printf("| | | |");
        break;
    }

    printf("\n\nSpeed: %f\n", speed_mps);
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

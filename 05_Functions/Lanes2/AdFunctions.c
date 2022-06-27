

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

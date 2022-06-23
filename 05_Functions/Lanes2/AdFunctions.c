

#include "AdFunctions.h"

void print_scene(float speed_mps, uint32_t lane_idx)
{
    printf("\n       L C R\n      ");

    switch (lane_idx)
    {
    case RIGHT_LANE:
    {
        printf("| | |v|");
        break;
    }
    case CENTER_LANE:
    {
        printf("| |v| |");
        break;
    }
    case LEFT_LANE:
    {
        printf("|v| | |");
        break;
    }
    case UNKNOWN_LANE:
    default:
        printf("| | | |");
        break;
    }

    printf("\n\nSpeed: %f\n", speed_mps);
}

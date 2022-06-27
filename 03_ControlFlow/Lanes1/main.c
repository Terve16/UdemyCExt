#include <stdint.h>
#include <stdio.h>

enum LaneAssociationType
{
    LANE_ASSOCIATION_TYPE_NONE = 0,
    LANE_ASSOCIATION_TYPE_RIGHT = 1,
    LANE_ASSOCIATION_TYPE_CENTER = 2,
    LANE_ASSOCIATION_TYPE_LEFT = 3
};

int main()
{
    printf("Create the properties of a vehicle.\n");

    float speed;
    int temp_lane;
    enum LaneAssociationType lane;

    printf("Speed in m/s: ");
    scanf("%f", &speed);

    printf("Lane (1=Right, 2=Center, 3=Left): ");
    scanf("%d", &temp_lane);

    if ((speed >= 0) && (temp_lane > 0) && (temp_lane <= 3))
    {
        lane = (enum LaneAssociationType)temp_lane;

        printf("\n       L C R\n      ");
        switch (lane)
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
            break;
        }

        printf("\n\nSpeed: %f\n", speed);
    }
    else
    {
        printf("Invalid input!");
    }

    return 0;
}

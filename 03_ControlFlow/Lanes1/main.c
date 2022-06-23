#include <stdint.h>
#include <stdio.h>

enum LaneAssociationType
{
    UNKNOWN_LANE = 0,
    RIGHT_LANE = 1,
    CENTER_LANE = 2,
    LEFT_LANE = 3
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

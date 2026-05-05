#include <stdio.h>

#define ITEMS 5
#define CAPACITY 18
//Main function establishing the item and weight
int main() {
    int weight[ITEMS + 1] = {0, 6, 4, 5, 3, 7};
    int value[ITEMS + 1]  = {0, 1600, 1000, 1800, 1200, 2000};

    int dp[ITEMS + 1][CAPACITY + 1];
    int i, w;

    //base case
    for (i = 0; i <= ITEMS; i++) {
        for (w = 0; w <= CAPACITY; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
        }
    }

    // Function to fill in out DP Table.
    for (i = 1; i <= ITEMS; i++) {
        for (w = 1; w <= CAPACITY; w++) {

            //  scenario = skip item
            dp[i][w] = dp[i - 1][w];

            // scenario = keep item if it fits
            if (weight[i] <= w) {
                int keepItem = dp[i - 1][w - weight[i]] + value[i];

                if (keepItem > dp[i][w]) {
                    dp[i][w] = keepItem;
                }
            }
        }
    }

    printf("Maximum Biodiversity Score: %d\n", dp[ITEMS][CAPACITY]);

}

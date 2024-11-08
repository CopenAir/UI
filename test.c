#include <stdio.h>

#define GREEN "[0;32m"
#define RED "[0;31m"
#define RESET_COLOUR "[0m"

void print_chart(float max_val, float threshold, int size, float data[]) {
    int steps = (int)(max_val * 10); // Number of steps for the loop

    for (int step = steps; step >= 0; step--) {
        float i = step / 10.0; // Calculate the floating-point value

        printf("%s", i >= 10.0 ? "" : " ");
        printf("%s%.1f║", i <= threshold ? GREEN : RED, i);

        for (int j = 0; j < size; j++) {
            printf("%s", data[j] >= i ? "███ " : "    ");
        }
        printf("\n%s", RESET_COLOUR);
    }

    printf("    ╚");
    for (int i = 0; i < size; i++) {
        printf("════");
    }
    printf("\n     ");
    for (int i = 1; i <= size; printf("%d   ", i++));
}

int main() {
    float max_val = 10.0;
    float threshold = 5.0;
    int size = 5;
    float data[] = {9.5, 7.2, 5.5, 3.3, 1.0};

    print_chart(max_val, threshold, size, data);

    return 0;
}

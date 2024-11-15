//define colour
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET_COLOUR "\x1b[0m"
#define CLR_SCREEN "\033[H\033[J"

#include <stdio.h>

void draw_graph(int size, float *data, float max_val, float threshold) {
    //TODO: Implement dynamic scalling
    int steps = (int)(max_val * 10);

    for (int step = steps; step >= 0; step--) {
        float i = step / 10.0;

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
    int size = 10;
    float a[10] = {0.5, 0.7, 0.3, 0.8, 0.2, 0.9, 0.4, 0.6, 0.1, 0.5};
    float max_val = 0.9;
    float threshold = 0.5;

    draw_graph(size, a, max_val, threshold);

    return 0;
}

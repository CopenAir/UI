/*  Graph generation engine
    18/10/2024 @ 08:45
    ui_proto.c V1.4.2
    
    Sebastian Lindau-Skands
    slinda24@student.aau.dk*/
#include <stdio.h>
#include "lib/graph_engine.h"

int main() {
    //data declaration (will be handled in CSV backend)
    float a[] = {2.6, 2.9, 2.9, 2.2, 1.7, 1.8, 2.5, 3.5, 3.8, 7.4, 5.8, 9.5, 3.4, 2.3, 1.4};
    int max_val=0;
    int size = sizeof(a) / sizeof(a[0]);

    // find the maximum value in the array and define the threshold
    for(int i = 0; i < size; i++) {if (a[i] > max_val) {max_val = a[i];}}
    int threshold = 3.0;

    printf("Date: 17/10/2024 | Area: A.C.Meyers Vænge\n");
    printf("Substance: PM2.5\n");
    printf("▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n\n");
    generate_table(size, a, max_val, threshold);

    return 0;
}

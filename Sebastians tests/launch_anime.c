//a launch animation for copenAir air monitoring cli application. It should clear the screen, and then draw copenair in a box, from top to bottom, left to right

#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

// Function to clear the terminal screen
void clear_screen() {
    printf("\033[2J\033[1;1H");
}

void animation() {
    clear_screen();
    for (int i = 0; i<80; i++) {
        usleep(10);
        printf("-");
    }
    printf("\nCopenAir\n Air monitoring system\n");
    for (int i = 0; i<80; i++) {
        usleep(10);
        printf("-");
    }
} 

int main() {
    animation();
}


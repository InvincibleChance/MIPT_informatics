#include <stdio.h>
#include <string.h>

int main() {
    int n;
    int x = 0, y = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char direction[50];
        int distance;
        scanf("%s %d", direction, &distance);

        if (strcmp(direction, "North") == 0) {
            y += distance;
        } else if (strcmp(direction, "South") == 0) {
            y -= distance;
        } else if (strcmp(direction, "East") == 0) {
            x += distance;
        } else if (strcmp(direction, "West") == 0) {
            x -= distance;
        }
    }

    printf("%d %d\n", x, y);
}
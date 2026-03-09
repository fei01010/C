#include <stdio.h>
#include <string.h>

int main() {
    char *weekDays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int weekNum[] = {0, 1, 2, 3, 4, 5, 6};
    char input[20];
    int i;
    int found = 0;
    scanf("%s", input);
    
    for (i = 0; i < 7; i++) {
        if (strcmp(input, weekDays[i]) == 0) {
            printf("%d\n", weekNum[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Error\n");
    }

    return 0;
}
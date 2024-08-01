#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr;
    char str[100];

    // Writing to a file
    fptr = fopen("my_file.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("Enter a string to write to the file: ");
    fgets(str, 100, stdin);

    fprintf(fptr, "%s", str);
    fclose(fptr);

    // Reading from the file and printing to the screen
    fptr = fopen("my_file.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("Contents of the file:\n");
    while (fgets(str, 100, fptr) != NULL) {
        printf("%s", str);
    }
    fclose(fptr);

    return 0;
}

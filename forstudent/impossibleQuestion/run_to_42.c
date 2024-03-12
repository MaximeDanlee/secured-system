#include "fcntl.h"
#include "stdio.h"
#include "sys/stat.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("usage: %s number\n", argv[0]);
        exit(1);
    }

    short fileContent;
    FILE *file = fopen("number.txt", "r");

    if (file == NULL) {
        perror("Error opening file, did you run ./init before launching the program ?");
        return 1;
    }

    struct stat stat_data;
    
    if (stat("number.txt", &stat_data) < 0) {
        fprintf(stderr, "Failed to stat number.txt\n");
        exit(1);
    }
    if(stat_data.st_uid != 0)
    {
        fprintf(stderr, "File number.txt should be owned by root and therefore created by ./init\n");
        exit(1);
    }

    fscanf(file, "%hd", &fileContent);
    fclose(file);

    int userInput = atoi(argv[1]);
    if (userInput < 0) {
        userInput = -userInput;
    }

    short sum = userInput + fileContent;

    if (sum == 42) {
        printf("\nCongratulations! You found the answer to everything !\n Here is your prize:\n");
        system("echo 'aHR0cHM6Ly93d3cueW91dHViZS5jb20vd2F0Y2g/dj1kUXc0dzlXZ1hjUQ==' | base64 -d");
        printf("\n");
        
    } else {
        printf("Result is %d\n",sum);
        printf("Sum is not equal to 42. The file with the secret number will be deleted. Try again after executing ./init\n");
        remove("number.txt");
    }

    return 0;
}

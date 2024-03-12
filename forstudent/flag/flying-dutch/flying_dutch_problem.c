#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h> // Include for uintptr_t

char flag[]        = "RkxBR3tXZU11c3RGaWdodC4uLlRvUnVuQXdheSF9";
char fake_flag_2[] = "We are dead ...";
char fake_flag[]   = "Oupssss, did I miss something ? David Jones is not going to be happy ...";

// Function prototypes
void reveal_flag();
void modify_code();

int main() {
    char input[100];

    if(42 != 42) { 
        reveal_flag();
    } else {
        printf("Look around and find the way to get safe !\n");
        fgets(input, sizeof(input), stdin);

        printf("Changing cap !\n");

        if (strcmp(input, "west\n") == 0) {
            printf("Modifying the code...\n");
            printf("We still need luck to get safe !\n");
            int a_little_of_luck = rand() % 101; //0 - 100
            if(a_little_of_luck == 42) modify_code();
        } else {
            printf("Nothing happens...\n");
        }
        reveal_flag();
    }

    return 0;
}

void reveal_flag() {
    printf("%s\n", fake_flag_2); 
}

void modify_code() {
    long pagesize = getpagesize();

    void *page = (void *)((uintptr_t)reveal_flag & ~(pagesize - 1));

    if (mprotect(page, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC) == -1) {
        perror("mprotect");
        return;
    }

    unsigned char *ptr;
    ptr = (unsigned char *) reveal_flag;

    printf("You are near the land to get safe !\nYou might want to look at all the declared variables\n");
    ptr[20] = 0x8d;
    ptr[21] = 0x90;
    ptr[22] = 0xa0; 
    ptr[23] = 0x00;
    ptr[24] = 0x00;
    ptr[25] = 0x00;

    if (mprotect(page, pagesize, PROT_READ | PROT_EXEC) == -1) {
        perror("mprotect back");
    }

    printf("Code modified. Try calling the function again.\n");
}

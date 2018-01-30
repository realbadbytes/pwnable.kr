#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

unsigned char submit[6];

void play()
{
    int i;
    fflush(stdout);
    int r;
    r = read(0, submit, 6);
    int fd = open("/dev/urandom", O_RDONLY);
    unsigned char lotto[6];
    read(fd, lotto, 6);

    for (int i = 0; i < 6; i++)
    {
        lotto[i] = (lotto[i] & 45) + 1;
        printf("lotto at %d : 0x%02x\n", i, lotto[i]);
    }

    int match = 0;
    int j = 0;

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            printf("checking 0x%02x vs 0x%02x\n", lotto[i], submit[i]);
            if (lotto[i] == submit[j])
                match++;
        }
    }

    if (match == 6)
        system("/bin/cat flag");
    else
        printf("LOSS\n");
    
}

int main(int argc, char* argv[])
{
    unsigned int menu;
    while(1)
    {
        scanf("%d", &menu);
        switch(menu)
        {
            case 1:
                play();
                break;
        }
    }
    return 0;
}

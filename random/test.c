#include <stdio.h>

int main()
{
        unsigned int random;
        random = rand(); // unsafe, no seed
        unsigned int key=0;
        //scanf("%d", &key);
        for (int i = 0; i < 5000; i++)
        {
            printf(" %d ", random);
            // xor 0xdeadbeef with 1804289383 to get key
            if ((key ^ random) == 0xdeadbeef)
            {
                printf("win");
                return 0;
            }
        }
}

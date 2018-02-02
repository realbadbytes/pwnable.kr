#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagOBJ
{
    struct tagOBJ* fd;
    struct tagOBJ* bk;
    char buf[8];
}OBJ;

void shell()
{
    system("/bin/sh");
}

void unlink(OBJ* P)
{
    OBJ* BK;
    OBJ* FD;
    BK = P->bk;
    FD = P->fd;
    /* here is the arbitrary write */
    /* if BK is stack (pc),        */
    /* BK->fd */
    FD->bk = BK;
    BK->fd = FD;
}

int main(int argc, char* argv[])
{
    /* 0x9f38008 */
    malloc(1024);

    /* all objects will be in same smallbin */

    /* 0x9f38410 */
    OBJ* A = (OBJ*)malloc(sizeof(OBJ));
    /* 0x9f38428 */
    OBJ* B = (OBJ*)malloc(sizeof(OBJ));
    /* 0x9f38440 */
    OBJ* C = (OBJ*)malloc(sizeof(OBJ));

    // doubly linked list: A <-> B <-> C
    A->fd = B;
    B->bk = A;
    B->fd = C;
    C->bk = B;

    printf("here is stack address leak: %p\n", &A);
    printf("here is heap address leak: %p\n", A);
    printf("get shell\n");

    /* corrupt OBJ metadata */
    gets(A->buf);

    /* trigger exploit ? */
    unlink(B);
    return 0;
}











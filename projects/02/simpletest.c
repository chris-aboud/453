#include "lwp.h"

#include <stdio.h>

unsigned long * sp;
unsigned long * bp;

static void foo(void *);
static void foo2(void *);
static void foo3(void *);

int main(int argc, char *argv[]){
    /* Returns immediately. */
    lwp_start();

    /* Prints "Hallo thar!" once and exits. */
    printf("Expected: Hallo thar!\n----\n");
    new_lwp(foo, (void *)212, 256);
    lwp_start();

    printf("---------------------------------\n");
    
    /* Returns immediately. */
    lwp_start();

    /* Prints "Hallo thar!" once and exits. */
    printf("Expected: Hallo thar!\n----\n");
    new_lwp(foo2, (void *)212, 256);
    lwp_start();

    printf("---------------------------------\n");
    
    printf("Expected: Bar is 212\n----\n");
    new_lwp(foo3, (void *)212, 256);
    lwp_start();
    
    return 0;
}

static void foo(void * bar) {
    GetSP(sp);
    GetBP(bp);
    printf("Hallo thar!\n");
    lwp_exit();
}

static void foo2(void * bar) {
    GetSP(sp);
    GetBP(bp);
    /* This line should not be necessary. */
    /*bp[1] = (unsigned long)lwp_exit;*/
    printf("Hallo thar!\n");
}

static void foo3(void * bar) {
    GetSP(sp);
    GetBP(bp);
    printf("Bar is %d\n", (int)bar);
}


#include<stdlib.h>
#include <stdio.h>

#define BUFSZ 1024

int main() {
    char buf[BUFSZ];
    FILE *p;
   
    p = popen("pppppp", "r");
    printf("p = %p\n", (void *)p);

    printf("fgets: %s\n", fgets(buf, BUFSZ, p));

    return EXIT_SUCCESS;
}

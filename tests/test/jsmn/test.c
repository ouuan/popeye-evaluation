#include <stdio.h>

#include "jsmn.h"

int main()
{
    jsmn_parser p;
    jsmn_init(&p);

    int result = jsmn_parse(&p, "{", 1, NULL, 0);
    printf("%d\n", result);

    return 0;
}

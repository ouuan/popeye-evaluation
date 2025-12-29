#include <assert.h>
#include <stdint.h>

#include "jsmn.h"

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

int popeye_main()
{
    jsmn_parser p;
    jsmn_init(&p);

    jsmntok_t t[1024];

    void *message = popeye_make_message();
    size_t size = popeye_make_message_length();

    int result = jsmn_parse(&p, message, size, t, 1024);
    assert(result >= 0);

    return 0;
}

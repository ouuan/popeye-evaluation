#include <assert.h>
#include <stdint.h>

#define SJ_IMPL
#include "sj.h"

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

int popeye_main()
{
    char *message = popeye_make_message();
    size_t size = popeye_make_message_length();

    sj_Reader reader = sj_reader(message, size);
    sj_read(&reader);
    assert(!reader.error);

    return 0;
}

#include <assert.h>
#include <stdint.h>

#include "cJSON.h"

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

int popeye_main()
{
    void *message = popeye_make_message();
    size_t size = popeye_make_message_length();
    cJSON *json = cJSON_ParseWithLength(message, size);
    assert(json != NULL);
    return 0;
}

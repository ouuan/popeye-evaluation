#include <assert.h>
#include <stdint.h>

#include "osdp_common.h"

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

int popeye_main()
{
    uint8_t *buf = popeye_make_message();
    uint32_t size = popeye_make_message_length();

    struct osdp_pd *p = popeye_make_object(sizeof(struct osdp_pd));
    int one_pkt_len;

    int ret = osdp_phy_check_packet(p, buf, size, &one_pkt_len);
    assert(ret >= 0);

    return 0;
}

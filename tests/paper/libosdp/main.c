#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "osdp_common.h"

void *popeye_make_object(uint64_t size);

void *popeye_make_message();

uint32_t popeye_make_message_length();

int popeye_main()
{
    uint8_t *buf = popeye_make_message();
    uint32_t size = popeye_make_message_length();
    assert(size >= 32);
    const uint32_t len = size - 32;
    assert(len <= OSDP_PACKET_BUF_SIZE);

    struct osdp_pd pd = {0};
    pd.packet_buf_len = len;
    memcpy(&pd.flags, buf, 32);
    memcpy(pd.packet_buf, buf + 32, len);

    uint8_t *pkt_start;
    int ret = osdp_phy_decode_packet(&pd, &pkt_start);
    assert(ret >= 0);

    return 0;
}

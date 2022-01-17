
#ifndef DYNAMIC_HDR_METADATA_H
#define DYNAMIC_HDR_METADATA_H

#include <stdint.h>
#include "libavutil/hdr_dynamic_metadata.h"

void hb_dynamic_hdr10_plus_to_itu_t_t35(const AVDynamicHDRPlus *s, uint8_t **buf_p, uint32_t *size);

#endif

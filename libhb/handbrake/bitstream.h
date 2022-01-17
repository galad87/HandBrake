
#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <stdint.h>

struct bitstream_t {
    uint8_t*    buf;
    uint32_t    pos;
    uint32_t    buf_size;
};

void bitstream_init(struct bitstream_t *bs,
                    uint8_t *buf, uint32_t bufsize, int clear);

void bitstream_put_bytes(struct bitstream_t *bs,
                         uint8_t* bytes,
                         uint32_t num_bytes);

void bitstream_put_bits(struct bitstream_t *bs,
                        uint32_t bits,
                        uint32_t num_bits);

uint32_t bitstream_peak_bits(struct bitstream_t *bs,
                              uint32_t num_bits);
uint32_t bitstream_get_bits(struct bitstream_t *bs,
                             uint32_t num_bits);

void bitstream_skip_bytes(struct bitstream_t *bs,
                          uint32_t num_bytes);

void bitstream_skip_bits(struct bitstream_t *bs,
                         uint32_t num_bits);

uint32_t bitstream_get_bit_position(struct bitstream_t *bs);

void bitstream_set_bit_position(struct bitstream_t *bs,
                                uint32_t bitPos);

uint8_t* bitstream_get_buffer(struct bitstream_t *bs);

uint32_t bitstream_get_number_of_bytes(struct bitstream_t *bs);

uint32_t bitstream_get_number_of_bits(struct bitstream_t *bs);

uint32_t bitstream_get_remaining_bits(struct bitstream_t *bs);

#endif

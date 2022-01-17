#include <string.h>
#include "handbrake/bitstream.h"

void bitstream_init(struct bitstream_t *bs,
                           uint8_t *buf, uint32_t buf_size, int clear)
{
    bs->pos = 0;
    bs->buf = buf;
    bs->buf_size = buf_size << 3;
    if (clear)
    {
        memset(bs->buf, 0, buf_size);
    }
}

void bitstream_put_bytes(struct bitstream_t *bs,
                         uint8_t* bytes,
                         uint32_t num_bytes)
{
    uint32_t num_bits = num_bytes << 3;

    if (num_bits + bs->pos > bs->buf_size)
    {
        return; //throw EIO;
    }

    if ((bs->pos & 7) == 0)
    {
        memcpy(&bs->buf[bs->pos >> 3], bytes, num_bytes);
        bs->pos += num_bits;
    }
    else
    {
        for (uint32_t i = 0; i < num_bytes; i++)
        {
            bitstream_put_bits(bs, bytes[i], 8);
        }
    }
}

void bitstream_put_bits(struct bitstream_t *bs,
                        uint32_t bits,
                        uint32_t num_bits)
{
    if (num_bits + bs->pos > bs->buf_size)
    {
        return; //throw EIO;
    }
    if (num_bits > 32) {
        return; //throw EIO;
    }

    for (int8_t i = num_bits - 1; i >= 0; i--)
    {
        bs->buf[bs->pos >> 3] |= ((bits >> i) & 1) << (7 - (bs->pos & 7));
        bs->pos++;
    }

}

uint32_t bitstream_peak_bits(struct bitstream_t *bs,
                              uint32_t num_bits)
{
    if (num_bits + bs->pos > bs->buf_size)
    {
        return 0; //throw EIO;
    }
    if (num_bits > 32) {
        return 0; //throw EIO;
    }

    uint32_t val = 0;
    uint32_t pos = bs->pos;

    for (uint8_t i = 0; i < num_bits; i++)
    {
        val <<= 1;
        val |= (bs->buf[pos >> 3] >> (7 - (pos & 7))) & 1;
        pos++;
    }

    return val;
}

uint32_t bitstream_get_bits(struct bitstream_t *bs,
                            uint32_t num_bits)
{
    if (num_bits + bs->pos > bs->buf_size)
    {
        return 0; //throw EIO;
    }
    if (num_bits > 32)
    {
        return 0; //throw EIO;
    }

    uint32_t val = 0;

    for (uint8_t i = 0; i < num_bits; i++)
    {
        val <<= 1;
        val |= (bs->buf[bs->pos >> 3] >> (7 - (bs->pos & 7))) & 1;
        bs->pos++;
    }

    return val;
}

void bitstream_skip_bytes(struct bitstream_t *bs,
                          uint32_t num_bytes)
{
    bitstream_skip_bits(bs, num_bytes << 3);
}

void bitstream_skip_bits(struct bitstream_t *bs,
                         uint32_t num_bits)
{
    bitstream_set_bit_position(bs, bitstream_get_bit_position(bs) + num_bits);
}

uint32_t bitstream_get_bit_position(struct bitstream_t *bs)
{
    return bs->pos;
}

void bitstream_set_bit_position(struct bitstream_t *bs,
                                uint32_t pos)
{
    if (pos > bs->buf_size)
    {
        return; //throw EIO;
    }
    bs->pos = pos;
}

uint8_t* bitstream_get_buffer(struct bitstream_t *bs)
{
    return bs->buf;
}

uint32_t bitstream_get_number_of_bytes(struct bitstream_t *bs)
{
    return (bitstream_get_number_of_bits(bs) + 7) / 8;
}

uint32_t bitstream_get_number_of_bits(struct bitstream_t *bs)
{
    return bs->buf_size;
}

uint32_t bitstream_get_remaining_bits(struct bitstream_t *bs)
{
    return bs->buf_size - bs->pos;
}

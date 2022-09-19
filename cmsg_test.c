#include <stdio.h>
#include "pb_ndarray.h"
#include "cmsg.pb.h"

/* pb_encode_buf */
#define G_ENC_BUF_SZ (512 * 1024)
#define G_SCRATCH_SZ (  1 * 1024)
uint8_t g_enc_buf[G_ENC_BUF_SZ] = {0};
uint8_t g_scratch_buf[G_SCRATCH_SZ] = {0};

/* convenience struct for common, known message */
#define CMSG_DEFAULT_PARAMS (cmsg){ \
    .tag = cmsg_tag_TAGB, \
    .has_a = true, \
    .a = { \
        .shape_count = 2, \
        .shape = {16, 7, 0, 0}, \
        .eltype = ElementType_int16, \
        .byte_order = ByteOrder_LITTLE_ENDIAN, \
        .shape_description = "time channel", \
        .crc = 0, \
        .data = NULL \
    } \
}

int main(void) {
    bool retbool = false;
    cmsg m;
    pb_ostream_t ostream = pb_ostream_from_buffer(g_enc_buf, G_ENC_BUF_SZ);

    /* fill out ndarray details and encode */
    m = CMSG_DEFAULT_PARAMS;

    int16_t *data_ptr = (int16_t *)g_scratch_buf;
    for(int32_t ix=0; ix<pb_ndarray_numel(&(m.a)); ix++) {
        *(data_ptr++) = ix;
    }
    m.a.crc = 42000;
    /* set callback to copy bytes via buf_desc_t, i.e. ptr and len*/
    m.a.data = BUF_DESC_ENCODE_CB(BUF_DESC(g_scratch_buf, pb_ndarray_data_bytes_len(&(m.a))));
    /* encode matrix object into output stream, ostream */
    retbool = pb_encode_delimited(&ostream, &cmsg_msg, &m);
    printf("retbool = %d, bytes_written = %ld\n", retbool, ostream.bytes_written);

    {
        FILE *fid = fopen("cmsg_test.bin", "wb");
        size_t check = fwrite(g_enc_buf, 1, ostream.bytes_written, fid);
        fclose(fid);
    }

}

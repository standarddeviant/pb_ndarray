
#include <stdio.h>
#include "pb_ndarray.h"

/* pb_encode_buf */
#define G_ENC_BUF_SZ (512 * 1024)
#define G_SCRATCH_SZ (  1 * 1024)
uint8_t g_enc_buf[G_ENC_BUF_SZ] = {0};
uint8_t g_scratch_buf[G_SCRATCH_SZ] = {0};

int main(void) {
    bool retbool = false;
    ndarray a = ndarray_init_zero;
    // pb_ostream_t pb_ostream_from_buffer(pb_byte_t *buf, size_t bufsize);
    pb_ostream_t ostream = pb_ostream_from_buffer(g_enc_buf, G_ENC_BUF_SZ);
    // pb_callback_t buf_callback;
    // buf_t bufdesc;
    int32_t *i32_ptr = (int32_t *)g_scratch_buf;
    for(int32_t ix=0; ix<64*4; ix++) {
        *(i32_ptr++) = ix;
    }

    /* fill out ndarray details and encode */
    a.shape[0] = 64;                            /* set constant */
    a.shape[1] = 4;                             /* set constant */
    a.shape_count = 2;                          /* set constant */
    a.eltype = ElementType_int32;               /* set constant */
    a.byte_order = ByteOrder_LITTLE_ENDIAN;     /* set constant */
    strcpy(a.shape_description, "time channel");/* set constant (optional) */
    a.crc = 42;
    /* set callback to copy bytes via buf_desc_t, i.e. ptr and len*/
    a.data = BUF_DESC_ENCODE_CB(encode_buf_desc, BUF_DESC(g_scratch_buf, G_SCRATCH_SZ)); 
    retbool = pb_encode_ex(&ostream, &ndarray_msg, &a, PB_ENCODE_DELIMITED);

    printf("retbool = %d, bytes_written = %ld\n", retbool, ostream.bytes_written);

    {
        FILE *fid = fopen("ndarray_test.bin", "wb");
        size_t check = fwrite(g_enc_buf, 1, ostream.bytes_written, fid);
        fclose(fid);
    }

}

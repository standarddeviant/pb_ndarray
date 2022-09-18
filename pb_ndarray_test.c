
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
    pb_ostream_t ostream = pb_ostream_from_buffer(g_enc_buf, G_ENC_BUF_SZ);

    /* fill out ndarray details and encode */
    a.shape[0] = 16;                            /* set constant */
    a.shape[1] = 7;                             /* set constant */
    int16_t *data_ptr = (int16_t *)g_scratch_buf;
    for(int32_t ix=0; ix<a.shape[0]*a.shape[1]; ix++) {
        *(data_ptr++) = ix;
    }
    a.shape_count = 2;                          /* set constant */
    a.eltype = ElementType_int16;               /* set constant */
    a.byte_order = ByteOrder_LITTLE_ENDIAN;     /* set constant */
    strcpy(a.shape_description, "time channel");/* set constant (optional) */
    a.crc = 42;
    /* set callback to copy bytes via buf_desc_t, i.e. ptr and len*/
    a.data = BUF_DESC_ENCODE_CB(
        encode_buf_desc, 
        BUF_DESC(
            g_scratch_buf,
            pb_ndarray_data_bytes_len(&a)
        )
    );
    retbool = pb_encode_ex(&ostream, &ndarray_msg, &a, PB_ENCODE_DELIMITED);

    printf("retbool = %d, bytes_written = %ld\n", retbool, ostream.bytes_written);

    {
        FILE *fid = fopen("ndarray_test.bin", "wb");
        size_t check = fwrite(g_enc_buf, 1, ostream.bytes_written, fid);
        fclose(fid);
    }

}

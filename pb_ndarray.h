#ifndef PB_NDARRAY_HEADER_GUARD
#define PB_NDARRAY_HEADER_GUARD

#include "pb_encode.h"
#include "ndarray.pb.h"


typedef struct {
    unsigned char *ptr;
    unsigned int len;
} buf_desc_t;

#define BUF_DESC(P, L) &((buf_desc_t){.ptr=(unsigned char *)P, .len=(unsigned int)L})
#define BUF_DESC_ENCODE_CB(B) (pb_callback_t){.funcs.encode=encode_buf_desc, .arg=B};

uint32_t pb_ndarray_bytes_per_eltype(uint32_t eltype);
uint32_t pb_ndarray_numel(ndarray *a);
uint32_t pb_ndarray_data_bytes_len(ndarray *a);
bool encode_buf_desc(pb_ostream_t *stream, const pb_field_t *field, void * const *arg);

#endif

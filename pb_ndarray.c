
#include <stdio.h>
#include "pb_ndarray.h"

uint32_t pb_ndarray_bytes_per_eltype(uint32_t eltype) {
    switch(eltype) {
        case ElementType_complex128:
        case ElementType_complexint128:
            return 16;

        case ElementType_complex64:
        case ElementType_complexint64:
        case ElementType_float64:
        case ElementType_int64:
        case ElementType_uint64:
            return 8;

        case ElementType_complexint32:
        case ElementType_float32:
        case ElementType_int32:
        case ElementType_uint32:
            return 4;

        case ElementType_float16:
        case ElementType_int16:
        case ElementType_uint16:
            return 2;

        case ElementType_int8:
        case ElementType_uint8:
            return 1;
    }
    return 0;
}

uint32_t pb_ndarray_numel(ndarray *a) {
    uint32_t ix;
    uint32_t out=1;
    for(ix=0; ix<a->shape_count; ix++) {
        out *= a->shape[ix];
    }
    return out;
}

uint32_t pb_ndarray_data_bytes_len(ndarray *a) {
    return pb_ndarray_numel(a) * pb_ndarray_bytes_per_eltype(a->eltype);
}

bool encode_buf_desc(pb_ostream_t *stream, const pb_field_t *field, void * const *arg) {
    /* Free arg for use by callback */
    /* deref void** to void*, then cast void* to buf_t* */
    buf_desc_t *b = (buf_desc_t *)(*arg);
    return pb_encode_tag_for_field(stream, field) &&
           pb_encode_string(stream, (const pb_byte_t *)b->ptr, (size_t) b->len);
};


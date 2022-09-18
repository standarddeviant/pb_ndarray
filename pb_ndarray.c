
#include <stdio.h>
#include "pb_ndarray.h"

bool encode_buf_desc(pb_ostream_t *stream, const pb_field_t *field, void * const *arg) {
    /* Free arg for use by callback */
    /* deref void** to void*, then cast void* to buf_t* */
    buf_desc_t *b = (buf_desc_t *)(*arg);
    return pb_encode_tag_for_field(stream, field) &&
           pb_encode_string(stream, (const pb_byte_t *)b->ptr, (size_t) b->len);
};


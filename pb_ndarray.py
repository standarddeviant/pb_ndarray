# pb_ndarray.py

import numpy as np
import ndarray_pb2
from google.protobuf.internal.decoder import _DecodeVarint32

BYTES_PER_ELTYPE = {
    ndarray_pb2.float64       :  8,
    ndarray_pb2.float32       :  4,
    ndarray_pb2.float16       :  2,
    ndarray_pb2.complex128    : 16,
    ndarray_pb2.complex64     :  8,
    ndarray_pb2.uint64        :  8,
    ndarray_pb2.uint32        :  4,
    ndarray_pb2.uint16        :  2,
    ndarray_pb2.uint8         :  1,
    ndarray_pb2.int64         :  8,
    ndarray_pb2.int32         :  4,
    ndarray_pb2.int16         :  2,
    ndarray_pb2.int8          :  1,
    ndarray_pb2.complexint128 : 16,
    ndarray_pb2.complexint64  :  8,
    ndarray_pb2.complexint32  :  4
}

DTYPE_ELTYPE = {
    ndarray_pb2.float64       : 'f8',
    ndarray_pb2.float32       : 'f4',
    ndarray_pb2.float16       : 'f2',
    ndarray_pb2.complex128    : 'c16',
    ndarray_pb2.complex64     : 'c8',
    ndarray_pb2.uint64        : 'u8',
    ndarray_pb2.uint32        : 'u4',
    ndarray_pb2.uint16        : 'u2',
    ndarray_pb2.uint8         : 'u1',
    ndarray_pb2.int64         : 'i8',
    ndarray_pb2.int32         : 'i4',
    ndarray_pb2.int16         : 'i2',
    ndarray_pb2.int8          : 'i1',
    ndarray_pb2.complexint128 : None, # special case
    ndarray_pb2.complexint64  : None, # special case
    ndarray_pb2.complexint32  : None  # special case
}

DTYPE_BYTE_ORDER = {
    ndarray_pb2.LITTLE_ENDIAN : '<',
    ndarray_pb2.BIG_ENDIAN    : '>',
    ndarray_pb2.NATIVE        : None, # special case
    ndarray_pb2.NA            : None  # special case
}

def pb_ndarray_decode(b):
    msg_len, new_pos = _DecodeVarint32(b, 0)
    try:
        pba = ndarray_pb2.ndarray.FromString(b[ new_pos : new_pos + msg_len])
        byte_order = DTYPE_BYTE_ORDER.get(pba.byte_order, None)
        eltype =  DTYPE_ELTYPE.get(pba.eltype, None)
        if byte_order and eltype:
            dtype = byte_order + eltype
            a1 = np.frombuffer(pba.data, dtype=dtype)
            a2 = np.reshape(a1, list(pba.shape), order='F')
            return a2, new_pos + msg_len
        else:
            # TODO - handle special case of dtype
            pass
    except Exception as exc:
        print(exc)
    return None, None


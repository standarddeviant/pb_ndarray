
# import ndarray_pb2
import cmsg_pb2
from pb_ndarray import pb_ndarray_to_np_ndarray
from google.protobuf.internal.decoder import _DecodeVarint32

with open('cmsg_test.bin', 'rb') as f:
    b = f.read()
    msg_len, new_pos = _DecodeVarint32(b, 0)
    print(f'len(buf) = {len(b)}, msg_len = {msg_len}, new_pos = {new_pos}')
    try:
        cm = cmsg_pb2.cmsg.FromString(b[ new_pos : new_pos + msg_len])
        new_pos += msg_len
        print(f'len(buf) = {len(b)}, new_pos = {new_pos}')
        print(f'cm.tag = {cm.tag}')
        print(f'cm = \n{cm}')
        a = pb_ndarray_to_np_ndarray(cm.a)
        print(f'type(a) = {type(a)}')
        print(f'a.shape = {a.shape}')
        print(f'a.dtype = {a.dtype}')
        print(f'a = {a}')
    except Exception as exc:
        print(f'oh no! {exc}')

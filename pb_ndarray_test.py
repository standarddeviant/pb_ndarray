from pb_ndarray import pb_ndarray_decode

with open('ndarray_test.bin', 'rb') as f:
    buf = f.read()
    a, new_pos = pb_ndarray_decode(buf)

print(f'len(buf) = {len(buf)}, new_pos = {new_pos}')

print(f'a.shape = {a.shape}')
print(f'a.dtype = {a.dtype}')
# print(f'shape_description = {a.shape_description.split()}')
print(f'a = {a}')


# generate C bindings
./nanopb-0.4.6-linux-x86/generator-bin/nanopb_generator ndarray.proto cmsg.proto

# generate Python bindings
./nanopb-0.4.6-linux-x86/generator/protoc --python_out=. ndarray.proto cmsg.proto
# ./nanopb-0.4.6-linux-x86/generator/protoc --java_out=. ndarray.proto s1msg.proto


# compile test binary (to encode in C)
gcc -I. -o ./cmsg_test_c   \
    ./ndarray.pb.c         \
    ./cmsg.pb.c            \
    ./pb_common.c          \
    ./pb_encode.c          \
    ./pb_ndarray.c         \
    ./cmsg_test.c

# run test binary (to encode in C)
./cmsg_test_c

# run test script (decode in Python) 
python3 cmsg_test.py

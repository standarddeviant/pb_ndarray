
# Required Software
***TODO***

# Steps to run demo

1. Generate C bindings to `ndarray` type by running
    - `nanopb_generator.py ndarray.proto`
    - **INFO:** this should generate `ndarray.pb.c` and `ndarray.pb.h`
2. Compile and execute C test program by running
    - `gcc -I. ./*.c -o ndarray_test_c && ./ndarray_test_c`
    - **INFO:** this shoulld generate `ndarray_test.bin`
3. Generate Python bindings to `ndarray` type by running
    - `protoc --python_out=. ndarray.proto`
4. Execute Python test program by running
    - `python3 pb_ndarray.py`

The last step should print the details of the array generated in the C program:
```
len(buf) = 1054, new_pos = 1054
a.shape = (64, 4)
a.dtype = int32
a = [[  0  64 128 192]
 [  1  65 129 193]
 [  2  66 130 194]
 [  3  67 131 195]
 [  4  68 132 196]
 [  5  69 133 197]
 [  6  70 134 198]
 [  7  71 135 199]
 [  8  72 136 200]
 [  9  73 137 201]
 [ 10  74 138 202]
 [ 11  75 139 203]
 [ 12  76 140 204]
 [ 13  77 141 205]
 [ 14  78 142 206]
 [ 15  79 143 207]
 [ 16  80 144 208]
 [ 17  81 145 209]
 [ 18  82 146 210]
 [ 19  83 147 211]
 [ 20  84 148 212]
 [ 21  85 149 213]
 [ 22  86 150 214]
 [ 23  87 151 215]
 [ 24  88 152 216]
 [ 25  89 153 217]
 [ 26  90 154 218]
 [ 27  91 155 219]
 [ 28  92 156 220]
 [ 29  93 157 221]
 [ 30  94 158 222]
 [ 31  95 159 223]
 [ 32  96 160 224]
 [ 33  97 161 225]
 [ 34  98 162 226]
 [ 35  99 163 227]
 [ 36 100 164 228]
 [ 37 101 165 229]
 [ 38 102 166 230]
 [ 39 103 167 231]
 [ 40 104 168 232]
 [ 41 105 169 233]
 [ 42 106 170 234]
 [ 43 107 171 235]
 [ 44 108 172 236]
 [ 45 109 173 237]
 [ 46 110 174 238]
 [ 47 111 175 239]
 [ 48 112 176 240]
 [ 49 113 177 241]
 [ 50 114 178 242]
 [ 51 115 179 243]
 [ 52 116 180 244]
 [ 53 117 181 245]
 [ 54 118 182 246]
 [ 55 119 183 247]
 [ 56 120 184 248]
 [ 57 121 185 249]
 [ 58 122 186 250]
 [ 59 123 187 251]
 [ 60 124 188 252]
 [ 61 125 189 253]
 [ 62 126 190 254]
 [ 63 127 191 255]]
 ```

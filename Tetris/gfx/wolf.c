#include<stdlib.h>
size_t wolf_s = 118136;
size_t wolf_sz = 897;
const char wolf_z[] = {
0x78,0xda,0xed,0xdd,0x31,0x6e,0xdb,0x30,0x14,0x6,0x60,0x67,0xd0,0x1d,0x2,0x74,
0xec,0xd2,0xa9,0x63,0xe,0x90,0xbd,0xa7,0xe9,0xd2,0x3,0xf5,0x32,0x1e,0x7a,0x97,
0x6e,0x5e,0xab,0xd8,0x68,0x50,0xc0,0xb5,0x42,0x91,0xa2,0x44,0x3e,0x7e,0x3f,0x7e,
0x1,0x45,0x1a,0x35,0xc6,0xfb,0x2a,0x42,0x96,0x65,0xe7,0xf5,0xdb,0x8f,0x5f,0x4f,
0xa7,0xb7,0xbc,0xcc,0xdb,0x97,0x79,0xfb,0x39,0x6f,0xbf,0xe7,0xed,0xe9,0xf4,0x7c,
0xfd,0xfa,0xeb,0xfc,0xf7,0x9f,0xbf,0x9e,0xae,0xdb,0xdf,0x4c,0x22,0x22,0x22,0x22,
0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,
0x22,0x22,0xd2,0x73,0xbe,0x3f,0x7f,0xba,0xd5,0x28,0x58,0x4b,0xef,0xb2,0xef,0xb8,
0xac,0x59,0x4b,0xa7,0xac,0xff,0x2d,0x6b,0xd6,0xd2,0xbb,0x2c,0x6b,0xd6,0xac,0xe3,
0xc9,0xde,0x2b,0xb3,0x66,0x2d,0xfd,0xca,0xa6,0x38,0xb2,0x66,0x2d,0x8d,0xfb,0x7e,
0xf8,0xcf,0xde,0xff,0x59,0x58,0x4b,0x83,0xab,0xf4,0xc2,0x49,0x57,0xe2,0x37,0x50,
0x60,0x2d,0x1f,0xe6,0x72,0xcd,0x21,0xd6,0xab,0x96,0x77,0xd6,0xac,0xd9,0xa5,0x7f,
0xe7,0x2a,0xeb,0x6d,0xc5,0x17,0x88,0x17,0xd6,0x73,0xc4,0xac,0x87,0xf2,0xcd,0xb3,
0xcb,0xd8,0xab,0xaa,0xf2,0xa3,0x1f,0xc1,0x9a,0xf5,0x98,0xbe,0x79,0xe2,0x19,0x7b,
0xd5,0x53,0x2e,0xb9,0x7c,0xca,0x9a,0x75,0x60,0xdf,0xb5,0x76,0xd9,0xeb,0xff,0x6e,
0xcf,0xbf,0xc6,0x44,0x67,0x1d,0x92,0x7b,0x95,0xe6,0xf9,0x1a,0xd6,0xac,0x59,0xc7,
0x58,0xa2,0xcf,0x77,0x29,0xb7,0x4e,0xdc,0xb1,0xde,0x15,0x15,0xd6,0xac,0x7b,0xb7,
0xbe,0x6c,0x91,0x6d,0xd7,0xf0,0x55,0x8b,0x39,0x6b,0xd6,0x3b,0x58,0x67,0x5c,0xc9,
0xef,0xd4,0x77,0xab,0xe7,0x5c,0xb,0xf,0x89,0x35,0xeb,0xa6,0xac,0x6f,0x6b,0x5a,
0x25,0xa9,0xe5,0x5,0x73,0x79,0x4a,0x97,0x23,0xc2,0x9a,0x75,0xc,0xeb,0xaa,0xaf,
0xee,0xd5,0xb8,0x2c,0xc9,0x9a,0x35,0x6b,0xd6,0xac,0x37,0x1c,0x63,0xe1,0xb9,0x74,
0x23,0xd6,0x85,0x4f,0xd,0x58,0xb3,0x66,0xdd,0xd4,0xd9,0x78,0xc9,0x53,0xfe,0xf7,
0x4b,0xeb,0xac,0x59,0x7,0xb3,0xae,0xba,0x92,0x37,0xab,0xdc,0xd4,0xbd,0xe2,0xac,
0x59,0xb7,0x66,0x7d,0xc8,0xb9,0x59,0xf9,0xc5,0xf9,0x8c,0xdd,0x59,0xb3,0x66,0xfd,
0x68,0xaf,0xe5,0x1b,0x4b,0x28,0xb3,0x66,0xdd,0x97,0xf5,0xf9,0x41,0xaa,0x2a,0xb3,
0x66,0xcd,0xba,0x4d,0xeb,0xad,0x6e,0x8f,0xd9,0x5c,0x79,0x87,0xff,0x21,0xac,0x59,
0x97,0x9c,0x2,0xb5,0x7c,0x6e,0x76,0xc8,0xea,0x5d,0xef,0xf6,0x5d,0xd6,0xac,0x57,
0x59,0x9f,0x13,0xd2,0xe3,0xb5,0x94,0x9d,0x57,0xef,0x9d,0x6f,0xc5,0x67,0xcd,0x7a,
0x34,0xeb,0x69,0xdf,0x1c,0xf8,0x16,0x1b,0xd6,0xac,0x4b,0xac,0xf3,0xde,0xe1,0x18,
0xde,0xba,0xa9,0xb7,0xcb,0xb1,0x1e,0xd9,0x3a,0x4f,0xdc,0x1a,0xce,0x9a,0x75,0x9b,
0xd6,0x29,0x57,0x54,0x36,0x54,0x5e,0xb6,0xab,0x64,0x7d,0xc8,0x54,0xa7,0x36,0xc2,
0x9a,0x75,0xf9,0x52,0x59,0xd5,0x3a,0xe3,0xe1,0x1d,0x38,0xd5,0xfd,0x2f,0x95,0xa4,
0x7c,0x8a,0x38,0xeb,0xa1,0xac,0xcb,0x5f,0xdf,0xdc,0xff,0x5,0x85,0xe5,0x93,0xc9,
0xa9,0xff,0x54,0xfd,0xc0,0x52,0xd6,0xa3,0x59,0xe7,0x89,0x1f,0x3e,0x99,0x18,0xc4,
0x87,0x7c,0xfe,0x15,0xeb,0xd8,0xd6,0x25,0x2b,0xf9,0x24,0x9d,0xf8,0xb2,0x1e,0xd9,
0x3a,0x5d,0x1c,0x56,0x8f,0xca,0xac,0x47,0xb3,0x5e,0x2b,0x8e,0xac,0x5f,0x65,0xd6,
0xac,0x59,0x47,0xb5,0x4e,0x17,0x7,0xd7,0xbb,0x32,0xeb,0xd1,0xac,0x53,0xc4,0xf1,
0xb1,0x96,0x1e,0xad,0x1f,0x89,0x83,0x8b,0xa7,0xcc,0x7a,0x34,0x6b,0xbf,0x77,0x75,
0x1c,0x65,0xd6,0x8e,0x68,0x71,0x44,0x8b,0x23,0x9a,0x35,0x6b,0xd6,0xac,0x29,0xb3,
0x66,0xcd,0x9a,0x32,0x6b,0xd6,0x94,0x1d,0xce,0xac,0xc7,0xb1,0x66,0xe7,0x88,0x16,
0xd6,0x7c,0x59,0xb3,0xa6,0x4c,0x99,0x35,0x6b,0xd6,0x7c,0x59,0xb3,0x66,0x4d,0x99,
0x35,0x6b,0xd6,0xe3,0xf8,0xb2,0x66,0xcd,0x91,0x35,0x6b,0xd6,0x7c,0x59,0xb3,0x66,
0xcd,0x97,0x35,0x6b,0xca,0x88,0x59,0xb3,0x1e,0xca,0x1a,0x1f,0x6b,0x65,0xcd,0x9a,
0x32,0x6b,0xd6,0xac,0xf9,0xb2,0x66,0xcd,0x9a,0x2f,0x6b,0xd6,0xac,0x29,0xb3,0xd6,
0x78,0xd6,0xff,0x3e,0xbc,0xdb,0x6f,0x5b,0xc3,0xc4,0x5a,0x7b,0xb4,0x6,0xc1,0x5a,
0x23,0x59,0x23,0x60,0xad,0x91,0xac,0xd,0x9f,0xb5,0x46,0xb2,0x36,0x76,0xd6,0xca,
0x5a,0x59,0x6b,0xcb,0xd6,0x6,0xce,0x5a,0xe3,0x89,0x1b,0x35,0x6b,0xb5,0x92,0x2b,
0x6b,0xb5,0x92,0xb7,0xd0,0x2e,0xee,0xaf,0x60,0xcd,0x9a,0xb2,0x35,0x9c,0x35,0x6b,
0xca,0xac,0x35,0xbc,0xb5,0xc1,0xb2,0x56,0xd6,0xca,0x5a,0x5b,0xb6,0x36,0x52,0xd6,
0xca,0x5a,0x59,0x2b,0x6b,0x65,0xad,0xac,0xb5,0x86,0xb5,0x61,0xb2,0xd6,0x48,0xd6,
0xc6,0xc8,0x5a,0xc3,0x58,0x9b,0x1e,0x6b,0xa5,0xac,0xac,0xb5,0x4d,0x6b,0x73,0x63,
0xad,0x91,0xac,0x4d,0xac,0xdf,0xb7,0x99,0xb0,0x66,0xcd,0xda,0x1a,0x6e,0x62,0xbd,
0x5b,0xa7,0xb8,0x9b,0x15,0x6b,0x8d,0xb4,0x9e,0x9b,0xc,0x6b,0x65,0xad,0xac,0xb5,
0x65,0x71,0xd3,0x60,0xad,0xaa,0xaa,0xba,0xf9,0xe5,0x7d,0x65,0xad,0xaa,0xaa,0xaa,
0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0x5a,0xd2,0xd3,0xe9,0xf,0xc2,0x4e,0xf2,0xb7};
#include<stdlib.h>
size_t squash_s = 27563;
size_t squash_sz = 1105;
const char squash_z[] = {
0x78,0xda,0xed,0x5c,0xe9,0x7a,0xea,0x20,0x10,0x7d,0x72,0x13,0xe2,0xda,0x6b,0x37,
0xbb,0x6b,0xb5,0x90,0xbc,0x69,0x13,0xf5,0xd6,0x40,0x32,0x64,0xd8,0x89,0x72,0xbc,
0x5f,0xfb,0xe3,0xa,0xc,0x33,0xc3,0x99,0x85,0xa4,0x84,0x24,0x24,0x24,0x24,0x24,
0x24,0x24,0x24,0x24,0xdc,0x32,0xf2,0xcb,0xa7,0x98,0xdc,0x55,0x94,0x75,0x40,0x4b,
0x5a,0x7d,0x65,0xa7,0xaf,0x5c,0xbe,0x7d,0xfe,0x95,0x7d,0x56,0xf5,0xff,0xb3,0x1e,
0xd0,0x79,0x46,0x3a,0x5f,0x3f,0x8d,0xd9,0xf6,0x8e,0x69,0xd6,0x79,0xcb,0xda,0x23,
0xb8,0x85,0xde,0xa1,0x85,0xd8,0xcf,0x2c,0x27,0xc0,0x67,0xba,0x7,0xc6,0x30,0x5a,
0xdd,0x4f,0x8a,0x8e,0x7c,0xe7,0xb5,0xe6,0x3f,0xc0,0xa0,0x5a,0xc4,0x2d,0xaf,0x8,
0xdc,0x72,0xcd,0xc0,0x67,0x6e,0x3d,0xac,0x1a,0x3b,0x92,0xe6,0x9c,0xdd,0x8a,0xc9,
0xb,0x3c,0xb2,0x1e,0xbb,0xc8,0xb8,0x9d,0xf1,0xe6,0x5e,0x55,0xd0,0xc0,0x46,0xde,
0xcf,0xac,0xc7,0x76,0x7f,0x9f,0xd9,0xa1,0x64,0x92,0xc1,0x1b,0x7e,0xb3,0x84,0x9f,
0x21,0x7b,0x93,0x6c,0xb7,0x6f,0xb4,0xb8,0x36,0x63,0xb2,0xc5,0x3f,0x44,0xc9,0x31,
0x6e,0xde,0x76,0xa8,0xb9,0xa0,0x35,0x71,0x82,0xb5,0x6c,0x82,0x46,0x82,0x57,0xde,
0x8f,0x3b,0x33,0x64,0xcb,0x52,0x2e,0x2,0xad,0xd6,0xb0,0xd1,0x4f,0x7e,0x47,0x76,
0xf5,0x1c,0x94,0x29,0x59,0x41,0x54,0x25,0xe8,0xe9,0xad,0x69,0xbe,0x8b,0xbc,0xa3,
0xd,0x42,0xf8,0x3,0xb0,0x95,0x39,0x21,0x47,0x21,0xa2,0x38,0x9c,0x5e,0xef,0x7,
0xc,0xd3,0x73,0xfe,0xf8,0x79,0x10,0xc7,0x9,0xa4,0x8d,0x36,0x27,0x5e,0x14,0xf4,
0x8a,0x98,0x9,0x9e,0xa,0x7b,0x64,0xda,0x5b,0x5c,0xf5,0x18,0xbe,0xab,0xaa,0x55,
0x35,0x28,0x15,0x6d,0x8c,0x47,0xe0,0x4d,0xb6,0x15,0xf6,0x81,0xd9,0x26,0x63,0x7,
0x50,0x67,0xc2,0x7c,0xef,0xa8,0xf9,0x68,0xb9,0x2f,0xc0,0x9,0x79,0x47,0x5d,0x32,
0x24,0x60,0xb3,0xf2,0x93,0x16,0x93,0x27,0xa4,0x8c,0x62,0x58,0xca,0xc1,0x8,0x7a,
0xb4,0x31,0x42,0x8d,0xc7,0x49,0xdf,0xbb,0x2c,0x5,0x6d,0x7e,0xf0,0x94,0xc2,0x61,
0x46,0x1a,0xef,0xef,0x2b,0x8a,0x55,0x6b,0x37,0x94,0x80,0x13,0x37,0xff,0x76,0x38,
0x7f,0x42,0x89,0x2c,0xb8,0xf0,0xb7,0x94,0xf6,0x30,0x34,0x6a,0xc1,0xcb,0xce,0xde,
0x3b,0x95,0xfa,0x9a,0x4a,0xd8,0x43,0x7,0x7e,0x99,0x3d,0xd7,0xa,0xf6,0x84,0x3,
0x84,0x72,0x86,0x68,0x64,0x5c,0x75,0x23,0xd0,0xea,0x6e,0x58,0x2f,0x44,0xc8,0x79,
0xb6,0x4a,0xaa,0xef,0x4d,0x7a,0x31,0xb2,0x2f,0x54,0xd4,0x83,0xf6,0x51,0x7d,0x86,
0x55,0xe2,0x1c,0x88,0x28,0x1f,0xeb,0xa5,0x94,0xb7,0xd5,0x9b,0x45,0xd,0x69,0xb0,
0xf9,0xb1,0x53,0xdd,0xd8,0x69,0x6b,0x2f,0x17,0x25,0x2a,0x54,0x3d,0xd8,0x28,0xa0,
0xce,0x87,0x3d,0xcb,0x29,0x24,0x27,0xb8,0x8c,0x1c,0x5d,0xd8,0xad,0xb4,0xb6,0x78,
0x74,0xce,0x47,0xcc,0xf9,0x35,0xf,0x2f,0xe2,0x5e,0x9f,0x94,0x96,0x35,0x3e,0x84,
0x43,0xe9,0x2e,0xd6,0x9b,0x9e,0x35,0xbd,0x9,0x2c,0x5c,0x54,0x16,0xdf,0x68,0x2f,
0x2e,0xcb,0xac,0xdd,0x3b,0x99,0x42,0xb8,0x73,0xa5,0xfd,0xc1,0xe4,0x1b,0x2d,0x83,
0x1e,0x59,0xaa,0x87,0x4c,0x79,0x96,0x84,0xcc,0x43,0xad,0x31,0x9c,0x2b,0xa7,0x50,
0xd,0x25,0x52,0xe2,0xfd,0x32,0x74,0x8f,0x23,0xca,0xc3,0x2c,0xd7,0x13,0xc6,0x28,
0x19,0xc4,0x16,0x27,0xda,0x1d,0xc0,0x81,0x4e,0x12,0x5a,0xa2,0x5a,0xa6,0x1d,0xe1,
0xfb,0x62,0xba,0xd,0x49,0x23,0x26,0xef,0xb0,0x5b,0x7f,0xff,0x41,0x49,0x2a,0x62,
0x12,0xc1,0xcd,0x53,0x32,0x77,0x11,0x17,0x20,0xc3,0xac,0xd0,0x36,0xa3,0x5b,0xd9,
0x6a,0xe1,0xe,0x53,0xdd,0x63,0x68,0x56,0x63,0x23,0x59,0x42,0x35,0x71,0xb2,0x50,
0x17,0x69,0x40,0x93,0xe1,0x25,0x81,0x7,0xee,0xb8,0x9b,0x26,0x26,0xc4,0x54,0x99,
0xd6,0x92,0x25,0x4b,0x19,0x7a,0x48,0xc3,0x1b,0xd3,0xb4,0xc3,0x2c,0xc,0x3c,0xf1,
0xb3,0x9c,0xd8,0x92,0xd7,0x7e,0x28,0x76,0xc3,0xee,0x30,0x9f,0xba,0xf0,0xa,0x37,
0xae,0xd1,0x15,0x9c,0x32,0x57,0xd0,0x2d,0x22,0xb0,0xf4,0x56,0xec,0x4b,0x77,0xc2,
0xbb,0x90,0xde,0x3d,0x95,0x18,0x97,0xcf,0xa,0x5b,0xd0,0x69,0xe5,0xe9,0x98,0x61,
0x6d,0xdf,0xc,0xce,0x49,0x47,0xa1,0x65,0x69,0x48,0xf0,0x86,0x25,0x2e,0xd6,0x8,
0x77,0x4e,0x8c,0xe0,0xfb,0x48,0xc8,0x2f,0x85,0x2d,0xef,0xc8,0x66,0xa1,0xeb,0x39,
0x35,0xb,0x95,0x57,0xd8,0xed,0x7d,0x44,0x50,0x1a,0xd,0x1f,0xac,0x7f,0xce,0xe,
0x96,0xb5,0x8e,0x7e,0x7c,0x31,0x28,0x3c,0x87,0xb8,0xcc,0x2c,0x71,0x7e,0xba,0xf6,
0xe9,0xa7,0xff,0x37,0xba,0x23,0xfc,0xc3,0x47,0x3e,0x1e,0x85,0xb3,0xdd,0xe,0xc0,
0x63,0x99,0x15,0xb9,0x8f,0xcd,0x8a,0xa6,0x7d,0xf0,0x6d,0x5a,0xd3,0x96,0xbb,0xab,
0xc7,0x1d,0x3d,0x71,0xb0,0x8d,0xee,0x50,0xf0,0xfe,0x65,0x4c,0xc9,0xb5,0x4a,0xf6,
0xca,0xc2,0xc1,0x6e,0x1b,0x63,0x5c,0x67,0xbd,0xe5,0x3,0xf,0x1,0x7c,0x20,0x68,
0xd6,0x15,0x2c,0xd1,0x8c,0x9d,0xa,0x8d,0xef,0xa0,0x9d,0xc4,0xff,0xa1,0xa7,0x6b,
0x7d,0xea,0xe4,0xb5,0xf5,0x64,0x8b,0x5f,0x8d,0x84,0xaa,0x2c,0xe3,0x26,0x11,0x93,
0xc7,0x7b,0x3d,0xba,0xcd,0x57,0xe6,0xb8,0x34,0x57,0x7e,0x14,0xa0,0xa2,0x2c,0x2a,
0x78,0xce,0x3d,0x71,0xd5,0x32,0xd9,0xc5,0x73,0xc4,0x7c,0xf4,0xe2,0x4c,0x8a,0xb4,
0x5,0x8b,0x11,0x9e,0x1a,0x10,0x71,0xdc,0x7a,0xda,0xe3,0xab,0x8d,0xdf,0x8a,0x28,
0xe8,0xad,0xf6,0x15,0x54,0x14,0xe3,0x77,0x3a,0xa0,0x18,0x8f,0x44,0x7f,0x7e,0x2e,
0x7b,0x5d,0x3c,0xfc,0x10,0x97,0x1a,0x4d,0x5e,0x1f,0x9,0xa7,0xcd,0xfd,0x34,0xc2,
0x23,0x1d,0x65,0x2f,0x41,0xd9,0x3d,0x49,0x84,0x2a,0xd5,0x7c,0x1d,0x2f,0xe,0xc5,
0xfe,0xdd,0x44,0xe4,0x31,0x2a,0xb6,0x5b,0x86,0xc4,0xad,0x59,0xc7,0xd7,0xf8,0xd7,
0x71,0x1,0x76,0x3,0x84,0x20,0x28,0x3a,0xd7,0x7e,0xef,0x2b,0xe,0x65,0x3f,0xc5,
0x95,0xdd,0xe3,0x1f,0xd3,0x19,0xa1,0xbe,0xcf,0x88,0xb2,0x2c,0xb8,0x92,0x9a,0x61,
0xc0,0xdb,0x3f,0x46,0x42,0x2d,0xd1,0x5c,0xf4,0xdb,0x45,0xe9,0xfd,0x7e,0xd5,0x49,
0x43,0xf9,0x87,0x8d,0x1c,0xca,0xef,0xe5,0xc6,0x9b,0xe0,0xcc,0x47,0x6f,0x8c,0xe0,
0x17,0x8e,0x37,0xd5,0x95,0xbb,0x81,0x68,0x2d,0xb5,0x4d,0xf1,0x7d,0x45,0xb6,0x19,
0xfa,0x4b,0x35,0x23,0xe5,0xb4,0x25,0xbb,0x32,0x44,0x78,0x8d,0x70,0xd,0x8f,0x6c,
0xa5,0x70,0xa4,0x17,0x9e,0x80,0x77,0xf0,0x23,0xba,0x4d,0x4d,0x48,0x48,0x48,0x48,
0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x8,0x8c,0x5f,0xff,0x5,0xb8,0xbf};

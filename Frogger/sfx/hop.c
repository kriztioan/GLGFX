#include<stdlib.h>
size_t hop_s = 14293;
size_t hop_sz = 1021;
const char hop_z[] = {
0x78,0xda,0xed,0x57,0xd9,0x72,0x23,0x21,0xc,0xfc,0xf3,0xe1,0x18,0xe6,0xf6,0x41,
0xe,0x3b,0xbf,0xbb,0x73,0x20,0xd4,0x2,0xec,0x38,0xbb,0x79,0xd9,0x2a,0x7a,0xaa,
0xec,0x58,0x62,0x1a,0x9,0x1a,0x89,0x68,0x5d,0x51,0x51,0x51,0x51,0x51,0x51,0x51,
0x51,0x51,0xf1,0xdb,0x50,0xf1,0x69,0x96,0xaf,0xdb,0xfd,0x76,0x7,0xdc,0xee,0x5d,
0x3,0x3,0xf6,0xa7,0x15,0x23,0xd6,0x21,0xb7,0xaf,0xb,0xd,0x62,0xaa,0x73,0x4a,
0x75,0xbf,0xb5,0x9,0x91,0x6e,0x5c,0x3a,0xdb,0xed,0xeb,0xc4,0xf3,0xd1,0x1f,0x8b,
0xbf,0xfa,0x2b,0xc2,0x5f,0x4c,0x4e,0x25,0x87,0xac,0x6f,0xf8,0x41,0x84,0xbe,0x7f,
0x9c,0x32,0xaa,0xb3,0xce,0xa8,0xba,0x64,0xd0,0xfa,0x33,0x5f,0x5,0x7d,0xf6,0xe9,
0x7c,0x27,0x9e,0x87,0xa8,0x86,0x74,0xbe,0xab,0x77,0x19,0x95,0xb9,0x64,0x54,0x8b,
0xca,0x16,0x74,0xcc,0xa8,0xae,0xd9,0x82,0x2a,0x8b,0x34,0xa7,0x79,0x59,0xe6,0xa5,
0x57,0xd9,0x82,0xe,0xab,0x79,0xf5,0x1,0x66,0x93,0x53,0xc9,0x21,0xdb,0x1b,0x5d,
0xba,0x9c,0x5a,0x8d,0x9,0xd5,0xbc,0x4c,0xd9,0x4a,0xa9,0x36,0x99,0x6d,0xfd,0xe9,
0x44,0x44,0x4d,0x3b,0x6f,0x7a,0x89,0x22,0x38,0x37,0xc2,0x3b,0xb3,0x96,0x36,0xef,
0x28,0xd4,0xd6,0x5c,0x77,0x6f,0x14,0x92,0x5c,0x5f,0xf3,0x11,0x7d,0xdb,0xab,0xef,
0xe6,0x91,0xfe,0x36,0xef,0x55,0x4e,0xdb,0xc3,0x8a,0xa3,0x9c,0x8e,0xaf,0x59,0xec,
0x87,0x6f,0x9b,0x54,0x1d,0x1e,0x44,0x66,0x1e,0xef,0x12,0x6d,0x76,0x51,0x7e,0xf9,
0xb4,0x93,0x9c,0xd6,0x89,0xe3,0xa2,0xa5,0xbe,0x93,0x63,0x62,0x2f,0x4f,0xe4,0xba,
0x4d,0x8b,0x5e,0x5a,0xe4,0xa2,0xfa,0xe0,0x3c,0x94,0x8e,0x95,0x95,0xf2,0x9e,0x85,
0x88,0x26,0x2d,0xce,0x8,0xc8,0x6c,0x66,0xb5,0x92,0xb7,0x43,0x79,0x45,0xd5,0x90,
0x3f,0x11,0x9f,0x9c,0x56,0x4f,0xd1,0x37,0xe7,0xb2,0xb4,0x45,0x5a,0x94,0xc4,0x26,
0x8,0xa8,0x20,0x8d,0xbb,0xdd,0xb,0x12,0xc4,0x7a,0xb8,0x39,0xa6,0x57,0x1c,0xf6,
0x13,0x1c,0xb3,0x74,0x6c,0x6a,0x7d,0xdb,0xd7,0x18,0xe7,0x30,0xb1,0xda,0x78,0xe9,
0xd0,0xe8,0x98,0x9a,0x92,0x2,0x37,0x7,0x1c,0x5b,0xd6,0xc8,0xfa,0x3d,0xe3,0x82,
0x6,0x87,0x47,0x7,0x6f,0x6f,0x78,0x16,0xdc,0x80,0xe5,0x75,0x87,0x82,0x53,0x13,
0x9e,0x53,0xc1,0x71,0x28,0x53,0x83,0x4,0x26,0x8,0xf7,0x4,0xed,0xaa,0x41,0x87,
0xa8,0xe2,0xfd,0xbe,0xe1,0x73,0xbe,0xed,0xac,0xa6,0x27,0xe,0x51,0xa,0x51,0x7f,
0xc2,0xe1,0xfe,0xca,0x21,0xa4,0x7a,0x9c,0xab,0xa3,0xec,0xad,0x95,0x29,0x96,0x1d,
0x4f,0xa6,0xbd,0xa,0xa2,0x5e,0x82,0x20,0xf7,0xc6,0x42,0xe5,0xf2,0xd3,0x86,0x55,
0x6f,0xce,0xf4,0x9e,0x8f,0x9b,0xfa,0x4e,0xa6,0x85,0xde,0x23,0x15,0xdf,0xbe,0x3a,
0x32,0x4d,0x61,0xd0,0xfd,0xc3,0xd0,0x6,0x1e,0xb5,0x8d,0x64,0x20,0x4,0xe8,0x7b,
0x7a,0xaf,0xf5,0xe2,0xbc,0x87,0x76,0x17,0x5a,0x4f,0xdc,0x27,0x52,0xdb,0xa1,0x41,
0x51,0x86,0x8e,0xe2,0x25,0x6a,0xcf,0x25,0x86,0x30,0xf9,0xac,0x15,0x9e,0x88,0x9d,
0x56,0x41,0xb5,0x5c,0x7e,0x29,0x84,0xde,0x63,0x63,0x17,0x95,0xfa,0x69,0x36,0x2e,
0xcf,0x66,0x8c,0xd9,0xa8,0x2c,0x9b,0xf1,0x41,0x36,0xa,0xdb,0xdd,0x1c,0xb3,0xe9,
0xf,0xd3,0xbc,0x8c,0x51,0xf3,0x13,0x99,0xba,0x48,0x15,0xb,0x12,0x85,0x40,0xa2,
0x9,0x72,0x8d,0xcd,0x7b,0x37,0xd,0x31,0x9b,0x48,0xe5,0xc8,0xf4,0x5d,0x8,0x58,
0x6f,0xe4,0xed,0x8c,0x14,0x18,0x84,0x33,0x52,0x52,0x47,0x17,0xc6,0xfb,0x5e,0x68,
0x1b,0x6c,0x85,0xe6,0x6a,0x3e,0x22,0x5,0x35,0xe4,0x6d,0xf0,0x85,0x89,0x67,0x26,
0x1e,0x83,0xf5,0xf3,0xf2,0xb6,0x70,0x9,0xb1,0x85,0xeb,0x9e,0xe8,0x70,0x9e,0x89,
0x63,0x91,0xf0,0xb0,0x33,0xbc,0xa7,0xa1,0xd6,0x14,0xae,0x5b,0x96,0x8b,0x16,0xdf,
0x32,0xf,0x51,0x28,0x25,0x14,0xd,0xea,0x41,0xe9,0x8b,0xca,0xc3,0x57,0x42,0xba,
0xe,0xc8,0x8b,0x42,0xe8,0xe5,0x4a,0xe8,0x34,0x28,0xfc,0x59,0xd2,0xaa,0x9c,0xf4,
0x98,0x24,0xad,0xf0,0xb2,0xb5,0x55,0xa1,0x91,0x5b,0xad,0xc9,0xab,0x92,0xe8,0xa0,
0xd4,0x4,0x63,0xd5,0xb,0x14,0x3,0xc4,0x16,0x35,0x25,0x8a,0xe7,0xc4,0x66,0x58,
0xcd,0x81,0x89,0x3b,0x26,0x76,0x10,0x1b,0x13,0xe3,0x5,0x1,0x92,0x86,0xd8,0x58,
0x9b,0x24,0xe3,0x78,0xb3,0xd5,0x69,0xd2,0x13,0xf7,0x8,0x4c,0xda,0x3e,0x49,0xfa,
0x38,0x32,0xe3,0x30,0xe,0x2b,0xd6,0xaf,0xe,0x62,0xdb,0x6d,0xbb,0xbd,0x87,0xa4,
0xfb,0x30,0x78,0x35,0xc3,0x6a,0x3a,0xa6,0x68,0x39,0x69,0x4b,0x23,0x25,0xf1,0x10,
0x89,0x7,0x48,0x1a,0x88,0x6d,0x91,0xd8,0xc1,0x86,0x30,0x71,0xf,0x8d,0x71,0x88,
0x21,0xf,0x10,0x5b,0x57,0x8c,0xed,0x41,0xd2,0xc3,0x4f,0x93,0xee,0x76,0x58,0x26,
0x36,0x5d,0x4,0x44,0xac,0xd9,0xda,0xc1,0xc5,0xc3,0xb1,0x15,0x88,0x2d,0x5b,0x5b,
0x88,0xd,0x88,0x21,0xe9,0x32,0x45,0xcb,0x56,0x88,0xed,0x5,0x62,0xf5,0x43,0x62,
0xfd,0x6b,0x49,0xbb,0xd6,0xb5,0x2b,0xd6,0x2f,0x24,0xde,0x6d,0xbb,0xb5,0x85,0xd8,
0xda,0x60,0x5e,0xa1,0x8b,0x14,0x6,0x36,0xa4,0x48,0xac,0x23,0x1,0x10,0x6b,0xdd,
0x3a,0xa2,0x76,0x3f,0x8a,0xd,0x89,0x8b,0xb1,0x65,0xc4,0xea,0x31,0xb1,0x7e,0x98,
0xb4,0xcb,0x89,0x8d,0x8d,0xc0,0xa4,0x13,0x6b,0x78,0x81,0xad,0x16,0x92,0xce,0xad,
0xaf,0x51,0xc0,0x3f,0x51,0x65,0xa,0xfb,0xaf,0xb1,0xa9,0x17,0x63,0xcb,0x88,0xed,
0xb,0xc4,0x66,0x7b,0xb6,0xf,0x41,0xbc,0xd9,0x76,0xab,0x88,0x4d,0x58,0x89,0x82,
0x6,0xaf,0x48,0x29,0x90,0xb8,0x44,0xc1,0xc4,0x86,0xac,0x10,0x1b,0x13,0x3f,0x88,
0x2d,0x23,0xb6,0x29,0xb1,0xc9,0x89,0x57,0x5f,0x46,0xf1,0x62,0xd2,0x3a,0x49,0xda,
0x66,0x49,0x33,0x30,0xb6,0xc4,0xaa,0x53,0xab,0x48,0x3a,0xb3,0x96,0x28,0x32,0x62,
0xf3,0x9c,0xb8,0x14,0x9b,0x7e,0x31,0x36,0xfd,0x4d,0x6c,0xbf,0x90,0x74,0x45,0x45,
0x45,0x45,0x45,0x45,0x45,0x45,0x45,0x45,0x45,0x45,0x45,0x45,0x45,0x45,0x45,0x45,
0x45,0x45,0x45,0x45,0x45,0xc5,0xff,0x8c,0x3f,0xd4,0x2a,0x56,0xed};
#include<stdlib.h>
size_t tick_s = 10454;
size_t tick_sz = 1718;
const char tick_z[] = {
0x78,0xda,0xed,0x58,0x5b,0x4f,0xdb,0x4a,0x10,0xfe,0x89,0x55,0x4f,0x5b,0x28,0xea,
0x5,0x5a,0xa5,0x8,0xaa,0x10,0x87,0x26,0xc1,0xd8,0xb1,0xd7,0xb7,0xc4,0xb9,0x18,
0x42,0x2e,0xa5,0x12,0x45,0xa1,0x14,0xf1,0x82,0x2a,0xd1,0xf2,0x40,0x1f,0xe8,0x9f,
0x3b,0x5e,0x26,0xcb,0xec,0xae,0x77,0x1d,0xa7,0xf4,0x9c,0x53,0xe9,0x74,0x1e,0xaa,
0x22,0x7f,0xcc,0xee,0x5c,0xbe,0x6f,0x66,0xf1,0x3c,0x42,0x5c,0x97,0xa4,0xe6,0xa5,
0xe6,0xfb,0x41,0x6a,0xe1,0x9d,0xd1,0x9f,0x7c,0xdf,0xf3,0xc8,0xcc,0x28,0x82,0x19,
0x8f,0x44,0x9c,0x3b,0x33,0xe6,0x2f,0xc,0x5b,0xad,0xf6,0xad,0x45,0x11,0x60,0x10,
0xe5,0xa4,0xe6,0xba,0xfc,0xa9,0x51,0x6a,0xad,0x5b,0x8b,0x22,0xea,0x15,0xb0,0x8e,
0xd3,0xbc,0x35,0x86,0xa6,0x38,0xea,0x35,0x4e,0xad,0xdd,0xa6,0x58,0x8a,0x74,0xdd,
0x66,0xd3,0xb6,0x2d,0xcb,0x4e,0xcd,0x71,0x8,0x1,0x1c,0xa0,0x3a,0xa9,0xc5,0x71,
0xab,0x15,0x86,0x80,0xb3,0x66,0xd6,0x6c,0x52,0x8f,0x41,0x40,0x71,0xd4,0xe8,0xc9,
0xe0,0x31,0xc,0x7d,0x9f,0x9e,0xcd,0x4e,0xa6,0x67,0xd3,0x98,0xe8,0x3d,0x99,0x57,
0x8a,0x64,0x38,0x8a,0xc0,0x3b,0x52,0x8f,0x2c,0x6e,0xb8,0x1f,0xa0,0x30,0x6a,0xf0,
0x85,0x51,0xb3,0x3c,0x3a,0x4e,0xad,0xb6,0xb9,0xb9,0xba,0xba,0xb2,0xf2,0xec,0x59,
0xa9,0x64,0x18,0x3b,0x3b,0x84,0x1c,0x1c,0x9c,0x9f,0x5f,0x5f,0xdf,0xdc,0x7c,0xff,
0xfe,0xe5,0xcb,0xd1,0x51,0x18,0x96,0xcb,0x2f,0x5f,0xae,0xac,0x2c,0x2f,0x3f,0x79,
0xf2,0xf8,0xf1,0xd2,0xd2,0xda,0xda,0xf6,0x76,0xa7,0x33,0x9d,0x5e,0x5e,0x5e,0x5f,
0x5f,0x5d,0x9d,0x9f,0x7f,0xf8,0xb0,0xbf,0xdf,0xed,0x46,0x91,0x6d,0x57,0x2a,0xaf,
0x5e,0x2d,0x2f,0x3f,0x7c,0xb8,0xb4,0xf4,0xe6,0x8d,0x6d,0x27,0xc9,0x64,0x72,0x78,
0xf8,0xfe,0xfd,0xe1,0xe1,0xd1,0xd1,0xc9,0xc9,0xe9,0xe9,0x74,0x3a,0x99,0x84,0x61,
0xb5,0x5a,0x2a,0xad,0xae,0xae,0xad,0x95,0x4a,0x9b,0x9b,0x95,0xca,0xf6,0x76,0xad,
0x66,0x9a,0x61,0x38,0x1c,0x4e,0xa7,0x67,0x67,0x9f,0x3f,0x1f,0x1f,0x4f,0x26,0x49,
0x12,0xc7,0x61,0x48,0x88,0x69,0x6e,0x6d,0xbd,0x7e,0x4d,0xfd,0x3d,0x78,0xf0,0xe8,
0xd1,0x8b,0x17,0xe5,0xb2,0x65,0x85,0x61,0xaf,0x37,0x1e,0x9f,0x9e,0x5e,0x5d,0xfd,
0xf8,0x71,0x73,0xf3,0xed,0xdb,0xd9,0xd9,0x68,0xe4,0xba,0x1b,0x1b,0x2b,0x2b,0x7f,
0xa5,0xf6,0xf8,0xc9,0xf2,0xd3,0xe7,0xcf,0x4b,0xa5,0x6a,0x95,0x90,0xc1,0x60,0x3a,
0xbd,0xb8,0xb8,0xfc,0xfa,0xf5,0xeb,0xc5,0xc5,0xc9,0xc9,0xc1,0x41,0x10,0x98,0xa6,
0x61,0xbc,0x7d,0xbb,0xbe,0x5e,0x4a,0x6d,0x7d,0x7d,0x63,0xa3,0x5c,0xae,0xd7,0x83,
0xf4,0xe4,0xe3,0xe3,0xd3,0xd3,0x4f,0x9f,0x3e,0x7e,0x1c,0x8f,0xfb,0xfd,0x28,0x22,
0xc4,0x71,0x2c,0x6b,0x67,0xa7,0x56,0x33,0x8c,0xad,0x4a,0xc5,0xa8,0xd5,0x6c,0x3b,
0x8,0x3a,0x9d,0x24,0xd9,0xdb,0xeb,0xf7,0xe3,0x98,0xe6,0x16,0x32,0xe7,0x79,0x8e,
0x3,0xf5,0x77,0x9c,0x20,0x88,0xe3,0x7e,0x3f,0x49,0x7a,0xbd,0x76,0x9b,0xd5,0x9c,
0x7e,0x33,0xcd,0x46,0xa3,0x5e,0x6f,0xec,0xd8,0xb6,0xef,0xc7,0x71,0x92,0x1c,0x1c,
0xc,0x53,0x1b,0xc,0xfa,0xfd,0x76,0x1b,0x7a,0xc8,0xb2,0x1a,0xd,0xc3,0x28,0x97,
0xb7,0xb6,0xaa,0xd5,0x9d,0x86,0xe3,0x84,0x61,0xb7,0xbb,0xb7,0x47,0x71,0xa3,0xd1,
0x78,0x3c,0x1c,0xee,0xef,0x77,0x3a,0xbe,0x6f,0x59,0xb5,0x5a,0xa5,0x42,0x51,0x34,
0x67,0xf5,0xba,0x65,0x11,0xd2,0x6e,0x27,0xc9,0x68,0x44,0xf3,0x3b,0x99,0xc,0x87,
0x7b,0x7b,0x9d,0x4e,0x18,0x3a,0x8e,0x69,0xbe,0x7b,0x47,0x91,0xe5,0xb2,0x61,00,
0x2e,0x8a,0xba,0xdd,0xfd,0xfd,0xe1,0x70,0x9c,0xda,0x68,0x34,0x18,0xf4,0x7a,0x51,
0xe4,0xba,0xbb,0xbb,0xf5,0xfa,0xf6,0xb6,0x61,0x54,0x2a,0xd5,0x2a,0xad,0x41,0xb3,
0x49,0x63,0x48,0x92,0xc1,00,0x6e,0x98,0x24,0xb4,0xa6,0x9e,0x67,0xdb,0xa6,0x59,
0xaf,0xd7,0x6a,0x69,0x14,0xd,0xd3,0xb4,0x6d,0x42,0x82,0xa0,0xd5,0x8a,0xe3,0x6e,
0xb7,0x9f,0x5a,0xaf,0xd7,0xe9,0xd0,0x88,0x7d,0x9f,0x45,0x4c,0xf3,0x1,0x5d,0xce,
0xb8,0x88,0x7d,0x8b,0x4c,0x9c,0x71,0x7b,0xd6,0xdd,0xc0,0x3d,0xe0,0x2a,0x30,0x9e,
0x29,00,0xe3,0x2a,0xfd,0xca,0xfe,0xc7,0x33,0x9f,0xb2,0x8e,0xd7,0xf,0xe6,0x8b,
0x7e,0x77,0x1c,0xd6,0xf9,0xcc,0x28,0x96,0x31,0xf,0x79,0x82,0xd5,0x2,0x7e,0xc2,
0xbd,0x81,0xc3,0xc0,0xe2,0x20,0x20,0x84,0x72,0x78,0x77,0x17,0xaa,0xcd,0x58,0x89,
0x8c,0xb,0x23,0x64,0x25,0x3d,0xf3,0x2e,0x42,0x1f,0x99,0xc9,0x58,0x8e,0x1a,0x43,
0x33,0xc5,0x94,0x3,0x94,0x60,0xe6,0x8f,0xe2,0x3c,0xb5,0x16,0xa0,0xe,0xe1,0xed,
0x69,0x1f,0x52,0x83,0xbc,0x33,0x5,0xa4,0x18,0x54,0x2b,0xe8,0x55,0x56,0x1d,0x76,
0x26,0x8b,0x12,0xbc,0xf1,0x99,0xa0,0xb9,0xa0,0xb5,0x46,0xed,0x11,0x75,0x8a,0xa9,
0xf,0xdc,0xd,0xaa,0xc0,0xc7,0x89,0x55,0x2,0x24,0xa2,0xd4,0x9a,0x8b,0x6,0x79,
0x3,0x1c,0xab,0x27,0xd4,0x1f,0x91,0xb2,0x86,0xf3,0x27,0xf2,0xc6,0x66,0xc,0x4e,
0xd,0xf0,0xa4,0xee,0x31,0x34,0xf8,0x8e,0xfd,0xc8,0x7e,0x3,0xba,0x50,0x9c,0x41,
0x50,0x1,0xcc,0x4,0x74,0x6,0xde,0x9e,0xcf,0x5,0x1f,0x25,0xeb,0xd,0xcc,0x4,
0xf3,0x88,0xd9,0x9d,0xd5,0xdd,0xe7,0xeb,0xce,0x4f,00,0xe8,0xb5,0x6c,0xce,0x98,
0xb1,0xca,0xb3,0x19,0x85,0x9d,0xb,0x73,0x7,0x79,0x49,0x8d,0x4d,0xb,0x7e,0xa6,
0xdc,0xde,0xae,0x5,0x91,0xb0,0xbb,0xb1,0x7b,0xf1,0xb3,0x99,0x61,0xef,0xa2,0xbd,
0x65,0x20,0x74,0x30,0xf3,0x26,0x1a,0xc4,0x21,0xb3,0x94,0x9f,0xe1,0xc8,0x50,0x98,
0xe2,0x2c,0x2b,0x90,0x65,0xde,0x20,0xd1,0x9c,0x2e,0xb8,0x7c,0xe5,0x44,0x95,0xc1,
0xea,0x63,0x2c,0x7a,0x15,0xa1,0x18,0xb6,0x5d,0xb0,0x5e,0x2,0x46,0xf3,0x73,0xd6,
0x99,0x99,0x2b,0xe5,0xb8,0xd5,0xc2,0x1e,0xe0,0xd9,0x80,0x8c,0x16,0xe7,0x36,0xcb,
0x89,0xb8,0x7f,0x88,0xfe,0x78,0x5f,0x14,0x49,0xff,0x15,0x7d,0x31,0x9c,0xb2,0x97,
0xb0,0xfe,0x2d,0x91,0xcf,0xaa,0x6e,0x42,0x7f,0x70,0x2a,0xe8,0x3,0xaf,0x5b,0xc8,
0xe6,0xec,0x99,0x7c,0xb5,0x44,0xdd,0xc5,0x6d,0x47,0xf6,0xd6,0x9a,0x5d,0x4d,0xd4,
0x10,0x56,0x29,0x97,0x88,0x35,0xd0,0x54,0x1,0x22,0x50,0x68,0x8d,0x18,0x2b,0xea,
0x3,0x8f,0x53,0xef,0x4e,0x7c,0x15,0x44,0xbd,0x41,0x46,0x63,0x7e,0x8b,0x69,0x52,
0x56,0x21,0x38,0x88,0xc7,0xab,0xd,0xa0,0xc4,0xcd,0x58,0xc6,0xf0,0xda,0xc5,0xf4,
0xb,0xcf,0xcb,0x6a,0x1c,0xaf,0x73,0xf2,0xdd,0xd4,0x5b,0xb9,0x78,0x43,0x7e,0x27,
0xd7,0xfb,0xc3,0x93,0x79,0x66,0x89,0x59,0xf1,0x14,0xf1,0xa2,0xee,0xcb,0x5b,0xbe,
0xec,0xf,0x2b,0xcb,0x2b,0x2c,0x56,0x43,0x54,0x58,0x9d,0x3f,0x91,0xf9,0xaa,0xfb,
0xa9,0x5f,0x20,0xa8,0x9d,0xb2,0x2f,0x9c,0x5b,0xfc,0x34,0x41,0xc3,0x57,0x8d,0x5c,
0x91,0xcc,0x6f,0xf8,0xb2,0x65,0x3d,0xcb,0x5f,0x79,0x6f,0x38,0x3d,0xf9,0x7e,0x10,
0xeb,0x2c,0x44,0x73,0xd7,0x39,0xfc,0xbc,0xcb,0xbe,0xd0,0xc4,0x1c,0x22,0xdb,0x98,
0x6a,0x67,0xfa,0x9e,0xf3,0xa6,0x9b,0x8d,0x2a,0x6f,0x32,0xc3,0x71,0x3,0x90,0xb5,
0x7,0x6f,0x96,0x9d,0xc8,0xbc,0xa,0xa0,0x7e,0xaa,0x5e,0x84,0xa8,0xd8,0x72,0xc,
0xdc,0xa4,0x88,0xc4,0x9d,0x2,0xa7,0x89,0xb8,0x4f,0xa8,0xf6,0x13,0xdd,0xa6,0xc3,
0xe3,0x44,0x95,0xe2,0x79,0xc1,0x77,0xbc,0xbc,0x35,0x61,0xde,0x14,0x1a,0xe5,0x88,
0x38,0xd5,0xee,0x4,0x9a,0x97,0xf5,0xa7,0xc2,0x21,0x4a,0x7d,0x3b,0x2d,0x4e,0xb1,
0xd5,0xb1,0x6d,0x5e,0xbc,0x9d,0xd0,0x71,0x19,0x8c,0xa8,0x52,0xc8,0x47,0xea,0x4f,
0xc3,0xb0,0xbb,0x1f,0x79,0xe6,0xf2,0x9a,0xa7,0xde,00,0x65,0xd6,0xaa,0x74,0x54,
0xd6,0x50,0x91,0x39,0x78,0xa2,0xec,0x4d,0xf7,0xf7,0xf,0xdd,0xec,0xe1,0x5f,0x11,
0x32,0xbf,0xf2,0xea,0xc5,0x77,0x13,0x53,0x45,0x7e,0xc3,0x92,0xd5,0x53,0x9c,0x77,
0x22,0x53,0xc5,0x9b,0xcd,0x9f,0x78,0xaa,0xaa,0xaa,0x95,0x24,0x1b,0x45,0x9e,0x42,
0xe8,0x74,0x44,0xd4,0x6c,0xf5,0x9c,0x55,0xf9,0xe2,0x77,0x70,0x71,0x76,0x66,0xab,
0x2e,0x76,0x87,0x8c,0x51,0x69,0xbe,0x5a,0x9b,0xd5,0x2f,0xd,0x15,0x4e,0xe7,0x49,
0x9c,0xc,0x59,0x8c,0x3c,0x3b,0x54,0x63,0xe5,0xce,0x57,0xa0,0xc7,0xa9,0xa6,0x94,
0x8e,0x1b,0xd9,0x9,0x29,0x7f,0xcf,0x63,0xd9,0xfc,0xf3,0x7c,0xd5,0x44,0xf4,0x8b,
0x5b,0x50,0x10,0xae,0xc3,0xe5,0xcd,0x70,0x75,0x86,0xd5,0x11,0xdd,0x66,0x47,0x99,
0x1f,0x51,0xd1,0xd4,0x7d,0xc6,0xef,0x18,0xb2,0x9e,0x15,0x51,0xb4,0x79,0x37,0xcb,
0x8f,0x52,0x8d,0x52,0x77,0x78,0x7e,0x3f,0xc9,0x18,0x5d,0x25,0x7e,0x86,0x5b,0xfa,
0x9e,0xc9,0x57,0xfa,0x79,0x5c,0xd5,0xe7,0x58,0x9d,0x15,0x5f,0x7b,0x37,0xff,0x97,
0x9a,0xa7,0x8c,0xb2,0xf0,0x6f,0x6b,0x33,0xf5,0x4b,0x2f,0x59,0x58,0xff,0x74,0x77,
0x9c,0x1f,0x45,0x5e,0xb5,0x8b,0x69,0x5c,0x1e,0x63,0xf2,0x6b,0xae,0xea,0xd,0xbd,
0x62,0xce,0x67,0xd6,0x5c,0xed,0x24,0x39,0xbb,0xc9,0x1c,0x6f,0xba,0xb7,0xa0,0x88,
0x13,0xdf,0x33,0xec,0x54,0x42,0x8a,0x79,0x93,0x63,0x55,0x7a,0x2b,0x58,0x9,0xb2,
0x60,0xe6,0xee,0x5b,0xd7,0xfb,0xf8,0x5b,0xac,0xae,0x79,0x7a,0xa4,0xbd,0x5d,0xe1,
0xaa,0x16,0xe9,0xce,0x9f,0x8b,0xe1,0x3e,0xb1,0x2e,0xd6,0x1,0x12,0x63,0xbd,0x22,
0xbb,0x52,0xde,0x36,0xb1,0xd8,0xfc,0x2a,0xb2,0x23,0xe4,0x6c,0x56,0xb9,0xd3,0x48,
0x77,0xa2,0x7e,0x1e,0x66,0x30,0x5e,0x11,0x7f,0x45,0x67,0x80,0xff,0x3f,0xb0,0x7f,
0x60,0xa4,0x5,0x9a,0x84,0x16,0x9a,0xba,0xff,0x75,0xd6,0x83,0x7b,0x8c,0x79,0xb9,
0x3,0x8b,0xef,0x61,0x45,0xb8,0x5b,0xfc,0xd5,0x94,0xad,0xc4,0x7c,0x84,0x8a,0x6b,
0x45,0xef,0x9f,0x85,0xe5,0x6f,0xd7,0xbf,0x66,0x37,0xd2,0xf0,0x7b,0xa1,0x6d,0x38,
0x6f,0xea,0x2d,0xfa,0x1a,0x43,0x58,0xe1,0x6d,0xb8,0xd0,0xb,0x77,0xf1,0xfe,0x58,
0x98,0x7a,0xff,0x36,0xc3,0x7e,0xea,0x7d,0x5a,0xb4,0xa3,0xe6,0xbf,0x87,0xee,0xa3,
0x34,0xaa,0xcb,0xcb,0x73,0x67,0xb1,0x77,0x45,0x51,0x55,0x55,0x45,0x39,0xf,0xf7,
0x3b,0x28,0xea,0x1f,0x5b,0xf0,0x85,0xa7,0x9c,0x22,0x7f,0xb2,0xf7,0xc7,0x7e,0x77,
0xfb,0x1b,0x7c,0x76,0x6b,0x30};

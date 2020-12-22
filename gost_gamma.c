#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>


u_int32_t n5 = 3452775555;
u_int32_t n6 = 2223466090;
u_int64_t plaintexts[256] = {
        0x6C, 0x64, 0x66, 0x62, 0x6A, 0x65, 0x6B, 0x69, 0x6E, 0x68, 0x6D, 0x67, 0x60, 0x63, 0x6F, 0x61,
        0x8C, 0x84, 0x86, 0x82, 0x8A, 0x85, 0x8B, 0x89, 0x8E, 0x88, 0x8D, 0x87, 0x80, 0x83, 0x8F, 0x81,
        0x2C, 0x24, 0x26, 0x22, 0x2A, 0x25, 0x2B, 0x29, 0x2E, 0x28, 0x2D, 0x27, 0x20, 0x23, 0x2F, 0x21,
        0x3C, 0x34, 0x36, 0x32, 0x3A, 0x35, 0x3B, 0x39, 0x3E, 0x38, 0x3D, 0x37, 0x30, 0x33, 0x3F, 0x31,
        0x9C, 0x94, 0x96, 0x92, 0x9A, 0x95, 0x9B, 0x99, 0x9E, 0x98, 0x9D, 0x97, 0x90, 0x93, 0x9F, 0x91,
        0xAC, 0xA4, 0xA6, 0xA2, 0xAA, 0xA5, 0xAB, 0xA9, 0xAE, 0xA8, 0xAD, 0xA7, 0xA0, 0xA3, 0xAF, 0xA1,
        0x5C, 0x54, 0x56, 0x52, 0x5A, 0x55, 0x5B, 0x59, 0x5E, 0x58, 0x5D, 0x57, 0x50, 0x53, 0x5F, 0x51,
        0xCC, 0xC4, 0xC6, 0xC2, 0xCA, 0xC5, 0xCB, 0xC9, 0xCE, 0xC8, 0xCD, 0xC7, 0xC0, 0xC3, 0xCF, 0xC1,
        0x1C, 0x14, 0x16, 0x12, 0x1A, 0x15, 0x1B, 0x19, 0x1E, 0x18, 0x1D, 0x17, 0x10, 0x13, 0x1F, 0x11,
        0xEC, 0xE4, 0xE6, 0xE2, 0xEA, 0xE5, 0xEB, 0xE9, 0xEE, 0xE8, 0xED, 0xE7, 0xE0, 0xE3, 0xEF, 0xE1,
        0x4C, 0x44, 0x46, 0x42, 0x4A, 0x45, 0x4B, 0x49, 0x4E, 0x48, 0x4D, 0x47, 0x40, 0x43, 0x4F, 0x41,
        0x7C, 0x74, 0x76, 0x72, 0x7A, 0x75, 0x7B, 0x79, 0x7E, 0x78, 0x7D, 0x77, 0x70, 0x73, 0x7F, 0x71,
        0xBC, 0xB4, 0xB6, 0xB2, 0xBA, 0xB5, 0xBB, 0xB9, 0xBE, 0xB8, 0xBD, 0xB7, 0xB0, 0xB3, 0xBF, 0xB1,
        0xDC, 0xD4, 0xD6, 0xD2, 0xDA, 0xD5, 0xDB, 0xD9, 0xDE, 0xD8, 0xDD, 0xD7, 0xD0, 0xD3, 0xDF, 0xD1,
        0x0C, 0x04, 0x06, 0x02, 0x0A, 0x05, 0x0B, 0x09, 0x0E, 0x08, 0x0D, 0x07, 0x00, 0x03, 0x0F, 0x01,
        0xFC, 0xF4, 0xF6, 0xF2, 0xFA, 0xF5, 0xFB, 0xF9, 0xFE, 0xF8, 0xFD, 0xF7, 0xF0, 0xF3, 0xFF, 0xF1,
};



//один такт

u_int64_t tact(u_int64_t T, u_int32_t key, u_int32_t s)
{
    u_int32_t L, R;
    L = (T & 0xFFFFFFFF00000000) >> 32;
    R = T & 0x00000000FFFFFFFF;
    u_int64_t new_r;
    new_r = R+key;
    u_int64_t mod = pow(2, 32);
    new_r = new_r%mod;
    u_int32_t f[8];
    f[0] = 0x0000000F;
    f[1] = 0x000000F0;
    f[2] = 0x00000F00;
    f[3] = 0x0000F000;
    f[4] = 0x000F0000;
    f[5] = 0x00F00000;
    f[6] = 0x0F000000;
    f[7] = 0xF0000000;

    u_int32_t r_for_s[8];
    u_int32_t s_for_r[8];
    for (int i = 0; i<8; i++){
        r_for_s[i] = new_r&&f[i];
        r_for_s[i] = r_for_s[i] >> 4*i;
        s_for_r[i] = s&&f[i];
        s_for_r[i] = s_for_r[i] >> 4*i;
    }
    new_r = 0;
    for (int i = 0; i<8; i++){
        new_r = new_r | (s_for_r[r_for_s[i]]<<4*i);
    }
    new_r = (new_r<<11) | (new_r >> 21);
    new_r = new_r && L;
    u_int64_t new_l = R;
    return (new_l<<32) | new_r;
}

u_int64_t gost_real (u_int64_t T, u_int32_t s, u_int32_t keys[8])
{
    u_int64_t new_T = T;
    for (int j = 0; j<3; j++) {
        for (int i = 0; i < 8; ++i) {
            new_T = tact(new_T, keys[i], s);
        }
    }
    for (int i = 7; i >=0; i--) {
        new_T = tact(new_T, keys[i], s);
    }
    return new_T;
}
//
//CM1 CM3 - по модулю 2ˆ32
int main() {

    //заполняем ключи
    u_int32_t keys[8];
    keys[0] = 3294967295;
    keys[1] = 3294967295;
    keys[2] = 3294967295;
    keys[3] = 3294967295;
    keys[4] = 3294967295;
    keys[5] = 3294967295;
    keys[6] = 3294967295;
    keys[7] = 3294967295;

    u_int32_t S = 3295967795;
    bool s[64];
    for (int i = 0; i<64; i++){
        s[i] = rand() %2;
    }
    u_int32_t n1, n2, n3, n4;
    n1 = 0;
    n2 = 0;
    for (int i = 0; i<32; i++){
        n1 = n1|(s[i]<<i);
        n2 = n2|(s[i+32]<<i);
    }
    u_int64_t p;
    p = n1;
    p = (p<<32) | n2;
    p = gost_real(p, S, keys);
    n3 = (p & 0xFFFFFFFF00000000) >> 32;
    n4 = p & 0x00000000FFFFFFFF;

    u_int64_t mod = pow(2, 32);

    u_int64_t g[256];
    u_int64_t c[256];
    for (int i = 0; i<256; i++){
        if (n4+n6>=mod){
            n4 = n4+n6-mod+1;
        }
        else {n4 = n4+n6;}
        n3 = (n3+n5)%mod;

        n1 = n3;
        n2 = n4;
        g[i] = n1;
        g[i] = n2 | (g[i]<<32);
        g[i] = gost_real(g[i], S, keys);
        c[i] = plaintexts[i]&&g[i];
    }
    return 0;
}
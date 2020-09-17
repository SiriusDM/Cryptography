//本题的数据生成器
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ctime>

int sbn[16] = {0xE, 0x3, 0x4, 0x8, 0x1, 0xC, 0xA, 0xF,
               0x7, 0xD, 0x9, 0x6, 0xB, 0x2, 0x0, 0x5};

int cp[65536];
int color[65536];
int cnt[16][16];

int sb1[65536] = {0}; // S
int pb1[65536] = {0}; // P
int sbn1[65536] = {0};

inline int read() {
  int x = 0;
  char ch = getchar();
  while (ch == ' ' || ch == '\n')
    ch = getchar();
  while (ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'f') {
    if (ch >= '0' && ch <= '9')
      x = (x << 4) + (ch - '0');
    else if (ch >= 'a' && ch <= 'f')
      x = (x << 4) + 10 + (ch - 'a');
    ch = getchar();
  }
  return x;
}
int snbox(int u) {
  int sbn11[16] = {0xE, 0x3, 0x4, 0x8, 0x1, 0xC, 0xA, 0xF,
                   0x7, 0xD, 0x9, 0x6, 0xB, 0x2, 0x0, 0x5};
  int ut = 0, u1 = 0;
  for (int i = 1; i <= 4; i++) {
    if (i == 1)
      u1 = u & 0xF000;
    else if (i == 2)
      u1 = u & 0x0F00;
    else if (i == 3)
      u1 = u & 0x00F0;
    else
      u1 = u & 0x000F;
    int ui = u1 >> ((4 - i) << 2);
    ui = sbn11[ui];
    ut <<= 4;
    ut |= ui;
  }
  return ut;
}
// S
int sbox(int u) {
  int sb[16] = {0xE, 0x4, 0xD, 0x1, 0x2, 0xF, 0xB, 0x8,
                0x3, 0xA, 0x6, 0xC, 0x5, 0x9, 0x0, 0x7};
  int ut = 0, u1 = 0;
  for (int i = 1; i <= 4; i++) {
    if (i == 1)
      u1 = u & 0xF000;
    else if (i == 2)
      u1 = u & 0x0F00;
    else if (i == 3)
      u1 = u & 0x00F0;
    else
      u1 = u & 0x000F;
    int ui = u1 >> ((4 - i) << 2);
    ui = sb[ui];
    ut <<= 4;
    ut |= ui;
  }
  return ut;
}

// P
int pbox(int v) {
  int vt = 0, vr = 0, v1 = 0;
  for (int i = 15; i >= 12; i--) {
    for (int j = 0; j < 4; j++) {
      v1 = v << (15 - i + (j << 2));
      vr = v1 >> 15;
      vt <<= 1;
      vr &= 0x1;
      vt |= vr;
    }
  }
  return vt;
}

int spn(int k, int p) {
  int N = 4;
  int n;
  int w = 0, v = 0, kr = 0, u = 0, c = 0;
  w = p;
  for (int i = 0; i < 3; i++) {
    kr = (k >> (16 - (i << 2))) & 0xFFFF;
    u = w ^ kr;
    v = sb1[u];
    w = pb1[v];
  }
  kr = (k >> 4) & 0xFFFF;
  u = w ^ kr;
  v = sb1[u];
  kr = k & 0xFFFF;
  u = v ^ kr;
  return u;
}

int main() {
   freopen("T31.in","r",stdin); 
   freopen("T31.out","w",stdout);
  srand((int)time(0));
printf("10\n");
  for (int i = 0; i < 65536; i++)
    sb1[i] = sbox(i);
  for (int i = 0; i < 65536; i++)
    pb1[i] = pbox(i);
  for (int i = 0; i < 65536; i++)
    sbn1[i] = snbox(i);
  int cpi[100];
  for (int i=0; i<10; i++) {
    cpi[i] = read();
  }
  for (int i=0; i<10; i++) {
    for (int j = 0; j < 65536; j++) 
      printf("%04x ",spn(cpi[i], j));
    printf("\n");
  }
  fclose(stdin);
  fclose(stdout);
}
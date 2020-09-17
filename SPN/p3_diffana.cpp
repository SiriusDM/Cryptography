// SPN
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

#define MAXT 100
#define MAXT1 1500
#define MAXT2 1500

using namespace std;
// x' = x_ y = y1 y* = y

struct RightPairs {
  int y, _y;
};
struct Kcnt {
  int k1, k2;
  int cnt;
  bool operator<(const Kcnt &b) { return cnt > b.cnt; }
};

int sbn[16] = {0xE, 0x3, 0x4, 0x8, 0x1, 0xC, 0xA, 0xF,
               0x7, 0xD, 0x9, 0x6, 0xB, 0x2, 0x0, 0x5};

int cp[65536];
int cnt[16][16];

int sb1[65536] = {0}; // S
int pb1[65536] = {0}; // P
int sbn1[65536] = {0};

int ppp = 0;

// func
inline int read(void); // fast read
int sbox(int u);       // S
int snbox(int u);
int pbox(int u);       // P
int spn(int k, int p); // spn

inline int getnum(char c){return (c>='0'&&c<='9')?c-'0':c-87;}
int main() {
  int n; // All
  RightPairs T[2000];
  RightPairs T2[MAXT1 + 1];
  char str[350010];
  Kcnt Kcnt1[256], Kcnt3[256], Kcnt2[256];
#ifndef ONLINE_JUDGE
  freopen("T31.out", "r", stdin);
#endif

  for (int i = 0; i < 65536; i++)
    sb1[i] = sbox(i);
  for (int i = 0; i < 65536; i++)
    pb1[i] = pbox(i);
  for (int i = 0; i < 65536; i++)
    sbn1[i] = snbox(i);
  scanf("%d\n", &n);
  while (n--) {
    ppp = 0;
    memset(cnt, 0, sizeof(cnt));
		fgets(str,65536*5+1,stdin);
		for(int i = 0; i < 65536; ++i)
		{
			cp[i] = getnum(str[i*5]) << 12;
			cp[i] |= getnum(str[i*5+1]) << 8;
			cp[i] |= getnum(str[i*5+2]) << 4;
			cp[i] |= getnum(str[i*5+3]);
		}
    int u1, u2, u3, u4;     // u
    int _u1, _u2, _u3, _u4; // u*
    int u1_, u2_, u3_, u4_; // u'
    int v1, v2, v3, v4;     // u
    int _v1, _v2, _v3, _v4; // u*
    int v1_, v2_, v3_, v4_; // u'

    int t; // counter

    t = 0;
    for (int i = 0; i < MAXT2; i++) {
      int y1 = (cp[i] & 0xf000) >> 12,
          y3 = (cp[i] & 0x00f0) >> 4; // y
      int _y1 = (cp[(i ^ 0x0b00)] & 0xf000) >> 12,
          _y3 = (cp[(i ^ 0x0b00)] & 0x00f0) >> 4; // y*
      if (y1 == _y1 && y3 == _y3) {

        T[t].y = cp[i];
        T[t++]._y = cp[(i ^ 0x0b00)];
      }
    }
    // calc cnt
    for (int i = 0; i < t; i++) {
      for (int K2 = 0; K2 < 16; K2++)
        for (int K4 = 0; K4 < 16; K4++) {
          int y = T[i].y, _y = T[i]._y;
          int y1 = (y & 0xf000) >> 12, y2 = (y & 0x0f00) >> 8,
              y3 = (y & 0x00f0) >> 4, y4 = y & 0x000f; // y
          int _y1 = (_y & 0xf000) >> 12, _y2 = (_y & 0x0f00) >> 8,
              _y3 = (_y & 0x00f0) >> 4,
              _y4 = _y & 0x000f; // y*
          // u
          v2 = K2 ^ y2;
          v4 = K4 ^ y4;
          u2 = sbn[v2];
          u4 = sbn[v4];
          // u*
          _v2 = K2 ^ _y2;
          _v4 = K4 ^ _y4;
          _u2 = sbn[_v2];
          _u4 = sbn[_v4];
          // u'
          u2_ = u2 ^ _u2;
          u4_ = u4 ^ _u4;

          if (u2_ == 6 && u4_ == 6)
            cnt[K2][K4]++;
        }
    }
    // save cnt
    t = 0;
    for (int i = 0; i < 16; i++)
      for (int j = 0; j < 16; j++) {
        Kcnt1[t].k1 = i;
        Kcnt1[t].k2 = j;
        Kcnt1[t++].cnt = cnt[i][j];
        //	printf("%d\n",cnt[i][j]);
      }
    sort(Kcnt1, Kcnt1 + 256);
    for (int K24 = 0; K24 < 256; K24++) {
      if (ppp)
        break;
      memset(cnt, 0, sizeof(cnt));
      t = 0;
      for (int i = 0; i < MAXT1; i++) {
        int y1 = (cp[i] & 0xf000) >> 12, y2 = (cp[i] & 0x0f00) >> 8,
            y3 = (cp[i] & 0x00f0) >> 4, y4 = cp[i] & 0x000f; // y
        int _y1 = (cp[(i ^ 0x0f00)] & 0xf000) >> 12,
            _y2 = (cp[(i ^ 0x0f00)] & 0x0f00) >> 8,
            _y3 = (cp[(i ^ 0x0f00)] & 0x00f0) >> 4,
            _y4 = cp[(i ^ 0x0f00)] & 0x000f; // y*
        //				printf("------------------fail!------------------------\n");//debug
        T2[t].y = cp[i];
        T2[t++]._y = cp[(i ^ 0x0f00)];
      }
      // calc cnt
      for (int i = 0; i < t; i++) {
        for (int K1 = 0; K1 < 16; K1++) 
          for (int K3 =0; K3 < 16; K3++){
          
          int y = T2[i].y, _y = T2[i]._y;
          int y1 = (y & 0xf000) >> 12, y2 = (y & 0x0f00) >> 8,
              y3 = (y & 0x00f0) >> 4, y4 = y & 0x000f; // y
          int _y1 = (_y & 0xf000) >> 12, _y2 = (_y & 0x0f00) >> 8,
              _y3 = (_y & 0x00f0) >> 4,
              _y4 = _y & 0x000f; // y*
          // u
          v1 = K1 ^ y1;
          v2 = Kcnt1[K24].k1 ^ y2;
          v3 = K3 ^ y3;
          v4 = Kcnt1[K24].k2 ^ y4;
          u1 = sbn[v1];
          u2 = sbn[v2];
          u3 = sbn[v3];
          u4 = sbn[v4];
          // u*
          _v1 = K1 ^ _y1;
          _v2 = Kcnt1[K24].k1 ^ _y2;
          _v3 = K3 ^ _y3;
          _v4 = Kcnt1[K24].k2 ^ _y4;
          _u1 = sbn[_v1];
          _u2 = sbn[_v2];
          _u3 = sbn[_v3];
          _u4 = sbn[_v4];
          // u'
          u1_ = u1 ^ _u1;
          u2_ = u2 ^ _u2;
          u3_ = u3 ^ _u3;
          u4_ = u4 ^ _u4;

          if (u1_ == 4 && u2_ == 2 && u3_ == 6 && u4_ == 4)
            cnt[K1][K3]++;
          if (u1_ == 2 && u2_ == 4 && u3_ == 6 && u4_ == 2)
            cnt[K1][K3]++;
          if (u1_ == 6 && u2_ == 0 && u3_ == 6 && u4_ == 6)
            cnt[K1][K3]++;
        }
      }
      t = 0;
      for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++) {
          Kcnt3[t].k1 = i;
          Kcnt3[t].k2 = j;
          Kcnt3[t++].cnt = cnt[i][j];
        }
      sort(Kcnt3, Kcnt3 + 256);
      for (int w=0; w<256; w++) {
        if (ppp) break;
      for (int j = 0; j < 256; j++) {
        if (ppp) break;
        for (int i = 0; i < 65536; i++) {
          if (ppp)
            break;
          int kk = Kcnt3[j].k1, l = i;
          kk <<= 4;
          kk |= Kcnt1[w].k1;
          kk <<= 4;
          kk |= Kcnt3[j].k2;
          kk <<= 4;
          kk |= Kcnt1[w].k2;
          l <<= 16;
          kk |= l;
          if (spn(kk, 1234) == cp[1234] && spn(kk, 5678) == cp[5678]) {
            printf("%08x\n", kk);
            ppp = 1;
            break;
          }
        }
        }
      }

    }
  }
  fclose(stdin);
  return 0;
}

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
//  原始的SPN加解密算法
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int N = 4;
int n;

int sb1[65536],sbn1[65536],pb1[65536];


struct IO
{
#define MAXSIZE (1 << 16)
    char buf[MAXSIZE], *p1, *p2;
    char pbuf[MAXSIZE], *pp;
    IO() : p1(buf), p2(buf), pp(pbuf) {}
    ~IO()
    {
        fwrite(pbuf, 1, pp - pbuf, stdout);
    }
    void flush()
    {
        fwrite(pbuf, 1, pp - pbuf, stdout);
        pp = pbuf;
    }
    inline char gc()
    {
        if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
        return (p1 == p2 ? ' ' : *p1++);
    }
    inline bool blank(char ch)
    {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }
    template <class T> inline void read_uint(T& x)
    {
        x                = 0;
        register char ch = gc();
        for (; blank(ch); ch = gc())
            ;
        for (; !blank(ch); ch = gc()) x = x * 10 + ch - '0';
    }
    int hex2bin_char(char x)
    {
        if (isdigit(x)) return x - '0';
        if (isupper(x)) x = tolower(x);
        return x - 'a' + 10;
    }
    template <class T> inline void read_in_hex(T& x)
    {
        x                = 0;
        register char ch = gc();
        for (; blank(ch); ch = gc())
            ;
        for (; !blank(ch); ch = gc()) x = (x << 4) + hex2bin_char(ch);
    }
    inline void push(const char& c)
    {
        if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
        *pp++ = c;
    }
    char bin2hex_char(int x)
    {
        return x >= 10 ? x - 10 + 'a' : x + '0';
    }
    template <class T> inline void write_in_hex(T x)
    {
        static T sta[30];
        int      top = 0;
        do {
            sta[top++] = x & 15, x /= 16;
        } while (x);
        while (top != 4) sta[top++] = 0;
        while (top) push(bin2hex_char(sta[--top]));
    }
} io;
inline int read() { //快速读入
    int x=0;
    char ch=getchar(); 
    while (ch == ' '||ch =='\n') ch=getchar();
    while (ch >= '0' && ch <='9' || ch >= 'a' && ch <= 'f') {
        if (ch >= '0' && ch <='9') x = (x<<4) + (ch - '0');
        else if (ch >= 'a' && ch <= 'f') x= (x<<4) + 10 + (ch - 'a');
        ch = getchar(); 
    }
    return x;
}

//S盒
int sbox(int u) {
    int sb[16] = {0xE,0x4,0xD,0x1,0x2,0xF,0xB,0x8,0x3,0xA,0x6,0xC,0x5,0x9,0x0,0x7};
    int ut=0,u1=0;
    for (int i=1; i<=4; i++) {
        if (i==1) u1 = u & 0xF000;
        else if (i==2) u1 = u & 0x0F00;
        else if (i==3) u1 = u & 0x00F0;
        else u1 = u & 0x000F; 
        int ui = u1 >> ((4-i)<<2);
        ui = sb[ui];
        ut<<=4;
        ut|=ui; 
    }
    return ut;
}

int sbnox(int u) {
    int sbn[16] = {0xE,0x3,0x4,0x8,0x1,0xC,0xA,0xF,0x7,0xD,0x9,0x6,0xB,0x2,0x0,0x5};
    int ut=0,u1=0;
    for (int i=1; i<=4; i++) {
        if (i==1) u1 = u & 0xF000;
        else if (i==2) u1 = u & 0x0F00;
        else if (i==3) u1 = u & 0x00F0;
        else u1 = u & 0x000F; 
        int ui = u1 >> ((4-i)<<2);
        ui = sbn[ui];
        ut<<=4;
        ut|=ui; 
    }
    return ut;
}
//P盒
int pbox(int v) {
    int vt=0,vr=0,v1=0;
    for (int i=15; i>=12; i--) {
        for (int j=0; j<4; j++) {
            v1 = v<<(15-i+(j<<2));
            vr = v1>>15;
            vt <<=1;
            vr &= 0x1;
            vt |=vr;
        }
    }
    return vt;
}

int main() {
    scanf("%d",&n); 
    for (int i=0; i<65536; i++) {
        sb1[i] = sbox(i);
        sbn1[i] = sbnox(i);
        pb1[i] = pbox(i);
    }
    while (n--) {
        int k,p,w=0,v=0,kr=0,u=0,c=0;
        io.read_in_hex(k);
        io.read_in_hex(p);
        //加密过程 p为明文
        w = p;
        for (int i=0;i<3;i++) {
            kr = (k>>(16-(i<<2))) & 0xFFFF;
            u = w^kr;
            v = sb1[u];
            w = pb1[v];
        }
        kr = (k>>4) & 0xFFFF;
        u = w^kr;
        v = sb1[u];
        kr = k & 0xFFFF;
        u = v^kr;
        io.write_in_hex(u);
        io.push(' ');
        c = u^1;
         //解密过程 c为密文
        c ^= kr;
        c = sbn1[c];
        kr = (k>>4) & 0xFFFF;
        c ^=kr;
        for (int i=2;i>=0;i--) {
            kr = (k>>(16-(i<<2))) & 0xFFFF;
            c = pb1[c];
            c = sbn1[c];
            c ^=kr;
        }
    io.write_in_hex(c);
    io.push('\n');
    }
}
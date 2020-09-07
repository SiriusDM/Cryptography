#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int N = 4;
int n;

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
    while (n--) {
        int k=read(),p=read(),w=0,v=0,kr=0,u=0,c=0;
        w = p;
        for (int i=0;i<3;i++) {
            kr = (k>>(16-(i<<2))) & 0xFFFF;
            u = w^kr;
            v = sbox(u);
            w = pbox(v);
        }
        kr = (k>>4) & 0xFFFF;
        u = w^kr;
        v = sbox(u);
        kr = k & 0xFFFF;
        u = v^kr;
        printf("%04x ",u);
        c = u^1;
        c ^= kr;
        c = sbnox(c);
        kr = (k>>4) & 0xFFFF;
        c ^=kr;
        for (int i=2;i>=0;i--) {
            kr = (k>>(16-(i<<2))) & 0xFFFF;
            c = pbox(c);
            c = sbnox(c);
            c ^=kr;
        }
        printf("%04x\n",c);
    //    cout<<w;
    //    printf("%d %d",k,p);
    }
//    for (int i=1; i<=8; i++) printf("%d ",k[i]);
//    for (int i=1; i<=8; i++) printf("%d ",p[i]);
}
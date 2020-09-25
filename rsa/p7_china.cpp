#include <gmpxx.h>
#include <cstdio>
#include <cstdlib>
#include <gmp.h>

#define K 5

using namespace std;

int t=0;
mpz_t g[50];
mpz_t ei[50]

void qpow1(mpz_t ra1, mpz_t base, mpz_t power, mpz_t n) {
    mpz_t result,rop,power1;
    mpz_init(result);
    mpz_init(rop);
      mpz_init(power1);
//    gmp_printf("%Zd %Zd %Zd %Zd          1231231sad 12312\n",c,d,c1,d1);
    mpz_init_set_ui(result,1);
    mpz_init_set_ui(power1,1);
    while (mpz_cmp_ui(power,0) > 0) {
        mpz_and(rop,power,power1);
        if (mpz_cmp_ui(rop,1) == 0) {
            mpz_mul(result,result,base);
            mpz_mod(result,result,n);
        }
        mpz_fdiv_q_ui(power, power, 2);
        mpz_mul(base,base,base);
        mpz_mod(base,base,n);

    }
 //   gmp_printf("%Zd %Zd %Zd %Zd          1231231sad 12312\n",c,d,c1,d1);
    mpz_set(ra1,result);
 //   gmp_printf("%Zd\n",ra1);
 //   mpz_clear(result);
 //   mpz_clear(rop);
 //   mpz_clear(power1);
} 
void qpow(mpz_t ra1, mpz_t base, mpz_t power, mpz_t n) {
    mpz_t result,rop11;
    gmp_printf("%Zd %Zd %Zd      11111\n",base,power,n); 
    mpz_init_set_ui(result,1);
    mpz_init(rop11);
    for (int i=t; i>=0; i--) {
        mpz_set_ui(rop11,(1<<K));
      //  qpow1(result,result,rop11,n);
        mpz_powm_ui(result,result,(1<<K),n);
        mpz_mul(result,result,g[mpz_tstbit(power,i)]);
        gmp_printf("g[i] = %Zd\n",g[mpz_tstbit(power,i)]);
        mpz_mod(result,result,n);
    }
 //   printf("= = = = = = \n");
 //   gmp_printf("%Zd %Zd %Zd %Zd          1231231sad 12312\n",c,d,c1,d1);
    mpz_set(ra1,result);
 //   gmp_printf("%Zd\n",ra1);
 //   mpz_clear(result);  
 //   mpz_clear(rop);
 //   mpz_clear(power1);
}   


int main() {
    int N;

    mpz_t e,d,p,q,p1,q1,c,rop,rop1,M,a1,a2,phi1,phi2,c1,d1,rop_,rop1_,d_,d1_;

    mpz_init(e);
    mpz_init(q);    mpz_init(p); 
    mpz_init(p1); mpz_init(q1);
    mpz_init(rop);  mpz_init(rop1);
    mpz_init(rop_);  mpz_init(rop1_);
    mpz_init(d);
    mpz_init(d_);
    mpz_init(d1_);
    mpz_init(a1);   mpz_init(a2);
    mpz_init(phi1); mpz_init(phi2);
    mpz_init(c1); mpz_init(d1);



//    mpz_init(c);

    scanf("%d",&N);
    gmp_scanf("%Zd %Zd %Zd",p,q,e);
    mpz_sub_ui(p1,p,1); //p1 = p-1
    mpz_sub_ui(q1,q,1); //q1 = q-1
    mpz_mul(rop,p1,q1); 
    mpz_invert(d,e,rop);
    mpz_set(d1,d);
 //   printf(" ===== = = =\n");

//    gmp_printf("%Zd\n",d);
    mpz_init(M);
    mpz_mul(M,p,q);// M =p * q
    mpz_invert(phi1,q,p); //M-1
//    gmp_printf("%Zd\n",phi1);

    mpz_invert(phi2,p,q); //M-2
//    gmp_printf("%Zd\n",phi2);
    mpz_mul(rop,q,phi1); // rop = M1 * M-1 
    mpz_mul(rop1,p,phi2);// rop1 = M2 * M-2

//    printf(" ===== = = =\n");
//qpow_pre

    for (int i=0; i<(1<<K); i++)
        mpz_init(g[i]);
    mpz_set_ui(g[0],1);
//    printf(" ===== = = =\n");
    while (mpz_cmp_ui(d,0)) { 
        t++;
        mpz_fdiv_q_ui(d,d,(1<<K));
    }
    printf("%d\n",t);

    while (N--) {
        mpz_init(c);
        gmp_scanf("%Zd",c);
    //    printf("%d\n",mpz_tstbit(c,0));
        for (int i=1; i<=((1<<K)-1); i++)  {
            mpz_mul(g[i],g[i-1],c);
            gmp_printf("g[i] = %Zd\n",g[i]);
        //    mpz_mod(g[i],g[i],M);
        }
//        gmp_printf("%Zd %Zd %Zd %Zd  %Zd\n",M,g[0],g[1],g[2],g[3]);
        mpz_mod(c1,c,p);
        mpz_mod(d,d1,p1);
        qpow(a1,c,d,p); //a1 = c^d (mod p)
        mpz_mod(c,c1,q);
        mpz_mod(d,d1,q1);
        qpow(a2,c,d,q); //a2 = c^d (mod q)
        mpz_mul(rop_,rop,a1);   // rop = a1 * M1 * M-1
        mpz_mul(rop1_,rop1,a2);  //  rop1 = a2 * M2 * M-2
        mpz_add(rop_,rop_,rop1_);  // rop = rop + rop1
        mpz_mod(rop_,rop_,M); // mod M
        gmp_printf("%Zd\n",rop_);
    }
    mpz_clear(e); 
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(p1);
    mpz_clear(q1);
    mpz_clear(rop);
    mpz_clear(rop_);
    mpz_clear(rop1_);
    mpz_clear(rop1);
    mpz_clear(d);
    mpz_clear(c);
    mpz_clear(a1);
    mpz_clear(a2);
    mpz_clear(phi1);
    mpz_clear(phi2);
    mpz_clear(M);
//    mpz_clear(c1); mpz_clear(d1);


    return 0;
}
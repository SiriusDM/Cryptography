#include <gmpxx.h>
#include <cstdio>
#include <cstdlib>
#include <gmp.h>

#define k 7

using namespace std;

int t1=0,t2=0;
mpz_t g[1030];
int e1[1030],e2[1030];
int K = (1<<k);

void qpow1(mpz_t ra1, mpz_t base, mpz_t power, mpz_t n) {
    mpz_t result,rop,power1;
    mpz_init(result);
    mpz_init(rop);
      mpz_init(power1);
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
    mpz_set(ra1,result);
} 
void qpow_1(mpz_t ra1, mpz_t base, mpz_t power, mpz_t n) {
    mpz_t result,rop11; 
    mpz_init_set_ui(result,1);
    mpz_init_set_ui(rop11,K);
    for (int i=t1-1; i>=0; i--) {
        mpz_powm_ui(result,result,K,n);
        mpz_mul(result,result,g[e1[i]]);
        mpz_mod(result,result,n);
    }
    mpz_set(ra1,result);
}   
void qpow_2(mpz_t ra1, mpz_t base, mpz_t power, mpz_t n) {
    mpz_t result,rop11;
    mpz_init_set_ui(result,1);
    mpz_init_set_ui(rop11,K);
    for (int i=t2-1; i>=0; i--) {
        mpz_powm_ui(result,result,K,n);
        mpz_mul(result,result,g[e2[i]]);
        mpz_mod(result,result,n);
    }
    mpz_set(ra1,result);
}   


int main() {
    int N;

    mpz_t e,d,p,q,p1,q1,c,rop,rop1,M,a1,a2,phi1,phi2,c1,d1,rop_,rop1_,dp,dq;
    mpz_init(e);
    mpz_init(q);    mpz_init(p); 
    mpz_init(p1); mpz_init(q1);
    mpz_init(rop);  mpz_init(rop1);
    mpz_init(rop_);  mpz_init(rop1_);
    mpz_init(d);
    mpz_init(dp);
    mpz_init(dq);
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
    mpz_mod(dp,d,p1);
    mpz_mod(dq,d,q1);
    mpz_init(M);
    mpz_mul(M,p,q);// M =p * q
    mpz_invert(phi1,q,p); //M-1
    mpz_invert(phi2,p,q); //M-2
    mpz_mul(rop,q,phi1); // rop = M1 * M-1 
    mpz_mul(rop1,p,phi2);// rop1 = M2 * M-2
    for (int i=0; i<K; i++)
        mpz_init(g[i]);
    mpz_set_ui(g[0],1);
    mpz_set(d1,dp);

    while (mpz_cmp_ui(d1,0)) { 
        mpz_mod_ui(rop_,d1,K);
        e1[t1] = mpz_get_ui(rop_);
        t1++;
        mpz_fdiv_q_ui(d1,d1,K);
    }
    mpz_set(d1,dq);
    while (mpz_cmp_ui(d1,0)) { 
        mpz_mod_ui(rop_,d1,K);
        e2[t2] = mpz_get_ui(rop_);
        t2++;
        mpz_fdiv_q_ui(d1,d1,K);
    }
    while (N--) {
        mpz_init(c);
        gmp_scanf("%Zd",c);
        for (int i=1; i<=(K-1); i++)  {
            mpz_mul(g[i],g[i-1],c);
            mpz_mod(g[i],g[i],p);
        }
        mpz_mod(c1,c,p);
        mpz_set(d,dp);
        qpow_1(a1,c,d,p); //a1 = c^d (mod p)
        mpz_set_ui(g[0],1);
        for (int i=1; i<=(K-1); i++)  {
            mpz_mul(g[i],g[i-1],c);
            mpz_mod(g[i],g[i],q);
        }
        mpz_mod(c,c1,q);
        mpz_set(d,dq);
        qpow_2(a2,c,d,q); //a2 = c^d (mod q)
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
    mpz_clear(d1);
    mpz_clear(dp);
    mpz_clear(dq);
    mpz_clear(c);
    mpz_clear(a1);
    mpz_clear(a2);
    mpz_clear(phi1);
    mpz_clear(phi2);
    mpz_clear(M);
//    mpz_clear(c1); mpz_clear(d1);


    return 0;
}
#include <gmpxx.h>
#include <cstdio>
#include <cstdlib>
#include <gmp.h>

using namespace std;

void qpow(mpz_t base, mpz_t power, mpz_t n) {
    mpz_t result,rop,power1;
    mpz_init_set_ui(result,1);
//    gmp_printf("%Zd\n",result);

    mpz_init_set_ui(power1,1);
    while (mpz_cmp_ui(power,0) > 0) {
        mpz_and(rop,power,power1);
  //      gmp_printf("%Zd\n",rop);
        if (mpz_cmp_ui(rop,1) == 0) {//此处等价于if(power%2==1)
            mpz_mul(result,result,base);
            mpz_mod(result,result,n);
        //    gmp_printf("%Zd\n",result);
        }
        mpz_fdiv_q_ui(power, power, 2);//此处等价于power=power/2
        mpz_mul(base,base,base);
        mpz_mod(base,base,n);
     //   gmp_printf("%Zd\n",power);
    }
    gmp_printf("%Zd\n",result);
}   


int main() {
    int N;
    mpz_t e,a,p,q,n;
    mpz_init(e);
    mpz_init(a);
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    scanf("%d",&N);
    while (N--) {
        gmp_scanf("%Zd",e);
        gmp_scanf("%Zd",a);
        gmp_scanf("%Zd",p);
        gmp_scanf("%Zd",q);
        mpz_mul(n,p,q);
  //      gmp_printf("%Zd %Zd %Zd\n",n,p,q);
        qpow(a,e,n);
    //    gmp_printf("%Zd\n",qpow(a,e,n));
    }
    return 0;
}
#include <gmpxx.h>
#include <cstdio>
#include <cstdlib>
#include <gmp.h>

using namespace std;

mpz_t qpow(mpz_t base, mpz_t power) {
    mpz_t result,rop,power1;
    mpz_init_set_ui(result,1);
    mpz_init_set_ui(power1,1);
    while (mpz_cmp_ui(power,0) > 0) {
        mpz_ior(rop,power,power1);
        if (mpz_cmp_ui(rop,1) == 0) {//此处等价于if(power%2==1)
            mpz_mul(result,result,base);
            mpz_mod(result,result,);
        }
        power >>= 1;//此处等价于power=power/2
        base = (base * base) % 1000;
    }
    return result;


int main() {
    int n;
    mpz_t e,a,p,q,n;
    mpz_init(e);
    mpz_init(a);
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    scanf("%d",&n);
    while (n--) {
        gmp_scanf("%Zd",e);
        gmp_scanf("%Zd",a);
        gmp_scanf("%Zd",p);
        gmp_scanf("%Zd",q);
    }
    return 0;
}
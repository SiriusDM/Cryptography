#include <gmpxx.h>
#include <cstdio>
#include <cstdlib>
#include <gmp.h>

using namespace std;

inline int read();

int main() {
    mpz_t e,p,q,rop,p1,q1,rop1;
    mpz_init(e);
    mpz_init(p);
    mpz_init(p1);
    mpz_init(q1);
    mpz_init(q);
    mpz_init(rop);
    mpz_init(rop1);
    scanf("%d",&n);
    while (n--) {
        gmp_scanf("%Zd",e);
        gmp_scanf("%Zd",p);
        gmp_scanf("%Zd",q);
        mpz_sub_ui(p1,p,1); //p1 = p-1
        mpz_sub_ui(q1,q,1); //q1 = q-1
        if (mpz_cmp_si(e,10) < 0) {  //e < 10
            printf("ERROR\n");
            continue;
        }
        if (mpz_probab_prime_p(p) != 2 || mpz_probab_prime_p(q) != 2) { //p,q是否为素数
            printf("ERROR\n");
            continue;
        }
        mpz_sub(rop,p,q);
        if (mpz_cmp_si(rop,10000) < 0 || mpz_cmp_si(rop,-10000)) {  //10000>p-q>-10000
            printf("ERROR\n");
            continue;
        }
        mpz_gcd(rop,p1,q1);
        if (mpz_cmp_si(rop,50) <0) { //gcd(p-1,q-1) < 50
            printf("ERROR\n");
            continue;
        }
        mpz_mul(rop1,p1,q1);
        mpz_gcd(rop,rop1,e);
        if (mpz_cmp(rop,1) !=0 || mpz_cmp(rop1,e) <0) { //e 和 fi(n)不互质 或 e >fi(n)
            printf("ERROR\n");
            continue;
        }
        mpz_invert(rop,e,rop1); // d= e % fi(n);
        gmp_printf("%Zd\n",rop);
    }
    mpz_clear(e);
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(p1);
    mpz_clear(q1);
    mpz_clear(rop);
    mpz_clear(rop1);

    return 0;
}
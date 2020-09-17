//用于读取生成数据的某组数据
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
int main() {
    freopen("T31.out","r",stdin);
    freopen("qqqqqq.out","w",stdout);
    int a;
    scanf("%d\n",&a);
 //   printf("%d\n",a);
    printf("1\n");
    for (int i=0;i<a;i++) {
        if (i == 5) {
            for (int j=0;j<65536;j++) {
                int b;
                scanf("%x",&b);
                printf("%04x ",b);
            }
            printf("\n");
        }
        else for (int j=0; j<65536; j++) {
            int b;
            scanf("%x",&b);
        }
    }
    cout<<endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
//数据（随机数）生成器

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    freopen("T31.in","w",stdout);
    srand((int)time(0));
    for (int i=0; i<10; i++) 
    printf("%08x\n",(((rand()%65536)<<16)|(rand()%65536)) );
    return 0;
    fclose(stdout);
}
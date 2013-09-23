#include <cstdio>
#include <cstring>
int gcd(int a,int b){
    return !b ? a : gcd(b,a%b);
}
int main()
{
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        if(n == 1 || m == 1) {
            printf("%d\n",m*n);
        } else {
            printf("%d\n",gcd(m-1,n-1)+1);
        }
    }
    return 0;
}

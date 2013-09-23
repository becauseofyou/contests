#include <cstdio>
#include <cstring>
int a[1010];
int main()
{
    int t,n,k;
    scanf("%d",&t);
    while(t--)
    {
        long long ans;

        scanf("%d%d%lld",&n,&k,&ans);
        long long ret = ans,tmp = ans;
        char str[10];

        for(int i = 0; i < n; i++) {
            scanf("%d",&a[i]);
              }
        scanf("%s",str);ans = 0;
        for(int i = 0; i < n; i++){
            if(str[0] == 'X') ans ^= a[i];
            if(str[0]=='A') ans &= a[i];
            if(str[0] == 'O') ans |= a[i];
        }
        if(str[0] == 'X') if(k%2==0) ans = 0;
        if(str[0] == 'A') ans &= ret;
        if(str[0] == 'O') ans |= ret;
        if(str[0] == 'X') ans ^= ret;
        if(k == 0) printf("%lld\n",ret);
        else         printf("%lld\n",ans);
    }
    return 0;
}

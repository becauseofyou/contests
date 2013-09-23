#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long lld;
const int N = 1000010;
const int mod = 1000000007;
// the sum of [l,r]'s  2^i
// 10101   A[x] = 2^0  + 2^2 + 2^4
//         B[x] = 2^1  + 2^3
lld  A[N<<2] , B[N<<2];
int sum[N<<2], lz[N<<2];
char s[N];
lld two[N];
void pushup(int x,int l,int r)
{
    int m = l + r >> 1;
    sum[x] = sum[x+x] + sum[x+x+1];
    A[x] = (A[x+x] * two[r-m]%mod + A[x+x+1])%mod;
    B[x] = (B[x+x] * two[r-m]%mod + B[x+x+1])%mod;
}
void build(int l,int r,int x)
{
    lz[x] = 0;
    if(l == r) {
        sum[x] = (s[l] == '1');
        A[x] = sum[x]; B[x] = !A[x];
        return ;
    }
    int m = l + r >> 1;
    build(l,m,x+x);
    build(m+1,r,x+x+1);
    pushup(x,l,r);
}
void flip(int x,int l,int r)
{
    std::swap(A[x],B[x]);
    sum[x] = r-l+1 - sum[x];
}
void push(int x,int l,int r)
{
    int m = l + r >> 1;
    if(lz[x]) {
        lz[x+x] ^= 1; lz[x+x+1] ^= 1;
        flip(x+x,l,m); flip(x+x+1,m+1,r);
        lz[x] = 0;
    }
}
void insert(int L,int R,int l,int r,int x)
{
    if(L <= l && r <= R) {
        flip(x,l,r);
        lz[x] ^= 1;
        return ;
    }
    push(x,l,r);
    int m = l + r >> 1;
    if(L <= m) insert(L,R,l,m,x+x);
    if(R > m) insert(L,R,m+1,r,x+x+1);
    pushup(x,l,r);
}
lld Pow(lld a,lld b,lld mod)
{
    lld ans = 1;
    while(b) {
        if(b&1) ans = ans * a % mod;
        a = a*a % mod;  b >>= 1;
    }
    return ans;
}
bool odd;
lld get(int &sum,lld &A,lld &inv)
{
    lld ans = 0;
    if(sum == 0) return 1;
    if(odd) {
        ans++;
        ans = ans + (A-1+mod)*inv;
        if(ans>=mod)ans %= mod;
    }
    else {
        if(sum%2==0) ans++;
        ans += A*inv;
        if(ans>=mod) ans %= mod;
    }
    return ans;
}
int main()
{
    lld inv = Pow(2,mod-2,mod);
    two[0] = 1;
    for(int i = 1; i <= 1000000; i++) {
       two[i] = two[i-1] + two[i-1];
       if(two[i] >= mod) two[i] -= mod;
    }
    scanf("%s",s+1);
    int n = strlen(s+1),m;
    odd = (s[n] == '1');
    build(1,n,1);
    scanf("%d",&m);
    lld ans = get(sum[1],A[1],inv);
    printf("%lld\n",ans);
    for(int i = 0,L,R; i < m; i++) {
        scanf("%d%d",&L,&R);
        if(L > R) std::swap(L,R);
        if(R == n) odd ^= 1;
        insert(L,R,1,n,1);
        printf("%lld\n",get(sum[1],A[1],inv));      
    }
    return 0;
}

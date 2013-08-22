#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstring>
const int N = 100010;
typedef __int64 lld;
lld dp[N];
int head[N] , pnt[N*2] , nxt[N*2];
int E ;
int son[N];
lld sum[N];
void add(int a,int b) {
    pnt[E] = b;
    nxt[E] = head[a];
    head[a] = E++;
}
lld ans;
void dfs(int u,int f) {
    son[u] = 1;
    for(int i = head[u]; i != -1; i = nxt[i]) {
        int v = pnt[i];
        if(v == f) continue;
        dfs(v,u);
        son[u] += son[v];
        dp[u] += dp[v] + son[v];
        sum[u] += dp[v];
        ans -= dp[v]; // 一条链
    }
    int s = son[u];
    for(int i = head[u]; i != -1; i = nxt[i]) {
        int v = pnt[i];
        if(v == f) continue;
        ans -= (lld)son[v] *  (sum[u] - dp[v]); // 不选根
        ans -= (lld)son[v] *  (s - son[v] - 1); // 选根
        s -= son[v];
    }

}
int main() {
    int n,a,b;
    while(scanf("%d",&n)!=EOF) {
        E = 0;
        memset(head,-1,sizeof(head));
        memset(dp,0,sizeof(dp));
        memset(sum,0,sizeof(sum));
        for(int i = 1; i < n; i++) {
            scanf("%d%d",&a,&b);
            add(a,b);
            add(b,a);
        }
        ans = (lld)n*(n-1)*(n-2)/6;
        dfs(1,-1);
        printf("%I64d\n",ans);
        
    }
    return 0;
}
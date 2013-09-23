#include <cstdio>
#include <algorithm>
#include <cstring>
const int N = 100010;
int dp[18][N];
int E;
int nxt[N*2],head[N],pnt[N*2];
void add(int a,int b)
{
    pnt[E] = b;
    nxt[E] = head[a];
    head[a] = E++;
}
int dep[N];
void dfs(int u,int f)
{
    dep[u] = ( f==-1 )? 0 : dep[f] + 1;
    for(int i = head[u]; ~i ; i = nxt[i]) if(pnt[i]-f){
        dp[0][pnt[i]] = u;
        for(int j = 1; j < 18; j++) dp[j][pnt[i]] = dp[j-1][dp[j-1][pnt[i]]];
        dfs(pnt[i],u);
    }
}
int lca(int a,int b)
{
    if(dep[a]<dep[b]) std::swap(a,b); 
    int d = dep[a] - dep[b];
    for(int i = 17; i >= 0; i--) if(d&(1<<i)) a = dp[i][a];
    if(a!=b){
        for(int i = 17; i >= 0; i--) 
            if(dp[i][a] != dp[i][b])
                a = dp[i][a],b = dp[i][b];
        a = dp[0][a];
    }
    return a;
}
int getd(int a,int b)
{
    return dep[a] + dep[b] - 2*dep[lca(a,b)];
}
void gao(int n)
{
    E = 0;
    std::fill(head,head+n,-1);
    for(int i = 1,f; i < n; i++) scanf("%d",&f),add(--f,i),add(i,f);
    if(n <= 1) return ;
    dfs(0,-1);
    int p1 = 0, p2 = 1, len = 1; puts("1");
    for(int i = 2; i < n; i++){
        int len1 = getd(i,p1);
        int len2 = getd(i,p2);
        if(len1 >= len2 && len1 > len) p2 = i, len = len1;
        else if(len2 >= len1 && len2 > len) p1 = i, len = len2;
        printf("%d\n",len);
    }
}
int main()
{
    int t,n;
    scanf("%d",&t);
    while(t--){        scanf("%d",&n);gao(n);}
    return 0;
}

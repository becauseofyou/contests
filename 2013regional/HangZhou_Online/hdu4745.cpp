#include <cstdio>
#include <cstring>
#include <algorithm>
using std::max;
struct _O_O_{
    int n;
    int a[1000];
    int dp[1000][1000];
    int left[1000],right[1000];
    void Init(int n) {
        this->n = n;
        for(int i = 0; i < n; i++) scanf("%d",&a[i]);
    }
    void DP(){
        memset(dp,0,sizeof(dp));
        for(int i = 0; i < n; i++) dp[i][i] = 1;
        for(int i = 2; i <= n; i++) { // length
            for(int j = 0; j+i-1 < n; j++) {
                dp[j][j+i-1] = max(dp[j+1][j+i-1],dp[j][j+i-2]);
                if(a[j] == a[j+i-1]) {
                    dp[j][j+i-1] = max(dp[j][j+i-1],dp[j+1][j+i-2]+2);
                }
            }
        }
    }
    void Solve(){
        DP();
        int ans = dp[0][n-1];
        for(int i = 0; i < n-1; i++) {
            if(dp[0][i] + dp[i+1][n-1] > ans) ans = dp[0][i]+dp[i+1][n-1];
        }
        printf("%d\n",ans);
    }
}ta;
int main()
{
    int t,n;
    while(1)
    {
        scanf("%d",&n); if(!n) break;
        ta.Init(n);     
        ta.Solve();
    }
    return 0;
}

#include <cstdio>
#include <map>
#include <algorithm>
#include <cstring>
using std::map;
const int N = 200010;
int next_pos[N],next[N],a[N];
map<int,int> mex;
bool vis[N];
int main()
{
    int n;
    while(scanf("%d",&n),n)
    {
        long long ans = 0, sum = 0;
        for(int i = 0; i < n; i++)  {
            scanf("%d",&a[i]);
            if(a[i] > n) a[i] = n;
        }
        std::fill(next,next+n+1,n);
        std::fill(vis,vis+n+1,false);
        for(int i = n-1; i >= 0; i--) {
            next_pos[i] = next[a[i]];
            next[a[i]] = i;
        }
        int j = 0;
        for(int i = 0; i < n; i++) {
            vis[a[i]] = true;
            while(vis[j]) j++;
            mex[i] = j;
            sum += j;
        }
//        for(int i = 0; i < n; i++) printf("%d ",mex[i]);puts("");
        ans = sum;
        for(int i = 0; i < n-1; i++){
//            mex.erase(i);
            sum -= mex.begin()->second;
//            printf("tsum=%lld %d\n",sum,mex.begin()->second);
            mex[i] = -1;
            map<int,int> ::iterator it = mex.lower_bound(next_pos[i]-1),it2;
            if(it->second > a[i]) {
   //               printf("i=%d %d\n",i,it->second);
                  if(it->first >= next_pos[i])  {
                      int tmp = it->second;
                      it--;
                      sum -= (next_pos[i] - 1 - it->first) * (tmp-a[i]);
                  }
                  while(it->second > a[i]) {
                      it2 = it;
                      it2--;
                      sum -= (long long)(it->first-it2->first)*(it->second-a[i]);
                      mex.erase(it--);
                  }
                  mex[next_pos[i]-1] = a[i];
            }
//            printf("sum=%lld\n",sum);
            ans += sum;
  //          mex[next_pos[i]-1] = a[i];
            mex.erase(i);
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

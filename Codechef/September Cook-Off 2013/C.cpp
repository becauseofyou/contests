//就是确定一下上下界
//最多能进行多少次游戏，最少能进行多少次游戏
//注意到最终肯定只剩下一堆或者没堆
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long lld;
const int N = 100010;
lld a[N];
int main()
{
    int n;
    lld m,k;
    scanf("%d%lld%lld",&n,&m,&k);
    lld sum = 0,m1=0,m2=0;
    for(int i = 0; i < n; i++) {
      scanf("%lld",&a[i]);
      a[i] = (m-a[i]) / k + 1;
      sum += a[i];
      if(a[i] > m1) m2 = m1,m1 = a[i];
      else if(a[i]>m2) m2 = a[i];
    }
//    for(int i = 0; i < n; i++) printf("%lld ",a[i]);puts("");
//    printf("m1=%lld m2=%lld\n",m1,m2);
    lld upper_bound = (m1 <= sum/2) ? sum/2 : (sum - m1);
    lld lower_bound = upper_bound;
//    printf("upp=%lld\n",upper_bound);
    for(int i = 0; i < n; i++) {
        lld m0 = (a[i] == m1) ? m2 : m1;
        lld s0 = sum - a[i];
        lld left = s0 % 2;
        if(2 * m0 > s0) left = std::max(left,m0-(s0-m0)); //剩下的最大值大于s0的一半,肯定有一些搞不定
        // 除了a[i]以外剩下的还有left次搞不定，得让a[i]来帮忙一下
        if(a[i] <= left) continue;
        lower_bound = std::min(lower_bound,(s0+left)/2);
        //printf("lo=%lld\n",lower_bound);
    }
    printf("%lld\n",(upper_bound-lower_bound+1)%1000000007);
    return 0;
}

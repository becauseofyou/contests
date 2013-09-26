#include <cstdio>
#include <cstring>
#include <algorithm>
using std::pair;
using std::make_pair;
const int mod = 1<<30;
typedef pair<int,int> pii;
const int N = 100010;
struct point 
{
    int x,y,z;
    int id;
    bool operator < (const point& b) const {
       return x==b.x?y==b.y?z<b.z:y<b.y:x<b.x;
    }
}p[N],g[N];
int cmpy(point a,point b)
{
    return a.y==b.y ? a.z<b.z : a.y<b.y;
}
pii operator + (const pii& a,const pii& b)
{
    if(a.first==b.first) {
        int t = a.second + b.second; if(t >= mod) t -= mod;
        return make_pair(a.first,t);
    } else {
        return std::max(a,b);
    }
}
struct BIT
{
   int n;
   pii c[N];
   void init(int n) {
       this->n = n;
   }
   void insert(int x,pii add) {
        for(;x<=n;x+=x&-x) c[x] = c[x] + add;
   }
   pii ask(int x) {
       pii ret=make_pair(0,0);
       for(;x;x-=x&-x) ret = ret + c[x];
       return ret;
   }
   void clear(int x) {
       for(;x<=n;x+=x&-x) c[x]= make_pair(0,0);
   }
}ta;
pii f[N];
//左右区间的x是严格递增的，这时候再提出某段区间的所有数按y排序
//那么y也搞定了，剩下的一维用数状数组即可
//复杂度递归logn层，每层的运算量是nlogn , so n logn^2
void solve(int l,int r)
{
    if(l == r) {    f[p[l].id] = f[p[l].id]+make_pair(1,1); return ; }
    int mid = l + r >> 1;
    solve(l,mid);//先将左区间的问题解决
    for(int i = l; i <= r; i++) g[i] = p[i];
    std::sort(g+l,g+mid+1,cmpy);std::sort(g+mid+1,g+r+1,cmpy);
    int pt = l;
    for(int i = mid+1; i <= r; i++) //利用左区间的答案更新右区间
    {
        while(pt <= mid && g[pt].y <= g[i].y){
            ta.insert(g[pt].z,f[g[pt].id]);
            pt++;
        }
        pii opt=ta.ask(g[i].z);
        f[g[i].id] = f[g[i].id] + make_pair(opt.first+1,opt.second);
    }
    for(int i = l; i <= pt; i++) ta.clear(g[i].z);
    solve(mid+1,r);//右区间自己内部再更新
}
int main()
{
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n); 
        static int num[N];
        for(int i = 1; i <= n; i++) scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z),num[i]=p[i].z,p[i].id=i;
        std::sort(num+1,num+n+1);
        int tot = std::unique(num+1,num+n+1) - num - 1; 
        ta.init(tot);
        for(int i = 1; i <= n; i++) p[i].z = std::lower_bound(num+1,num+tot+1,p[i].z) - num;
        std::sort(p+1,p+n+1); 
        for(int i = 1; i <= n; i++) f[i]=make_pair(0,0);
        solve(1,n);
        pii ret = make_pair(0,0);
        for(int i = 1; i <= n; i++) ret = ret + f[i];
        printf("%d %d\n",ret.first,ret.second);
    }
    return 0;
}

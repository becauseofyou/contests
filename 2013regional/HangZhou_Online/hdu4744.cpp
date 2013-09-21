#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using std::min;
const int N = 510;
const int M = 100010;
const int inf = ~0u>>2;
struct Edge{
    int v,cap,flow,cost,next;
    Edge(){
    }
    Edge(int _v,int _cap,int _cost,int _next) : v(_v),cap(_cap),cost(_cost),next(_next) {
    }
};
struct ZKW{
    int S,T,flow,cost,head[N],biao[N],n,vis[N];
    int E; Edge edge[M];
    void init(int n) {
        this->n = n;
        std::fill(head,head+n,-1);
        E = 0;
    }
    void addedge(int i,int j,int cap,int cost) {
        edge[E] = Edge(j,cap,cost,head[i]);
        head[i] = E++;
        edge[E] = Edge(i,0,-cost,head[j]);
        head[j] = E++;
    }
    int aug(int u,int maxCap) {
        if(u == T) {
            cost += biao[T] * maxCap;
            flow += maxCap;
            return maxCap;
        }
        vis[u] = 1;
        for(int i = head[u]; ~i; i = edge[i].next) {
            Edge &go = edge[i];
            if(go.cap-go.flow>0&&!vis[go.v]&&biao[u]+go.cost==biao[go.v]){
                if(int d = aug(go.v,min(maxCap,go.cap-go.flow))) {
                    go.flow += d;
                    edge[i^1].flow -= d;
                    return d;
                }
            }
        }
        return 0;
    }
    bool update() {
        int d = inf;
        for(int i = 0; i < n; i++) if(vis[i]) {
            for(int j = head[i]; ~j; j = edge[j].next) {
                Edge &go = edge[j];
                if(go.cap-go.flow>0&&!vis[go.v]) 
                    d = min(d,biao[i]+go.cost-biao[go.v]);
            }
        }
        if(d == inf) return false;
        for(int i = 0; i < n; i++) if(!vis[i]) biao[i] += d;
        return true;
    }
    std::pair<int,int> solve(int S,int T) {
        this->S = S; this->T = T;
        for(int i = 0; i < n; i++) biao[i]=0;
        for(int i = 0; i < E; i++) edge[i].flow = 0;
        flow = 0; cost = 0;
        do {
            do {
                memset(vis,0,sizeof(vis)); 
            }while(aug(S,inf));
        } while(update());
        return std::make_pair(flow,cost);
    }
}ta;
struct point 
{
    double x,y,z;
}p[N];
int w[N];
int dis(point a,point b)
{
    return floor(sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z)));
}
int main()
{
    int n;
    while(scanf("%d",&n),n) {
        int sumw = 0;
        for(int i = 0; i < n; i++) {
            scanf("%lf%lf%lf%d",&p[i].x,&p[i].y,&p[i].z,&w[i]);
            sumw += w[i];
        }
        int S = 2*n, T = 2*n+1;
        ta.init(T+1);
        for(int i = 0; i < n; i++) ta.addedge(S,i,w[i],0),ta.addedge(i+n,T,w[i],0);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) if(i!=j){
                ta.addedge(i,j+n,w[i],dis(p[i],p[j]));
            }
        }
        std::pair<int,int> ans = ta.solve(S,T);
        if(ans.first != sumw) {
            puts("-1");
        } else {
            printf("%d\n",ans.second);
        }
    }
    return 0;
}

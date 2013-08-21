/* **********************************************
Author      : wuyiqi
Created Time: 2013-8-22 2:38:51
File Name   : ABBYY_D.cpp
*********************************************** */
//tourist orz
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using std::swap;
#define lson l,m,x<<1
#define rson m+1,r,x<<1|1
const int N = 222222;
const long long inf = (long long)1e16;

int n, q, b;
int fi[N], sl[N], id[N], sr[N];
int xa[N], ya[N], xb[N], yb[N];
int ex[N], ey[N], ed[N], help[N];
int go[N], arrd[N], who[55][N];
long long v[N], f[55][N], next[N], dist[N];
bool good[N], swapx[N], swapy[N] , col[4*N];
int tree[4*N];

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
const char dir[4] = {'U', 'R', 'D', 'L'};
int tot;
void mysort(int l,int r) {
    int i = l , j = r;
    int x = fi[(l+r)>>1];
    int y = sl[(l+r)>>1];
    do {
        while(fi[i] < x || fi[i] == x && sl[i] > y) i++;
        while(fi[j] > x || fi[j] == x && y > sl[j]) j--;
        if(i <= j) {
            swap(fi[i],fi[j]);
            swap(sl[i],sl[j]);
            swap(sr[i],sr[j]);
            swap(id[i],id[j]);
            i++;   j--;
        }
    }while(i <= j);
    if(l < j) mysort(l,j);
    if(i < r) mysort(i,r);
}
void build(int l,int r,int x) {
    col[x] = false;
    tree[x] = 0;
    if(l < r) {
        int m = l + r >> 1;
        build(lson);
        build(rson);
    }
}
void update(int L,int R,int v,int l,int r,int x) {
    if(L <= l && r <= R) {
        col[x] = true;
        tree[x] = v;
        return ;
    }
    if(col[x]) {
        tree[x+x] = tree[x+x+1] = tree[x];
        col[x+x] = col[x+x+1] = true;
        col[x] = false;
    }
    int m = l + r >> 1;
    if(L <= m) update(L,R,v,lson);
    if(R > m) update(L,R,v,rson);
}
int  query(int p,int l,int r,int x) {
     if(l == r || col[x]) return tree[x];
     int m = l + r >> 1;
     if(p <= m) return query(p,lson);
     else return query(p,rson);
}
bool valid(int x,int y) {
    return x >= 0 && x <= b && y >= 0 && y <= b;
}
void _X_X_long_long_gao() {
    for(int i = 1; i <= n+q; i++) {
        go[i] = 0; swapx[i] = swapy[i] = false;
        if(!valid(ex[i],ey[i])) good[i] = false;
        else good[i] = true;
        if(xa[i] > xb[i]) { swap(xa[i],xb[i]);   swapx[i] = true;}
        if(ya[i] > yb[i]) { swap(ya[i],yb[i]);   swapy[i] = true;}
    }
    // up->0

    tot = 0;
    for(int i = 1; i <= n; i++) {
        fi[i-1] = -yb[i];
        sl[i-1] = xa[i];
        sr[i-1] = xb[i];
        id[i-1] = i;
        help[i] = -ya[i];
    }
    tot = n;
    for(int i = 1; i <= n+q; i++) {
        if(ed[i] == 0 && good[i]) {
          //  printf("ddd %d %d\n",ex[i],ey[i]);
            fi[tot] = -ey[i];
            sl[tot] = ~ex[i];//-0还是 0 , ~就很nice
            id[tot] = i;
            tot++;
        }
    }
//    for(int i = 0; i < tot; i++) printf("%d %d\n",sl[i],sr[i]); puts("");
   
    mysort(0,tot-1);
 //    for(int i = 0; i < tot; i++) printf("%d %d %d\n",sl[i],sr[i],id[i]);
    build(0,b,1);
    for(int i = 0; i < tot; i++) {
        if(sl[i] >= 0) {
            update(sl[i],sr[i],id[i],0,b,1);
        } else {
            int num = query(~sl[i],0,b,1);
         //   printf("num=%d\n",num);
            go[id[i]] = num;

            next[id[i]] = fi[i] - help[num];
         //   printf("id=%d : val=%I64d\n",id[i],next[id[i]]);
        }
    }
 //   for(int i = 1; i <= n+q; i++) printf("%d ",go[i]);puts("");
    // down->2

    tot = 0;
    for(int i = 1; i <= n; i++) {
        fi[i-1] = ya[i];
        sl[i-1] = xa[i];
        sr[i-1] = xb[i];
        id[i-1] = i;
        help[i] = yb[i];
    }
    tot = n;
    for(int i = 1; i <= n+q; i++) {
        if(ed[i] == 2 && good[i]) {
            fi[tot] = ey[i];
            sl[tot] = ~ex[i];
            id[tot] = i;
            tot ++;
        }
    }
    mysort(0,tot-1);
    build(0,b,1);
    for(int i = 0; i < tot; i++) {
        if(sl[i] >= 0) {
            update(sl[i],sr[i],id[i],0,b,1);
        } else {
            int num = query(~sl[i],0,b,1);
            go[id[i]] = num;
            next[id[i]] = fi[i] - help[num];
        }
    }
    // right->1
    
    tot = 0;
    for(int i = 1; i <= n; i++) {
        fi[i-1] = -xb[i];
        sl[i-1] = ya[i];
        sr[i-1] = yb[i];
        id[i-1] = i;
        help[i] = -xa[i];
    }
    tot = n;
    for(int i = 1; i <= n+q; i++) {
        if(ed[i] == 1 && good[i]) {
            fi[tot] = -ex[i];
            sl[tot] = ~ey[i];
            id[tot] = i;
            tot ++;
        }
    }
    mysort(0,tot-1);
    build(0,b,1);
    for(int i = 0; i < tot; i++) {
        if(sl[i] >= 0) {
            update(sl[i],sr[i],id[i],0,b,1);
        } else {
            int num = query(~sl[i],0,b,1);
            go[id[i]] = num;
            next[id[i]] = fi[i] - help[num];
        }
    }
    // left->3
    tot = 0;
    for(int i = 1; i <= n; i++) {
        fi[i-1] = xa[i];
        sl[i-1] = ya[i];
        sr[i-1] = yb[i];
        id[i-1] = i;
        help[i] = xb[i];
    }
    tot = n;
    for(int i = 1; i <= n+q; i++) {
        if(ed[i] == 3 && good[i]) {
            fi[tot] = ex[i];
            sl[tot] = ~ey[i];
            id[tot] = i;
            tot ++;
        }
    }
    mysort(0,tot-1);
    build(0,b,1);
    for(int i = 0; i < tot; i++) {
        if(sl[i] >= 0) {
            update(sl[i],sr[i],id[i],0,b,1);
        } else {
            int num = query(~sl[i],0,b,1);
            go[id[i]] = num;
            next[id[i]] = fi[i] - help[num];
        }
    }
    for(int i = 1; i <= n+q; i++) {
        if(go[i] == 0) next[i] = inf;
        if(next[i] < 0) next[i] = 0;
    }
    for(int i = 1; i <= n; i++) {
        if(swapx[i])   swap(xa[i],xb[i]);  
        if(swapy[i])   swap(ya[i],yb[i]); 
    }
}


int main()
{
    scanf("%d%d",&n,&b);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d%d%d",xa+i,ya+i,xb+i,yb+i);
        if(xa[i] < xb[i]) ed[i] = 1; 
        if(xa[i] > xb[i]) ed[i] = 3;
        if(ya[i] > yb[i]) ed[i] = 2;
        if(ya[i] < yb[i]) ed[i] = 0;
        ex[i] = xb[i] + dx[ed[i]];
        ey[i] = yb[i] + dy[ed[i]];
    }
    scanf("%d",&q);
    char ch;
    for(int i = n+1; i <= n+q; i++) {
        scanf("%d %d %c %I64d",ex+i,ey+i,&ch,v+i);
        for(int j = 0; j < 4; j++) if(dir[j] == ch) ed[i] = j;
    }
    _X_X_long_long_gao();
  //  for(int i = 1; i <= n+q; i++) printf("next[%d]=%I64d\n",i,next[i]);
    for(int i = 1; i <= n+q; i++) {
        if(go[i] == 0) dist[i] = inf;
        else dist[i] = abs(ex[i]-xb[go[i]]) + abs(ey[i]-yb[go[i]]);
    }
    go[0] = 0;    dist[0] = inf;    next[0] = inf;
    for(int i = 0; i <= n; i++) {
        who[0][i] = go[i];
        f[0][i] = dist[i] + 1;
    }
    for(int j = 1; j <= 50; j++) {
        for(int i = 0; i <= n; i++)  {
            who[j][i] = who[j-1][who[j-1][i]]; 
            f[j][i] = f[j-1][i] + f[j-1][who[j-1][i]];
            if(f[j][i] > inf) f[j][i] = inf;
        }
    }
   // printf("%I64d\n",dist[4]);
    long long ansx , ansy;
    for(int i = n+1; i <= n+q; i++) {
        if(v[i] <= dist[i]) {
            ansx = ex[i];
            ansy = ey[i];
            if(v[i] <= next[i]) {
                ansx += v[i] * dx[ed[i]] ;
                ansy += v[i] * dy[ed[i]] ;
                if(ansx < 0) ansx = 0;
                if(ansx > b) ansx = b;
                if(ansy < 0) ansy = 0;
                if(ansy > b) ansy = b;
                printf("%I64d %I64d\n",ansx,ansy);
                continue ;
            }
            v[i] -= next[i];
            ansx += next[i] * dx[ed[i]];
            ansy += next[i] * dy[ed[i]];
            ansx += dx[ed[go[i]]] * v[i];
            ansy += dy[ed[go[i]]] * v[i];
            printf("%I64d %I64d\n",ansx,ansy);
            continue;
        } 
        v[i] -= dist[i];
        int now = go[i];
        for(int j = 50; j >= 0; j--) {
            if(f[j][now] <= v[i]) {
                v[i] -= f[j][now];
                now = who[j][now];
            }
        }
        if(go[now] == 0 || v[i] <= next[now] + 1) {
            ansx = xb[now] + v[i] * dx[ed[now]];
            ansy = yb[now] + v[i] * dy[ed[now]];
            if(ansx < 0) ansx = 0;
            if(ansx > b) ansx = b;
            if(ansy < 0) ansy = 0;
            if(ansy > b) ansy = b;
            printf("%I64d %I64d\n",ansx,ansy);
            continue;
        }
        v[i] -= next[now] + 1;
        ansx = xb[now] + dx[ed[now]] * (next[now]+1);
        ansy = yb[now] + dy[ed[now]] * (next[now]+1);
        ansx += v[i] * dx[ed[go[now]]];
        ansy += v[i] * dy[ed[go[now]]];
        printf("%I64d %I64d\n",ansx,ansy);
    }
    return 0;
}


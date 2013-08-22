/* **********************************************
Author      : wuyiqi
Created Time: 2013-8-20 9:45:56
File Name   : ABBYY_B.cpp
*********************************************** */

#include <cstdio>
#include <algorithm>
const int N = 333333;
int a[N];
int pos[N];
int sum[N<<2];
void up(int l,int r,int rt) {
    int m = l + r >> 1;
    sum[rt] = sum[rt<<1] + sum[rt<<1|1] ;
    if(pos[m] < pos[m+1]) sum[rt] --;
}
void build(int l,int r,int rt) {
    if(l == r) {
        sum[rt] = 1;
        return ;
    }
    int m = l + r >> 1;
    build(l,m,rt*2);
    build(m+1,r,rt*2+1);
    up(l,r,rt);
}
void update(int p,int val,int l,int r,int rt) {
    if(l == r) {
        pos[l] = val;
        sum[rt] = 1;
        return ;
    }
    int m = l + r >> 1;
    if(p <= m) update(p,val,l,m,rt*2);
    else update(p,val,m+1,r,rt*2+1);
    up(l,r,rt);
}
int query(int L,int R,int l,int r,int rt) {
    if(L <= l && r <= R) {
        return sum[rt];
    }
    int m = l + r >> 1;
    int ret = 0;
    if(L <= m) ret += query(L,R,l,m,rt*2);
    if(R > m) ret += query(L,R,m+1,r,rt*2+1);
    if(L<=m && R>m && pos[m]<pos[m+1]) ret--;
    return ret;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        pos[a[i]] = i;
    }
    build(1,n,1);
    int q;
    scanf("%d",&q);
    while(q--)
    {
        int op , x , y;
        scanf("%d%d%d",&op,&x,&y);
        if(op == 1) {
            printf("%d\n",query(x,y,1,n,1));
        } else{
        //    printf("first  %d %d\n",a[x],y);
            update(a[x],y,1,n,1);
       //     printf("next %d %d\n",a[y],x);
            update(a[y],x,1,n,1);
            std::swap(a[x],a[y]);
        }
    }
    return 0;
}

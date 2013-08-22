/* **********************************************
Author      : wuyiqi
Created Time: 2013-8-20 9:13:59
File Name   : ABBYY_A.cpp
*********************************************** */

#include <cstdio>
#include <map>
const int N = 333333;
typedef long long lld;
using std::map;
int a[N];
long long sum[N];
int main()
{
    map<int,int> last,first;
    int n;
    scanf("%d",&n);
    sum[0] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        if(first.find(a[i])==first.end()){
            first[a[i]] = i;
        }
        last[a[i]] = i;
        if(a[i]>=0) sum[i] = sum[i-1] + a[i];
        else sum[i] = sum[i-1];
    }
    long long ans = -1000000000000000000LL;
    int st , ed;
    for(map<int,int>::iterator it = first.begin(); it != first.end(); it++) {
        int end = last[it->first];
        if(end == it->second) continue;
        long long tmp = sum[end-1]-sum[it->second];
        if(tmp + a[end] + a[it->second] > ans) {
            ans = tmp + a[end] + a[it->second];
            st = it->second;
            ed = end;
        }
    }
  //  printf("%d %d\n",st,ed);
    int del = st-1 + n-ed;
    for(int i = st+1; i < ed; i++) if(a[i]<0) del++;
    printf("%I64d %d\n",ans,del);
    for(int i = 1; i < st; i++) printf("%d ",i);
    for(int i = st+1; i < ed; i++) if(a[i]<0) printf("%d ",i);
    for(int i = ed+1; i <= n; i++) printf("%d ",i);
    puts("");
    return 0;
}

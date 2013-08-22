/* **********************************************
Author      : wuyiqi
Created Time: 2013-8-20 10:30:16
File Name   : ABBYY_C.cpp
*********************************************** */
#include <cstdio>
#include <algorithm>
using namespace std;
const int mod = 1000000;
int cnt[10][mod+10];
int dec[10][mod+10];
int val[mod+10];
int main() {
    for(int i = 1; i <= mod; i++) {
        int num = i;
        int mx = 0;
        for(;num;num/=10) mx = max(mx,num%10);
        val[i] = mx;
    }
    long long n;
    scanf("%I64d",&n);
    cnt[0][0] = 0;
    dec[0][0] = 0;
    for(int has = 0; has < 10; has++) { 
        for(int i = 0; i <= mod;i++) {
            if(has == 0 && i == 0) continue;
            int nxt = i - max(has,val[i]);
            if(nxt < 0) {
                cnt[has][i] = 1;
                dec[has][i] = nxt;
            } else {
                cnt[has][i] = cnt[has][nxt] + 1;
                dec[has][i] = dec[has][nxt];
            }
        }
    }
    long long ans = 0;
    int part1 = n / mod;
    int part2 = n % mod;
    int cn = 0;
 /*   while(n>0) {
        int tot=0;
        int tmp = n;
        int  mx = 0;
        while(tmp) {
            if(tmp%10 > mx) mx = tmp%10;
            tmp/=10;
        }
        cn++;
        n -= mx;
    }
    printf("cnt=%d\n",cn);*/
//    printf("%d %d %d %d\n",part1,part2,dec[1][0],cnt[1][0]);
    while(part1 >= 0) {
        int has = val[part1];
        ans += cnt[has][part2];
        part2 = mod + dec[has][part2];
        part1--;
    }
    printf("%I64d\n",ans);
    return 0;
}
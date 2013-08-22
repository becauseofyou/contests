/* **********************************************
Author      : wuyiqi
Created Time: 2013-8-21 6:07:09
File Name   : ABBYY_C.cpp
*********************************************** */

#include <cstdio>
#include <map>
using std::map;
using std::pair;
using std::make_pair;
typedef long long lld;
typedef pair<lld,int> pp;
map<pp,pp> mp;

/*
 since we using gready to subtract ...
 we can use dp.
 dp state : 
 dp[i][j] represents that
 the maximum digit of the previous digits is i,
 the number is j ,
 the meaning of the state is the minimum number of time needed 
 to make j become a non positive integer.
 Suppose we've got a number "NOW",
 we also need to know what is the negative number "decr" that j will become
 and then subtract the absolute value |decr| from NOW.
 every time , now's highest digit will decrease by 1 ,and this is our state transition

 */
pp gao(lld val,int mx) {
  // printf("val=%I64d\n",val);
   if(val == 0) return make_pair(0,0);
   if(val < 10) {
       pp ans = make_pair(1,0);
       if(val < mx) ans.second = val - mx;
       return ans;
   }
   pp now = make_pair(val,mx);
   if(mp.find(now) != mp.end()) return mp[now];
   lld lim = 1;
   while(lim<=val/10) lim*=10;
  // printf("lim=%I64d\n",lim);
   pp ans = make_pair(0,0);
   while(true) {
        int newmx = mx;
        int dig = val / lim;
        if(dig > newmx) newmx = dig;
        pp tmp = gao(val%lim,newmx);
        ans.first += tmp.first;
        val -= val%lim;
//           printf("val=%I64d %d\n",val,newmx);
        if(tmp.second < 0) val += tmp.second;
        else if(tmp.second == 0) {
            val -= newmx ;
            if(newmx > 0) ans.first ++;
        }
        if(dig == 0) break;
   }
   ans.second = val;
   mp[now]  =  ans;
   return ans;
}
int main()
{
    mp.clear();
    lld n;
    scanf("%I64d",&n);
    printf("%I64d\n",gao(n,0).first);
    return 0;
}

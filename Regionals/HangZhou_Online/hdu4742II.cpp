#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

/*
  Author: Master_Miu(Xiamen No.1 Middle School --> THU)
 */

struct triple
{
  int a,b,c;
  triple() {}
  triple(int _a,int _b,int _c) : a(_a),b(_b),c(_c) {}
  bool operator < (const triple &o) const 
  {
    return a < o.a || (a == o.a && (b < o.b || (b == o.b && c < o.c)));
  }
};

const int MAXN = 101000;
triple d[MAXN],tmp[MAXN];

const int bmod = (1 << 30) - 1;

typedef pair<int,int> ans_t;
ans_t merge(const ans_t &a,const ans_t &b)
{
  return a.first == b.first ? ans_t(a.first,(a.second + b.second) & bmod) : max(a,b);
}

struct qmax
{
  ans_t c[MAXN];
  int len;
  void reset()
  {
    fill(c + 1,c + len + 1,ans_t(0,0));
  }
  void update(int pos,const ans_t &v)
  {
    for(int x = pos + 1; x <= len; x += x & (-x))
      c[x] = merge(c[x],v);
  }
  void undo(int pos)
  {
    for(int x = pos + 1; x <= len; x += x & (-x))
      c[x] = ans_t(0,0);
  }
  ans_t getsum(int pos)
  {
    ans_t res(0,0);
    for(int x = pos + 1; x > 0; x -= x & (-x))
      res = merge(res,c[x]);
    return res;
  }
} q;

ans_t f[MAXN];
void solve(int l,int r)
{
  if (l + 1 != r)
    {
      int mid = (l + r) >> 1;
      solve(l,mid);

      copy(d + l,d + r,tmp + l);
      sort(tmp + l,tmp + r);
      for(int i = l; i < r; i++)
    {
      if (tmp[i].c < mid) 
        {
          q.update(tmp[i].b,f[tmp[i].c]);
        }
      else
        {
          f[tmp[i].c] = merge(f[tmp[i].c],q.getsum(tmp[i].b));
         }
    }

      for(int i = l; i < r; i++)
    {
      if (tmp[i].c < mid) 
        {
          q.undo(tmp[i].b);
        }
    }


      solve(mid,r);
    }
  else ++f[l].first;
}

int main()
{
  int t;
  scanf("%d",&t);
  while(t--)
    {
      int n;
      scanf("%d",&n);
      int x,y,z;
      for(int i = 0; i < n; i++) 
    {
      scanf("%d%d%d",&x,&y,&z);
      d[i] = triple(x,y,z);
    }
      sort(d,d + n);
      for(int i = 0; i < n; i++)
    {
      d[i] = triple(d[i].b,d[i].c,i);
    }
      sort(d,d + n);
      for(int i = 0; i < n; i++)
    {
      d[i] = triple(d[i].b,d[i].c,i);
    }

      q.len = n;
      q.reset();
      fill(f,f + n,ans_t(0,1));
      solve(0,n);

      ans_t res(0,0);
      for(int i = 0; i < n; i++) res = merge(res,f[i]);
      printf("%d %d\n",res.first,res.second);
    }
  return 0;
}

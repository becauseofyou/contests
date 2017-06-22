#include <bits/stdc++.h>
using namespace std;

const int  N = 4000 + 10;
int a[N], last[N], now[N], l[N], r[N];
int stk[N];
int n, m, k;
struct Data {
    int height, other, id;
    bool operator < (const Data&cmp) const {
        return height < cmp.height;
    }
};
struct Node {
    Data data[N];
    int tot;
    bool f[N];
    void init() {
        tot = 0;
    }
    void baseSort() {
        sort(data, data + tot);
    }
    void add(int num, int end) {
        data[tot].height = num;
        data[tot++].other = end;
    }
}L[N], R[N];

int sum[N], g[N], h[N];
bool mp[N][N];
long long sum2[N];

long long calc (int preH, int nowH, int l, int r) {
    int len = r - l + 1;
    int tmp = -1;
    if(k > len)
        tmp = k / len + (k % len != 0) - 1;
    if(preH < tmp)  preH = tmp;
    if(preH >= nowH) return 0;
    int delta = nowH - preH;
    long long ret = 0;
    ret += (1LL * (len * len + len) * delta - 1LL*(2 * len + 1) * (sum[nowH] - sum[preH]) + sum2[nowH]-sum2[preH]) / 2;
    ret += 1LL * (len + 1) * (h[nowH] - h[preH]) - (g[nowH] - g[preH]) ;
    return ret;
}
bool read (int &x) {
    int c = getchar (); int sign = 1;
    while (~c && c < '0' || c > '9') { if (c == '-') sign = -1; c = getchar (); }
    for (x = 0; ~c && '0' <= c && c <= '9'; c = getchar ()) x = x * 10 + c - '0';
    x *= sign;
    return ~c;
}
int main() {
     freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    while( scanf("%d%d%d", &n, &m, &k)==3) {
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + k / i;
            sum2[i] = sum2[i - 1] + 1LL*(k / i) * (k / i);
            g[i] = g[i - 1] +((k % i) == 0 ? k / i : 0) ;
            h[i] = h[i - 1] + ((k % i) == 0);
        } 
        long long ret = 0;
        memset(last, 0, sizeof(last));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                L[j].init(); R[j].init();
                read(a[j]);
                if(a[j]) {
                    now[j] = 0;
                } else {
                    now[j] = last[j] + 1;
                }
            }
            for (int j = 0; j < m; j++) {
                l[j] = j;
                while(l[j] > 0 && now[l[j] - 1] >= now[j]) {
                    l[j] = l[l[j] - 1];
                }
            }
            for (int j = m - 1; j >= 0; j--) {
                r[j] = j;
                while (r[j] < m - 1 && now[r[j] + 1] >= now[j]) {
                    r[j] = r[r[j] + 1];
                }
            }
            int tot = 0;
            for (int j = 0; j < m; j++) {
                if(now[j] == 0) continue;
                if(mp[l[j]][r[j]]) continue;
                mp[l[j]][r[j]] = true;
                L[l[j]].add(now[j], r[j]);
                R[r[j]].add(now[j], l[j]);
            }
            for (int j = 0; j < m; j++) {
                L[j].baseSort();
                R[j].baseSort();
                for (int x = 0; x < L[j].tot; x++) {
                    int h = L[j].data[x].height;
                    int rig = L[j].data[x].other;
                    int pre = 0;
                    if(tot) pre = stk[tot - 1];
                    ret += calc(pre, h, j, rig);
                    stk[tot++] = h;
                }
                for(int x = 0; x < R[j].tot; x++) {
                    tot--;
                }
            }
            for(int j = 0; j < m; j++) {
                mp[l[j]][r[j]] = false;
            }
            memcpy (last, now, sizeof(now));
        }
        printf("%lld\n", ret);
    }
    return 0;
}

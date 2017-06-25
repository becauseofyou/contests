#include <bits/stdc++.h>
using namespace std;

const int N = 2510;
int n, m;
vector <int> edge[N];
int f[3][N][N];
int g[3][3][N];
int size[N];

void dfs (int u, int fa) {
    f[0][u][0] = 1;
    f[1][u][1] = 1;
    f[2][u][0] = 1;
    int sz = 1;
    for (int v : edge[u]) if (v != fa){
        dfs (v);
        for (int color_u = 0; color_u < 3; color_u++) {
            for (int pre = 0; pre <= sz; pre++) {
                for (int now = 0; now <= size[v]; now++) {
                    for (int color_v = 0; color_v < 3; color_v++) {
                    }
                }
            }
        }
        sz += size[v];
    }
    size[u] = sz;
}
int main () {
    scanf("%d%d", &n, &m);
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        edge[a].push_back(b);
        edge[a].push_back(a);
    }
    memset (f, -1, sizeof(f));
    dfs (1);
    return 0;
}

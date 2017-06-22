#include <bits/stdc++.h>
using namespace std;

int a[100][100];
int main() {
    int n, m, k;
    freopen("data.in", "r", stdin);
    freopen("brute.out","w", stdout);
    while(scanf("%d%d%d", &n, &m, &k) == 3 ) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        int cnt = 0;
        for(int x1 = 0; x1 < n; x1++) {
            for(int y1 = 0; y1 < m; y1++) {
                int sum = 0;
                for(int x2 = x1; x2 < n; x2++) {
                    for(int y2 = y1; y2 < m; y2++) {
                        sum = 0;
                        for(int i = x1; i <= x2; i++) {
                            for(int j = y1; j <= y2; j++) {
                                sum += a[i][j] == 0;
                            }
                        }
                        if(sum == (y2 - y1 + 1) * (x2 - x1 + 1) && sum >= k) {
                           // printf("%d %d %d %d\n", x1, y1, x2, y2);
                            cnt++;
                        }
                    }
                }
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}

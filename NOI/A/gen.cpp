#include <bits/stdc++.h>
using namespace std;

int main () {
    freopen("data.in", "w", stdout);
    srand(time(NULL));
    int n, m, k;
    for(int ca = 0; ca < 50; ca++) {
        n = 3; m = 3;  k = rand() % 3 + 1;
        printf("%d %d %d\n", n, m, k);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(j) printf(" ");
                printf("%d", rand() % 2);
            }
            puts("");
        }
    }
    return 0;
}

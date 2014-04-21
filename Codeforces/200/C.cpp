#include <cstdio>
#include <iostream>
template<typename T>
T _abs(T x) {
    return x < 0 ? -x : x;
}
const int MAX_N = 100010;
long long position[MAX_N], aim[MAX_N];
int n, m;
long long minimum(long long now, long long left, long long right) {
    if(now <= left || now >= right) {
        return right - left + (now <= left ? left - now : now - right); 
    } else {
        return right - left + std::min(right - now, now - left);
    }
}
bool  check(long long time) {
    int nowaim = 0;
    for(int i = 0; i < n; i++) {
        long long posi = position[i];
        long long ti = time;
        if(_abs(aim[nowaim] - posi) > ti){
            continue;
        }
        int l = nowaim, r = m - 1, best = -1;
        while(l <= r) {
            int mid = l + r >> 1;
            if(minimum(posi, aim[nowaim], aim[mid]) <= ti) {
                best = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        nowaim = best + 1;
        if(nowaim == m) {
            break;
        }
    }
    return nowaim == m ;
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i = 0; i < n; i++) {
        std::cin>>position[i];
    }
    for(int i = 0; i < m; i++) {
        std::cin>>aim[i];
    }
    long long l = 0, r = 10000000000000LL;
    long long best = -1;
    while(l <= r) {
        long long mid = l + r >> 1;
        if(check(mid)) {
            best = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    std::cout<<best<<std::endl;
    return 0;
}


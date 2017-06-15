#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct DQ {
    int f, r;
    int index[N];
    int value[N];
    void init() {
        f = 0;
        r = -1;
    }
    void push(int _index, int _value) {
        while(f <= r && _value >= value[r]) {
            r--;
        }
        r++;
        index[r] = _index;
        value[r] = _value;
    }
    void pop() {
        f++;
    }
    void pop(int _index) {
        while(f <= r && index[f] <= _index) {
            f++;
        }
    }
    int top() {
        return value[f];
    }
    bool empty() {
        return f <= r;
    }
}dq[5];

long long SumMax(int m) {
    long long ret = 0;
    for(int i = 0; i < m; i++) {
        ret += dq[i].top();
    }
    return ret;
}

int main() {
    int n, m, k, num;
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 0; i < m; i++) dq[i].init();
    int pointer = 0;
    int ret[5]={0}, maxLength = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &num);
            dq[j].push(i, num);
        }
        while(SumMax(m) > k) {
            for(int i = 0; i < m; i++) {
                dq[i].pop(pointer);
            }
            pointer++;
        }
        if(i - pointer + 1 > maxLength)
        {
            maxLength = i - pointer + 1;
            for(int i = 0; i < m; i++) {
                ret[i] = dq[i].top();
            }
        }
    }
    for(int i = 0; i < m; i++) printf("%d ", ret[i]);
    return 0;
}

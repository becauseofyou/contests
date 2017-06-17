/*
 *
 ���⣺
 ����a b k t
 ��ʾ������A Bһ��ʼ�����ֱ�Ϊa b��t����ÿһ�ֿ���ѡ��-k -> k֮��������ۼ�
 ����ж�����ѡ��ʹ�����ĺ�sum(A) > sum(B)
 
 ���������ݷ�Χ�����󣬺���Ȼ������Ҫdp��Ȼ�����dpת�ƹ��̵��Ż��ˡ�
 f[t][i]��ʾ������t�� ��Ϊi�ķ�����
 f[t][i] =  sum(f[t - 1][i - k] -> f[t - 1][i + k])
 ���Ե�ǰ�׶ε�һ��״̬����ǰ��״̬��һ����������ĺ͵����ģ���˿������뵽ÿ�δ����ǰ׺���������ֵ
 ת�Ƶĸ��ӶȾͱ����O(1)
 ���Ӷ�Ϊ O(t * k )
 */
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
int f[200010], sum[200010];

void Add(int &x, int y) {
    x += y;
    if(x >= MOD) {
        x -= MOD;
    }
}

int lim;
inline int Sum(int id) {
    if (id < 0) {
        return 0;
    }
    if(id > lim) {
        return sum[lim];
    }
    return sum[id];
}

int main() {
    int a, b, k, t;
    cin >> a >> b >> k >> t;
    memset(f, 0, sizeof(f));
    lim = 2 * k * t;
    f[k*t] = 1;
    for (int i = 1; i <= lim; i++) {
        sum[i] = sum[i - 1];
        Add(sum[i], f[i]);
    }
    for (int i = 0; i < t; i++) {
        for (int s = lim; s >= 0; s--)  {
            int l = s - k, r = s + k;
            f[s] = ( (Sum(r) - Sum(l - 1) ) % MOD + MOD) % MOD;
        }
        memset(sum, 0, sizeof(sum));
        sum[0] = f[0];
        for (int j = 1; j <= lim; j++) {
            sum[j] = sum[j - 1];
            Add(sum[j], f[j]);
        }
    }
    memset(sum, 0, sizeof(sum));
    for (int i = 0; i <= lim; i++) {
        sum[i] = f[i];
        if (i) {
            Add(sum[i], sum[i - 1]);
        }
    }
    int ret = 0;
    for (int i = 0; i <= lim; i++) {
        int id = i + (a - b) - 1;
        Add(ret, 1LL * f[i] * Sum(i + (a - b) - 1) % MOD);
    }
    /*
    int tmp = 0;
    for (int i = 0; i <= lim; i++) {
        for (int j = 0; j <= lim; j++) if(a + i > b + j){
            tmp += f[i] * f[j];
        }
    }
    */
    printf("%d\n" , ret);
    return 0;
}

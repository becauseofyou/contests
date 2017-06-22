/*
 ��ͬ���ȵ��ַ������ֵ������� ������һ��
 Ԥ�����ʱ��ö��ģʽ����ÿһ��λ�ã�ɾ��������ǰ׺ ��׺��Ӧ���ֵ����еĽڵ�
 ���һ��pair <A B> ��ѯ�ʵ�ʱ��ö��ÿһ��λ��ɾ���� ����ͬ�ķ������ֵ����в���ǰ��׺
 ���ֵ����еĽڵ�C D��������pair���ֹ����ͱ�ʾģʽ������һ�����������λ���ⶼ�뵱ǰ����ͬ��

 �����и�С�ӣ�����ģʽ���м�����ȫ��ȵģ����н���һ��λ�ò���ȵģ�����Ҫ��¼һ��ÿһ��pair
 �ǿ���ͨ��ɾ����Щ�ַ�������
 ���Ӷ�Ϊ����ַ������� len * log(len)
 */
#include <bits/stdc++.h>
using namespace std;

#define Clr(a, v) memset(a, v, sizeof(a))

const int N = 600010;
int n, m;
int ch[N][3];
int value[N];
int rootPrefix[N];
int rootSuffix[N];
int sz;

int Insert(int &root, char *s) {
    if(root == -1) {
        root = ++sz;
    }
    int p = root;
    for(; *s; s++) {
        int c = *s - 'a';
        if(!ch[p][c]) {
            ch[p][c] = ++sz;
        }
        p = ch[p][c];
    }
    value[p] = 1;
    return p;
}

bool Find(int root, char *s, vector<int> &v) {
    int p = root;
    for(; *s; s++) {
        v.emplace_back(p);
        if(p == -1) continue;
        int c = *s - 'a';
        if(!ch[p][c]) {
            p = -1;
            continue;
        }
        p = ch[p][c];
    }
    v.emplace_back(p);
    if(p == -1 || !value[p]) return false;
    return true;
}

char s[N], t[N];
map<pair<int, int>, int> mp;
vector<string> str;

int main() {
   // freopen("C.in", "r", stdin);
    scanf("%d%d", &n, &m);
    Clr(rootPrefix, -1);
    Clr(rootSuffix, -1);

    for(int i = 0; i < n; i++) {
        scanf("%s", s);
        str.push_back(s);
        strcpy(t, s);
        int len = strlen(s);
        reverse(t, t + len);
        Insert(rootPrefix[len], s);
        Insert(rootSuffix[len], t);
        vector<int> v0, v1;
        Find(rootPrefix[len], s, v0);
        Find(rootSuffix[len], t, v1);
        for(int j = 0; j < len; j++) {
            pair<int, int> pp = make_pair(v0[j], v1[len - 1 - j]);
            if(mp.count(pp) ) {
                mp[pp] |= 1 << (s[j]-'a') ;
            } else {
                mp[pp] = 1 << (s[j]-'a') ;
            }
        }
    }
    for(int i = 0; i < m; i++) {
        scanf("%s", s);
        strcpy(t, s);
        int len = strlen(s);
        reverse(t, t + len);
        vector<int> v0, v1;
        Find(rootPrefix[len], s, v0);
        Find(rootSuffix[len], t, v1);
        bool flag = false;
        for(int j = 0; j < len; j++) {
            pair<int, int> pp = make_pair(v0[j], v1[len - 1 - j]);
            if(mp.find(pp) != mp.end() && (mp[pp] ^ (1 << (s[j]-'a')) )) {
                flag = true;
                break;
            }
        }
        if(flag) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}

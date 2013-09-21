#include <cstdio>
#include <cstring>
#include <algorithm>
const int mod = 1<<30;
using std::max;
struct data
{
    int first,second;
    data() {

    }
    data(int _first,int _second):first(_first),second(_second){
    }
    bool operator < (const data& cmp) const {
        return first < cmp.first;
    }
};
data operator + (const data& a, const data& b) 
{
    if(a.first == b.first)  {
         int tmp = a.second + b.second;
         if(tmp >= mod) tmp -= mod;
         return data(a.first,a.second+b.second);
    }
    return max(a,b);
}
int get_val()
{
    int ret(0),sign(1);
    char c;
    while((c=getchar())==' '||c=='\n'||c=='\r');if(c=='-')  sign=-1;
    else    ret=c-'0';
    while((c=getchar())!=' '&&c!='\n'&&c!='\r') if(c=='-')  sign=-1;
    else    ret=ret*10+c-'0';
    return ret*sign;
}
struct node
{
    node* c[2],*fa;
    data kk,val;
    int z;
    void setc(int d,node* s) {
        c[d] = s;
        s->fa = this;
    }
    bool d() {
        return fa->c[1] == this;
    }
    void up() {
        kk = c[0]->kk + c[1]->kk;
        kk = kk + val;
    }
}NODE[940000],*null=NODE;
int top;
struct Tree
{
    node *root;
    void rot(node* x,int f) {
        node *y = x->fa;
        y->setc(!f,x->c[f]);
        x->fa = y->fa;
        if(y->fa != null) y->fa->c[y->d()] = x;
        x->setc(f,y);
        y->up();
    }
    void splay(node* x,node *goal) {
        while(x->fa!=goal) {
            if(x->fa->fa==goal) rot(x,!x->d());
            else {
                bool f = x->fa->d();
                x->d() == f ? rot(x->fa,!f) : rot(x,f);
                rot(x,!f);
            }
        }
        x->up();
        if(goal == null) root = x;
    }
    node* new_node(int z) {
        node* tmp = &NODE[++top];
        tmp->fa = tmp->c[0] = tmp->c[1] = null;
        tmp->z = z;
        return tmp;
    }
    void init() {
        root = null;
    }
    void insert(node* &x,node *y) {
        if(x == null) {
            x = y; return ;
        }
        if(y->z <= x->z) {
            insert(x->c[0],y);
            x->c[0]->fa = x;
        } else {
            insert(x->c[1],y);
            x->c[1]->fa = x;
        }
        x->up();
     }
    void insert(int z,data t) {
         node* tmp = new_node(z);
         tmp->kk = tmp->val = t;
         insert(root,tmp);
         splay(tmp,null);
    }
    node* find(node *x,int z) {
        if(x==null) return x;
        if(x->z <= z) {
            node* tmp = find(x->c[1],z);
            return tmp == null ? x : tmp;
        } else 
            return find(x->c[0],z);
    }
    node* find_max() {
        node* x = root, *tmp = null;
        while(x != null) tmp=x,x = x->c[1];
        return tmp;
    }
    data query(int z) {
        node* tmp = find(root,z);
        if(tmp == null) {
            node* t = find_max();
            if(t!=null) splay(t,null);
            return data(0,0);
        }
        splay(tmp,null);
        return tmp->c[0]->kk+ tmp->val;
    }
};
void init()
{
    top = 0;
    null->kk = null->val = data(0,0);
    null->c[0] = null->c[1] = null->fa = NULL;
}
const int N = 100010;
struct BIT
{
    int n;
    Tree spt[N];
    void build(int n) {
        this->n = n;
        for(int i = 1; i <= n; i++) spt[i].init();
    }
    void update(int y,int z,data in) {
        for(;y<=n;y+=y&-y) spt[y].insert(z,in);
    }
    data query(int y,int z) {
        data ret = spt[y].query(z);
        for(y-=y&-y;y;y-=y&-y) ret = ret + spt[y].query(z);
        return ret;
    }
}bt;
struct Point 
{
    int x,y,z;
    void in() {
        x = get_val(); y = get_val(); z = get_val();
    }
    bool operator < (const Point& cmp) const {
        return x < cmp.x || (x==cmp.x && y < cmp.y) ||(x==cmp.x&&y==cmp.y
                &&z < cmp.z);
    }
}p[N];
int num[N];
int main()
{
    int t,n;
    scanf("%d",&t);
    while(t--){
        init();
        scanf("%d",&n);
        int tot = 0;
 //       for(int i = 0; i < n; i++) p[i].x = i,p[i].y=i,p[i].z=i,num[++tot]=p[i].y;
        for(int i = 0; i < n; i++)  p[i].in(),num[++tot]=p[i].y;
        std::sort(p,p+n);
        std::sort(num+1,num+tot+1);
        tot = std::unique(num+1,num+tot+1) - num - 1;
        bt.build(tot);
        data ret = data(0,0);
        for(int i = 0; i < n; i++) 
        {
            int y = std::lower_bound(num+1,num+1+tot,p[i].y) - num;
            int z = p[i].z;
           // printf("y=%d z=%d\n",y,z);
            data tmp = bt.query(y,z);
            tmp.first ++; tmp.second = max(tmp.second,1);
            if(tmp.first==1) tmp.second = 1;
            ret = ret + tmp;
            //printf("first=%d second=%d\n",tmp.first,tmp.second);
            bt.update(y,z,tmp);
        }
        printf("%d %d\n",ret.first,ret.second);
    }
    return 0;
}

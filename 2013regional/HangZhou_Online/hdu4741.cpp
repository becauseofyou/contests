#include <cstdio>
#include <cmath>
struct Pt {
    double x,y,z;
    Pt() {
    }
    Pt(double _x,double _y,double _z) {
        x = _x; y = _y; z = _z;
    }
    void in() {
        scanf("%lf%lf%lf",&x,&y,&z);
    }
    void show() {
        printf("xyz=%.6f %.6f %.6f\n",x,y,z);
    }
    double length(){
        return sqrt(x*x + y*y + z*z);
    }
    Pt operator - (const Pt& cmp) const {
        return Pt(x-cmp.x,y-cmp.y,z-cmp.z);
    }
    Pt operator + (const Pt& cmp) const {
        return Pt(x+cmp.x,y+cmp.y,z+cmp.z);
    }
    Pt operator * (const double& k) const {
        return Pt(x*k , y*k, z*k);
    }
};
struct line {
    Pt a,b;
    void in() {
        a.in(); b.in();
    }
};
struct plane {
    Pt a,b,c;
    plane() {
    }
    plane(Pt _a,Pt _b,Pt _c) {
        a = _a; b = _b; c = _c;
    }
};
Pt Cross(Pt a,Pt b) // 三维叉积，返回法向量
{
    Pt tmp;
    tmp.x = a.y * b.z - a.z * b.y;
    tmp.y = a.z * b.x - a.x * b.z;
    tmp.z = a.x * b.y - a.y * b.x;
    return tmp;
}
double Dot(Pt a,Pt b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
Pt getNormal(plane s)
{
    return Cross(s.b-s.a,s.c-s.a);
}
double distance(Pt a,Pt b)
{
    return (b-a).length();
}
//求线线距离，先求出法向量，再在两条线上各取一点构成线段在此法向量上投影
double dis_line_to_line(line l1,line l2,Pt &normal)
{
    normal = Cross(l2.b-l2.a,l1.b-l1.a);
    return fabs(Dot(l1.a-l2.a,normal)/normal.length()) ;
}
//求直线与平面的交点，先求出法向量，然后利用投影（点积）求出两个高度，利用高度的比例
//求出交点
Pt line_to_plane(line ln,plane s)
{
    Pt nor = getNormal(s);
    double t = Dot(ln.a-s.a,nor) / Dot(ln.a-ln.b,nor);
    Pt tmp = ln.b - ln.a;
    return ln.a+tmp*t;
}

line L1,L2;
void gao()
{
    Pt normal = Cross(L2.b-L2.a,L1.b-L1.a);
    plane p1 = plane(L1.a,L1.b,L1.a+normal);
    Pt inter1 = line_to_plane(L2,p1);
    plane p2 = plane(L2.a,L2.b,L2.a+normal);
    Pt inter2 = line_to_plane(L1,p2);
    printf("%.6f\n",distance(inter1,inter2));
    printf("%.6f %.6f %.6f %.6f %.6f %.6f\n",inter2.x,inter2.y,inter2.z,
            inter1.x,inter1.y,inter1.z);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        L1.in(); L2.in();
        gao();
    }
    return 0;
}

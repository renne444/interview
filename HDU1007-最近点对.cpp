//
// Created by yuki on 2020/5/21.
//

#include <cstdio>
#include "cmath"
#include "algorithm"

using namespace std;

const int N = 1e5+7;
const double eps = 1e-8;
const double inf = 1e18;

struct Point {
    double x,y;
    Point():x(0),y(0){}
    Point(double x,double y):x(x),y(y){}

    double dist(const Point& rhs){
        return sqrt( (x-rhs.x)*(x-rhs.x) + (y-rhs.y)*(y-rhs.y) );
    }
};

//x为第一关键字
bool cmp_x_lt(Point a,Point b){
    if (a.x-eps < b.x && b.x < a.x+eps){
        return a.y < b.y;
    }
    return a.x < b.x;
}

bool cmp_y_lt(Point a,Point b){
    if (a.y-eps < b.y && b.y < a.y+eps){
        return a.x < b.x;
    }
    return a.y < b.y;
}

int n;
Point pointList[N];
int Y[N],Y_clone[N];
int stack[N],sz = 0;

void merge(int l,int mid,int r){
    int p = l, q = mid+1, index = l;
    while(p <= mid && q <= r){
        Y_clone[index++] = cmp_y_lt(pointList[ Y[p] ], pointList[ Y[q] ]) ? Y[p++] : Y[q++];
    }
    while(p <= mid){
        Y_clone[index++] = Y[p++];
    }
    while(q <= r){
        Y_clone[index++] = Y[q++];
    }
    copy(Y_clone+l,Y_clone+r+1,Y+l);
}

double dfs(int l,int r){
    if(l == r){
        return inf;
    } else{
        int mid = (l+r) >> 1;
        double d1 = dfs(l,mid), d2 = dfs(mid+1,r);
        double d = min(d1,d2);

        merge(l,mid,r);

        sz = 0;
        for(int i = l;i <= r; i++){
            if( pointList[mid].x - d - eps <= pointList[ Y[i] ].x && pointList[ Y[i]].x <= pointList[i].x + d + eps ){
                for(int j = sz-1;j >= 0 && pointList[ stack[j] ].y >= pointList[ Y[i]].y - d; j-- ){
                    d = min(d, pointList[Y[i]].dist(pointList[ stack[j] ]));
                }
                stack[sz++] = Y[i];
            }
        }
        return d;
    }
}

void solve(){
    sort(pointList,pointList+n,cmp_x_lt);
    for(int i=0;i<n;i++) Y[i] = i;
    double ans = dfs(0,n-1);
    printf("%.2f\n",ans/2);
}

int main() {

    while(scanf("%d",&n) && n){
        for(int i=0;i<n;i++){
            double x,y;
            scanf("%lf%lf",&x,&y);
            pointList[i] = Point(x,y);

        }
        solve();
    }

    return 0;
}
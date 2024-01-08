#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../../../Include/nachia/geometry/delaunay-triangulation.hpp"

#include <cstdio>
#include <cassert>
int main(){
    nachia::DelaunayTriangulation<long long, long long> delaunay;
    
    using Vec2 = nachia::VecI2<long long, long long>;
    std::vector<Vec2> points;
    points.push_back(Vec2());
    points.push_back(Vec2(5, 5));
    delaunay = nachia::DelaunayTriangulation(std::move(points));
    auto edges = delaunay.getEdges();
    assert((int)edges.size() == 1);
    
    int a,b; scanf("%d%d",&a,&b); printf("%d\n",a+b);
    return 0;
}

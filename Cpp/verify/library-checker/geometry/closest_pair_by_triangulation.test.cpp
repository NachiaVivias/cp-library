#define PROBLEM "https://judge.yosupo.jp/problem/closest_pair"
#include "../../../Include/nachia/geometry/delaunay-triangulation.hpp"
#include <iostream>
#include <cstdint>
#include <vector>

void testcase(int caseid){
    using std::cin;
    using std::cout;
    using DTri = nachia::DelaunayTriangulation<int, long long, __int128_t>;
    using Vec2 = DTri::GPos2;
    int N; cin >> N;
    std::vector<Vec2> A(N);
    for(int i=0; i<N; i++) cin >> A[i].x >> A[i].y;
    auto dt = DTri(A);
    auto dist = [&](int a, int b){
        auto v = A[a] - A[b];
        return v.norm();
    };
    std::pair<int,int> ans = {0,1};
    auto ansd = dist(0,1);
    for(auto [u,v] : dt.getEdges()){
        auto duv = dist(u,v);
        if(ansd > duv){ ansd = duv; ans = {u,v}; }
    }
    cout << ans.first << ' ' << ans.second << '\n';
}

int main(){
    int T; std::cin >> T;
    for(int t=0; t<T; t++){
        testcase(t);
    }
    return 0;
}

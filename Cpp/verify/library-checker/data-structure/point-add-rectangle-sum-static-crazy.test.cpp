#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"
#include "../../../Include/nachia/multi-dimensional/two-d-rectangle-query.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

#include <string>

struct BIT{
    std::vector<long long> A;
    BIT(int n=0){ A.assign(n+1,0); }
    long long sum(int r){
        long long res = 0;
        while(r){ res += A[r]; r -= r & -r; }
        return res;
    }
    void add(int p, long long x){
        p += 1;
        while(p < A.size()){ A[p] += x; p += p & -p; }
    }
};


std::string int_to_compstr(int x){
    std::string a = std::to_string(x);
    return std::string(10 - a.size(), '0') + a;
}

struct ReversedInt{
    int x;
};
bool operator<(ReversedInt l, ReversedInt r){ return r.x < l.x; }


int main(){
    using nachia::cin;
    using nachia::cout;

    int N,Q; cin >> N >> Q;
    std::vector<std::pair<ReversedInt, std::string>> P;
    std::vector<int> A;
    for(int i=0; i<N; i++){
        int x, y, w; cin >> x >> y >> w;
        P.push_back({ ReversedInt{x}, int_to_compstr(y) });
        A.push_back(w);
    }

    std::vector<std::vector<int>> queries;

    // read all queries first
    for(int i=0; i<Q; i++){
        int t; cin >> t;
        if(t == 0) /* additional point */ {
            int x, y, w; cin >> x >> y >> w;
            queries.push_back({ t, (int)P.size(), w });
            P.push_back({ ReversedInt{x}, int_to_compstr(y) });
            A.push_back(0);
        }
        if(t == 1) /* query */ {
            int xl, yl, xr, yr; cin >> xl >> yl >> xr >> yr;
            queries.push_back({ t, xl, xr, yl, yr });
        }
    }

    // 2-dimensional to 1-dimensional
    nachia::TwoDRectangleQuery<ReversedInt, std::string> two_dim(P);

    // 1-dimensional data structure
    std::vector<BIT> rq(two_dim.get_segment_count());
    for(int d=0; d<two_dim.get_segment_count(); d++){
        rq[d] = BIT(two_dim.size() + 1);
        for(int i=0; i<two_dim.size(); i++) rq[d].add(i, A[two_dim.to_vtx(d, i)]);
    }

    for(auto& q : queries){
        if(q[0] == 0) /* update */ {
            for(auto qq : two_dim.get_update_points(q[1])){
                rq[qq.d].add(qq.i, q[2]);
            }
        }
        if(q[0] == 1) /* query */ {
            long long ans = 0;
            for(auto qq : two_dim.get_ranges(
                ReversedInt{q[2]-1}, ReversedInt{q[1]-1},
                int_to_compstr(q[3]), int_to_compstr(q[4]))
            ){
                ans += rq[qq.d].sum(qq.r) - rq[qq.d].sum(qq.l);
            }
            cout << ans << '\n';
        }
    }
    
    return 0;
}

#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"
#include "../../../Include/nachia/multi-dimensional/two-d-rectangle-query.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

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


int main(){
    using nachia::cin;
    using nachia::cout;

    int N,Q; cin >> N >> Q;
    std::vector<std::pair<int,int>> P(N);
    std::vector<int> A(N);
    for(int i=0; i<N; i++){
        cin >> P[i].first >> P[i].second;
        cin >> A[i];
    }

    std::vector<std::vector<int>> queries;

    // read all queries first
    for(int i=0; i<Q; i++){
        int t; cin >> t;
        if(t == 0) /* additional point */ {
            int x, y, w; cin >> x >> y >> w;
            queries.push_back({ t, (int)P.size(), w });
            P.push_back({ x, y });
            A.push_back(0);
        }
        if(t == 1) /* query */ {
            int xl, yl, xr, yr; cin >> xl >> yl >> xr >> yr;
            queries.push_back({ t, xl, xr, yl, yr });
        }
    }

    // 2-dimensional to 1-dimensional
    nachia::TwoDRectangleQuery<int, int> two_dim(P);

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
            for(auto qq : two_dim.get_ranges(q[1], q[2], q[3], q[4])){
                ans += rq[qq.d].sum(qq.r) - rq[qq.d].sum(qq.l);
            }
            cout << ans << '\n';
        }
    }
    
    return 0;
}

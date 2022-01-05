
#include <vector>
#include <algorithm>
#include <utility>

namespace nachia{

template<class PosX, class PosY>
struct TwoDRectangeQuery{
private:
    
    int n;
    int N;
    int logN;
    std::vector<PosX> Xsorted;
    std::vector<PosY> Ysorted;
    std::vector<int> rankX;
    std::vector<std::vector<int>> Idx;
    std::vector<int> Z;
    std::vector<std::vector<int>> L;

public:

    TwoDRectangeQuery(const std::vector<std::pair<PosX, PosY>>& pos){
        n = pos.size();

        std::vector<int> sortIY(n);
        for(int i=0; i<n; i++) sortIY[i] = i;
        std::sort(sortIY.begin(),sortIY.end(),[&pos](int l,int r){ return pos[l].second<pos[r].second; });
        Ysorted.resize(n);
        for(int i=0; i<n; i++) Ysorted[i] = pos[sortIY[i]].second;

        std::vector<int> sortIX(n);
        rankX.resize(n);
        for(int i=0; i<n; i++) sortIX[i] = i;
        std::sort(sortIX.begin(),sortIX.end(),[&pos](int l,int r){ return pos[l]<pos[r]; });
        Xsorted.resize(n);
        for(int i=0; i<n; i++) Xsorted[i] = pos[sortIX[i]].first;
        for(int i=0; i<n; i++) rankX[sortIX[i]] = i;

        N = 1; logN = 0;
        while(N < n){ N *= 2; logN++; }
        Idx.assign(logN+1,std::vector<int>(n,-1));
        L.resize(logN,std::vector<int>(n+1,0));
        Z.resize(logN);
        for(int i=0; i<n; i++) Idx.back()[i] = sortIY[i];
        for(int i=logN-1; i>=0; i--){
            auto& preList = Idx[i+1];
            int z = ((n >> (i+1)) << i) + std::min(1<<i, (n % (2 << i)));
            Z[i] = z;
            int ai = 0, bi = z;
            for(int k=0; k<n; k++){
                L[i][k] = ai;
                bool chooseb = rankX[preList[k]] & (1<<i);
                if(!chooseb) Idx[i][ai++] = preList[k];
                else Idx[i][bi++] = preList[k];
            }
            L[i][n] = z;
        }

        for(int i=0; i<n; i++) rankX[sortIY[i]] = i;
    }
 
    int get_segment_count() const { return Idx.size(); }
    int size() const { return n; }
    int to_vtx(int d, int i) const { return Idx[d][i]; }


    struct UpdatePoint{ int d, i; };

    std::vector<UpdatePoint> get_update_points(int v) const {
        std::vector<UpdatePoint> res(logN+1);
        int p = rankX[v];
        int d = logN;
        while(d > 0){
            res[d] = { d,p };
            d--;
            if(L[d][p] != L[d][p+1]) p = L[d][p];
            else p = Z[d] + p - L[d][p];
        }
        res[d] = {d,p};
        return res;
    }


    struct Query{ int d,l,r; };
    std::vector<Query> get_ranges_from_idx(int xl, int xr, int yl, int yr){
        std::vector<Query> res;
        struct Search{ int i, xa, xb, ys, yt; };
        std::vector<Search> Q;
        res.reserve((logN+1)*2);
        Q.reserve((logN+1)*2);
        Q.push_back({ logN,0,n,yl,yr });
        for(int i=0; i<Q.size(); i++){
            auto p = Q[i];
            if(p.xa == p.xb) continue;
            if(xr <= p.xa || p.xb <= xl) continue;
            if(xl <= p.xa && p.xb <= xr){
                res.push_back({ p.i, p.ys, p.yt });
                continue;
            }
            p.i--;
            Q.push_back({ p.i,p.xa,p.xa+(1<<p.i),L[p.i][p.ys],L[p.i][p.yt] });
            Q.push_back({ p.i,p.xa+(1<<p.i),p.xb,Z[p.i]+p.ys-L[p.i][p.ys],Z[p.i]+p.yt-L[p.i][p.yt] });
        }
        return res; 
    }
  
    std::vector<Query> get_ranges(PosX xl, PosX xr, PosY yl, PosY yr){
        return get_ranges_from_idx(
            lower_bound(Xsorted.begin(),Xsorted.end(),xl) - Xsorted.begin(),
            lower_bound(Xsorted.begin(),Xsorted.end(),xr) - Xsorted.begin(),
            lower_bound(Ysorted.begin(),Ysorted.end(),yl) - Ysorted.begin(),
            lower_bound(Ysorted.begin(),Ysorted.end(),yr) - Ysorted.begin()
        );
    }
};

} // namespace nachia

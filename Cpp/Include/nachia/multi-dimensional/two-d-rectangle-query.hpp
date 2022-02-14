#pragma once

#include <vector>
#include <cstdint>
#include <algorithm>
#include <utility>


namespace nachia{



template<class PosX, class PosY>
struct TwoDRectangleQuery{
private:

    struct BitVectorRank {
        using u64 = ::std::uint64_t;
        using u32 = ::std::uint32_t;

        static u32 popcountll(u64 c){
        #ifdef __GNUC__
            return __builtin_popcountll(c);
        #else
            c = (c & (~0ull/3)) + ((c >> 1) & (~0ull/3));
            c = (c & (~0ull/5)) + ((c >> 2) & (~0ull/5));
            c = (c & (~0ull/17)) + ((c >> 4) & (~0ull/17));
            c = (c * (~0ull/255)) >> 56;
            return c;
        #endif
        }
        
        ::std::vector<::std::pair<u64, u32>> a;
        BitVectorRank(const ::std::vector<bool>& b = {}){
            int n = b.size();
            a.assign(n/64 + 1, ::std::make_pair((u64)0, (u32)0));
            auto p = b.begin();
            u32 sum = 0;
            u64 tmp = 0;
            for(int i=0; i<=n; i+=64){
                tmp = 0;
                int maxd = ::std::min<int>(n - i, 64);
                for(int d=0; d<maxd; d++){
                    tmp |= (u64)(*p ? 1 : 0) << d;
                    ++p;
                }
                a[i/64] = ::std::make_pair(tmp, sum);
                sum += popcountll(tmp);
            }
        }
        ::std::uint32_t rank(::std::uint32_t i) const {
            auto [b, s] = a[i >> 6];
            return (u32)(popcountll(b & ~(~u64(0) << (i & 63)))) + s;
        }
        bool get(::std::uint32_t i) const { return (a[i >> 6].first >> (i & 63)) & 1; }
    };
    
    int n;
    int N;
    int logN;
    ::std::vector<PosX> Xsorted;
    ::std::vector<PosY> Ysorted;
    ::std::vector<int> rankX;
    ::std::vector<::std::vector<int>> Idx;
    ::std::vector<int> Z;
    ::std::vector<BitVectorRank> L;

public:

    TwoDRectangleQuery(const ::std::vector<::std::pair<PosX, PosY>>& pos){
        n = pos.size();

        ::std::vector<int> sortIY(n);
        for(int i=0; i<n; i++) sortIY[i] = i;
        ::std::sort(sortIY.begin(),sortIY.end(),[&pos](int l,int r){ return pos[l].second<pos[r].second; });
        Ysorted.resize(n);
        for(int i=0; i<n; i++) Ysorted[i] = pos[sortIY[i]].second;

        ::std::vector<int> sortIX(n);
        rankX.resize(n);
        for(int i=0; i<n; i++) sortIX[i] = i;
        ::std::sort(sortIX.begin(),sortIX.end(),[&pos](int l,int r){ return pos[l]<pos[r]; });
        Xsorted.resize(n);
        for(int i=0; i<n; i++) Xsorted[i] = pos[sortIX[i]].first;
        for(int i=0; i<n; i++) rankX[sortIX[i]] = i;

        N = 1; logN = 0;
        while(N < n){ N *= 2; logN++; }
        Idx.assign(logN+1, ::std::vector<int>(n,-1));
        L.resize(logN);
        Z.resize(logN);
        for(int i=0; i<n; i++) Idx.back()[i] = sortIY[i];
        for(int i=logN-1; i>=0; i--){
            ::std::vector<bool> Lbuf(n,0);
            auto& preList = Idx[i+1];
            int z = ((n >> (i+1)) << i) + ::std::min(1<<i, (n % (2 << i)));
            Z[i] = z;
            int ai = 0, bi = z;
            for(int k=0; k<n; k++){
                bool chooseb = rankX[preList[k]] & (1<<i);
                if(!chooseb) Idx[i][ai++] = preList[k];
                else Idx[i][bi++] = preList[k];
                Lbuf[k] = !chooseb;
            }
            L[i] = BitVectorRank(Lbuf);
        }

        for(int i=0; i<n; i++) rankX[sortIY[i]] = i;
    }
 
    int get_segment_count() const { return Idx.size(); }
    int size() const { return n; }
    int to_vtx(int d, int i) const { return Idx[d][i]; }


    struct UpdatePoint{ int d, i; };

    ::std::vector<UpdatePoint> get_update_points(int v) const {
        ::std::vector<UpdatePoint> res(logN+1);
        int p = rankX[v];
        int d = logN;
        while(d > 0){
            res[d] = { d,p };
            d--;
            if(L[d].get(p)) p = L[d].rank(p);
            else p = Z[d] + p - L[d].rank(p);
        }
        res[d] = {d,p};
        return res;
    }


    struct Query{ int d,l,r; };
    ::std::vector<Query> get_ranges_from_idx(int xl, int xr, int yl, int yr){
        ::std::vector<Query> res;
        struct Search{ int i, xa, xb, ys, yt; };
        ::std::vector<Search> Q;
        res.reserve((logN+1)*2);
        Q.reserve((logN+1)*2);
        Q.push_back({ logN,0,n,yl,yr });
        for(int i=0; i<(int)Q.size(); i++){
            auto p = Q[i];
            if(p.xa == p.xb) continue;
            if(xr <= p.xa || p.xb <= xl) continue;
            if(xl <= p.xa && p.xb <= xr){
                res.push_back({ p.i, p.ys, p.yt });
                continue;
            }
            p.i--;
            int nxs = L[p.i].rank(p.ys), nxt = L[p.i].rank(p.yt);
            Q.push_back({ p.i,p.xa,p.xa+(1<<p.i),nxs,nxt });
            Q.push_back({ p.i,p.xa+(1<<p.i),p.xb,Z[p.i]+p.ys-nxs,Z[p.i]+p.yt-nxt });
        }
        return res; 
    }
  
    ::std::vector<Query> get_ranges(PosX xl, PosX xr, PosY yl, PosY yr){
        return get_ranges_from_idx(
            lower_bound(Xsorted.begin(),Xsorted.end(),xl) - Xsorted.begin(),
            lower_bound(Xsorted.begin(),Xsorted.end(),xr) - Xsorted.begin(),
            lower_bound(Ysorted.begin(),Ysorted.end(),yl) - Ysorted.begin(),
            lower_bound(Ysorted.begin(),Ysorted.end(),yr) - Ysorted.begin()
        );
    }
};

} // namespace nachia

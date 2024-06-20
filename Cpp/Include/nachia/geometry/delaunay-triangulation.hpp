#pragma once
#include <utility>
#include <vector>
#include <tuple>
#include <algorithm>
#include "../geometry/veci2.hpp"
#include "../array/csr-array.hpp"

namespace nachia{

// Int3 must be able to handle the value range :
//  |x| <= | (any input - any input) ** 4 * 12 |

template<class Int = long long, class Int2 = long long, class Int3 = Int2>
class DelaunayTriangulation {
public:

    using GPos2 = VecI2<Int, Int2>;
    struct Circumcenter {
        Int3 x; Int3 y; Int2 d;
        static Circumcenter From3Points(GPos2 p1, GPos2 p2, GPos2 p3){
            GPos2 dp1 = p2 - p1;
            GPos2 dp2 = p3 - p1;
            Int2 d1 = dp1.norm(); Int2 d2 = dp2.norm();
            Int2 w = dp1 ^ dp2; w += w;
            Int3 px = (Int3(dp2.y) * Int3(d1) - Int3(dp1.y) * Int3(d2)) + Int3(w) * Int3(p1.x);
            Int3 py = (Int3(dp1.x) * Int3(d2) - Int3(dp2.x) * Int3(d1)) + Int3(w) * Int3(p1.y);
            return { px, py, w };
        }
    };

    struct Edge {
        int to;
        int ccw;
        int cw;
        int rev;
        bool enabled = false;
    };
    
private:

    static int isDinOABC(GPos2 a, GPos2 b, GPos2 c, GPos2 d){
        a = a - d;
        b = b - d;
        c = c - d;
        auto val = Int3(b^c) * Int3(a.norm()) + Int3(c^a) * Int3(b.norm()) + Int3(a^b) * Int3(c.norm());
        return val > Int3(0) ? 1 : 0;
    }

    int getOpenAddress(){
        if(openAddress.empty()){
            edges.push_back({});
            return (int)edges.size() - 1;
        }
        int res = openAddress.back();
        openAddress.pop_back();
        return res;
    }

    std::pair<int, int> newEdge(int u, int v){
        int euv = getOpenAddress();
        int evu = getOpenAddress();
        edges[euv].ccw = edges[euv].cw = euv;
        edges[evu].ccw = edges[evu].cw = evu;
        edges[euv].to = v;
        edges[evu].to = u;
        edges[euv].rev = evu;
        edges[evu].rev = euv;
        edges[euv].enabled = true;
        edges[evu].enabled = true;
        return { euv, evu };
    }

    void eraseSingleEdge(int e){
        int eccw = edges[e].ccw;
        int ecw = edges[e].cw;
        edges[eccw].cw = ecw;
        edges[ecw].ccw = eccw;
        edges[e].enabled = false;
    }

    void eraseEdgeBidirectional(int e){
        int ex = edges[e].rev;
        eraseSingleEdge(e);
        eraseSingleEdge(ex);
        openAddress.push_back(e);
        openAddress.push_back(ex);
    }

    void insertCcwAfter(int e, int x){
        int xccw = edges[x].ccw;
        edges[e].ccw = xccw;
        edges[xccw].cw = e;
        edges[e].cw = x;
        edges[x].ccw = e;
    }

    void insertCwAfter(int e, int x){
        int xcw = edges[x].cw;
        edges[e].cw = xcw;
        edges[xcw].ccw = e;
        edges[e].ccw = x;
        edges[x].cw = e;
    }

    // move from ab to ac ... is this ccw?
    int isCcw(int a, int b, int c) const {
        auto ab = pos[b] - pos[a];
        auto ac = pos[c] - pos[a];
        auto cp = ab ^ ac;
        if(0 < cp) return 1;
        if(cp < 0) return -1;
        return 0;
    }

    std::pair<int, int> goNext(int , int ea){
        int ap = edges[ea].to;
        int eap = edges[edges[ea].rev].ccw;
        return { ap, eap };
    }

    std::pair<int, int> goPrev(int , int ea){
        int ap = edges[edges[ea].cw].to;
        int eap = edges[edges[ea].cw].rev;
        return { ap, eap };
    }

    std::tuple<int, int, int, int> goBottom(int a, int ea, int b, int eb){
        while(true){
            auto [ap, eap] = goPrev(a, ea);
            if(isCcw(b, a, ap) > 0){
                std::tie(a, ea) = { ap, eap };
                continue;
            }
            auto [bp, ebp] = goNext(b, eb);
            if(isCcw(a, b, bp) < 0){
                std::tie(b, eb) = { bp, ebp };
                continue;
            }
            break;
        }
        return { a, ea, b, eb };
    }

    std::pair<int, int> getMaximum(int a, int ea, bool toMin){
        std::pair<int, int> ans = { a, ea };
        int p = a, ep = ea;
        do {
            std::tie(p, ep) = goNext(p, ep);
            if(toMin) ans = std::min(ans, std::make_pair(p, ep));
            else ans = std::max(ans, std::make_pair(p, ep));
        } while(ep != ea);
        return ans;
    }

    bool isDinOABC(int a, int b, int c, int d){
        return isDinOABC(pos[a], pos[b], pos[c], pos[d]);
    }

    std::pair<int, int> dfs(int a, int ea, int b, int eb){
        std::tie(a, ea) = getMaximum(a, ea, false);
        std::tie(b, eb) = getMaximum(b, eb, true);
        auto [al, eal, bl, ebl] = goBottom(a, ea, b, eb);
        auto [bu, ebu, au, eau] = goBottom(b, eb, a, ea);
        ebl = edges[ebl].cw;
        ebu = edges[ebu].cw;

        auto [abl, bal] = newEdge(al, bl);
        insertCwAfter(abl, eal);
        insertCcwAfter(bal, ebl);
        if(al == au) eau = abl;
        if(bl == bu) ebu = bal;

        int ap = al, eap = eal;
        int bp = bl, ebp = ebl;
        while(ap != au || bp != bu){
            int a2 = edges[eap].to;
            int b2 = edges[ebp].to;
            int nxeap = edges[eap].ccw;
            int nxebp = edges[ebp].cw;

            if(eap != eau && nxeap != abl){
                int a1 = edges[nxeap].to;
                if(isDinOABC(ap, bp, a2, a1)){
                    eraseEdgeBidirectional(eap);
                    eap = nxeap;
                    continue;
                }
            }

            if(ebp != ebu && nxebp != bal){
                int b1 = edges[nxebp].to;
                if(isDinOABC(b2, ap, bp, b1)){
                    eraseEdgeBidirectional(ebp);
                    ebp = nxebp;
                    continue;
                }
            }

            bool chooseA = ebp == ebu;
            if(eap != eau && ebp != ebu){
				if(isCcw(ap, bp, b2) < 0) chooseA = true;
				else if(isCcw(a2, ap, bp) < 0) chooseA = false;
				else chooseA = isDinOABC(ap, bp, b2, a2);
            }

            if(chooseA){
                nxeap = edges[edges[eap].rev].ccw;
                auto [hab, hba] = newEdge(a2, bp);
                insertCwAfter(hab, nxeap);
                insertCcwAfter(hba, ebp);
                eap = nxeap; ap = a2;
            }
            else {
                nxebp = edges[edges[ebp].rev].cw;
                auto [hba, hab] = newEdge(b2, ap);
                insertCcwAfter(hba, nxebp);
                insertCwAfter(hab, eap);
                ebp = nxebp; bp = b2;
            }
        }

        return { al, abl };
    }

    std::pair<int, int> solveRange(int l, int r){
        if(r - l == 2){
            int u = l;
            int v = l + 1;
            auto [uv, vu] = newEdge(u, v);
            return { u, uv };
        }
        if(r - l == 3){
            int u = l;
            int v = l + 1;
            int w = l + 2;
            auto [uv, vu] = newEdge(u, v);
            auto [vw, wv] = newEdge(v, w);
            int ccw = isCcw(u, v, w);
            if(ccw == 0){
                insertCcwAfter(vu, vw);
            }
            if(ccw > 0){
                auto [uw, wu] = newEdge(u, w);
                insertCwAfter(uv, uw);
                insertCwAfter(vw, vu);
                insertCwAfter(wu, wv);
                return { u, uv };
            }
            if(ccw < 0){
                auto [uw, wu] = newEdge(u, w);
                insertCcwAfter(uv, uw);
                insertCcwAfter(vw, vu);
                insertCcwAfter(wu, wv);
                return { v, vu };
            }
            return { u, uv };
        }
        int m = (l + r) / 2;

        auto [a, ea] = solveRange(l, m);
        auto [b, eb] = solveRange(m, r);

        return dfs(a, ea, b, eb);
    }

    void solve(){
        int sz = (int)pos.size();
        if(sz <= 1) return;

        std::vector<int> pi(pos.size());
        for(int i=0; i<(int)pi.size(); i++) pi[i] = i;
        std::sort(
            pi.begin(), pi.end(),
            [&](int l, int r){
                return pos[l].x != pos[r].x ?
                    pos[l].x < pos[r].x : pos[l].y < pos[r].y;
            }
        );
        auto posbuf = pos;
        int posptr = 0;
        mappings.assign(sz, 0);
        for(int i=0; i<sz; i++){
            int v = pi[i];
            if(i == 0 || !(posbuf[pi[posptr-1]] == posbuf[v])){
                pi[posptr] = v;
                pos[posptr++] = posbuf[v];
                mappings[v] = v;
            } else {
                mappings[v] = pi[posptr-1];
            }
        }
        
        if(posptr >= 2) outerOneEdge = solveRange(0, posptr).second;
        std::swap(pos, posbuf);
        for(auto& e : edges) e.to = pi[e.to];
    }
    
    std::vector<int> openAddress;
    std::vector<GPos2> pos;
    std::vector<Edge> edges;
    std::vector<int> mappings;

    bool voronoiCalculated = false;
    int outerOneEdge = -1;
    std::vector<Circumcenter> circumcenters;
    std::vector<int> voronoiNodeRefLH;
    CsrArray<std::pair<int,int>> voronoi;
    void solveVoronoiDiagram(){
        if(edges.empty()){
            voronoi = CsrArray<std::pair<int,int>>::FromRaw({}, std::vector<int>(pos.size()+1, 0));
            voronoiCalculated = true;
        }
        if(voronoiCalculated) return;
        int m = edges.size();
        std::vector<int> res(m, -1);
        int outlineCount = 0;
        {
            int eu = outerOneEdge;
            int es = eu;
            do{
                eu = edges[eu].rev;
                res[eu] = -2;
                eu = edges[eu].ccw;
                outlineCount++;
            } while(es != eu);
        }
        for(int e=0; e<m; e++) if(res[e] == -1){
            int f = edges[edges[e].rev].cw;
            int g = edges[edges[f].rev].cw;
            int v = edges[e].to;
            int w = edges[f].to;
            int u = edges[g].to;
            int c = circumcenters.size();
            circumcenters.push_back(Circumcenter::From3Points(pos[u], pos[v], pos[w]));
            res[e] = res[f] = res[g] = c;
        }
        for(int e=0; e<m; e++) if(res[e] == -2){
            int f = edges[e].rev;
            int v = edges[e].to;
            int u = edges[f].to;
            if(res[f] == -2){
                int c1 = circumcenters.size();
                circumcenters.push_back({
                    Int2(pos[u].x) + Int2(pos[v].x) + Int2(pos[v].y - pos[u].y),
                    Int2(pos[u].y) + Int2(pos[v].y) - Int2(pos[v].x - pos[u].x), Int2(2) });
                int c2 = circumcenters.size();
                circumcenters.push_back({
                    Int2(pos[u].x) + Int2(pos[v].x) - Int2(pos[v].y - pos[u].y),
                    Int2(pos[u].y) + Int2(pos[v].y) + Int2(pos[v].x - pos[u].x), Int2(2) });
                res[e] = c1;
                res[f] = c2;
            } else {
                int c1 = circumcenters.size();
                auto q = circumcenters[res[f]];
                auto d = pos[v] - pos[u];
                q.x -= Int3(q.d) * Int3(d.y);
                q.y += Int3(q.d) * Int3(d.x);
                circumcenters.push_back(q);
                res[e] = c1;
            }
        }
		voronoiNodeRefLH = std::move(res);
        std::vector<int> oneEdge(pos.size(), -1);
        for(int e=0; e<m; e++) oneEdge[edges[e].to] = edges[e].rev;
        {
            std::vector<std::pair<int,int>> res(m*2);
            std::vector<int> ptr(pos.size() + 1);
            for(int s=0; s<int(pos.size()); s++){
                ptr[s+1] = ptr[s];
                if(oneEdge[s] >= 0){
                    int es = oneEdge[s];
                    int e = es;
                    do{
                        int re = edges[e].rev;
                        res[ptr[s+1]++] = { voronoiNodeRefLH[re], voronoiNodeRefLH[e] };
                        e = edges[e].ccw;
                    } while(e != es);
                }
            }
            voronoi = CsrArray<std::pair<int,int>>::FromRaw(std::move(res), std::move(ptr));
        }
        voronoiCalculated = true;
    }

public:

    DelaunayTriangulation()
        : pos()
    { solve(); }

    DelaunayTriangulation(std::vector<GPos2> x_points)
        : pos(std::move(x_points))
    {
        solve();
    }

    std::vector<std::pair<int, int>> getEdges() const {
        std::vector<std::pair<int, int>> res;
        for(int e=0; e<(int)edges.size(); e++) if(edges[e].enabled){
            int re = edges[e].rev;
            if(e < re) continue;
            res.push_back({ edges[e].to, edges[re].to });
        }
        for(int v=0; v<int(mappings.size()); v++){
            if(mappings[v] != v) res.push_back({ v, mappings[v] });
        }
        return res;
    }

    const std::vector<Circumcenter>& getVirtualCircumcenters(){
        solveVoronoiDiagram();
        return circumcenters;
    }

    std::vector<std::pair<double, double>> getVirtualCircumcentersAsDouble(){
        solveVoronoiDiagram();
        std::vector<std::pair<double, double>> res(circumcenters.size());
        for(int i=0; i<int(circumcenters.size()); i++){
            res[i].first = double(circumcenters[i].x) / double(circumcenters[i].d);
            res[i].second = double(circumcenters[i].y) / double(circumcenters[i].d);
        }
        return res;
    }

    const CsrArray<std::pair<int,int>>& getVoronoiDiagram(){
        solveVoronoiDiagram();
        return voronoi;
    }

};

} // namespace nachia

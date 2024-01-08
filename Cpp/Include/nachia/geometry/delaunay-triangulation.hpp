#pragma once
#include <utility>
#include <vector>
#include <tuple>
#include <algorithm>
#include "../geometry/veci2.hpp"

namespace nachia{

// Int2 must be able to handle the value range :
//  |x| <= | (any input - any input) ** 4 * 12 |

template<class Int = long long, class Int2 = long long>
class DelaunayTriangulation {
public:

    using GPos2 = class VecI2<Int, Int2>;

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
        auto val = (b^c) * a.norm() + (c^a) * b.norm() + (a^b) * c.norm();
        return val > Int2(0) ? 1 : 0;
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
                chooseA = isDinOABC(ap, bp, b2, a2);
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
        for(int i=0; i<(int)pos.size(); i++) pos[i] = posbuf[pi[i]];

        solveRange(0, sz);
        std::swap(pos, posbuf);
        for(auto& e : edges) e.to = pi[e.to];
    }
    
    std::vector<int> openAddress;
    std::vector<GPos2> pos;
    std::vector<Edge> edges;
    
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
        return res;
    }

};

} // namespace nachia

#pragma once
#include <iterator>

namespace nachia{

struct GridAdj4{
    int H;
    int W;
    struct GridPos { int y; int x; };
    struct GridAdj4Iter{
        using value_type = GridPos;
        using iterator_category = std::forward_iterator_tag;
        using Me = GridAdj4Iter;
        int c; int y; int x; int p;
        static inline const int dy[4] = { -1, 0, 1, 0 };
        static inline const int dx[4] = { 0, -1, 0, 1 };
        static Me Beg(int c, int y, int x){
            Me res = Me{c,y,x,4};
            return ++res;
        }
        Me& operator++(){
            p--; while(p >= 0 && !((c >> p) & 1)) p--;
            return *this;
        }
        Me operator++(int){ auto q=*this; return ++q; }
        bool operator==(const Me& r) const { return p == r.p; }
        bool operator!=(const Me& r) const { return p != r.p; }
        GridPos operator*() const { return GridPos{ y+dy[p], x+dx[p] }; }
    };
    struct GridAdj4Range{
        int c; int y; int x;
        GridAdj4Iter begin() const { return GridAdj4Iter::Beg(c,y,x); }
        GridAdj4Iter end() const { return GridAdj4Iter{c,y,x,-1}; }
    };
    GridAdj4(int height, int width)
        : H(height), W(width) {}
    GridAdj4Range operator()(int y, int x) const {
        GridAdj4Range res = {0,y,x};
        if(0 < y) res.c |= 1;
        if(0 < x) res.c |= 2;
        if(y < H-1) res.c |= 4;
        if(x < W-1) res.c |= 8;
        return res;
    }
};

} // namespace nachia

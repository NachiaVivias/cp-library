#pragma once
#include <iterator>

namespace nachia{

struct GridAdj8{
    int H;
    int W;
    struct GridPos { int y; int x; };
    struct GridAdj8Iter{
        using value_type = GridPos;
        using iterator_category = std::forward_iterator_tag;
        using Me = GridAdj8Iter;
        int c; int y; int x; int p;
        static inline const int dy[8] = { -1,-1,-1,0,1,1,1,0 };
        static inline const int dx[8] = { 1,0,-1,-1,-1,0,1,1 };
        static Me Beg(int c, int y, int x){
            Me res = Me{c,y,x,8};
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
    struct GridAdj8Range{
        int c; int y; int x;
        GridAdj8Iter begin() const { return GridAdj8Iter::Beg(c,y,x); }
        GridAdj8Iter end() const { return GridAdj8Iter{c,y,x,-1}; }
    };
    GridAdj8(int height, int width)
        : H(height), W(width) {}
    GridAdj8Range operator()(int y, int x) const {
        GridAdj8Range res = {255,y,x};
        if(0 == y) res.c &= 0xf8;
        if(0 == x) res.c &= 0xe3;
        if(y == H-1) res.c &= 0x8f;
        if(x == W-1) res.c &= 0x3e;
        return res;
    }
};

} // namespace nachia

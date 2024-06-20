#pragma once
#include <utility>
#include <algorithm>

namespace nachia{

template<class Int = long long, class Int2 = long long>
struct VecI2 {
    Int x, y;
    VecI2() : x(0), y(0) {}
    VecI2(std::pair<Int, Int> _p) : x(std::move(_p.first)), y(std::move(_p.second)) {}
    VecI2(Int _x, Int _y) : x(std::move(_x)), y(std::move(_y)) {}
    VecI2& operator+=(VecI2 r){ x+=r.x; y+=r.y; return *this; }
    VecI2& operator-=(VecI2 r){ x-=r.x; y-=r.y; return *this; }
    VecI2& operator*=(Int r){ x*=r; y*=r; return *this; }
    VecI2 operator+(VecI2 r) const { return VecI2(x+r.x, y+r.y); }
    VecI2 operator-(VecI2 r) const { return VecI2(x-r.x, y-r.y); }
    VecI2 operator*(Int r) const { return VecI2(x*r, y*r); }
    VecI2 operator-() const { return VecI2(-x, -y); }
    Int2 operator*(VecI2 r) const { return Int2(x) * Int2(r.x) + Int2(y) * Int2(r.y); }
    Int2 operator^(VecI2 r) const { return Int2(x) * Int2(r.y) - Int2(y) * Int2(r.x); }
    bool operator<(VecI2 r) const { return x < r.x || (!(r.x < x) && y < r.y); }
    Int2 norm() const { return Int2(x) * Int2(x) + Int2(y) * Int2(y); }
    static bool compareYX(VecI2 a, VecI2 b){ return a.y < b.y || (!(b.y < a.y) && a.x < b.x); }
    static bool compareXY(VecI2 a, VecI2 b){ return a.x < b.x || (!(b.x < a.x) && a.y < b.y); }
    bool operator==(VecI2 r) const { return x == r.x && y == r.y; }
    bool operator!=(VecI2 r) const { return x != r.x || y != r.y; }
};

} // namespace nachia

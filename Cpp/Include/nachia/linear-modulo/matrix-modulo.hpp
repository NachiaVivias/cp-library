#pragma once

#include <vector>
#include <cassert>
#include <utility>


namespace nachia{

template<class Elem>
struct MatrixModulo{
private:
    int h;
    int w;
    std::vector<Elem> elems;

public:
    
    MatrixModulo(int new_h=0, int new_w=0){ h = new_h; w = new_w; elems.assign(h * w, 0); }
    MatrixModulo(MatrixModulo const&) = default;
    int numRow() const { return h; }
    int numColumn() const { return w; }
    int height() const { return numRow(); }
    int width() const { return numColumn(); }
    typename std::vector<Elem>::iterator operator[](int y){ return elems.begin() + (y * w); }
    typename std::vector<Elem>::const_iterator operator[](int y) const { return elems.begin() + (y * w); }
    static MatrixModulo Identity(int idx){ auto res = MatrixModulo(idx, idx); for(int i = 0; i < idx; i++) res[i][i] = 1; return res; }
    void swapColumns(int x1, int x2){
        assert(0 <= x1 && x1 < numColumn());
        assert(0 <= x2 && x2 < numColumn());
        for(int y=0; y<numRow(); y++) std::swap((*this)[y][x1], (*this)[y][x2]);
    }
    void swapRows(int y1, int y2){
        assert(0 <= y1 && y1 < numRow());
        assert(0 <= y2 && y2 < numRow());
        for(int x=0; x<numColumn(); x++) std::swap((*this)[y1][x], (*this)[y2][x]);
    }
    MatrixModulo operator*(const MatrixModulo& r) const {
        assert(width() == r.height());
        auto res = MatrixModulo(h, r.w);
        for (int i=0; i<h; i++) for (int j=0; j<w; j++) for (int k=0; k<r.w; k++) res[i][k] += (*this)[i][j] * r[j][k];
        return res;
    }
    Elem det() const {
        assert(height() == width());
        MatrixModulo g = *this;
        Elem ans = 1;
        for (int i=0; i<h; i++) {
            int tg = -1;
            for (int j=i; j<h; j++) { if (g[j][i].val() != 0) tg = j; }
            if (tg == -1) return 0;
            if (tg != i) ans = -ans;
            for (int j=0; j<h; j++) std::swap(g[i][j], g[tg][j]);
            tg = i;
            ans *= g[i][i];
            Elem const_coeff = g[i][i].inv();
            for (int j=0; j<h; j++) g[i][j] *= const_coeff;
            for (int j=i+1; j<h; j++) for(int k=h-1; k>=i; k--) g[j][k] -= g[j][i] * g[i][k];
        }
        return ans;
    }
    int rank() const {
        MatrixModulo g = *this;
        int y = 0;
        for (int d=0; d<w; d++) {
            if(y == h) break;
            int tg = -1;
            for (int i=y; i<h; i++) { if (g[i][d].val() != 0){ tg = i; break; } }
            if (tg == -1) continue;
            for (int j=d; j<w; j++) std::swap(g[y][j], g[tg][j]);
            tg = y;
            Elem const_coeff = g[y][d].inv();
            for (int j=d; j<w; j++) g[y][j] *= const_coeff;
            for (int i=y+1; i<h; i++) for(int j=w-1; j>=d; j--) g[i][j] -= g[i][d] * g[y][j];
            y++;
        }
        return y;
    }
    MatrixModulo pow(unsigned long long i){
        auto a = *this;
        auto res = Identity(height());
        while(i){
            if(i % 2 == 1) res = res * a;
            a = a * a;
            i /= 2;
        }
        return res;
    }
};


} // namespace nachia

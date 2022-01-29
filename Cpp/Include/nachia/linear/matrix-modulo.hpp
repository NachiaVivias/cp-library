
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
    
    MatrixModulo(int new_h, int new_w){ h = new_h; w = new_w; elems.assign(h * w, 0); }
    MatrixModulo(const MatrixModulo&) = default;
    int height() const { return h; }
    int width() const { return w; }
    typename std::vector<Elem>::iterator operator[](int y){ return elems.begin() + (y * w); }
    typename std::vector<Elem>::const_iterator operator[](int y) const { return elems.begin() + (y * w); }
    static MatrixModulo identity(int idx){ auto res = MatrixModulo(idx, idx); for(int i = 0; i < idx; i++) res[i][i] = 1; return res; }
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
    MatrixModulo linear_equation() const {
        MatrixModulo g = *this;
        int y = 0;
        std::vector<std::pair<int,int>> det_var;
        std::vector<int> rank_var;
        for (int d=0; d<w-1; d++) {
            int tg = -1;
            for (int i=y; i<h; i++) { if (g[i][d].val() != 0){ tg = i; break; } }
            if (tg == -1){ rank_var.push_back(d); continue; }
            for (int j=d; j<w; j++) std::swap(g[y][j], g[tg][j]);
            tg = y;
            Elem const_coeff = g[y][d].inv();
            for (int j=d; j<w; j++) g[y][j] *= const_coeff;
            for (int i=0; i<h; i++) if (i != y) for(int j=w-1; j>=d; j--) g[i][j] -= g[i][d] * g[y][j];
            det_var.push_back(std::make_pair(d,y));
            y++;
        }
        for (int i=y; i<h; i++) if (g[i][w-1].val() != 0) return MatrixModulo(0,0);
        MatrixModulo solution(1 + rank_var.size(), w);
        for (auto [x,i] : det_var) { solution[0][x] = -g[i][w-1]; }
        solution[0][w-1] = 1;
        for (int d=0; d<(int)rank_var.size(); d++) {
            int varid = rank_var[d];
            solution[d+1][varid] = -Elem(1);
            for (auto [x,i] : det_var) { solution[d+1][x] = g[i][varid]; }
        }
        return solution;
    }
};

}
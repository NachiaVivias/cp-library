#include "../linear-modulo/matrix-modulo.hpp"

namespace nachia{

template<class Elem>
MatrixModulo<Elem> LinearEquation(MatrixModulo<Elem> g){
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
    for (int i=y; i<h; i++) if (g[i][w-1].val() != 0) return MatrixModulo<Elem>(0,0);
    MatrixModulo<Elem> solution(1 + rank_var.size(), w);
    for (auto [x,i] : det_var) { solution[0][x] = -g[i][w-1]; }
    solution[0][w-1] = 1;
    for (int d=0; d<(int)rank_var.size(); d++) {
        int varid = rank_var[d];
        solution[d+1][varid] = -Elem(1);
        for (auto [x,i] : det_var) { solution[d+1][x] = g[i][varid]; }
    }
    return solution;
}

} // namespace nahica

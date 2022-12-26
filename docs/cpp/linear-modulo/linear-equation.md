# 線型方程式

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/linear-modulo/linear-equation.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/linear-modulo/linear-equation.hpp)

## 主な機能

体 $\mathbb{F} _ p$ 上の線型方程式の一般解を求める。

### 関数 LinearEquation

```c++
template<class Elem>
MatrixModulo<Elem> LinearEquation(MatrixModulo<Elem> g);
```

- $1 \leq h$
- $2 \leq w$
- $O(h^2w)$ 時間

$w$ 次列ベクトル

$$\boldsymbol{x}= \left\lparen \begin{matrix} x _ 0 \cr x _ 1 \cr \vdots \cr x _ {w-1} \end{matrix} \right\rparen $$

であって、 $x _ {w-1}=1$ かつ $A\boldsymbol{x}=O$ を満たすものの集合を求める。

これは次の線形連立方程式を解くことに対応する。

$$
\left\lbrace
    \begin{array}{l}
        A _ {0,0} x _ 0 + A _ {0,1} x_1 + \cdots + A _ {0,w-2} x _ {w-2} + A _ {0,w-1} = 0 \cr
        A _ {1,0} x _ 0 + A _ {1,1} x_1 + \cdots + A _ {1,w-2} x _ {w-2} + A _ {1,w-1} = 0 \cr
        \hspace{10px} \vdots \cr
        A _ {h-1,0} x _ 0 + A _ {h-1,1} x_1 + \cdots + A _ {h-1,w-2} x _ {w-2} + A _ {h-1,w-1} = 0 \cr
    \end{array}
\right.
$$

解がない場合は、 $h=0$ のインスタンスを返す。

解がある場合に返る行列を $B$ とする。 $B$ は $h' \times w$ 型行列 $(h' \leq h)$ である。 $B _ {0,w-1}=1,B _ {y,w-1}=0 \hspace{5px}(1 \leq y \lt h')$ を満たす。

$B$ の各行ベクトルを $\boldsymbol{b} _ 0,\boldsymbol{b} _ 1, \ldots ,\boldsymbol{b} _ {h'-1}$ とする。これらはいずれも零ベクトルでない。これらの線形結合の転置 $\boldsymbol{x}=(\sum_i t _ i \boldsymbol{b} _ i)^\top$ で方程式 $A\boldsymbol{x}=O$ の解が網羅される。ただし、線形連立方程式の定数項を正しく扱うには、 $\boldsymbol{b} _ 0$ の係数は $t _ 0=1$ としなければならない。

## 使用コード例

Library Checker : [System of Linear Equations](https://judge.yosupo.jp/problem/system_of_linear_equations)

```c++
#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"
#include <nachia/linear-modulo/matrix-modulo.hpp>
#include <nachia/linear-modulo/linear-equation.hpp>
#include <iostream>
#include <atcoder/modint>


int main() {
    using modint = atcoder::static_modint<998244353>;
    using matrix = nachia::MatrixModulo<modint>;

    int h,w; std::cin >> h >> w;
    matrix A(h, w+1);
    for(int i=0; i<h; i++) for(int j=0; j<w; j++){ int a; std::cin >> a; A[i][j] = a; }
    for(int i=0; i<h; i++){ int a; std::cin >> a; A[i][w] = -a; }
    auto sol = nachia::LinearEquation(std::move(A));
    if(sol.height() == 0){ std::cout << "-1\n"; }
    else{
        std::cout << (sol.height()-1) << '\n';
        for(int i=0; i<w; i++){ if(i){ std::cout << ' '; } std::cout << sol[0][i].val(); } std::cout << '\n';
        for(int i=1; i<sol.height(); i++){
            for(int j=0; j<sol.width()-1; j++){ if(j) std::cout << ' '; std::cout << sol[i][j].val(); }
            std::cout << '\n';
        }
    }
    return 0;
}
```

## 参考


---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>



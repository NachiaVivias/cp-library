# 彩色多項式 (Chromatic Polynomial)

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/counting/chromatic-polynomial.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/counting/chromatic-polynomial.hpp)

## 主な機能

$n$ 頂点のグラフの各頂点を $x$ 色のうち $1$ 色で塗るとき、辺で直接結ばれた $2$ 頂点の色が同じにならないような色の割り当ての個数は、高々 $n$ 次の多項式 $f(x)$ で表せるので、この多項式を求める。

## 関数

### ChromaticPolynomial

```c++
template<class Modint>
std::vector<Modint> ChromaticPolynomial(std::vector<std::vector<int>> adjacency_matrix);
```

- $1 \leq n \leq 20$
- `adjacency_matrix` は $n \times n$ の行列（以下、 $\text{adj}$ で参照する。）
- 頂点 $i$ と頂点 $j$ を結ぶ辺があるとき $\text{adj}[i][j]=1$ 、ないとき $\text{adj}[i][j]=0$
- $\text{adj}[i][j]=\text{adj}[j][i]$
- `Modint` は Modint 、整数型からの変換および加減乗レベルの演算子が適切に定義されている
- $O(n^22^n)$ 時間

無向グラフに対して、彩色多項式の係数を `Modint` で計算する。
戻り値は長さ $n+1$ の配列で、 $k$ 番目 ($0\leq k\leq n$) の要素は彩色多項式の $k$ 次の係数である。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>

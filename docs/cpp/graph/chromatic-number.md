# 頂点彩色数

[C++ 用ライブラリ一覧に戻る](../index.md)./index.md)

## ソースコード

[nachia/graph/chromatic-number.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/chromatic-number.hpp)

## 主な機能

グラフの頂点彩色数を求める。

頂点彩色数とは、隣接する $2$ 頂点に同じ色を塗らないようにしてすべての頂点を塗るとき、使う色の最小個数である。

## 関数

### ChromaticNumber

```c++
int ChromaticNumber(std::vector<std::vector<int>> adjacency_matrix);
```

- $1 \leq n \leq 30$
- `adjacency_matrix` は $n \times n$ の行列
- 頂点 $i$ と頂点 $j$ を結ぶ辺があるとき $\text{adjacency\_matrix}[i][j]=1$ 、ないとき $\text{adjacency\_matrix}[i][j]=0$
- $\text{adjacency\_matrix}[i][i]=0$  （自己ループはない）
- $\text{adjacency\_matrix}[i][j]=\text{adjacency\_matrix}[j][i]$
- $O(n 2^n)$ 時間

グラフの頂点彩色数を返す。

目安は $n\leq 24$ 。

### ChromaticNumberByMod

```c++
template<unsigned int MOD>
int ChromaticNumberByMod(std::vector<std::vector<int>> adjacency_matrix);
```

- $1 \leq n \leq 30$
- $2^n \lt \text{MOD} \lt 2^{31}$
- `adjacency_matrix` は $n \times n$ の行列
- 頂点 $i$ と頂点 $j$ を結ぶ辺があるとき $\text{adjacency\_matrix}[i][j]=1$ 、ないとき $\text{adjacency\_matrix}[i][j]=0$
- $\text{adjacency\_matrix}[i][i]=0$  （自己ループはない）
- $\text{adjacency\_matrix}[i][j]=\text{adjacency\_matrix}[j][i]$
- $O(2^n)$ 時間

一定のルールに従ってグラフの頂点を彩色する方法を $\bmod \hspace{3px} \text{MOD}$ で数え上げ、それがゼロかどうかで彩色数を推定した値を返す。

正しい彩色数以上 $n$ 以下の値を返す。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>

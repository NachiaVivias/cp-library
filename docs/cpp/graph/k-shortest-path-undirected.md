# 無向グラフの第 $K$ 最短路

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/k-shortest-path-undirected.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/k-shortest-path-undirected.hpp)

## 主な機能

辺に**正**の重みがついた無向グラフ上で、 $s$-$t$ 間の単純パスを短い順に求める。

## struct KShortestPathUndirected

### テンプレート引数

```c++
template<class Weight>
struct KShortestPathUndirected;
```

経路の重み計算には `Weight` 型を使用する。

`Weight` 型の変数 `A` , `B` に関して、次の演算を正しく行えなければならない。

- `A + B`
- `A < B`

### コンストラクタ

```c++
KShortestPathUndirected(int _n, Weight _inf, Weight _zero, int _s, int _t)
```

`_n` は頂点数 $n$ である。

`_inf` はどの単純パスの重みよりも大きい値である。

`_zero` は $0$ として機能する値である。

`_s` , `_t` は求める単純パスの両端の頂点 $s$ , $t$ である。 $s$ が始点、 $t$ が終点である。

- 頂点数： $2 \leq n \leq 10^8$
- $0 \leq s < n$
- $0 \leq t < n$
- $s \neq t$

### addEdge

```c++
int addEdge(int from, int to, Weight w);
```

- $0 \leq \texttt{from} < n$
- $0 \leq \texttt{to} < n$
- $0 \textcolor{red}{<} w$
- 辺の個数を $m$ としたとき、 $0 \leq m \leq 10^8$

追加した辺には $0,1,2,\ldots $ の順番で番号が付けられる。
この関数は追加した辺の番号を返す。

### getNextSmallest

```c++
std::optional<std::vector<int>> getNextSmallest();
```

- $O(n + m \log m)$ 時間
- 呼び出すごとに追加で $O(n+m)$ 空間を使用

これまでに出力したパス以外の単純パスが存在する場合、そのうち最短のものを求め、辺番号の列として返す。
存在しない場合、 `std::nullopt` を返す。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>

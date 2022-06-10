# Online Dynamic Connectivity

[C++ 用ライブラリ一覧に戻る](../index.md)

## 主な機能

fully-dynamic connectivity problem をオンラインで解き、全域森を管理する。

頂点の番号は $0$ -based 。

## struct OnlineFullyDynamicConnectivityBySplayEtt

### コンストラクタ

```c++
OnlineFullyDynamicConnectivityBySplayEtt(int n);
```

- $1 \leq n \leq 3 \times 10^5$
- $O(n \log n)$ 時間

$n$ 頂点で辺を持たないグラフで、初期化する。

### link

```c++
::std::pair<int, int> link(int u, int v);
```

- $0 \leq u \lt n$
- $0 \leq v \lt n$
- この時点でグラフは辺 $\lbrace u,v \rbrace $ をもたない
- 償却 平均 $O( ( \log n ) ^2 )$ 時間

グラフに辺 $\lbrace u,v \rbrace $ を追加する。

全域森の辺を追加する必要がある場合はその辺の両端の頂点番号、それ以外の場合は $(-1,-1)$ を返す。

### cut

```c++
ForestCutQuery cut(int u, int v);
```

- $0 \leq u \lt n$
- $0 \leq v \lt n$
- この時点でグラフは辺 $\lbrace u,v \rbrace $ をもつ
- 償却 平均 $O( ( \log n ) ^2 )$ 時間

グラフの辺 $\lbrace u,v \rbrace $ を削除する。

返り値は全域森における辺の削除 `forest_cut` と辺の追加 `forest_link` の組である。返り値を利用する場合、削除を先に行わなければならない。いずれも `::std::pair<int, int>` 型。

全域森の辺を削除する必要がある場合は `forest_cut` はその辺の両端の頂点番号、それ以外の場合は $(-1,-1)$ を返す。

全域森の辺を追加する必要がある場合は `forest_link` はその辺の両端の頂点番号、それ以外の場合は $(-1,-1)$ を返す。

### is_connected

```c++
bool is_connected(int u, int v);
```

- $0 \leq u \lt n$
- $0 \leq v \lt n$
- 償却 平均 $O( \log n )$ 時間

$2$ 頂点 $u$ , $v$ が連結かどうかの真偽値を返す。

## 備考

現状 splay tree を用いているが、今後 randomized BST を用いるように変更するかもしれない。

## 参考

hotman78 \| online dynamic connectivity(削除可能union-find)の作り方を詳しく解説！！！ [https://qiita.com/hotman78/items/78cd3aa50b05a57738d4](https://qiita.com/hotman78/items/78cd3aa50b05a57738d4)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>

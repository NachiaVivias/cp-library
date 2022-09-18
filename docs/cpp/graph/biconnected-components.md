# Biconnected Components ( 2-連結成分 )

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/biconnected-components.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/biconnected-components.hpp)

## 主な機能

自己ループを持たない無向グラフを $2$-連結成分に分解します。各辺がどの成分に属するか（一意）を求めます。

グラフが $2$-連結であるとは、 $1$ つどの頂点を選んで（その頂点とそれに隣接するすべての辺を）取り除いても連結であるようなグラフであり、無向グラフの $2$-連結成分とは $2$-連結な部分グラフのうち極大なものである。

### 深い再帰関数なしの実装

`biconnected-components-nonrecursive.hpp` には深い再帰関数を使わないで実装したもの（ BiconnectedComponentsNonrecursive ）が含まれる。

実行時間では劣る可能性があるが、 RAM 消費の軽減や、スタック制限超過の回避に役立つ。

## struct BiconnectedComponents

### コンストラクタ

```c++
BiconnectedComponents(int n, std::vector<std::pair<int, int>> edges);
```

- $1 \leq n \leq 5 \times 10^5$
- $1 \leq m \leq 5 \times 10^5$
- グラフは自己ループを含まない。
- $O(n + m)$ 時間

$n$ 頂点 $m$ 辺のグラフを $2$-連結成分に分解する。配列 edges 内のインデックスを用いて辺に番号を振って管理する。

逆辺を与える必要はない。

### get_num_bcs

```c++
int get_num_bcs() const;
```

※ 調整中

### get_bcs

```c++
std::vector<std::vector<int>> get_bcs() const;
```

辺を $1$ つ以上含む $2$-連結成分それぞれの辺集合を返す。（孤立点が除かれます）

今後の更新で仕様を変える可能性が高め。

### get_bct

```c++
AdjacencyList get_bct() const;
```

block-cut tree (?) の隣接リストを返す。

$n$ 個の頂点は頂点 $0$ から $n-1$ （ cut node ）にそのまま対応し、 $2$ 連結成分が頂点 $n$ 以降（ block node ）に対応する。

block node に隣接する cut node の集合は、 $2$-連結成分に属する頂点集合に一致する。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>

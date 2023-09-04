# セグメント木

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/array/segtree.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/array/segtree.hpp)

## 主な機能

モノイドの要素列を二分木で管理することで、要素を 1 つ書き換える変更と、任意の区間の集約値の取得を高速に処理できる。

AtCoder Library との違いは、単位元 `e` をテンプレート引数ではなくコンストラクタで設定することである。

以下、 `op` による集約を $+$ で表す。つまり $a+b=\text{op}(a,b)$ 。

## 構造体テンプレート Segtree

### テンプレート引数

```c++
template<
    class S,
    S op(S l, S r)
>
struct Segtree;
```

要素の型 `S` と、集約の演算 `op` を与える。

* $(a+b)+c = a+(b+c)$ と変形してよいことが必要。

以降、 `S` の要素のコピーは $O(1)$ 時間で行えるとする。

### コンストラクタ

```c++
Segtree();    // (0)
Segtree(int n, S e);   // (1)
Segtree(const std::vector<S>& a, S e);   // (2)
```

* 要素数 $n$ : $0 \leq n \leq 10^8$
* 計算に現れる $x$ について、 $e+x=x+e=x$ と変形してよいことが必要。
* $0 \leq l \lt r \leq n$ について、 $a[l]+a[l+1]+\cdots +a[r-1]$ を計算してよいことが必要。

--

* (0) : ダミーを構築する。このインスタンスでは操作をしてはいけない。
* (1) : $n$ 要素を $e$ で初期化する。
* (2) : 要素列 $a$ で初期化する。

### set

```c++
void set(int p, S x);
```

* $0 \leq p \lt n$
* $O( \log n )$ 時間 + $O(\log n)$ 回の `op`

単一の要素への操作。 `a[p] = x` に相当する。

### get

```c++
S get(int p) const;
```

* $0 \leq p \lt n$
* $O( 1 )$ 時間

`a[p]` を取得する。

### prod

```c++
S prod(int l, int r) const;
```

* $0 \leq l \leq r \leq n$
* $O( \log n )$ 時間 + $O(\log n)$ 回の `op`

$a[l]+a[l+1]+\cdots +a[r-1]$ を返す。 $l=r$ ならば $e$ を返す。

### allProd

```c++
S allProd() const;
```

* $O(1)$ 時間

$a[0]+a[1]+\cdots +a[n-1]$ を返す。 $n=0$ ならば $e$ を返す。

### minLeft

```c++
template<class E>
int minLeft(int r, E cmp);
```

* `cmp` は `bool cmp(S x)` という関数として呼び出せる。
* $0 \leq r \leq n$
* $O( \log n )$ 時間 + $O(\log n)$ 回の `op`

セグメント木上の二分探索によって、以下の条件をすべて満たすような整数 $l$ を一つ求める。

* `l == r || cmp(prod(l,r))`
* `l == 0 || !cmp(prod(l-1,r))`

### maxRight

```c++
template<class E>
int maxRight(int l, E cmp);
```

* `cmp` は `bool cmp(S x)` という関数として呼び出せる。
* $0 \leq l \leq n$
* $O( \log n )$ 時間 + $O(\log n)$ 回の `op`

セグメント木上の二分探索によって、以下の条件をすべて満たすような整数 $r$ を一つ求める。

* `r == l || cmp(prod(l,r))`
* `r == n || !cmp(prod(l,r+1))`

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>

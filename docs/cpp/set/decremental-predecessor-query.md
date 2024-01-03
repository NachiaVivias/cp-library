# decremental predecessor problem

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/set/decremental-predecessor-query.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/set/decremental-predecessor-query.hpp)

## 主な機能

はじめ、 $A=\lbrace 0,1,\ldots ,n \rbrace$ であるとする。以下のクエリを処理する。

* 整数 $p$ $(p\lt n)$ が与えられる。 $A$ の値を $A\setminus\lbrace p\rbrace$ に更新する。
* 整数 $x\leq n$ が与えられる。 $x\leq p$ かつ $p\in A$ を満たす最小の $p$ を返す。

## 構造体 DecrementalPredecessorQuery

### コンストラクタ

```c++
DecrementalPredecessorQuery(int _n);
```

* $0\leq n \leq 10^9$
* $O(n/\log n)$ 時間

初期化。

### queryNoLessThan

```c++
int queryNoLessThan(int x);
```

* $x\lt n$
* 償却 $O(1)$ 時間、最悪 $O(\log n)$ 時間

$x\leq p$ かつ $p\in A$ を満たす最小の $p$ を返す。

### dec

```c++
void dec(int p);
```

* $0\leq p \lt n$
* 償却 $O(1)$ 時間、最悪 $O(\log n)$ 時間

$A$ の値を $A\setminus\lbrace p\rbrace$ に更新する。

## 参考

- [α(m, n) のお勉強 + 定数時間 decremental neighbor query - えびちゃんの日記](https://rsk0315.hatenablog.com/entry/2022/05/04/215704)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>



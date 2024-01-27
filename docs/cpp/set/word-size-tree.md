# 64 分木

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/set/word-size-tree.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/set/word-size-tree.hpp)

## 主な機能

$\left\lbrace 0,1,\ldots ,n-1\right\rbrace$ の部分集合 $S$ を管理する。

$w=64$ として $w$ 分木で管理するため、基本的な計算量は $O(\log n/\log w)$ になる。

## struct nachia::WordsizeTree

### コンストラクタ

```c++
    WordsizeTree(int length);                     // (1)
    WordsizeTree(const std::string& binStr = ""); // (2)
```

- $O(n/w)$ 空間

`(1)` : $n=\text{length}$ として空集合で初期化する。

`(2)` : 0-indexed で $k$ 文字目が `1` であれば $k\in S$ 、 `0` であれば $k\notin S$ として初期化する。

### insert

```c++
void insert(int x);
```

- $0\leq x \lt n$
- $O(\log n/\log w)$ 時間

$x\notin S$ であれば、 $x$ を追加する。

### erase

```c++
int erase(int x);
```

- $0\leq x \lt n$
- $O(\log n/\log w)$ 時間

$x\in S$ であれば、 $x$ を取り除く。

### count

```c++
int count(int x) const;
```

- $0\leq x \lt n$
- $O(1)$ 時間

$x\in S$ なら $1$ 、でなければ $0$ を返す。

### noLessThan

```c++
int noLessThan(int x) const;
```

- $O(\log n/\log w)$ 時間

$x\leq y$ かつ $y\in S$ を満たす $y$ について、

* 存在すれば、その最小値 $y$ を返す。
* 存在しなければ、 $n$ を返す。

### noGreaterThan

```c++
int noGreaterThan(int x) const;
```

- $O(\log n/\log w)$ 時間

$y\leq x$ かつ $y\in S$ を満たす $y$ について、

* 存在すれば、その最大値 $y$ を返す。
* 存在しなければ、 $-1$ を返す。

## 参考


---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>



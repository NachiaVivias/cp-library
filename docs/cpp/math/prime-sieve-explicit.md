# 明示的な素数篩（エラトステネスの篩）

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/math/prime-sieve-explicit.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/math/prime-sieve-explicit.hpp)

## 主な機能

ある値以下の素数を列挙する。

「明示的な」 は、 $n$ 以下の素数の個数を $O(n^{3/4} / \log n)$ 時間で求めるアルゴリズムなどと区別するための語句である。

## 計算量

素数かもしれない整数 $k$ を扱うときは前計算に $O(k \log \log k)$ 時間かかる場合があるが、一連の呼び出しにおける $k$ の最大値を $N$ とすると、前計算全体は $O(N \log \log N)$ 時間に収まる。

各関数の計算量では、この $k$ の値と、前計算以外の計算量を示す。

なお、 Library Checker の [この提出](https://judge.yosupo.jp/submission/77249) では、 $k=5 \times 10^8$ の前計算に $2000 [\text{ms}]$ , $160 [\text{MiB}]$ 程度かかっている。

## 関数

### IsprimeExplicit

```c++
bool IsprimeExplicit(int n);
```

- $0 \leq n \leq 5 \times 10^8$
- 前計算 $k=n$ , $O(1)$ 時間

$n$ が素数かどうかの真偽値を返す。

### NthPrimeExplicit

```c++
int NthPrimeExplicit(int n);
```

- $0 \leq n \lt \pi (5 \times 10^8) = 26\hspace{2px}355\hspace{2px}867$
- 前計算 $k= \pi^{-1}(n)$ , $O(1)$ 時間 （ $\pi^{-1}(n)$ は $n$ 番目 ( $0$-origin) の素数）

小さいほうから $n$ 番目 ( $0$-origin) の素数を返す。

### PrimeCountingExplicit

```c++
int PrimeCountingExplicit(int n);
```

- $0 \leq n \leq 5 \times 10^8$
- 前計算 $k=n$ , $O(\log n)$ 時間

$n$ 以下の素数の個数を返す。

### SegmentedSieveExplicit

```c++
::std::vector<bool> SegmentedSieveExplicit(long long l, long long r);
```

- $d = r-l$
- $2 \leq l \leq r \leq 10^{17}$
- $0 \leq d \leq 10^8$
- 前計算 $k=\sqrt{r}$ , $O((\sqrt{r} + d) \log \log r)$ 時間

返る配列を `A` とすると、 `A[i]` $(0 \leq i \lt d)$ は、 $(l+i)$ が素数かどうかの真偽値である。

## 参考

アルゴ式 \| 整数論的アルゴリズム、エラトステネスのふるい (1)、EX. エラトステネスの区間篩 : [https://algo-method.com/tasks/332/editorial](https://algo-method.com/tasks/332/editorial)

37zigenのHP \| エラトステネスの篩 [https://37zigen.com/sieve-eratosthenes/](https://37zigen.com/sieve-eratosthenes/)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>

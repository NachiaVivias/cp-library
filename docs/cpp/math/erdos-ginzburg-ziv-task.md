# Erdős-Ginzburg-Ziv theorem

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/math/erdos-ginzburg-ziv-task.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/math/erdos-ginzburg-ziv-task.hpp)

## 主な機能

$2N-1$ 個の整数から $N$ 個を選ぶ方法であって、総和が $N$ の倍数となるものを $1$ つ求める。
これはかならず存在する。

## 関数

### ErdosGinzburgZivTask

```c++
std::vector<int> ErdosGinzburgZivTask(int N, std::vector<int> A);
```

- $1 \leq N \leq 5 \times 10^8$
- $0 <= A[i]$
- $O(N \log N)$ 時間

長さ $N$ の配列を返す。
返る配列を $B$ とすると、 $\sum _ i A[B[i]]$ は $N$ の倍数である。

## 参考

* Choi, Seokhwan, Hanpil Kang, and Dongjae Lim. "Simple deterministic O (n log n) algorithm finding a solution of Erdős-Ginzburg-Ziv theorem." arXiv preprint arXiv:2208.07728 (2022). ([https://arxiv.org/abs/2208.07728](https://arxiv.org/abs/2208.07728))

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>

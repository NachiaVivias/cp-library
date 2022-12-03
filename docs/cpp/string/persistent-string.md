# 永続文字列

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/string/persistent-string.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/string/persistent-string.hpp)

## 主な機能

文字列（バイト列）の連結、分割を非破壊的に行う。コピーペーストの繰り返しによって通常よりも長い文字列を生成でき、長さ $2^{60}$ まで表現できる。

$1$ バイトずつ二分探索木の葉に乗せるのに比べて、メモリ使用量を抑えるようにしている。

## struct nachia::PersistentString

### コンストラクタ

```c++
PersistentString(const std::string& s = "");
PersistentString(const char* s);
```

- $n$ を文字列の長さとして、 $n\leq 2^{28}$
- $O(n)$ 空間

文字列を与えて初期化する。

また、コピーとムーブが可能である。

### std::string と共通の部分

```c++
MyType substr(size_t pos, size_t len) const; // (1)
bool empty() const noexcept; // (2)
size_t size() const noexcept; // (2)
```

- (1)
  - $\text{pos}\leq\text{size}$
  - $O(\log n)$ 時間（ $n$ は文字列長）
- (2) 定数時間

メインの機能は std::string のものと同様である。

### operator+ , +=

```c++
MyType operator+(MyType rh) const;
MyType& operator+=(MyType rh);
```

- $O(\log n)$ 時間

std::string の演算と同じである。

### operator* , *=

```c++
MyType operator*(size_t z) const;
MyType& operator*=(size_t z);
```

- $0 \leq z$
- 文字列長が $2^{60}$ を超えないように注意すること。

文字列を $z$ 回繰り返した文字列を取得する。

$z=0$ ならば空文字列を取得する。

### insert, inserted

```c++
void insert(MyType other, size_t pos);
MyType inserted(MyType other, size_t pos) const;
```

- $0\leq \text{pos}\leq\text{size}$

位置 begin+pos に他の文字列を挿入する。 inserted は this の内容を破壊しない。

### to_string

```c++
std::string to_string();
```

- $O(n)$ 時間

文字列を明示的に取得する。

## 使用例

JOI2011/2022 春季トレーニング合宿 : copypaste - コピー＆ペースト (https://atcoder.jp/contests/joisc2012/tasks/joisc2012_copypaste)

```c++
#include <iostream>
#include <nachia/string/persistent-string.hpp>

int main(){
    int M; std::cin >> M;
    std::string buf; std::cin >> buf;
    auto S = nachia::PersistentString(buf);
    int Q; std::cin >> Q;
    for(int i=0; i<Q; i++){
        unsigned int l,r,p; std::cin >> l >> r >> p;
        S = S.inserted(S.substr(l, r-l), p).substr(0, M);
    }
    std::cout << S.to_string() << '\n';
    return 0;
}
```

## 参考


---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>



# 高速入出力

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/misc/fastio.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/misc/fastio.hpp)

## 主な機能

競技プログラミングでよく用いられる範囲で入出力をサポートする。環境によると思うが、標準ライブラリの `scanf` , `printf` を使用するよりも高速に動作する。

`nachia::cin` で標準入力、 `nachia::cout` で標準出力を操作する。

標準ライブラリ `<cstdio>` の `fread` , `fwrite` を使用する。

## nachia::cin

### 入力

```c++
    char nextChar();
    uint32_t nextU32();
    int32_t nextI32();
    uint64_t nextU64();
    int64_t nextI64();
    std::string nextToken();
```

Windows 環境では `\r` が正しく読み込まれないなど、入力内容は `fread` の影響を受ける。

これらの関数は、読み込みの前に空白を読み飛ばす。

- `nextChar` は、空白でない最初の 1 byte を読み込んで返す。
- `nextToken` は次の空白が現れるまでの文字列を読み込んで返す。その他の関数は、読み込んだ文字列をそれぞれの型にパースしたものを返す。パースが定義されない場合の動作は定義しない。
- 整数の符号は `-` のみ受理する。非負整数に符号がついている場合はパースを定義しない。

### operator\>\>

```c++
	MyType& operator>>(unsigned int& dest){ dest = nextU32(); return *this; }
	MyType& operator>>(int& dest){ dest = nextI32(); return *this; }
	MyType& operator>>(unsigned long& dest){ dest = nextU64(); return *this; }
	MyType& operator>>(long& dest){ dest = nextI64(); return *this; }
	MyType& operator>>(unsigned long long& dest){ dest = nextU64(); return *this; }
	MyType& operator>>(long long& dest){ dest = nextI64(); return *this; }
	MyType& operator>>(std::string& dest){ dest = nextToken(); return *this; }
	MyType& operator>>(char& dest){ dest = nextChar(); return *this; }
```

## nachia::cout

通常、出力はバッファに書き込む。プログラム終了時にデストラクタが呼ばれることで、ファイルへの書き込みと flush が行われる。 `writeToFile` の呼び出すことにより任意のタイミングでファイルに書き込める。

Windows 環境で `\n` を出力した場合に `\r\n` に置換されるなど、出力内容は `fwrite` の影響を受ける。

### 出力

```c++
// (1)
    void nextEoln();

// (2)
    void nextCstr(const char* s);

// (3)
    void nextChar(char c);
    void nextU32(uint32_t x);
    void nextI32(int32_t x);
    void nextU64(uint64_t x);
    void nextI64(int64_t x);
```

- (1) : `nextEoln()` は `nextChar('\n')` を呼び出す。
- (2) : 文字列を出力する。引数はヌル文字 `'\0'` で終端を表すこと。
- (3) : 引数のデータを文字列に変換して出力する。空白は自動で出力されないので、 `nextChar` を用いること。

### writeToFile

```c++
void writeToFile(bool flush = false)
```

ファイルへ書き込んでバッファをクリアする。引数を true にすると、書き込みのあとに flush する。

### operator\<\<

```c++
	MyType& operator<<(unsigned int tg){ nextU32(tg); return *this; }
	MyType& operator<<(unsigned long tg){ nextU64(tg); return *this; }
	MyType& operator<<(unsigned long long tg){ nextU64(tg); return *this; }
	MyType& operator<<(int tg){ nextI32(tg); return *this; }
	MyType& operator<<(long tg){ nextI64(tg); return *this; }
	MyType& operator<<(long long tg){ nextI64(tg); return *this; }
	MyType& operator<<(const std::string& tg){ nextCstr(tg.c_str()); return *this; }
	MyType& operator<<(const char* tg){ nextCstr(tg); return *this; }
	MyType& operator<<(char tg){ nextChar(tg); return *this; }
```

速く記述する用。

## 使用例


## 参考

- http://www9.plala.or.jp/sgwr-t/lib/fread.html

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>



# Do Not Push Game ～押すなよ！絶対！～

日本は言霊の力が強い、不思議な国。  
ならば言霊で遊ぼうやないか！  
押すなよ！絶対！

![Presentation1](Don't_push/Don't_push/assets/img/Presentation1.png)

## Download方法
[Release](https://github.com/TakeObara/DoNotPushGame/releases)よりビルド済みバイナリが手にはいります。

https://gist.github.com/yumetodo/1bc47ce42b6128e1950c
を使用するとReleaseから最新版を落としてきます。DVDに焼く場合はこれを推奨します。

ソースコードは

```sh
git clone https://github.com/TakeObara/DoNotPushGame.git
```

もしくは

```sh
git clone https://yumetodo@bitbucket.org/yumetodo/donotpushgame.git
```

## dependency 依存関係
- [DxLibEx](https://github.com/Nagarei/DxLibEx)(commit [641b3b06367d3c50347b55d1eeff07fcb1b22763(2016/09/25 JST)](https://github.com/Nagarei/DxLibEx/tree/641b3b06367d3c50347b55d1eeff07fcb1b22763)以降を推奨)
- [DxLib](http://homepage2.nifty.com/natupaji/DxLib/)
- [Boost](www.boost.org)(``boost::optional``, ``Boost::property_tree``を使用。boost 1.59.0, 1.60.0, 1.61.0, 1.62.0で動作確認)

最終的にSHandleはDxLibExに移行する。暫定的にオレオレclassを使用中・・・

## 動作環境
- OS : Microsoft Windows Vista/7/8/10(＊XPはビルドツールセット変えれば行けると思いますがサポートしません)
- CPU: SSE2対応CPU(＊ビルドツールセット変えればSSE2なしで行けますが今時SSE2使えないPCなんてないよね？)。RDRAND/RDSEED命令も対応していれば使用します。
- メモリ: 128MB以上
- DirectX9以降が必要

## ゲーム操作方法
- 十字キー:移動
- Zキー:状態変遷
- Esc:終了

## ゲーム終了方法
ウィンドウ右上の閉じるボタンを押すかEscボタンを押す

## LICENSE

[License.md](License.md)

## 免責事項
このプログラムを実行したことによって生じたいかなる損害について作者は一切の責任を負いません。

## Compiler Support 対応コンパイラー
- Visual Studio 2013 Update 5
- Visual Studio 2015 Update 3
- Visual Studio 2015 Clang with Microsoft CodeGen(clang3.8) (July 2016)

## Not Supported but may be work　非対応だがおそらく動くコンパイラ
- Visual Studio 2015 Update 1
- Visual Studio 2015 Update 2
- mingw-gcc 5.4.0
- mingw-clang 3.8.0

## We will never support 非対応コンパイラ
- Visaul Studio 2015
- Visual Studio 2013 November CTP
- Visual Studio 2012 November CTP
- or before...
- Visual Studio 2015 Clang with Microsoft CodeGen(clang 3.8)(May 2016)
- or before...

## Compile方法
1. 環境変数``DXLIB_ROOT``と``DXLIBEX_ROOT``と``BOOST_ROOT``を設定する  
ex.)``DXLIB_ROOT``を``D:\lib\DxLib_VC\プロジェクトに追加すべきファイル_VC用``に  
``DXLIBEX_ROOT``を``C:\Users\yumetodo\Documents\git\DxLibEx``に  
``BOOST_ROOT``を``C:\lib\boost_1_61_0``に
2. ``Don't_push.sln``を開く
3. (boost1.60.0以前のみ)Boost側のコンパイルエラーを回避するために下記の通り変更を加える
4. ビルド→ソリューションのビルドでビルドする

### Boostに加える変更(1.61.0以降では不要)

``./boost/smart_ptr/detail/sp_counted_base.hpp``

これがもっとも大事な変更です。書きにくかったのでこれだけdiffを直貼します。cdしてpatchするだけですし。diffを知らないようなプログラマはいないと思いますが、  
http://x68000.q-e-d.net/~68user/unix/pickup?patch  
http://hakobe932.hatenablog.com/entry/20071011/1192135295  
これでもみて勉強しましょう

```patch
--- C:/Users/yumetodo/Desktop/sp_counted_base.hpp	Thu Feb 11 23:05:32 2016
+++ C:/lib/boost_1_60_0/boost/smart_ptr/detail/sp_counted_base.hpp	Thu Feb 11 23:06:02 2016
@@ -22,3 +22,3 @@
 
-#if defined( __clang__ ) && defined( __has_extension )
+#if defined( __clang__ ) && defined( __has_extension ) && !defined( __c2__ )
 # if __has_extension( __c_atomic__ )
@@ -49,3 +49,3 @@
 
-#elif defined( __GNUC__ ) && ( defined( __i386__ ) || defined( __x86_64__ ) ) && !defined(__PATHSCALE__)
+#elif defined( __GNUC__ ) && ( defined( __i386__ ) || defined( __x86_64__ ) ) && !defined(__PATHSCALE__) && !defined( __c2__ )
 # include <boost/smart_ptr/detail/sp_counted_base_gcc_x86.hpp>
@@ -55,3 +55,3 @@
 
-#elif defined( __GNUC__ ) && defined( __ia64__ ) && !defined( __INTEL_COMPILER ) && !defined(__PATHSCALE__)
+#elif defined( __GNUC__ ) && defined( __ia64__ ) && !defined( __INTEL_COMPILER ) && !defined(__PATHSCALE__) && !defined( __c2__ )
 # include <boost/smart_ptr/detail/sp_counted_base_gcc_ia64.hpp>
```

cf.)
https://groups.google.com/forum/#!topic/boost-devel-archive/ZzKPda-TVDw  
https://llvm.org/bugs/show_bug.cgi?id=25384  
https://llvm.org/bugs/show_bug.cgi?id=25639

``./boost/property_tree/detail/json_parser/standard_callbacks.hpp`` l.131

変更前

```cpp
        Ptree& new_tree() {
            if (stack.empty()) {
                layer l = {leaf, &root};
                stack.push_back(l);
                return root;
            }
            layer& l = stack.back();
            switch (l.k) {
            case array: {
                l.t->push_back(std::make_pair(string(), Ptree()));
                layer nl = {leaf, &l.t->back().second};
                stack.push_back(nl);
                return *stack.back().t;
            }
            case object:
                assert(false); // must start with string, i.e. call new_value
            case key: {
                l.t->push_back(std::make_pair(key_buffer, Ptree()));
                l.k = object;
                layer nl = {leaf, &l.t->back().second};
                stack.push_back(nl);
                return *stack.back().t;
            }
            case leaf:
                stack.pop_back();
                return new_tree();
            }
            assert(false);
        }
```

変更後

```cpp
        Ptree& new_tree() {
            if (stack.empty()) {
                layer l = {leaf, &root};
                stack.push_back(l);
                return root;
            }
            layer& l = stack.back();
            switch (l.k) {
            case array: {
                l.t->push_back(std::make_pair(string(), Ptree()));
                layer nl = {leaf, &l.t->back().second};
                stack.push_back(nl);
                return *stack.back().t;
            }
            case object:
                assert(false); // must start with string, i.e. call new_value
            case key: {
                l.t->push_back(std::make_pair(key_buffer, Ptree()));
                l.k = object;
                layer nl = {leaf, &l.t->back().second};
                stack.push_back(nl);
                return *stack.back().t;
            }
            case leaf:
                stack.pop_back();
                return new_tree();
            }
			assert(l.k == leaf); stack.pop_back(); return new_tree();
        }

```

cf.)
https://svn.boost.org/trac/boost/ticket/11599

``./boost/property_tree/detail/json_parser/wide_encoding.hpp`` l.120

変更前

```cpp
        template <typename Iterator, typename Sentinel, typename TranscodedFn,
                  typename EncodingErrorFn>
        void transcode_codepoint(Iterator& cur, Sentinel end,
                                 TranscodedFn transcoded_fn,
                                 EncodingErrorFn error_fn,
                                 is_utf16<true>) const {
            wchar_t c = *cur;
            if (c < 0x20) {
                error_fn();
            }
            if (is_surrogate_low(c)) {
                error_fn();
            }
            transcoded_fn(c);
            ++cur;
            if (is_surrogate_high(c)) {
                c = *cur;
                if (!is_surrogate_low(c)) {
                    error_fn();
                }
                transcoded_fn(c);
                ++cur;
            }
        }
```

変更後

```cpp
        template <typename Iterator, typename Sentinel, typename TranscodedFn,
                  typename EncodingErrorFn>
        void transcode_codepoint(Iterator& cur, Sentinel,
                                 TranscodedFn transcoded_fn,
                                 EncodingErrorFn error_fn,
                                 is_utf16<true>) const {
            wchar_t c = *cur;
            if (c < 0x20) {
                error_fn();
            }
            if (is_surrogate_low(c)) {
                error_fn();
            }
            transcoded_fn(c);
            ++cur;
            if (is_surrogate_high(c)) {
                c = *cur;
                if (!is_surrogate_low(c)) {
                    error_fn();
                }
                transcoded_fn(c);
                ++cur;
            }
        }
```
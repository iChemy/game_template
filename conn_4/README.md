# Connect Four
<figure>
    <img src="https://upload.wikimedia.org/wikipedia/commons/a/ad/Connect_Four.gif" alt="Connect Four Image"/>
    <figcaption><a href="https://en.wikipedia.org/wiki/Connect_Four">Connect Four - Wikipedia</a> より</figcaption>
</figure>

## 実行方法
`conn_4` ディレクトリ内に移動し以下のコマンドを実行する.
```Bash
$ make
$ ../out/conn_4/main
```

## 実装の特徴
- ゲーム木を構築し深さ優先探索で探索する．
- ビットマップでゲームの盤面を表しており，メモリ効率が良い．
- 評価関数や勝利条件の制約はビット演算のみを利用して実装されている．
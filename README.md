# MeglimathSimulator
とある陣取りゲームのシミュレーションが行えるプログラムです。

## 概要
+ 2対2で行うターン制の陣取りゲームです
+ 数字の書かれたフィールド内で行動します
+ より多くポイントを取得したチームが勝利となります
+ フィールド内で行動するプレイヤーをエージェントと呼びます

# ゲームルール
## フィールド
+ 大きさは最大で12マス×12マスです
+ マス目に区切られており各マスには点数が付与されています
+ マスには-16 ~ 16点の間の点数が付与されます
+ マスの点数は対象となるように配分されます

## 行動
+ 4人のエージェントは同時に行動します
+ エージェントが通ったマスにはタイルが置かれます
+ エージェントは移動、タイル除去、停留のうちいずれかの行動ができます
    - 移動  
        * 周囲８マスのいずれかのマスに進むことができます  
        * 複数のエージェントが同じマスに移動しようとした場合、
        それらの行動は無効になります
    - タイル除去  
        * 周囲8マスのいずれかのマスに置かれたタイルを取り除くことができます  
        * エージェントが留まるマスのタイルは取り除くことができません
    - 停留  
        * 現在いるマスに留まることができます

## 得点
+ チームの得点はタイルポイントと領域ポイントの合計の点数となります
#### タイルポイント
+ 自チームのタイルが置かれているマスの点数の合計得点です

#### 領域ポイント
+ 自チームのタイルによって四方を囲まれた領域の点数の合計です
+ このとき各マスの点数の絶対値を取った点数が加算されます
+ 領域内に相手のタイルが置かれていても点数が加算されます

# 操作方法
### チームA
+ 移動、タイル除去
    - アナログスティックを傾けながら0番目のボタンを押し、方向を決めます
    - タイルのあるなしで移動かタイル除去かを決定します
+ 停留
    - 1番目のボタンを押します

### チームB
+ 移動、タイル除去
    - 右方向から反時計回りに、D, E, W, Q, A, Z, X, Cキーで方向を決めます
    - タイルのあるなしで移動かタイル除去かを決定します
+ 停留
    - Sキーを押します

### ゲーム進行
+ 左クリック
    - ターンを一回進行させます

+ Enterキー
    - 押している間ターンを進行させます

# 画面情報
![demo](https://github.com/Eulerd/MeglimathSimulator/blob/release/media/demo.gif)
+ チームAを青色,チームBを赤色で描画しています
+ 一人目のエージェントを円で、二人目のエージェントをひし形で描画しています
+ 画面右には上から順に
    - チームAのエージェントの行動
    - チームAの取得した合計得点
    - チームBのエージェントの行動
    - チームBの取得した合計得点
    - 現在のターン数  
    のステータスを描画しています
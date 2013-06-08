高橋テトリス
============

過去の遺物です。以下はver0.04のReadmeをMarkdown記法で書きなおしたものです。配布にあたりBGMは削除しました。

# 操作方法（キーボード全面ver）

## メニュー画面など

* 上下キー：選択
* Zキー(ホールドキー)：決定・変更
* 左Ctrlキー(ポーズキー)：戻る

## ゲーム画面

* 左右キー：移動
* 上キー：ハードドロップ（一瞬で下まで落ちる）
* 下キー：高速落下
* Zキー：ホールド
* Xキー：左回転
* Cキー：右回転
* 左Ctrlキー：ポーズ

※以上のボタンはメニュー画面からキーコンフィグできます。　　
※キーボード左面、右面verはキーコンフィグからご覧ください。ちなみに右面はフルキーボードじゃないと操作できません。  
※Escキーを押すと終了します。


# 前回（テスト版ver0.03/0.03a）からの変更点
* 2Pプレイに対応
* ゲームコントローラーに対応
* キーコンフィグに対応
* CPUの強さにレベル4を追加
* CPUのモードに列数優先を追加
* プレイヤー設定の大幅変更
* 得点システムの変更
* オートモードのＣＰＵ思考改善（特に密度優先）
* GAME OVER画面の表示改善
* 回転規則をかなり緩くした
* 高速落下時にブロックが床にめり込むバグを修正
* 自由移動時間中にあり得ないところにブロックが移動するバグを修正
* ブロック出現音（拍手音）の音量を小さくした
* 背景をちょっと濃くした
* ブロックの遊び時間の厳格化
* 回転ボタンを押し続けると永遠にブロックが固定されないバグを解消


# オートモードのレベルについて軽い解説

## レベル４

動体視力検査状態。これを二つ並べたら耳も死ぬ。

## レベル３

前回までのオートモードと概ね同じです。人間業じゃないテトリスを見たいときに。

## レベル２

レベル３・レベル４の思考を人間に見える速度で実演します。のんびりと眺めたいときはコレ。

## レベル１

レベル２よりも少し頭が悪い置き方をします。温かく見守ってあげてください。

## レベル０

レベル１よりもさらに頭が悪い置き方をします。テトリス慣れしてない人がプレイしてる感じ。


# オートモードの思考パターンについても軽い解説

## 密度優先

厄介な穴ボコをなるべく作らないように、また可能な限り消す方針で積んでいきます。

得点は最大。赤棒が長い間来ないと死ぬ。ペントリスは絶対にやらせるな。

## 接地優先

現在積まれているブロックの形状にぴったり合うように積んでいきます。

必要とあれば穴ボコも遠慮なく作る。ペントリスにて本領発揮。

## 列数優先

とりあえず目先のブロックを消すことだけに集中して積んでいきます。

シングル連打。得点も伸びないけど高く積み上げないので安定するのが唯一の取り柄。


# 利用素材

## 効果音

* 効果音源（こうかおんげん）様　http://koukaongen.com/　（一部加工）
* moiz様


# 使用したライブラリの著作権表示

libpngCopyright (c) 1998-2004 Glenn Randers-Pehrson.
zlibCopyright (C) 1995-2004 Jean-loup Gailly and Mark Adler.

***

ogg_static, vorbis_static, vorbisfile_static
Copyright (C) 1994-2002 XIPHOPHORUS Company http://www.xiph.org/ .

Please note that this is only a sample license; authoritative license terms are included with each software bundle. 

c year, Xiph.Org Foundation

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met: 

- Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer. 

- Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution. 

- Neither the name of the Xiph.org Foundation nor the names of its contributors may be used
to endorse or promote products derived from this software without specific prior written permission. 

This software is provided by the copyright holders and contributors “as is” and
any express or implied warranties, including, but not limited to, the implied warranties
of merchantability and fitness for a particular purpose are disclaimed. In no event shall
the foundation or contributors be liable for any direct, indirect, incidental, special,
exemplary, or consequential damages (including, but not limited to, procurement of
substitute goods or services; loss of use, data, or profits; or business interruption)
however caused and on any theory of liability, whether in contract, strict liability,
or tort (including negligence or otherwise) arising in any way out of the use of this
software, even if advised of the possibility of such damage. 

***

Mersenne Twister
Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

3. The name of the author may not be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

![Canzasi-logo](./assets/Canzasi-logo-small-m.png)

# Canzasi

「Canzasi」（かんざし）はArduinoを使ってI2C Slaveデバイスを試作するためのボードです。

# boards

## Canzasi-Prot

ATtiny841を採用した「Canzasi」最初のプロトタイプボードです。
Arduino IDEからISP経由での書き込みに対応しています。

### Concept

- Arduino IDE対応（ISP Programming）
- GROVEコネクタ
- ブレッドボードフレンドリー（1列GPIO）

### Design Data (v0.1)

![schematic(v0.1)](./boards/Prot/v0.1/schematic.png)
![board(v0.1)](./boards/Prot/v0.1/board.png)

[eagle files (v0.1)](./boards/Prot/v0.1/eagle/)

## Canzasi-Wrtr

Canzasi-Protにプログラムを書き込むためのArduino UNO用シールドです。

### Concept

- ミニマル
- Canzasi-Protとの接続にケーブル不要

### Design Data (v0.1)

![schematic(v0.1)](./boards/Wrtr/v0.1/schematic.png)
![board(v0.1)](./boards/Wrtr/v0.1/board.png)

[eagle files (v0.1)](./boards/Wrtr/v0.1/eagle/)

# examples

## [blink](./examples/blink/Canzasi_blink/Canzasi_blink.ino)

Canzasi用のLチカです。
これは単なるLチカで、I2Cデバイスではありません。

## [simpleButtonDevice](./examples/simpleButtonDevice/Canzasi/Canzasi_I2CDataProvider/Canzasi_I2CDataProvider.ino)

Masterからのreadデータを受けてButtonが押されているかどうかを返すサンプルです。    
simpleButtonDeviceの制御テスト用のマスターコードはこちら（[Arduino用](./examples/simpleButtonDevice/Master/Arduino/I2C_MasterReader/I2C_MasterReader.ino)）です。


## [simpleLedDevice](./examples/simpleLedDevice/Canzasi/Canzasi_I2Cblink/Canzasi_I2Cblink.ino)

Masterからのwriteデータを受けてLEDの点灯と消灯を行うサンプルです。    
simpleLedDeviceの制御テスト用のマスターコードはこちら（[Arduino用](./examples/simpleLedDevice/Master/Arduino/I2C_MasterWriter/I2C_MasterWriter.ino)）です。

# Licence

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="クリエイティブ・コモンズ・ライセンス" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/80x15.png" /></a><br />このリポジトリで公開するプログラムソースコードやハードウエア設計情報は <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">クリエイティブ・コモンズ 表示 4.0 国際 ライセンスの下に提供されています。</a>

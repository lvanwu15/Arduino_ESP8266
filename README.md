# Arduino_ESP8266

使用 Arduino 搭配 ESP8266 AT firmware 建立一個簡易 Socket Server，再由 PHP Socket Client 傳送指令給 Arduino，讓 Arduino 依照收到的 `pin` 參數控制繼電器腳位。

## 專案內容

- `Socket_server/Socket_server.ino`：Arduino + ESP8266 Socket Server 程式
- `PHP/Socket_Client.php`：PHP Socket Client 範例
- `image/`：連線畫面、執行結果與電路圖

## Arduino 設定

開啟 `Socket_server/Socket_server.ino`，先修改 Wi-Fi 設定：

```cpp
#define SSID "XXXXX"
#define PASSWORD "XXXXX"
```

預設 Socket Server port 為 `888`：

```cpp
#define SERVER_PORT 888
```

上傳程式後，請從 Serial Monitor 查看 ESP8266 取得的 IP，PHP 端需要使用這個 IP 連線。

## PHP 設定

開啟 `PHP/Socket_Client.php`，修改 `$host` 為 Serial Monitor 顯示的 ESP8266 IP：

```php
$host = "192.168.0.7";
$port = 888;
```

執行範例：

```bash
php Socket_Client.php
```

若放在 Apache/PHP 網站目錄，也可以用網址帶入 pin 指令：

```text
http://localhost/Socket_Client.php?pin=D1120
```

## 指令格式

PHP 會傳送 `pin` 參數給 Arduino：

```text
DmpPs
```

- `D`：固定開頭
- `m`：模式，目前支援 `0` 或 `1`
- `pP`：兩位數腳位，例如 `10`、`11`、`12`、`13`
- `s`：狀態，`1` 為 HIGH，`0` 為 LOW

範例：

- `D0111`：模式 0，控制 pin 11 為 HIGH
- `D0120`：模式 0，控制 pin 12 為 LOW
- `D1120`：模式 1，控制 pin 12 為 LOW

目前 Arduino 程式只允許控制 pin `10`、`11`、`12`、`13`，避免收到錯誤指令時控制到非預期腳位。

## 執行結果

傳送指令後，Arduino Serial Monitor 會顯示連線編號、收到的資料、解析出的模式、腳位與狀態。

![顯示結果](/image/2.jpg)

## 連線與電路圖

一開始啟動連接圖，以 port `888` 為例：

![連接圖](/image/9.jpg)

電路圖：

![電路圖](/image/3.jpg)

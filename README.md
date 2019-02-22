# Arduino_ESP8266
- 使用Arduino結合ESP8266開啟Socket server
- 再藉由PHP開啟的Socket Client連線將直傳給Arduino端做收值的動作
- Arduino端接收到值後再Serial視窗觀看結果，並且觸發Pin11,Pin12繼電器動作
# 檔案內容
# Socket_server資料夾
- Socket_server.ino > Arduino + ESP-8266 程式碼

  需要修改程式碼中
- #define SSID "XXXXX"        <<此為Esp8266需連結上之分享器名稱
- #define PASSWORD  "XXXXX"   <<此為開分享器之密碼
  
-一開始啟動連接圖_以Port888為例

![連接圖](/image/9.jpg)  

# PHP資料夾
- Socket_Client.php > 為PHP端程式碼放在Apache-www資料夾即可使用


- 需要修改程式碼中
![程式碼](/image/8.jpg)
- 紅線部分需參考
![程式碼](/image/1.jpg)

# 執行結果
- 傳送完多個值後Serial視窗會顯示結果
![顯示結果](/image/2.jpg)

# 電路圖
![電路圖](/image/3.jpg)

# Arduino_ESP8266
  使用Arduino結合ESP8266開啟Socket server
  再藉由PHP開啟的Socket Client連線將直傳給Arduino端做收值的動作
# 檔案內容
# Socket_server資料夾
  Socket_server.ino > Arduino + ESP-8266 程式碼

  需要修改程式碼中
  #define SSID "XXXXX"        <<此為Esp8266需連結上之分享器名稱
  #define PASSWORD  "XXXXX"   <<此為開分享器之密碼
  

  
  
  
  
  
  
# PHP資料夾
  Socket_Client.php > 

#include <SoftwareSerial.h>
#include "Timer.h"
SoftwareSerial WifiSerial(4,5);

Timer T1;


#define SSID "XXXXX"
#define PASSWORD  "XXXXX"

String cmdAT = "";
String StrWebMsg="";
int Wifi_State,delaytime;
byte connID;
String WebMsgIPD="";
int GetPin=0,GetPinH=0,GetPinL=0;
int GetMode=0;
int PinState=0;


void setup(void) {
    WifiSerial.begin(9600);
    Serial.begin(9600); 
    
    Serial.print("setup begin\r\n");
    pinMode(10,OUTPUT);
    digitalWrite(10,LOW);
    pinMode(11,OUTPUT);
    digitalWrite(11,LOW);
    pinMode(12,OUTPUT);
    digitalWrite(12,LOW);
    
    T1.every(5, ESP8266_Main);
    sendATcmd("AT+RST",2000); // 重置ESP模組，等待2秒
    
    for (int i=0;i<=10;i++){
    cmdAT ="AT";
    WifiSerial.println(cmdAT);
    if (WifiSerial.find("OK")) {  
    Serial.print("Start+++++++++++++++++++++++++++++++++++\r\n");
    Serial.print("ESP8266 Operation OK\r\n");
    break;
    } else {
    Serial.print("ESP8266 Operation error\r\n");
    }
    }

    for (int i=0;i<=10;i++){
    cmdAT ="AT+CWMODE=1";
    
    WifiSerial.println(cmdAT);
    if (WifiSerial.find("no change")) {  
    Serial.print("Operate to station ok\r\n");
    break;
    } else {
    Serial.print("Operate to station err\r\n");
    }
    }
            for (int i=0;i<=10;i++){
         cmdAT="AT+CWJAP=\"";
         cmdAT+=SSID;
         cmdAT+="\",\"";
         cmdAT+=PASSWORD;
         cmdAT+="\"";
              WifiSerial.println(cmdAT);
           if (WifiSerial.find("OK")){  
              Serial.print("Join AP success \r\n");
              sendATcmd("AT+CIFSR",1000);  //AT+CIFSR     #印出 IP 狀態
            break;
           } else {
             Serial.print("Try to Connectto AP,Loading...\r\n");
           }
          }

         for (int i=0;i<=10;i++){
              cmdAT ="AT+CIPMUX=1";
              WifiSerial.println(cmdAT);
           if (Loding("AT+CWMODE=1")){  
              Serial.print("Set AT+CIPMUX=1 success\r\n");
            break;
           } else {
              Serial.print("Set AT+CIPMUX=1  failure\r\n");
           }
          }

           for (int i=0;i<=10;i++){
               cmdAT ="AT+CIPSERVER=1,888";  //開啟Socket Server在Port888
               WifiSerial.println(cmdAT);
           if (Loding("AT+CIPSERVER=1")){  
              Serial.print("Set port 888  success\r\n");
              Serial.print("ESP8266 configuration Done!\r\n");
              Serial.print("End====================================\r\n");
            break;
           } else {
              Serial.print("Set port 9000  failure\r\n");
              Serial.print("End====================================\r\n");
           }
          }

    
}

void loop()
{
T1.update();
}

void sendATcmd(String cmd, unsigned int time){
    String response = "";  // 接收ESP回應值的變數  
    WifiSerial.println(cmd); // 送出AT命令到ESP模組
    unsigned long timeout = time + millis();
     
    while (WifiSerial.available() || millis() < timeout) {
      while(WifiSerial.available()) {
        char c = WifiSerial.read(); // 接收ESP傳入的字元
        response += c;
      }
    }
 
    Serial.print(response);  // 顯示ESP的回應
}



void ESP8266_Main(){
     int Debugflag=0;
     if(WifiSerial.available()) {
          StrWebMsg="";
               //Just Debug  for get all message from client
               if (Debugflag==1) {
                   while(WifiSerial.available())
                  {
                   StrWebMsg+=(char)WifiSerial.read(); 
                   delay(2);
                  }
                   Serial.println(StrWebMsg);
                    connID=0;
                    cmdAT = "AT+CIPCLOSE=";
                    cmdAT+=connID;   // 附加連線編號
                    sendATcmd(cmdAT,1000);  // 送出「中斷連線」命令
                    connID=1;
                    cmdAT = "AT+CIPCLOSE=";
                    cmdAT+=connID;   // 附加連線編號
                    sendATcmd(cmdAT,1000);  // 送出「中斷連線」命令
                     
               }else if (WifiSerial.find("+IPD,")) {  // 若接收到"+IPD,"，代表有用戶連線了…
                 delay(2);
                 connID = WifiSerial.read();// 讀取連線編號（1~5）並轉成數字[最多 5 個連線] ,48 is ASCII '0'
                 delay(2);
                 connID = connID-48;  // 讀取連線編號（1~5）並轉成數字[最多 5 個連線] ,48 is ASCII '0'
                while(WifiSerial.available())
                 {
                 StrWebMsg+=(char)WifiSerial.read(); 
                 delay(2);
                }
                Serial.print("connID=");
                Serial.println(connID);
                Serial.println(StrWebMsg);

                GetMode=(char)StrWebMsg[15]-48;   //48 is ASCII '0'
                Serial.print("Mode=");
                Serial.println(GetMode);
                 

                switch(GetMode)
                {
                  case 0:
                  {
                GetPinH=(char)StrWebMsg[16]-48;   //48 is ASCII '0', Pin :十位數
                GetPinL=(char)StrWebMsg[17]-48;   //48 is ASCII '0', Pin :個位數
                GetPin=GetPinH*10+GetPinL;
                 
                Serial.print("Pin=");
                Serial.println(GetPin);
 
                PinState=(char)StrWebMsg[18]-48;   //48 is ASCII '0'
                Serial.print("PinStatus=");
                Serial.println(PinState);
                   if(GetPin==12&&PinState==1)
                {
                  digitalWrite(10,1);
                  digitalWrite(11,1);
                  }
                  else if(GetPin==12&&PinState==0)
                  {
                  digitalWrite(10,0);
                  digitalWrite(11,0);
                    }
                   else{
                digitalWrite(GetPin,PinState);
                }
                break;
                    }
                  case 1:
                  {
                GetPinH=(char)StrWebMsg[19]-48;   //48 is ASCII '0', Pin :十位數
                GetPinL=(char)StrWebMsg[20]-48;   //48 is ASCII '0', Pin :個位數
                GetPin=GetPinH*10+GetPinL;
                 
                Serial.print("Pin=");
                Serial.println(GetPin);
 
                PinState=(char)StrWebMsg[21]-48;   //48 is ASCII '0'
                Serial.print("PinStatus=");
                Serial.println(PinState);
                    if(GetPin==13&&PinState==1)
                {
                  digitalWrite(10,1);
                  }
                  else if(GetPin==13&&PinState==0)
                  {
                  digitalWrite(10,0);
                    }
                }
                  }


                
                if(GetMode==0)
                {
                   
                  }
                else if(GetMode==1)
                {
                digitalWrite(GetPin,PinState);
                  }
    
   
                    cmdAT = "AT+CIPCLOSE=";
                    cmdAT+=connID;   // 附加連線編號
                    sendATcmd(cmdAT,500);  // 送出「中斷連線」命令

                    
 
           }
     }
   
}

String get_response() {  //get esp responce without "Serial.find()".
  String response="";  
  char c; 
  while (WifiSerial.available()) {  
    c=WifiSerial.read();
    response.concat(c);   
    delay(10);  
    }
  response.trim();  
  return response;
}


boolean Loding(String state){
  String response=get_response();
  for (int timeout=0 ; timeout<30 ; timeout++)
  {
    if(response.indexOf("OK") != -1 || response.indexOf("no change") != -1) 
    {
        Serial.print(" OK ! ");
        if(timeout>=2){
          Serial.print("This commend waste ");
          Serial.print(timeout/2);
          Serial.println(" sec.");
        }
        else Serial.println("");
        return 1; 
        break;
    }
    else if(timeout==29){ //after 15 sec for wait esp without responce.
      Serial.print(state);
      Serial.println(" fail...\nExit2");
      return 0; 
    }
    else{
      response=get_response(); //reget
      if(timeout==0)
        Serial.print("Wifi Loading.");
      else
        Serial.print(".");
      delay(500);
    }
  }
}


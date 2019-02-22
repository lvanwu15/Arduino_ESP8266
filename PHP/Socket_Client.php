<?php
$data = "GET /?pin=D1120 HTTP/1.1";
//socket
$url = "192.168.0.7:80";
$url_part = parse_url($url);
$host = $url_part["127.0.0.1"];
$address = gethostbyname($host);
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if (!$socket) {
    $err_msg = socket_strerror(socket_last_error($socket));
    socket_close($socket);
    throw new Exception("socket_create() failed:" . $err_msg);
}
$conn = socket_connect($socket, '192.168.0.7', '80');
if (!$conn) {
    $err_msg = socket_strerror(socket_last_error($socket));
    socket_close($socket);
    throw new Exception("socket_connect() failed:" . $err_msg);
}

//傳送資料
$bin_body = pack("a*",$data);
//$bin_body = $data;
$body_len = strlen($bin_body);
//$bin_head = pack("N", $body_len); //unsigned long (always 32 bit, big endian byte order)=>數字轉成一個 4 bytes 的big endian byte order
$bin_data = $bin_body; //4bytes資料本體長度 + 資料本體
$res = socket_write($socket, $bin_data, strlen($bin_data)); //返回成功寫入的bytes數 or false
if (!$res) {
    $err_msg = socket_strerror(socket_last_error($socket));
    socket_close($socket);
    throw new Exception("socket_write() failed:" . $err_msg);
}

//接收資料
$buf = "";
//先取得 4bytes 回應資料本體長度
if (false === ($bytes = socket_recv($socket, $buf, 4, MSG_WAITALL))) { //返回接收到的長度 or false。MSG_WAITALL：阻塞模式，若過程沒異常，一直等到讀到指定長度
    $err_msg = socket_strerror(socket_last_error($socket));
    socket_close($socket);
    throw new Exception("讀取資料長度失敗 socket_recv() failed:" . $err_msg);
}
$len_data = unpack("Nlen", $buf); //N：unsigned long (always 32 bit, big endian byte order)=>解析頭 4 個bytes

//再用取得的資料本體長度，抓回應資料本體
if (false === ($bytes = socket_recv($socket, $buf, $len_data["len"], MSG_WAITALL))) { //返回接收到的長度 or false。MSG_WAITALL：阻塞模式，若過程沒異常，一直等到讀到指定長度
    $err_msg = socket_strerror(socket_last_error($socket));
    socket_close($socket);
    throw new Exception("讀取回應資料本體失敗 socket_recv() failed:" . $err_msg);
}
socket_close($socket);
var_dump($buf);//回應的資料本體
?>

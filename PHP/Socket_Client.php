<?php
$host = "192.168.0.7";  // 修改為 ESP8266 在 Serial Monitor 顯示的 IP
$port = 888;            // 需與 Arduino 端 SERVER_PORT 相同
$pin = $_GET["pin"] ?? "D1120";

if (!preg_match("/^D[01][0-9]{2}[01]$/", $pin)) {
    throw new InvalidArgumentException("pin 格式錯誤，請使用 DmpPs，例如 D1120");
}

$data = "GET /?pin=" . $pin . " HTTP/1.1\r\nHost: " . $host . "\r\nConnection: close\r\n\r\n";

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    $err_msg = socket_strerror(socket_last_error());
    throw new Exception("socket_create() failed:" . $err_msg);
}

$conn = socket_connect($socket, $host, $port);
if (!$conn) {
    $err_msg = socket_strerror(socket_last_error($socket));
    socket_close($socket);
    throw new Exception("socket_connect() failed:" . $err_msg);
}

//傳送資料
$bin_body = pack("a*",$data);
$bin_data = $bin_body;
$written = 0;
$data_len = strlen($bin_data);

while ($written < $data_len) {
    $res = socket_write($socket, substr($bin_data, $written));
    if ($res === false) {
        $err_msg = socket_strerror(socket_last_error($socket));
        socket_close($socket);
        throw new Exception("socket_write() failed:" . $err_msg);
    }

    $written += $res;
}

//接收資料
$buf = "";
socket_set_option($socket, SOL_SOCKET, SO_RCVTIMEO, ["sec" => 2, "usec" => 0]);

if (false !== ($bytes = socket_recv($socket, $buf, 1024, 0)) && $bytes > 0) {
    var_dump($buf);
} else {
    echo "Command sent: " . $pin . PHP_EOL;
}

socket_close($socket);
?>

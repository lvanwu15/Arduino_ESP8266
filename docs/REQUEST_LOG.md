# Request Log

本文件記錄使用者對此專案提出的需求、採取的處理方式與結果。未來每次新增需求或修改專案時，請同步追加紀錄。

## 2026-06-23

### 需求 1：摘要專案並提供調整建議

- 需求內容：使用者提供 GitHub repository `lvanwu15/Arduino_ESP8266`，要求整理專案摘要與改善建議。
- 處理方式：檢視 README、Arduino `.ino` 程式、PHP socket client 與圖片資源。
- 結論：
  - 專案是 Arduino + ESP8266 AT command socket server，搭配 PHP socket client 控制繼電器腳位。
  - 主要問題包含 PHP port 與 Arduino port 不一致、Arduino 固定字元位置解析過於脆弱、PHP URL 解析錯誤、缺少安全機制與 README 說明不足。
- 結果：已回覆專案摘要與調整建議。

### 需求 2：調整專案並重新 push

- 需求內容：使用者要求依建議調整專案並重新 push 到 GitHub。
- 處理方式：
  - 修改 `Socket_server/Socket_server.ino`，改為解析 `pin=` 參數，並加入 pin 白名單。
  - 修改 `PHP/Socket_Client.php`，修正 host/port 設定、pin 格式驗證與 socket 回應處理。
  - 重寫 `README.md`，補上設定、執行與指令格式。
- 結果：
  - 已 commit：`16f575a Improve socket command handling`
  - 已 push 到 `origin/master`
- 驗證：
  - `git diff --check` 通過。
  - 本機未安裝 `php` 與 `arduino-cli`，因此未做語法 lint 或 Arduino 編譯驗證。

### 需求 3：記錄修改紀錄與每次需求

- 需求內容：使用者要求記錄此專案的修改紀錄與每次需求，未來有新異動時協助建立異動 Log。
- 處理方式：
  - 新增 `CHANGELOG.md` 記錄程式與文件異動。
  - 新增 `docs/REQUEST_LOG.md` 記錄需求、處理方式與結果。
  - 在 `README.md` 加入紀錄文件連結。
- 結果：本次需求紀錄已建立，未來異動應同步更新這兩份文件。

## 2026-06-25

### 需求 4：搬移專案到 `/Users/yifingwu/Project`

- 需求內容：使用者要求將此專案搬移到 `/Users/yifingwu/Project`。
- 處理方式：
  - 確認 `/Users/yifingwu/Project` 已存在。
  - 確認目標位置沒有既有 `Arduino_ESP8266` 子資料夾。
  - 從 GitHub clone 最新 repository 到 `/Users/yifingwu/Project/Arduino_ESP8266`。
- 結果：專案已建立在 `/Users/yifingwu/Project/Arduino_ESP8266`。
- 驗證：
  - 已確認檔案包含 `README.md`、`CHANGELOG.md`、`docs/REQUEST_LOG.md`、`PHP/Socket_Client.php`、`Socket_server/Socket_server.ino` 與圖片資源。
  - 已確認新位置 Git branch 為 `master`，並對齊 `origin/master`。
  - 已確認 remote 為 `https://github.com/lvanwu15/Arduino_ESP8266.git`。

## 維護規則

- 每次程式或文件異動，更新 `CHANGELOG.md`。
- 每次使用者提出新需求並完成處理，更新 `docs/REQUEST_LOG.md`。
- 若有執行驗證，記錄實際指令與結果。
- 若無法驗證，記錄原因，例如缺少工具、缺少硬體或缺少憑證。

# Changelog

本文件記錄此專案的程式、文件與設定異動。未來每次修改專案時，請同步更新本文件。

## 2026-06-23

### Added

- 新增專案修改紀錄文件 `CHANGELOG.md`。
- 新增需求紀錄文件 `docs/REQUEST_LOG.md`。

### Changed

- 調整 Arduino socket 指令處理邏輯，改為解析 HTTP 內容中的 `pin=` 參數，不再依賴固定字元位置。
- 新增 `SERVER_PORT` 設定，預設使用 port `888`。
- Arduino 端新增 pin 白名單檢查，目前允許 `10`、`11`、`12`、`13`。
- PHP client 改為連線到 port `888`，與 Arduino 端設定一致。
- PHP client 新增 `pin` 格式驗證，支援 `DmpPs` 格式，例如 `D1120`。
- README 重寫為較完整的設定、執行方式與指令格式說明。

### Fixed

- 修正 README 說明 port `888`，但 PHP 範例連線 port `80` 的不一致問題。
- 修正 PHP `parse_url()` 使用方式錯誤，以及 `$url_part["127.0.0.1"]` 這類無效 key。
- 移除 PHP client 對 4-byte 長度回應的等待，避免 Arduino 未回應資料時阻塞。

### Verification

- 已執行 `git diff --check`，沒有 whitespace 或 diff 格式問題。
- 本機環境沒有 `php`，未執行 PHP lint。
- 本機環境沒有 `arduino-cli`，未執行 Arduino 編譯驗證。

## 2026-06-25

### Changed

- 將專案工作目錄搬移到 `/Users/yifingwu/Project/Arduino_ESP8266`。

### Verification

- 已確認新位置的 Git remote 為 `https://github.com/lvanwu15/Arduino_ESP8266.git`。
- 已確認新位置目前位於 `master`，且對齊 `origin/master`。

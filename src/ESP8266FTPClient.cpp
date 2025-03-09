#include "ESP8266FTPClient.h"

ESP8266FTPClient::ESP8266FTPClient() {
    _server = "";
    _user = "";
    _pass = "";
    _port = 21;
}

ESP8266FTPClient::ESP8266FTPClient(const char* server, const char* user, const char* pass, int port) {
    begin(server, user, pass, port);
}

bool ESP8266FTPClient::begin(const char* server, const char* user, const char* pass, int port) {
    _server = server;
    _user = user;
    _pass = pass;
    _port = port;
    return connect();
}

bool ESP8266FTPClient::connect() {
    Serial.println("🔌 Kết nối đến FTP Server...");

    if (_ftpClient.connect(_server, _port)) {
        sendCommand("USER " + String(_user));
        sendCommand("PASS " + String(_pass));
        return true;
    } else {
        Serial.println("❌ Không thể kết nối FTP!");
        return false;
    }
}

bool ESP8266FTPClient::isConnected() {
    return _ftpClient.connected();
}

bool ESP8266FTPClient::enterPassiveMode() {
    if (!_ftpClient.connected()) {
        Serial.println("❌ FTP chưa kết nối!");
        return false;
    }

    sendCommand("PASV");
    String response = _ftpClient.readStringUntil('\n');
    Serial.println(response);

    int ip1, ip2, ip3, ip4, p1, p2;
    if (sscanf(response.c_str(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)", &ip1, &ip2, &ip3, &ip4, &p1, &p2) != 6) {
        Serial.println("❌ Lỗi phân tích PASV!");
        return false;
    }

    int dataPort = (p1 * 256) + p2;
    String dataIP = String(ip1) + "." + String(ip2) + "." + String(ip3) + "." + String(ip4);

    Serial.println("📡 Data IP: " + dataIP + " | Port: " + String(dataPort));
    return _dataClient.connect(dataIP.c_str(), dataPort);
}

bool ESP8266FTPClient::uploadFile(String fileName, String content) {
    if (!enterPassiveMode()) return false;

    sendCommand("STOR " + fileName);
    _dataClient.print(content);
    _dataClient.stop();

    Serial.println("✅ File đã được tải lên!");
    return true;
}

String ESP8266FTPClient::downloadFile(String fileName) {
    if (!enterPassiveMode()) return "";

    sendCommand("RETR " + fileName);
    String fileData = _dataClient.readString();
    _dataClient.stop();

    Serial.println("📥 Tải file về thành công!");
    return fileData;
}

bool ESP8266FTPClient::deleteFile(String fileName) {
    sendCommand("DELE " + fileName);
    Serial.println("🗑️ File đã bị xóa!");
    return true;
}

void ESP8266FTPClient::listFiles() {
    if (!enterPassiveMode()) return;

    sendCommand("LIST");
    while (_dataClient.connected() && _dataClient.available()) {
        Serial.write(_dataClient.read());
    }
    _dataClient.stop();
}

bool ESP8266FTPClient::available() {
    return _ftpClient.available();
}

String ESP8266FTPClient::getFileName() {
    return _ftpClient.readStringUntil(' ');
}

bool ESP8266FTPClient::isDirectory() {
    String response = _ftpClient.readStringUntil('\n');
    return response.startsWith("d");
}

void ESP8266FTPClient::sendCommand(String command) {
    if (!_ftpClient.connected()) {
        Serial.println("❌ Không thể gửi lệnh, FTP chưa kết nối!");
        return;
    }

    _ftpClient.print(command + "\r\n");
    Serial.println("> " + command);
    delay(100);

    while (_ftpClient.available()) {
        Serial.println(_ftpClient.readStringUntil('\n'));
    }
}

void ESP8266FTPClient::close() {
    sendCommand("QUIT");
    _ftpClient.stop();
    Serial.println("🔌 Đã thoát FTP.");
}
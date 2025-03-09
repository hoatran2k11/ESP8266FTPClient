#ifndef ESP8266FTPClient_H
#define ESP8266FTPClient_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

class ESP8266FTPClient {
public:
    // Constructor mới có thêm tham số port, và cả constructor mặc định
    ESP8266FTPClient();
    ESP8266FTPClient(const char* server, const char* user, const char* pass, int port = 21);

    // Khởi động kết nối FTP
    bool begin(const char* server, const char* user, const char* pass, int port = 21);
    bool connect();
    bool isConnected();
    
    // Quản lý file
    bool uploadFile(String fileName, String content);
    String downloadFile(String fileName);
    bool deleteFile(String fileName);
    void listFiles();
    bool available();
    String getFileName();
    bool isDirectory();

    // Đóng kết nối
    void close();

private:
    const char* _server;
    const char* _user;
    const char* _pass;
    int _port;
    
    WiFiClient _ftpClient;
    WiFiClient _dataClient;

    bool enterPassiveMode();
    void sendCommand(String command);
};

#endif
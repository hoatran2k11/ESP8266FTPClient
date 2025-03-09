#include <ESP8266FTPClient.h>

const char* ssid = "Your_WiFi_SSID";
const char* password = "Your_WiFi_Password";
const char* ftp_server = "ftp.example.com";
const char* ftp_user = "your_ftp_user";
const char* ftp_pass = "your_ftp_password";

ESP8266FTPClient ftp(ftp_server, ftp_user, ftp_pass);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.print("🔗 Kết nối WiFi...");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n✅ WiFi đã kết nối!");

    if (ftp.connect()) {
        ftp.uploadFile("test.txt", "Hello từ ESP8266 FTP Client!");
        String content = ftp.downloadFile("test.txt");
        Serial.println("Nội dung file: " + content);
        ftp.deleteFile("test.txt");
        ftp.listFiles();
        ftp.close();
    }
}

void loop() {
}
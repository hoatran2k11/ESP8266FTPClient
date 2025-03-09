# 📡 ESP8266 FTP Client

![Arduino](https://img.shields.io/badge/Arduino-ESP8266-blue.svg) ![GitHub stars](https://img.shields.io/github/stars/hoatran2k11/ESP8266FTPClient?style=social) ![GitHub license](https://img.shields.io/github/license/hoatran2k11/ESP8266FTPClient)

**ESP8266 FTP Client** là thư viện giúp ESP8266 kết nối đến **FTP Server** để tải lên, tải xuống, xóa, đổi tên và quản lý file một cách dễ dàng! 🚀  

## ✨ Tính năng
✅ Kết nối với FTP Server bằng tài khoản **username/password** 🔐  
✅ Hỗ trợ **upload / download file** từ server ⬆️⬇️  
✅ Liệt kê thư mục và file trên server 📂  
✅ Đổi tên và xóa file từ ESP8266 ✂️  
✅ Hỗ trợ các **lệnh FTP chuẩn** 🛠  

---

## 📦 Cài đặt
Bạn có thể cài đặt thư viện theo 2 cách:

### **Cách 1: Cài từ GitHub**
1. Clone repo về máy:
   ```sh
   git clone https://github.com/hoatran2k11/ESP8266FTPClient.git
   ```
2. Copy thư mục `ESP8266FTPClient` vào thư mục `libraries/` của Arduino IDE.

### **Cách 2: Cài từ Arduino IDE**
1. Mở **Arduino IDE**  
2. Vào **Sketch** > **Include Library** > **Add .ZIP Library...**  
3. Chọn file ZIP của thư viện và nhấn **Open**  

---

## 📜 Cách sử dụng

### 🔹 **1. Khởi tạo FTP Client**
```cpp
#include <ESP8266FTPClient.h>

ESP8266FTPClient ftp;

void setup() {
    Serial.begin(115200);
    ftp.begin("ftp.example.com", "username", "password");
}
```

---

### 🔹 **2. Tải file lên FTP Server**
```cpp
ftp.upload("/local/path/file.txt", "/remote/path/file.txt");
```

---

### 🔹 **3. Tải file từ FTP Server**
```cpp
ftp.download("/remote/path/file.txt", "/local/path/file.txt");
```

---

### 🔹 **4. Xóa file trên FTP Server**
```cpp
ftp.remove("/remote/path/file.txt");
```

---

## 📷 Demo
🖥️ **Giao diện Serial Monitor:**  
```
Connecting to FTP Server...
Connected! 🎉
Uploading file.txt... ✅ Success!
Downloading file.txt... ✅ Success!
```

---

## 📚 API - Lệnh FTP Hỗ Trợ
| Lệnh | Chức năng |
|------|----------|
| `upload(file, path)` | Upload file lên FTP |
| `download(path, file)` | Tải file từ FTP |
| `remove(path)` | Xóa file trên FTP |
| `rename(old, new)` | Đổi tên file |
| `list(path)` | Liệt kê file trong thư mục |

---

## 🔗 Thông tin liên hệ  
📩 **Tác giả:** [hoatran2k11](https://github.com/hoatran2k11)  
🌟 Nếu bạn thấy thư viện hữu ích, **hãy ấn 🌟 Star repo** để ủng hộ nhé!  

---

**🚀 Happy Coding! 💻🔥**

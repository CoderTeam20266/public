# Hướng dẫn sử dụng mã hóa và giải mã file lớn với rsa, cặp khóa 

## **1. Cài đặt OpenSSL**

### **Ubuntu**
1. **Cài đặt OpenSSL**:
```bash
   sudo apt update
   sudo apt install openssl libssl-dev
```
2. **Kiểm tra phiên bản OpenSSL**:
```bash
   openssl version
```
3. **Tạo cặp khóa, mật khẩu mã hóa khóa**:
```bash
   openssl genpkey -algorithm RSA -out private_key.pem -pkeyopt rsa_keygen_bits:2048 -passout pass:<mật khẩu>
```
      Tạo khóa không mật khẩu:
```bash
      openssl genpkey -algorithm RSA -out private_key.pem -pkeyopt rsa_keygen_bits:2048
```
      Thêm mật khẩu cho khóa riêng 
      OpenSSL sẽ yêu cầu bạn nhập một mật khẩu để bảo vệ khóa riêng. Bạn sẽ phải nhập mật khẩu 2 lần (một lần để xác nhận)):
```bash
      openssl genpkey -algorithm RSA -out private_key.pem -pkeyopt rsa_keygen_bits:2048 -aes256
```
4. **Kiểm tra file mã hóa: Sử dụng checksum (SHA256) để đảm bảo tính toàn vẹn của file**:
```bash
   sha256sum <file>
```
### **Windows** ###
1. **Tải xuống OpenSSL**:
   Truy cập [https://openssl-library.org/source/]. Hoặc bản đã dịch: https://slproweb.com/products/Win32OpenSSL.html
   Tải phiên bản phù hợp (Win64 hoặc Win32).
2. **Cài đặt OpenSSL**:
   Chạy file cài đặt .exe.
   Chọn "Copy OpenSSL DLLs to The Windows System Directory".
   Ghi nhớ đường dẫn thư mục cài đặt.
3. **Cấu hình biến môi trường (PATH)**:
   Thêm thư mục bin của OpenSSL vào PATH:
      Mở System Properties → Advanced → Environment Variables.
      Thêm đường dẫn, ví dụ: C:\OpenSSL-Win64\bin.
4. **Kiểm tra cài đặt**:
```cmd
   openssl version
```
   Kết quả sẽ hiển thị phiên bản OpenSSL đã cài đặt.
## **2. Tạo cặp khóa RSA**
1. **Tạo khóa riêng (private key)**:
```bash
   openssl genpkey -algorithm RSA -out private_key.pem -pkeyopt rsa_keygen_bits:2048
```
   File private_key.pem sẽ được tạo trong thư mục hiện tại.

2. **Tạo khóa công khai (public key)**:
```bash
   openssl rsa -pubout -in private_key.pem -out public_key.pem
```
   File public_key.pem được tạo từ khóa riêng.

3. **Kiểm tra nội dung khóa (tuỳ chọn)**:
Xem nội dung khóa riêng:
```bash
   openssl rsa -in private_key.pem -text -noout
```
Xem nội dung khóa công khai:
```bash
   openssl rsa -in public_key.pem -pubin -text -noout
```
## **3. Cài đặt Python và thư viện**
**Cài đặt Python**
Ubuntu:
```bash
   sudo apt update
   sudo apt install python3 python3-pip
```

Windows:
   *Tải Python từ https://www.python.org/downloads/.
   *Trong quá trình cài đặt, chọn Add Python to PATH.
   *Kiểm tra cài đặt:
```bash
   python3 --version  # Ubuntu
   python --version   # Windows
```
*Cài đặt thư viện cần thiết:
   Chạy lệnh sau để cài thư viện cryptography:
```bash
   pip install cryptography
```
## **4. Cài đặt trình biên dịch C++**
**Ubuntu**
1. **Cài đặt trình biên dịch:**
```bash
   sudo apt update
   sudo apt install build-essential
   sudo apt install libssl-dev
```
2. **Kiểm tra cài đặt:**
```bash
   g++ --version
```
**Windows**
1. **Tải và cài đặt MinGW-w64.**
2. **Thêm đường dẫn MinGW (bin) vào PATH.**
3, **Kiểm tra cài đặt:**
```cmd
   g++ --version
```
## **5. Compile và chạy chương trình**
**Python**
1. **Mã hóa file**:
```bash
   python encrypt.py
```
Nhập các tham số cần thiết khi được yêu cầu:
   Đường dẫn tới file khóa công khai.
   Đường dẫn file cần mã hóa.
   Đường dẫn file mã hóa đầu ra.
2. **Giải mã file**:
```
```bash
   python decrypt.py
```
Nhập các tham số cần thiết khi được yêu cầu:
   Đường dẫn tới file khóa riêng.
   Đường dẫn file mã hóa.
   Đường dẫn file đầu ra sau khi giải mã.

**C++**
1. **Compile mã hóa**:
```bash
   g++ -o encrypt encrypt.cpp -lssl -lcrypto
```
2. **Chạy chương trình**:
```bash
   ./encrypt <khoa_cong_khai.pem> <file_can_ma_hoa> <file_ket_qua>
```
3. **Compile giải mã**:
```bash
   g++ -o decrypt decrypt.cpp -lssl -lcrypto
```
4. **Chạy chương trình**:
```bash
   ./decrypt <khoa_rieng.pem> <file_ma_hoa> <file_ket_qua>
```
## **6. Tạo cặp khóa và Lưu ý bảo mật và **
*Bảo vệ khóa riêng: File private_key.pem không nên chia sẻ hoặc lưu trên máy không an toàn.
*Mật khẩu file: Nếu thêm mật khẩu vào khóa riêng, hãy nhớ sử dụng tham số -passout pass:<mật khẩu> khi tạo khóa
*Giải mã và cho luôn vao data-set




"""
Chương trình mã hóa file lớn bằng Python.
Yêu cầu cài đặt:
  - cryptography: pip install cryptography
"""

import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.primitives.padding import PKCS7
from cryptography.hazmat.backends import default_backend
import secrets

def generate_aes_key():
    """Tạo khóa AES 256-bit ngẫu nhiên"""
    return secrets.token_bytes(32)

def encrypt_file(public_key_path, input_file_path, output_file_path):
    print("Đang đọc khóa công khai...")
    with open(public_key_path, "rb") as key_file:
        public_key = serialization.load_pem_public_key(key_file.read())
    
    print("Đang tạo khóa AES ngẫu nhiên...")
    aes_key = generate_aes_key()

    print("Đang mã hóa khóa AES bằng RSA...")
    encrypted_aes_key = public_key.encrypt(
        aes_key,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )

    print("Đang khởi tạo AES với chế độ CBC...")
    iv = secrets.token_bytes(16)
    cipher = Cipher(algorithms.AES(aes_key), modes.CBC(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    padder = PKCS7(algorithms.AES.block_size).padder()

    print("Đang đọc dữ liệu từ file...")
    with open(input_file_path, "rb") as input_file:
        data = input_file.read()

    print("Đang thêm padding và mã hóa dữ liệu...")
    padded_data = padder.update(data) + padder.finalize()
    encrypted_data = encryptor.update(padded_data) + encryptor.finalize()

    print("Đang ghi dữ liệu mã hóa ra file...")
    with open(output_file_path, "wb") as output_file:
        output_file.write(len(encrypted_aes_key).to_bytes(4, "big"))
        output_file.write(encrypted_aes_key)
        output_file.write(iv)
        output_file.write(encrypted_data)

    print(f"Mã hóa thành công! File đã lưu tại: {output_file_path}")

if __name__ == "__main__":
    public_key_path = input("Nhập đường dẫn tới file khóa công khai: ").strip()
    input_file_path = input("Nhập đường dẫn tới file cần mã hóa: ").strip()
    output_file_path = input("Nhập đường dẫn tới file mã hóa: ").strip()
    try:
        encrypt_file(public_key_path, input_file_path, output_file_path)
    except Exception as e:
        print(f"Lỗi khi mã hóa: {e}")

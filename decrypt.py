"""
Chương trình giải mã file lớn bằng Python.
Yêu cầu cài đặt:
  - cryptography: pip install cryptography
"""

import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.primitives.padding import PKCS7
from cryptography.hazmat.backends import default_backend

def decrypt_file(private_key_path, input_file_path, output_file_path):
    print("Đang đọc khóa riêng...")
    with open(private_key_path, "rb") as key_file:
        private_key = serialization.load_pem_private_key(key_file.read(), password=None)

    print("Đang đọc dữ liệu từ file mã hóa...")
    with open(input_file_path, "rb") as input_file:
        key_length = int.from_bytes(input_file.read(4), "big")
        encrypted_aes_key = input_file.read(key_length)
        iv = input_file.read(16)
        encrypted_data = input_file.read()

    print("Đang giải mã khóa AES bằng RSA...")
    aes_key = private_key.decrypt(
        encrypted_aes_key,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )

    print("Đang giải mã dữ liệu bằng AES...")
    cipher = Cipher(algorithms.AES(aes_key), modes.CBC(iv), backend=default_backend())
    decryptor = cipher.decryptor()
    unpadder = PKCS7(algorithms.AES.block_size).unpadder()

    padded_data = decryptor.update(encrypted_data) + decryptor.finalize()
    data = unpadder.update(padded_data) + unpadder.finalize()

    print("Đang ghi dữ liệu đã giải mã ra file...")
    with open(output_file_path, "wb") as output_file:
        output_file.write(data)

    print(f"Giải mã thành công! File đã lưu tại: {output_file_path}")

if __name__ == "__main__":
    private_key_path = input("Nhập đường dẫn tới file khóa riêng: ").strip()
    input_file_path = input("Nhập đường dẫn tới file mã hóa: ").strip()
    output_file_path = input("Nhập đường dẫn tới file giải mã: ").strip()
    try:
        decrypt_file(private_key_path, input_file_path, output_file_path)
    except Exception as e:
        print(f"Lỗi khi giải mã: {e}")

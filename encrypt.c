// Chương trình mã hóa file lớn bằng C++
// Yêu cầu thư viện: OpenSSL

#include <iostream>
#include <fstream>
#include <vector>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

void handle_openssl_error() {
    ERR_print_errors_fp(stderr);
    exit(1);
}

std::vector<unsigned char> read_file(const std::string &file_name) {
    std::ifstream file(file_name, std::ios::binary);
    if (!file) throw std::runtime_error("Không thể mở file: " + file_name);
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

void write_file(const std::string &file_name, const std::vector<unsigned char> &data) {
    std::ofstream file(file_name, std::ios::binary);
    if (!file) throw std::runtime_error("Không thể ghi file: " + file_name);
    file.write(reinterpret_cast<const char *>(data.data()), data.size());
}

std::vector<unsigned char> generate_aes_key(int size) {
    std::vector<unsigned char> key(size);
    if (!RAND_bytes(key.data(), size)) handle_openssl_error();
    return key;
}

void encrypt_file(const std::string &public_key_file, const std::string &input_file, const std::string &output_file) {
    std::cout << "Đang đọc khóa công khai..." << std::endl;
    FILE *key_file = fopen(public_key_file.c_str(), "r");
    if (!key_file) throw std::runtime_error("Không thể mở khóa công khai: " + public_key_file);
    RSA *rsa = PEM_read_RSA_PUBKEY(key_file, nullptr, nullptr, nullptr);
    fclose(key_file);
    if (!rsa) handle_openssl_error();

    std::cout << "Đang tạo khóa AES ngẫu nhiên..." << std::endl;
    std::vector<unsigned char> aes_key = generate_aes_key(32);

    std::cout << "Đang mã hóa khóa AES bằng RSA..." << std::endl;
    std::vector<unsigned char> encrypted_aes_key(RSA_size(rsa));
    int encrypted_key_length = RSA_public_encrypt(
        aes_key.size(), aes_key.data(), encrypted_aes_key.data(), rsa, RSA_PKCS1_OAEP_PADDING);
    RSA_free(rsa);
    if (encrypted_key_length == -1) handle_openssl_error();

    std::cout << "Đang khởi tạo AES với chế độ CBC..." << std::endl;
    std::vector<unsigned char> iv(16);
    if (!RAND_bytes(iv.data(), iv.size())) handle_openssl_error();
    AES_KEY aes_encrypt_key;
    AES_set_encrypt_key(aes_key.data(), 256, &aes_encrypt_key);

    std::cout << "Đang đọc dữ liệu từ file..." << std::endl;
    std::vector<unsigned char> data = read_file(input_file);

    std::cout << "Đang thêm padding và mã hóa dữ liệu..." << std::endl;
    size_t padding = AES_BLOCK_SIZE - (data.size() % AES_BLOCK_SIZE);
    data.insert(data.end(), padding, padding);

    std::vector<unsigned char> encrypted_data(data.size());
    AES_cbc_encrypt(data.data(), encrypted_data.data(), data.size(), &aes_encrypt_key, iv.data(), AES_ENCRYPT);

    std::cout << "Đang ghi dữ liệu mã hóa ra file..." << std::endl;
    std::ofstream output(output_file, std::ios::binary);
    if (!output) throw std::runtime_error("Không thể ghi file: " + output_file);

    uint32_t encrypted_key_size = encrypted_key_length;
    output.write(reinterpret_cast<const char *>(&encrypted_key_size), sizeof(encrypted_key_size));
    output.write(reinterpret_cast<const char *>(encrypted_aes_key.data()), encrypted_key_length);
    output.write(reinterpret_cast<const char *>(iv.data()), iv.size());
    output.write(reinterpret_cast<const char *>(encrypted_data.data()), encrypted_data.size());

    std::cout << "Mã hóa thành công! File đã lưu tại: " << output_file << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Cách sử dụng: " << argv[0] << " <khoa_cong_khai.pem> <file_can_ma_hoa> <file_ket_qua>" << std::endl;
        return 1;
    }

    try {
        encrypt_file(argv[1], argv[2], argv[3]);
    } catch (const std::exception &e) {
        std::cerr << "Lỗi: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

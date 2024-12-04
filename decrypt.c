// Chương trình giải mã file lớn bằng C++
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

std::vector<unsigned char> decrypt_aes(
    const std::vector<unsigned char> &encrypted_data,
    const unsigned char *aes_key,
    const unsigned char *iv) {
    AES_KEY aes_decrypt_key;
    AES_set_decrypt_key(aes_key, 256, &aes_decrypt_key);

    std::vector<unsigned char> decrypted_data(encrypted_data.size());
    AES_cbc_encrypt(
        encrypted_data.data(), decrypted_data.data(), encrypted_data.size(), &aes_decrypt_key,
        const_cast<unsigned char *>(iv), AES_DECRYPT);

    size_t padding = decrypted_data.back();
    decrypted_data.resize(decrypted_data.size() - padding);

    return decrypted_data;
}

void decrypt_file(const std::string &private_key_file, const std::string &input_file, const std::string &output_file) {
    std::cout << "Đang đọc khóa riêng..." << std::endl;
    FILE *key_file = fopen(private_key_file.c_str(), "r");
    if (!key_file) throw std::runtime_error("Không thể mở khóa riêng: " + private_key_file);
    RSA *rsa = PEM_read_RSAPrivateKey(key_file, nullptr, nullptr, nullptr);
    fclose(key_file);
    if (!rsa) handle_openssl_error();

    std::cout << "Đang đọc dữ liệu từ file mã hóa..." << std::endl;
    std::ifstream input(input_file, std::ios::binary);
    if (!input) throw std::runtime_error("Không thể mở file mã hóa: " + input_file);

    uint32_t encrypted_key_size;
    input.read(reinterpret_cast<char *>(&encrypted_key_size), sizeof(encrypted_key_size));

    std::vector<unsigned char> encrypted_aes_key(encrypted_key_size);
    input.read(reinterpret_cast<char *>(encrypted_aes_key.data()), encrypted_key_size);

    std::vector<unsigned char> iv(16);
    input.read(reinterpret_cast<char *>(iv.data()), iv.size());

    std::vector<unsigned char> encrypted_data(
        (std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

    std::cout << "Đang giải mã khóa AES bằng RSA..." << std::endl;
    std::vector<unsigned char> aes_key(RSA_size(rsa));
    int aes_key_length = RSA_private_decrypt(
        encrypted_aes_key.size(), encrypted_aes_key.data(), aes_key.data(), rsa, RSA_PKCS1_OAEP_PADDING);
    RSA_free(rsa);
    if (aes_key_length == -1) handle_openssl_error();
    aes_key.resize(aes_key_length);

    std::cout << "Đang giải mã dữ liệu bằng AES..." << std::endl;
    std::vector<unsigned char> decrypted_data = decrypt_aes(encrypted_data, aes_key.data(), iv.data());

    std::cout << "Đang ghi dữ liệu đã giải mã ra file..." << std::endl;
    write_file(output_file, decrypted_data);

    std::cout << "Giải mã thành công! File đã lưu tại: " << output_file << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Cách sử dụng: " << argv[0] << " <khoa_rieng.pem> <file_ma_hoa> <file_ket_qua>" << std::endl;
        return 1;
    }

    try {
        decrypt_file(argv[1], argv[2], argv[3]);
    } catch (const std::exception &e) {
        std::cerr << "Lỗi: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

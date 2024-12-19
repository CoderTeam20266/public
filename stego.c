//sudo apt update
//sudo apt install build-essential
//sudo apt install libopencv-dev
//gcc stego.c -o steganography `pkg-config --cflags --libs opencv4`


#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void Encode(const string& src, const string& message, const string& dest) {
    try {
        Mat img = imread(src, IMREAD_UNCHANGED);
        if (img.empty()) {
            throw runtime_error("Không thể đọc hình ảnh nguồn.");
        }

        int channels = img.channels();
        if (channels != 3 && channels != 4) {
            throw runtime_error("Chế độ hình ảnh không được hỗ trợ! Chỉ sử dụng hình ảnh RGB hoặc RGBA.");
        }

        int total_pixels = img.rows * img.cols;
        string msg = message + "$#@%6&";
        string b_message;
        for (char c : msg) {
            b_message += bitset<8>(c).to_string();
        }

        int req_pixels = b_message.size();
        if (req_pixels > total_pixels * 3) {
            throw runtime_error("LỖI: Cần một hình ảnh lớn hơn để mã hóa thông điệp này.");
        }

        int index = 0;
        for (int i = 0; i < img.rows; ++i) {
            for (int j = 0; j < img.cols; ++j) {
                Vec3b& pixel = img.at<Vec3b>(i, j);
                for (int k = 0; k < 3; ++k) { // Chỉ sửa đổi 3 kênh đầu tiên (RGB)
                    if (index < req_pixels) {
                        bitset<8> bits(pixel[k]);
                        bits[0] = b_message[index] - '0';
                        pixel[k] = static_cast<uchar>(bits.to_ulong());
                        ++index;
                    }
                }
            }
        }

        if (!imwrite(dest, img)) {
            throw runtime_error("Không thể lưu hình ảnh đích.");
        }

        cout << "Mã hóa hình ảnh thành công" << endl;
    } catch (const exception& e) {
        cerr << "Đã xảy ra lỗi: " << e.what() << endl;
    }
}

void Decode(const string& src) {
    try {
        Mat img = imread(src, IMREAD_UNCHANGED);
        if (img.empty()) {
            throw runtime_error("Không thể đọc hình ảnh nguồn.");
        }

        int channels = img.channels();
        if (channels != 3 && channels != 4) {
            throw runtime_error("Chế độ hình ảnh không được hỗ trợ! Chỉ sử dụng hình ảnh RGB hoặc RGBA.");
        }

        string hidden_bits;
        for (int i = 0; i < img.rows; ++i) {
            for (int j = 0; j < img.cols; ++j) {
                Vec3b pixel = img.at<Vec3b>(i, j);
                for (int k = 0; k < 3; ++k) {
                    bitset<8> bits(pixel[k]);
                    hidden_bits += bits[0] ? '1' : '0';
                }
            }
        }

        if (hidden_bits.size() % 8 != 0) {
            throw runtime_error("Độ dài hidden_bits không hợp lệ, không thể giải mã thông điệp.");
        }

        string message;
        for (size_t i = 0; i < hidden_bits.size(); i += 8) {
            char c = static_cast<char>(bitset<8>(hidden_bits.substr(i, 8)).to_ulong());
            message += c;
            if (message.size() >= 6 && message.substr(message.size() - 6) == "$#@%6&") {
                break;
            }
        }

        if (message.size() >= 6 && message.substr(message.size() - 6) == "$#@%6&") {
            cout << "Thông điệp ẩn: " << message.substr(0, message.size() - 6) << endl;
        } else {
            cout << "Không tìm thấy thông điệp ẩn" << endl;
        }
    } catch (const exception& e) {
        cerr << "Đã xảy ra lỗi: " << e.what() << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Sử dụng: " << argv[0] << " [encode/decode] các_tham_số" << endl;
        return 1;
    }

    string command = argv[1];

    if (command == "encode") {
        if (argc != 5) {
            cout << "Sử dụng: " << argv[0] << " encode đường_dẫn_hình_ảnh_nguồn thông_điệp đường_dẫn_hình_ảnh_đích" << endl;
            return 1;
        }
        string src = argv[2];
        string message = argv[3];
        string dest = argv[4];
        cout << "Đang mã hóa..." << endl;
        Encode(src, message, dest);
    } else if (command == "decode") {
        if (argc != 3) {
            cout << "Sử dụng: " << argv[0] << " decode đường_dẫn_hình_ảnh_nguồn" << endl;
            return 1;
        }
        string src = argv[2];
        cout << "Đang giải mã..." << endl;
        Decode(src);
    } else {
        cout << "Lệnh không hợp lệ. Chỉ hỗ trợ 'encode' hoặc 'decode'." << endl;
        return 1;
    }

    return 0;
}

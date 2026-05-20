# ![Note](https://img.icons8.com/fluency/24/note.png) NOTE

Repository này dùng để ghi chú, tổng hợp và chia sẻ kiến thức về:

- Kiến trúc AI hiện đại
- LLM / SLM / VLM
- OCR & Voice AI
- AI Agent & Multimodal AI
- Thuật toán robot & tối ưu hóa
- Reinforcement Learning
- Bảo mật & mật mã học
- Hệ thống AI thực tế

Mục tiêu chính:
- học và ghi chú kiến thức
- tổng hợp paper
- giải thích thuật toán
- lưu tài liệu tham khảo
- chia sẻ kiến thức bằng tiếng Việt
- nghiên cứu kiến trúc hệ thống AI hiện đại

---

# ![Link](https://img.icons8.com/fluency/22/link.png) Nguồn tham khảo

- [Awesome NLP](https://github.com/keon/awesome-nlp)
- [Foundation Models & Multimodal Systems](https://arxiv.org/pdf/2412.19437)
- [Awesome AI Agents](https://github.com/jim-schwoebel/awesome_ai_agents)
- [Awesome World Models](https://github.com/leofan90/Awesome-World-Models)

---

# ![AI](https://img.icons8.com/fluency/22/artificial-intelligence.png) 1. Ghi chú AI hiện đại

## Các nhóm AI chính

| Chủ đề | Nội dung |
|---|---|
| LLM | AI ngôn ngữ lớn dùng cho chat, reasoning, coding |
| SLM | AI nhỏ tối ưu cho mobile, CPU, edge |
| VLM | AI hiểu đồng thời ảnh và văn bản |
| OCR | AI đọc tài liệu, giấy tờ, hóa đơn |
| Voice AI | Nhận dạng và tổng hợp giọng nói |
| Agent AI | AI có khả năng lập kế hoạch và gọi công cụ |
| Multimodal AI | AI xử lý nhiều loại dữ liệu cùng lúc |

---

## Các chủ đề sẽ ghi chú

### Kiến trúc mô hình

- Transformer
- Encoder / Decoder
- Attention
- Multi-Head Attention
- Cross Attention
- RoPE
- Positional Encoding
- KV Cache
- MoE (Mixture of Experts)
- Sparse Attention
- Sliding Window Attention

### Huấn luyện mô hình

- Pretraining
- Finetuning
- Instruction Tuning
- RLHF
- DPO / GRPO
- Distillation
- Quantization
- LoRA / QLoRA

### Suy luận & tối ưu

- Speculative Decoding
- Flash Attention
- vLLM
- Tensor Parallel
- Pipeline Parallel
- GGUF
- ONNX Runtime
- TensorRT

---

## Các mô hình phổ biến

### LLM

- GPT
- LLaMA
- Gemma
- DeepSeek
- Mistral
- Qwen
- Phi

### VLM

- LLaVA
- GPT-4o
- Gemini
- Qwen-VL
- Kosmos

### OCR

- PaddleOCR
- Tesseract
- TrOCR
- Donut
- LayoutLM

### Voice AI

- Whisper
- XTTS
- VALL-E
- DeepSpeech

---

# ![Bot](https://img.icons8.com/fluency/22/bot.png) 2. Ghi chú Robot & Điều hướng

Robot và hệ thống tự động cần:
- tìm đường
- tránh vật cản
- lập kế hoạch
- tối ưu chuyển động
- học hành vi

---

## Thuật toán tìm đường

| Thuật toán | Mục đích |
|---|---|
| BFS | Duyệt đồ thị |
| DFS | Tìm kiếm chiều sâu |
| Dijkstra | Đường đi ngắn nhất |
| A* | Tìm đường có heuristic |
| IDA* | Giảm bộ nhớ |

---

## Điều hướng & SLAM

- SLAM
- Graph SLAM
- ORB-SLAM
- Visual SLAM
- LiDAR SLAM
- EKF-SLAM

---

## Motion Planning

- RRT
- RRT*
- PRM
- Trajectory Planning
- Collision Avoidance

---

## Thuật toán tối ưu hóa

| Thuật toán | Ý tưởng |
|---|---|
| PSO | Bầy chim |
| ACO | Đàn kiến |
| Genetic Algorithm | Tiến hóa |
| Simulated Annealing | Luyện kim |
| Gradient Descent | Tối ưu gradient |

---

## Reinforcement Learning

- DQN
- PPO
- SAC
- TD3
- Dreamer
- MuZero

Ứng dụng:
- robot tự hành
- drone
- game AI
- xe tự lái
- tối ưu hành vi

---

# ![Security](https://img.icons8.com/fluency/22/lock.png) 3. Ghi chú Bảo mật & Mật mã học

Các thuật toán bảo mật giúp:
- mã hóa dữ liệu
- xác thực
- ký số
- bảo vệ giao tiếp
- bảo vệ blockchain
- bảo vệ AI

---

## Mã hóa dữ liệu

### Mã hóa đối xứng

- AES
- DES
- ChaCha20
- Blowfish

### Mã hóa khóa công khai

- RSA
- ECC
- ECDSA
- Ed25519

---

## Hashing

- SHA-256
- SHA-3
- BLAKE3
- MD5
- SHA-1

---

## Công nghệ bảo mật nâng cao

| Công nghệ | Mục đích |
|---|---|
| Zero-Knowledge Proof | Xác thực không lộ dữ liệu |
| Homomorphic Encryption | Tính toán trên dữ liệu mã hóa |
| MPC | Tính toán đa bên an toàn |
| Differential Privacy | Bảo vệ dữ liệu người dùng |
| Confidential Computing | Tính toán an toàn trong TEE |

---

## Mật mã hậu lượng tử

- Kyber
- Dilithium
- Falcon
- SPHINCS+

---

# ![Source Code](https://img.icons8.com/fluency/22/source-code.png) 4. Công nghệ & Framework

## AI

- PyTorch
- TensorFlow
- JAX
- ONNX Runtime
- TensorRT
- Ollama
- vLLM

## Robot

- ROS2
- Gazebo
- Isaac Sim
- OpenCV
- Open3D

## Security

- OpenSSL
- libsodium
- WireGuard
- HashiCorp Vault

---

# ![Folder](https://img.icons8.com/fluency/22/folder-invoices.png) 5. Cấu trúc Repository

```text
notes/
├── ai/
├── llm/
├── slm/
├── vlm/
├── ocr/
├── voice/
├── agents/
├── robotics/
├── planning/
├── optimization/
├── reinforcement-learning/
├── cryptography/
├── security/
├── papers/
├── tutorials/
└── diagrams/

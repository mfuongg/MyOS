# 🖥️ MyOS — Hệ Điều Hành Đơn Giản

> Hệ điều hành mini được xây dựng từ đầu bằng **C/C++ và Assembly**, phục vụ mục đích học tập và nghiên cứu các kiến thức cơ bản về hệ điều hành và lập trình hệ thống cấp thấp.

---

## 📌 Giới thiệu

**MyOS** là một hệ điều hành mini có khả năng khởi động trực tiếp trên máy ảo thông qua file ISO.

Dự án sử dụng:

* **C/C++** — phát triển Kernel, Mini Shell và các thành phần xử lý chính.
* **Assembly** — xây dựng Bootloader và xử lý các thao tác cấp thấp.
* **Makefile** — tự động hóa quá trình biên dịch và tạo file ISO.

MyOS có thể chạy trên:

* 🖥️ **VirtualBox**
* 🖥️ **VMware**
* ⚡ **QEMU**

Sau khi khởi động, hệ điều hành hiển thị giao diện chào mừng và cung cấp một **Mini Shell** cho phép người dùng nhập và thực thi các lệnh cơ bản.

---

## ✨ Tính năng

| Tính năng              | Mô tả                                        |
| ---------------------- | -------------------------------------------- |
| 🚀 **Bootloader**      | Khởi động và tải Kernel của MyOS             |
| ⚙️ **Kernel**          | Thành phần cốt lõi của hệ điều hành          |
| ⌨️ **Keyboard Driver** | Nhận và xử lý dữ liệu từ bàn phím            |
| 💻 **Mini Shell**      | Giao diện dòng lệnh tương tác với người dùng |
| 📋 **Command System**  | Hỗ trợ các lệnh cơ bản                       |
| 🧹 **Clear Screen**    | Xóa nội dung đang hiển thị                   |
| 🔄 **Reboot**          | Khởi động lại máy ảo                         |
| 💿 **Bootable ISO**    | Tạo file ISO có khả năng khởi động           |

---

## 💻 Các lệnh được hỗ trợ

MyOS cung cấp một Mini Shell với các lệnh cơ bản:

| Lệnh     | Chức năng                               |
| -------- | --------------------------------------- |
| `help`   | Hiển thị danh sách các lệnh được hỗ trợ |
| `about`  | Hiển thị thông tin về tác giả và dự án  |
| `clear`  | Xóa nội dung trên màn hình              |
| `hi`     | Hiển thị lời chào                       |
| `hello`  | Hiển thị lời chào                       |
| `reboot` | Khởi động lại máy ảo                    |

### Ví dụ

```text
MyOS> help

Các lệnh được hỗ trợ:
  help
  about
  clear
  hi
  hello
  reboot

MyOS> hello
Hello!

MyOS> about
MyOS - Simple Operating System

MyOS>
```

---

## 🏗️ Kiến trúc hệ thống

Quá trình hoạt động cơ bản của MyOS:

```text
                    ┌─────────────────────┐
                    │       MÁY ẢO        │
                    │ VirtualBox / VMware │
                    │       / QEMU        │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │     BOOTLOADER      │
                    │      loader.s       │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │       KERNEL        │
                    │     kernel.cpp      │
                    └──────────┬──────────┘
                               │
                    ┌──────────┴──────────┐
                    ▼                     ▼
           ┌─────────────────┐   ┌─────────────────┐
           │ KEYBOARD DRIVER │   │   MINI SHELL    │
           │ keyboard.cpp/h  │   │   shell.cpp/h   │
           └─────────────────┘   └─────────────────┘
```

---

## 📁 Cấu trúc dự án

```text
MyOS/
│
├── loader.s
├── kernel.cpp
│
├── keyboard.cpp
├── keyboard.h
│
├── shell.cpp
├── shell.h
│
├── linker.ld
├── Makefile
│
└── mykernel.iso
```

### Mô tả các thành phần

| Tệp            | Mô tả                                                         |
| -------------- | ------------------------------------------------------------- |
| `loader.s`     | Bootloader, thực hiện quá trình khởi động hệ điều hành        |
| `kernel.cpp`   | Kernel chính của MyOS                                         |
| `keyboard.cpp` | Cài đặt xử lý bàn phím                                        |
| `keyboard.h`   | Khai báo các thành phần của Keyboard Driver                   |
| `shell.cpp`    | Cài đặt Mini Shell và xử lý lệnh                              |
| `shell.h`      | Khai báo các thành phần của Shell                             |
| `linker.ld`    | Linker Script, quy định cách sắp xếp các section khi liên kết |
| `Makefile`     | Tự động hóa quá trình biên dịch                               |
| `mykernel.iso` | File ISO có khả năng khởi động MyOS                           |

---

## 🛠️ Yêu cầu môi trường

Để biên dịch lại MyOS từ mã nguồn, cần chuẩn bị:

* [NASM](https://www.nasm.us/)
* `i686-elf-gcc`
* `i686-elf-ld`
* `i686-elf-objcopy`
* `Make`

Để chạy và kiểm thử:

* [QEMU](https://www.qemu.org/)
* VirtualBox
* VMware

### Kiến trúc

```text
Architecture: x86 32-bit
```

---

## 🔨 Biên dịch từ mã nguồn

### 1. Clone repository

```bash
git clone https://github.com/mfuongg/MyOS.git
cd MyOS
```

### 2. Xóa các file build cũ

```bash
make clean
```

### 3. Biên dịch project

```bash
make
```

### 4. Tạo file ISO

```bash
make mykernel.iso
```

Sau khi build thành công:

```text
mykernel.iso
```

sẽ được tạo và có thể sử dụng để khởi động MyOS trên máy ảo.

---

## ▶️ Chạy MyOS

### 🪟 Windows — VirtualBox / VMware

#### Bước 1: Tạo máy ảo

Tạo một máy ảo mới với:

```text
Type: Other
Version: Other/Unknown (32-bit)
```

#### Bước 2: Ổ cứng

Không cần tạo hoặc thêm ổ cứng ảo.

#### Bước 3: Gắn file ISO

Chọn:

```text
mykernel.iso
```

làm ổ đĩa quang khởi động.

#### Bước 4: Tắt EFI

Nếu có tùy chọn EFI:

```text
Enable EFI → OFF
```

#### Bước 5: Khởi động

Nhấn **Start** để khởi động máy ảo.

MyOS sẽ được boot từ file ISO.

---

### 🍎 macOS — M1 / M2 / M3

Cài đặt QEMU thông qua Homebrew:

```bash
brew install qemu
```

Chạy MyOS:

```bash
qemu-system-i386 -cdrom mykernel.iso -boot d -m 64M
```

Nếu `Makefile` hỗ trợ lệnh `run`:

```bash
make run
```

---

### 🐧 Linux — Ubuntu / Debian / Fedora

Cài đặt QEMU:

```bash
sudo apt install qemu-system-x86
```

Chạy MyOS:

```bash
qemu-system-i386 -cdrom mykernel.iso -boot d -m 64M
```

---

## 🧪 Kiểm thử

Sau khi khởi động MyOS, có thể kiểm tra:

* [x] Khởi động hệ điều hành từ file ISO
* [x] Hiển thị giao diện chào mừng
* [x] Nhận dữ liệu từ bàn phím
* [x] Khởi động Mini Shell
* [x] Thực thi lệnh `help`
* [x] Thực thi lệnh `about`
* [x] Thực thi lệnh `hi`
* [x] Thực thi lệnh `hello`
* [x] Thực thi lệnh `clear`
* [x] Thực thi lệnh `reboot`

---

## 🎯 Mục tiêu học tập

Thông qua dự án MyOS, nhóm thực hiện tìm hiểu và thực hành:

* Kiến trúc cơ bản của hệ điều hành
* Quá trình Boot hệ điều hành
* Xây dựng Bootloader
* Xây dựng Kernel
* Lập trình C/C++
* Lập trình Assembly
* Xử lý dữ liệu từ bàn phím
* Xây dựng giao diện dòng lệnh
* Linker Script
* Cross Compilation
* Makefile
* Biên dịch và liên kết chương trình cấp thấp
* Chạy hệ điều hành trên môi trường máy ảo

---

## 📸 Demo

> Có thể bổ sung ảnh chụp MyOS đang chạy trên QEMU, VirtualBox hoặc VMware tại đây.

Ví dụ:

```markdown
![MyOS - Màn hình khởi động](images/myos-boot.png)

![MyOS - Mini Shell](images/myos-shell.png)
```

---

## 📌 Thông tin dự án

| Thông tin            | Chi tiết                      |
| -------------------- | ----------------------------- |
| **Tên dự án**        | MyOS — Hệ Điều Hành Đơn Giản  |
| **Loại dự án**       | Dự án học tập / Dự án môn học |
| **Ngôn ngữ**         | C/C++, Assembly               |
| **Kiến trúc**        | x86 32-bit                    |
| **Build System**     | Makefile                      |
| **Môi trường chạy**  | QEMU / VirtualBox / VMware    |
| **Định dạng đầu ra** | Bootable ISO                  |

---

## 👤 Tác giả

**Minh Phương**

* GitHub: [@mfuongg](https://github.com/mfuongg)
* Repository: [MyOS](https://github.com/mfuongg/MyOS)
* Email: fuongm06@gmail.com
---

## 📄 Ghi chú

MyOS được xây dựng với mục đích **học tập và nghiên cứu**, tập trung vào việc tìm hiểu các khái niệm cơ bản của hệ điều hành, lập trình hệ thống cấp thấp, quá trình boot và giao tiếp giữa người dùng với hệ thống thông qua Mini Shell.

---

⭐ **Nếu bạn thấy dự án hữu ích, hãy Star repository để ủng hộ dự án!**

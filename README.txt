MyOS — Simple Operating System

1. GIỚI THIỆU
MyOS là hệ điều hành mini được lập trình bằng ngôn ngữ C/C++ 
và Assembly. Hệ điều hành có thể khởi động trực tiếp trên máy ảo 
(VirtualBox, VMware hoặc QEMU) và hiển thị giao diện chào mừng 
kèm một mini shell hỗ trợ một số lệnh cơ bản.


2. CÁC LỆNH HỖ TRỢ TRONG SHELL
help    : Hiển thị danh sách lệnh
about   : Giới thiệu tác giả
clear   : Xóa màn hình
hi/hello: Gửi lời chào
reboot  : Khởi động lại máy ảo


3. CÁCH CHẠY TRÊN CÁC HỆ ĐIỀU HÀNH
--- Windows (VirtualBox / VMware) ---
1. Mở VirtualBox hoặc VMware
2. Tạo máy ảo mới:
   - Type: Other
   - Version: Other/Unknown (32-bit)
3. Không cần thêm ổ cứng
4. Gắn file ISO: mykernel.iso
5. Tắt "Enable EFI" (nếu có)
6. Start → hệ điều hành sẽ khởi động.

--- macOS (M1/M2/M3) ---
Cài QEMU (nếu chưa có):
    brew install qemu
Chạy MyOS:
    qemu-system-i386 -cdrom mykernel.iso -boot d -m 64M
Hoặc (nếu có Makefile):
    make run

--- Linux (Ubuntu / Debian / Fedora) ---
Cài QEMU:
    sudo apt install qemu-system-x86
Chạy MyOS:
    qemu-system-i386 -cdrom mykernel.iso -boot d -m 64M


4. CẤU TRÚC DỰ ÁN
loader.s       : Bootloader
kernel.cpp     : Kernel chính
keyboard.cpp/h : Driver bàn phím
shell.cpp/h    : Mini Shell
linker.ld      : Linker script
Makefile       : Build script
mykernel.iso   : File hệ điều hành bootable (nộp cho giảng viên)


5. CÁCH BIÊN DỊCH LẠI TỪ MÃ NGUỒN
Yêu cầu: 
    - nasm
    - i686-elf-gcc, i686-elf-ld, i686-elf-objcopy
Các lệnh:
    make clean
    make
    make mykernel.iso
Sau khi build xong, file mykernel.iso sẽ sẵn sàng để boot.


6. KẾT QUẢ
Hệ điều hành MyOS có thể:
- Khởi động thành công trên máy ảo
- Hiển thị giao diện chào mừng
- Nhận và xử lý bàn phím
- Chạy các lệnh cơ bản (help, about, hi, clear, reboot)
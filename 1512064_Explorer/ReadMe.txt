>> THÔNG TIN CÁ NHÂN
- Họ tên: Đường Trung Duy
- MSSV: 1512064
- Email: duongtrungduyit@gmail.com


>> CÁC CHỨC NĂNG ĐÃ LÀM:
- Lấy danh sách các ổ đĩa trong máy bằng hàm GetLogicalDrives hoặc GetLogicalDriveStrings,
 thêm các ổ đĩa vào node root, tạo sẵn thuộc tính cChildren = true để báo hiệu có các node con.
- Hiển thị toàn bộ thư mục và tập tin.
- Bấm đôi vào một thư mục sẽ thấy toàn bộ thư mục con và tập tin.
- Tạo ra ListView có 4 cột: Tên, thời gian chỉnh sửa, dung lượng.
- hiển thị 3 cột: Tên, thời gian chỉnh sửa, dung lượng
- Bấm đôi một tập tin sẽ chạy app tương ứng.

>> CÁC LUỒNG SỰ KIỆN CHÍNH (Main success scenario):
- Chạy chương trình lên, hiển thị node This PC trên TreeView bên trái ở trạng thái collapse (thu gọn).
Bấm vào sẽ xổ xuống các node con là danh sách ổ đĩa.
- Bấm vào ổ đĩa C đang ở trạng thái collapse(thu gọn) trong TreeView bên trái sẽ xổ xuống danh sách các thư mục con.


>> LINK YOUTUBE: https://youtu.be/HuHm4R_2gJk

>> LINK GITHUB: https://github.com/trungduy97/Explorer.git

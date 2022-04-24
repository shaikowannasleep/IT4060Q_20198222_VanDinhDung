Instructions
Viết chương trình client/server thực hiện các chức năng theo yêu cầu:

1. Chương trình clientinfo thực hiện kết nối đến máy chủ và gửi thông tin về tên máy, danh sách các ổ đĩa có trong máy, kích thước các ổ đĩa. 
Địa chỉ (tên miền) và cổng kết nối đến server nhận vào từ tham số dòng lệnh.

VD: clientinfo.exe localhost 1234

2. Chương trình serverinfo đợi kết nối từ clientinfo và thu nhận thông tin từ client, hiện kết quả ra màn hình. 
Cổng mà server đợi kết nối nhận vào từ tham số dòng lệnh.

VD: serverinfo.exe 1234


Gợi ý: sử dụng các hàm API của Windows


+ GetComputerNameA() - Trả về tên của máy tính

+ GetLogicalDriveStringsA() - Trả về danh sách ký tự ổ đĩa của máy tính

+ GetDiskFreeSpaceA() - Trả về kích thước của ổ đĩa



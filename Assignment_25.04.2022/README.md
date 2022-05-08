Hướng dẫn
Viết chương trình client/server thực hiện các chức năng theo yêu cầu:



1. Chương trình TCPClient, kết nối đến một máy chủ xác định bởi tên miền hoặc địa chỉ IP. Sau đó nhận dữ liệu từ bàn phím và gửi đến server. Tham số được truyền vào từ dòng lệnh có dạng:

TCPClient.exe <Địa chỉ IP/Tên miền> <Cổng>



2. Chương trình TCPServer, đợi kết nối ở cổngxác định bởi tham số dòng lệnh. Mỗi khi có client kết nối đến, thì gửi xâu chào chứa trong một tệp tin, sau đó ghi toàn bộ nội dung client gửi đến vào một tệp tin khác. Tên của tập tin chứa xâu chào và tập tin chứa nội dung client gửi đến được chỉ ra trong tham số dòng lệnh.

TCPServer.exe <Cổng> <Tệp tin chứa câu chào> <Tệp tin lưu nội dung client gửi đến>

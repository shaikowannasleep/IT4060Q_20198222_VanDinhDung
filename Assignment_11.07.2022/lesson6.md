Lập trình ứng dụng server thực hiện các yêu cầu sau:
+ Nhận các yêu cầu từ trình duyệt với tham số được đặt trong chuỗi query string bao gồm các tham số op (phép tính cần thực hiện), param1 (toán hạng 1), param2 (toán hạng 2). Các phép tính được chấp nhận gồm add (cộng), sub (trừ), mul (nhân) và div (chia).
+ Các tham số có thể có vị trí khác nhau.
+ Ứng dụng cần đọc giá trị các tham số, thực hiện phép tính và trả lại kết quả cho trình duyệt là trang web thể hiện phép tính đó.
+ Trong trường hợp thiếu tham số, ứng dụng cần trả lại trang web thông báo lỗi cho trình duyệt.

Hình bên dưới minh họa cho trường hợp op là add, param1 là 30, và param2 là 5.

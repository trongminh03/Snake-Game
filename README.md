# ***Snake Game*** 

## **Introduction** 

+ Họ và tên: Lê Trọng Minh - K66CB - UET

+ Mã sinh viên: 21020355 

+ Bài tập lớn: Snake Game (INT2215_1 - Lập trình nâng cao) 

## **Description** 

### *Game description and instruction* 
- Đây là trò chơi rắn săn mồi hoàn toàn mới với rất nhiều tính năng hay, vượt trội. Game có 3 chế độ chơi cho người chơi thoả sức lựa chọn: 

    + Game mode 1 - 1 Player: Giống với rắn săn mồi truyền thống người chơi sử dụng các phím mũi tên trên bàn phím để di chuyển rắn đến quả táo. 

    + Game mode 2 - 2 Player: Người chơi thứ nhất sử dụng các phím mũi tên còn người chơi thứ 2 dùng 4 phím w, a, s, d để di chuyển. 2 người chơi 
    sẽ phải né thêm những chướng ngại vật trên đường đi để ăn được táo. Sau 1 phút người nào điều khiển rắn ăn được nhiều táo hơn sẽ là người chiến thắng. Lưu ý: Nếu trong vòng 1 phút người nào di chuyển rắn chết trước thì sẽ là người thua cuộc ngay bất chấp điểm số. 

    + Game mode 3 - VS *AI Snake*: Người chơi sẽ có cơ hội thử sức với 1 con rắn thông minh có khả năng tránh né border và tìm táo rất nhanh. Nhiệm vụ của người chơi là trong vòng 1 phút cố gắng không để rắn chết và ăn nhiều táo hơn *AI Snake*. 

- Game có đầy đủ các chức năng hỗ trợ người chơi trong việc điều chỉnh dễ dàng giữa các chế độ, thoát game, mô tả cách chơi, sử dụng phím esc để dừng game, ... 
- Có âm thanh êm dịu thoải mái khi chơi

### *Control* 

| Control | Player 1 | Player 2 | 
|---------|----------|----------|
| UP      |     ↑    |     w    |
| DOWN    |     ↓    |     s    |
| LEFT    |     ←    |     a    |
| RIGHT   |     →    |     d    | 

### *Preview* 

![](res/demo%20image/end_demo.png)
![](res/demo%20image/gamemode_demo.png) 
![](res/demo%20image/gameplay_demo.png) 

## **Setup** 

- *Cài đặt* 
    + Yêu cầu: Có C++ compiler và tải sublime text 

    1. Dùng terminal hoặc git bash tải source code về máy: git clone https://github.com/trongminh03/Snake-Game.git 

    2. Vào thư mục vừa tải về và ấn đúp vào SnakeGame.sublime-project

    3. Trên thanh công cụ vào Tools → Build System và ấn tick vào Build Debug

    4. Ấn phím F7 hoặc tổ hợp phím Fn + F7 hoặc tổ hợp phím Ctr + Shift + B để chạy chương trình 

- *Mọi khó khăn trong phần cài đặt, trong quá trình chơi, hãy email qua 21020355@vnu.edu.vn.*/ 

## **See also**  

### *Các kỹ thuật sử dụng*  
    - Thư viện SDL2.0

    - Sử dụng nhiều class, vector, tách file, nạp chồng toán tử, ...

    - Có thể lưu lại điểm cao nhất sau mỗi lần chơi nhờ đọc, ghi file

    - Tạo các đối tượng: rắn, táo, đuôi, ... 

    - Dùng các kiến thức toán học để tính toán được góc cua của rắn để chèn ảnh thân và đuôi lúc cong 

    - Xử lý thời gian, thao tác chuột và bàn phím, âm thanh, hình ảnh, chữ. 

    - Tạo menu và các nút ấn di chuyển giữa các menu 

    - Sử dụng photoshop để tự edit hầu hết các ảnh trong game

    - Sử dụng các kiến thức Đại số, Toán rời rạc: cụ thể là sử dụng toạ độ, thuật toán tìm kiếm A* (A* search algorithm) để tạo nên AI Snake vượt trội, 1 trong những phương thức tối ưu nhất để giúp cho rắn có thể tìm đồ ăn nhanh và né được chướng ngại vật và đuôi rắn. Ngoài ra: còn có khá nhiều thuật toán có thể áp dụng để làm nên AI Snake nhưng sẽ không tối ưu bằng ví dụ như: BFS(Breadth-First Search), DFS(Depth-first Search), Đường đi Hamilton (Hamiltonian cycle), ... 

### *Nguồn tham khảo* 
- Cách sử dụng, cài đặt SDL2.0 trên sublime text 3: tham khảo trên reddit, stack overflow và kênh youtube codegopher 

- Cách sử dụng thư viện SDL2.0, quản lý chương trình: Thảo khảo trên lazyfoo và các video của cô Nguyễn Thị Minh Châu, stack overflow, kênh youtube: codegopher, Let's Make Games, Madsycode. 

- Hình ảnh: 90% tự design, còn lại tự tìm kiếm trên google và flaticon 

- Âm thanh: Tự tra trên google 

- Thuật toán: https://www.geeksforgeeks.org/a-search-algorithm/, https://en.wikipedia.org/wiki/A*_search_algorithm, https://www.youtube.com/watch?v=amlkE0g-YFU&ab_channel=edureka%21, https://jaubin.net/projects/snake-ai.html

## **Conclusion** 

### ***Điều tâm đắc***
- Dự án này hoàn toàn là do em tự làm, không đi sao chép ở bất kì đâu 

- Em thấy mình đã cải thiện được rất nhiều kỹ năng trong việc tư duy thuật toán và viết code, khả năng lên ý tưởng, các kỹ năng photoshop.

- Đa số hình ảnh là do em tự thiết kế, dù không quá đẹp nhưng nó lại tạo được tính độc đáo, mới lạ cho chương trình.

- Học được cách setup môi trường, sử dụng thư viện ngoài. 

- Học được thêm nhiều thuật toán hay và tự mình cài đặt vào chương trình. 

### ***Hướng phát triển*** 
- Cập nhật tính năng bảng xếp hạng, sau mỗi lần chơi người chơi sẽ được nhập tên để lưu lại kết quả chơi của mình.

- Thêm chế độ điều chỉnh tốc độ để người chơi có thể chọn tốc độ tuỳ thích, phù hợp với khả năng chơi của mình.

- Dựa vào thuật toán tìm kiếm A*, em nghĩ mình sẽ có thể mở rộng phạm vi duyệt của đầu rắn kết hợp với thuật toán tìm đường đi Halmiton để tạo ra 1 con AI Snake bất tử mà vẫn có khả năng tìm đồ ăn cực nhanh. 

- Nếu việc cải tiến AI Snake khả thi thì sẽ có thêm tính năng 2 người chơi vs AI Snake để giảm độ khó cho game. 

### *Mức điểm tự đánh giá: 9.5++/10* 






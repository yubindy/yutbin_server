# yutbin_server
采用 Reactor + threadpool + 非阻塞 IO + Epoll 的编程模型

Eventloop 异步事件驱动，并为每个连 接维护用户态的 IO Buffer，处理半包，解析正确的网络包，提高系统稳定性和鲁棒性

封装 Http 模块，支持静态资源的访问。

实现多缓冲区的 多线程异步日志库

采用 RAII 思想管理资源，避免内存泄漏 


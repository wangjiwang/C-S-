C/S 结构，即大家熟知的客户机和服务器结构。


本程序完成一个简单的时间获取功能，服务器依次调用socket，bind，listen三个函数准备监听描述符。


服务器进程调用accept函数，在accept调用中被投入睡眠，等待某个客户的连接到达并被内核接受。


TCP客户调用connect函数来建立与TCP服务器的连接，连接后调用read函数来读取服务器的应答，并用fputs函数输出结果显示在屏幕上。

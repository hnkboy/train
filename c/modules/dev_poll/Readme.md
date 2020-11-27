终端1执行应用程序：1.初始状态，只显示可写
Poll monitor:can be write
.....

2.执行命令1后，可读可写
Poll monitor:can be write
Poll monitor:can be read
....
3.执行命令2后，又变回可写，不可读了
Poll monitor:can be write
.....
终端2读写globalmem
# echo "test" > /dev/globalmem 　　// 命令1
# cat  /dev/globalmem 　　　　　　  // 命令2
test






https://www.cnblogs.com/liuwanpeng/p/6920443.html

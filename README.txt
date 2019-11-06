文件说明：
aes.h      // 头文件包含加解密函数的声明
aes.c      // 加解密函数的定义
main.c     // 主函数，测试加解密算法
compile.sh // 编译脚本

使用说明：
1.设置初始化向量为：aes.c文件611，636行，这个可以自己随意设置，单必须是16字节
2.设置秘钥：main.c 28行
3.linux:终端中执行./compile.sh脚本编译程序
4.执行./gen_enc testfile 1      //加密, 执行完之后会产生testile.enc文件
  设置k值，main.c 75行
  执行./gen_enc testfile.enc 0  //解密，执行完之后会产生testile.dec文件


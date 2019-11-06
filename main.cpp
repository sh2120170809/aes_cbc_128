#include <iostream>
#include <fstream>
#include <string>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "aes.h"
#include <stdlib.h>

using namespace std;
#define BUFF_SIZE (50*1024*1024)

static u8 dst[BUFF_SIZE] = {0};
static u8 des[BUFF_SIZE] = {0};
static char data[BUFF_SIZE] = {0};

int main(int argc, char* argv[]) {

    if (argc != 2 && argc != 3) {
        printf("application format: ./gen_enc <file>  [option] \n");
        return 0;
    }
    printf("parameter number is %d\n", argc);
    
    int op = atoi(argv[2]);

    const char* file = argv[1];
    const char* key_content = "abcdefghijklmnop"; // 秘钥 可以随意设置，长度为16字节
    u8* key = (u8*)key_content;

    std::ifstream ifs;
    ifs.open(file);
    ifs.seekg(0, ifs.end);
    long filesize = ifs.tellg();
    ifs.seekg(0);
    memset(data, 0, BUFF_SIZE);
    ifs.read(data, filesize); 
    ifs.close();
    printf("file size is: %ld\n", filesize);
    
  
    // 加密
    if(1 == op){
        std::ofstream ofs;
        int size = ((filesize / 16) + 1) * 16;
        printf("encryption data size is:%d\n", size);
        char file_enc[128] = {0};
        aes_cbc_crypt(data, (char*)dst, 1, (uint8_t*)key, size);
        sprintf(file_enc, "%s.enc", file);
        ofs.open(file_enc);
        ofs.write((char*)dst, size);       
        ofs.close();
        /*
        printf("@@@@@@@ encode data@@@@@@@\n");
        for(int i=0; i<size; i++){
            printf("%x", dst[i]);
            if((i+1) % 2 == 0)
                printf(" ");
            if((i+1) % 16 == 0)
                printf("\n");
        }
		printf("\n");
        */
    } 
    
    // 解密dst
    if (0 == op) {
        std::ofstream ofs;
        int size = filesize;
        char file_des[128] = {0};
        aes_cbc_crypt((char*)data, (char*)des, 0, (uint8_t*)key, size);
        printf("decryption size is:%d\n", size);
        sprintf(file_des, "%s.dec", file);
        ofs.open(file_des);
        ofs.write((char*)des, size-k); //减去多补的字节,k = 加密后文件大小 - 原文件大小
        ofs.close();
    }
    
}



#ifndef _AES_REF_H_
#define _AES_REF_H_

#include <inttypes.h>

#ifdef __cpluscplus
extern "C" {
#endif

    typedef unsigned char u8;
    typedef unsigned int u32;
#define debug(...) do {} while (0)


#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

    enum {
        AES_STATECOLS   = 4,
        AES_KEYCOLS = 4,
        AES_ROUNDS  = 10,
        AES_KEY_LENGTH  = 128 / 8,
        AES_EXPAND_KEY_LENGTH   = 4 * AES_STATECOLS * (AES_ROUNDS + 1),
    };

    void aes_expand_key(u8* key, u8* expkey); //扩展秘钥
    void aes_encrypt(u8* in, u8* expkey, u8* out);
    void aes_decrypt(u8* in, u8* expkey, u8* out);
    void aes_apply_cbc_chain_data(u8* cbc_chain_data, u8* src, u8* dst);
    void aes_cbc_encrypt_blocks(u8* key_exp, u8* src, u8* dst, u32 num_aes_blocks);
    void aes_cbc_decrypt_blocks(u8* key_exp, u8* src, u8* dst, u32 num_aes_blocks);
    int aes_cbc_crypt(char* payload, char* dst, const int enc, uint8_t* key, int len);

#ifdef __cpluscplus
}
#endif

#endif

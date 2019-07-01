#ifndef AZURE_SAS_H
#define AZURE_SAS_H

#include <Arduino.h>
#include <Base64.h>

#define openSSL OPENSSL_SYS_MINGW32

#ifdef openSSL
#   include <openssl/ssl.h>
#   include <openssl/err.h>
#else
#   include <sha256.h>
#endif

class AzureSAS
{
public:
    String SAS;

    AzureSAS() { SAS = ""; }
    AzureSAS(char *key, String url, uint32_t expire)
    {
        SAS = create(key, url, expire);
    }

    static String urlEncode(const char *msg)
    {
        const char *hex = "0123456789abcdef";
        String encodedMsg = "";
        while (*msg != '\0')
        {
            if (('a' <= *msg && *msg <= 'z') || ('A' <= *msg && *msg <= 'Z') || ('0' <= *msg && *msg <= '9'))
            {
                encodedMsg += *msg;
            }
            else
            {
                encodedMsg += '%';
                encodedMsg += hex[*msg >> 4];
                encodedMsg += hex[*msg & 15];
            }
            msg++;
        }
        return encodedMsg;
    }

    String get()
    {
        return SAS;
    }

    String create(char *key, String url, uint32_t expire)
    {
        if (expire == 0)
            expire = 1737504000; //hardcoded expire

        //url.toLowerCase();
        String stringToSign = url + "\n" + String(expire);
        int keyLength = strlen(key);
        int decodedKeyLength = base64_dec_len(key, keyLength);
        char decodedKey[decodedKeyLength];         //allocate char array big enough for the base64 decoded key
        base64_decode(decodedKey, key, keyLength); //decode key

        // openSSL version
#ifdef openSSL
        unsigned char *sign;
        unsigned int rlen;
        hmac_sha25_digest((unsigned char *)stringToSign.c_str(), stringToSign.length(), (unsigned char *)decodedKey, decodedKeyLength, &sign, &rlen);
#else
        Sha256.initHmac((const uint8_t *)decodedKey, decodedKeyLength);
        Sha256.print(stringToSign);
        char *sign = (char *)Sha256.resultHmac();
#endif

        // Get base64 of signature
        int encodedSignLen = base64_enc_len(32); // HASH_LENGTH
        char encodedSign[encodedSignLen];
        base64_encode(encodedSign, (char *)sign, 32); // HASH_LENGTH

        // SharedAccessSignature
        SAS = "SharedAccessSignature sr=" + url + "&sig=" + urlEncode(encodedSign) + "&se=" + String(expire);
#ifdef openSSL
        free(sign);
#endif
        return SAS;
    }

#ifdef openSSL
    static int hmac_sha25_digest(unsigned char *msg, int mlen, unsigned char *key, int key_len, unsigned char **res, unsigned int *rlen)
    {
        *res = (unsigned char *)malloc((SHA256_DIGEST_LENGTH + 1) * sizeof(u_char));
        memset(*res, 0, (SHA256_DIGEST_LENGTH + 1) * sizeof(u_char));
        HMAC_CTX *ctx = HMAC_CTX_new();
        HMAC_Init_ex(ctx, key, key_len, EVP_sha256(), NULL);
        HMAC_Update(ctx, msg, mlen);
        {
            *res = (unsigned char *)malloc((SHA256_DIGEST_LENGTH + 1) * sizeof(u_char));
            memset(*res, 0, (SHA256_DIGEST_LENGTH + 1) * sizeof(u_char));
            HMAC_CTX *ctx = HMAC_CTX_new();
            HMAC_Init_ex(ctx, key, key_len, EVP_sha256(), NULL);
            HMAC_Update(ctx, msg, mlen);
            HMAC_Final(ctx, *res, rlen);
            HMAC_CTX_free(ctx);
            return 0;
        }
    }
#endif     

}; // AzureSAS

#endif /* AZURE_SAS_H */
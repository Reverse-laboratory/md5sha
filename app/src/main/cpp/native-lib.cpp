#include <jni.h>
#include <string>
#include "openssl/md5.h"
#include <openssl/sha.h>

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>



extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_md5sha_MainActivity_calculateMd5(JNIEnv *env, jobject thiz, jstring input) {
    // TODO: implement calculateMd5()
    const char *inputStr = env->GetStringUTFChars(input, nullptr);

    // 初始化 MD5 哈希计算
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5_CTX ctx;
    MD5_Init(&ctx);

    MD5_Update(&ctx, inputStr, strlen(inputStr));
    MD5_Final(digest, &ctx);

    // 将 MD5 结果转为十六进制字符串
    char md5String[33];
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(&md5String[i*2], "%02x", digest[i]);
    }
    md5String[32] = '\0';

    // 释放获取的输入字符串
    env->ReleaseStringUTFChars(input, inputStr);

    // 返回 MD5 结果
    return env->NewStringUTF(md5String);
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_md5sha_MainActivity_calculateSha1(JNIEnv *env, jobject thiz, jstring input) {
    // TODO: implement calculateSha1()
    const char *inputChars = env->GetStringUTFChars(input, nullptr); // 从 Java 获取字符串
    std::string inputStr(inputChars);                               // 转换为 C++ 字符串
    env->ReleaseStringUTFChars(input, inputChars);                  // 释放字符串资源

    // 2. 初始化 SHA-1 上下文
    SHA_CTX ctx;
    unsigned char hash[SHA_DIGEST_LENGTH]; // 用于存储 SHA-1 结果（20 字节）

    if (!SHA1_Init(&ctx)) {
        return env->NewStringUTF("SHA1_Init failed"); // 初始化失败时返回错误信息
    }

    // 3. 更新 SHA-1 上下文（这里直接更新整个输入字符串）
    if (!SHA1_Update(&ctx, inputStr.c_str(), inputStr.size())) {
        return env->NewStringUTF("SHA1_Update failed"); // 更新失败时返回错误信息
    }

    // 4. 计算最终哈希值
    if (!SHA1_Final(hash, &ctx)) {
        return env->NewStringUTF("SHA1_Final failed"); // 计算失败时返回错误信息
    }

    // 5. 将哈希值转换为十六进制字符串
    std::string result;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        char buffer[3];
        snprintf(buffer, sizeof(buffer), "%02x", hash[i]); // 转换为两位十六进制字符串
        result += buffer;
    }

    // 6. 返回计算结果
    return env->NewStringUTF(result.c_str());
}
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_md5sha_MainActivity_customMd5(JNIEnv *env, jobject /* this */, jstring inputStr) {
    const char *input = env->GetStringUTFChars(inputStr, nullptr);
    if (input == nullptr) {
        return nullptr; // 内存分配失败
    }

    // 初始化 MD5 上下文
    MD5_CTX ctx;
    MD5_Init(&ctx);

    // 自定义初始向量
    unsigned char custom_iv[MD5_DIGEST_LENGTH] = {
            0x12, 0x34, 0x56, 0x78,
            0x9a, 0xbc, 0xde, 0xf0,
            0x11, 0x22, 0x33, 0x44,
            0x55, 0x66, 0x77, 0x88
    };

    // 将自定义初始向量更新到 MD5 上下文
    MD5_Update(&ctx, custom_iv, MD5_DIGEST_LENGTH);

    // 更新输入数据
    MD5_Update(&ctx, input, strlen(input));

    // 计算最终的哈希值
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5_Final(digest, &ctx);

    // 将哈希值转换为十六进制字符串
    char md5String[MD5_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        sprintf(&md5String[i * 2], "%02x", digest[i]);
    }

    env->ReleaseStringUTFChars(inputStr, input);
    return reinterpret_cast<jbyteArray>(env->NewStringUTF(md5String));
}
# 使用frida修改md5和sha1的计算结果
hook-sha.js
```function hookMd5() { 
// 获取 MD5 函数的导出地址
var MD5 = Module.findExportByName("libopensls.so", "MD5_Final");

if (MD5) {
    console.log("[+] MD5_Finalfound at: " + MD5);

    // Hook MD5 函数
    Interceptor.attach(MD5, {
        onEnter: function (args) {
            console.log("\N[*] MD5_Final called");

            // 读取输入数据（args[0] 是输入字符串指针）
            //var inputStr = Memory.readCString(args[0]);
            console.log("arg1:"+ args[0])
            console.log("arg2:"+ args[1])
            console.log("arg3:"+ args[2])
            console.log("arg4:"+ args[3])
            var a = this.md = args[0];
                console.log("[*] md5_Final called"+ a);
            this.digestPointer = args[0];
            console.log("[*] Digest pointer:", this.digestPointer);
            // 读取输入长度（args[1] 是输入字符串长度）
        },
        onLeave: function (reval) {
            
            console.log("[*] MD5_Final returned:", reval.toInt32());

            // 读取原始哈希值
            var digest = Memory.readByteArray(this.digestPointer, 16);
            console.log("[*] Original Digest:", hexDumpHelper(digest, {
                offset: 0,
                length: 16,
                header: true,
                ansi: true
            }));

            // 修改哈希值
            var fakeDigest = "11111111111111111111111111111111";
            var fakeDigestBytes = fakeDigest.match(/.{2}/g).map(function(byte) {
                return parseInt(byte, 16);
            });
            Memory.writeByteArray(this.digestPointer, fakeDigestBytes);
            console.log("[*] Modified Digest:", fakeDigest);
            
        }
    });
} else {
    console.error("[-] MD5 function not found.");
}

}

function hookSha1() { 
    // 获取 MD5 函数的导出地址
    var SHA1 = Module.findExportByName("libopensls.so", "SHA1_Final")
    
    if (SHA1) {
        console.log("[+] SHA1 called: " + SHA1);
    
        // Hook MD5 函数
        Interceptor.attach(SHA1, {
            onEnter: function (args) {
                var a = this.md = args[0];
                console.log("[*] SHA1_Final called"+ a);
                // 读取输入长度（args[1] 是输入字符串长度）
            },
            onLeave: function (reval) {
                console.log("[*] SHA1_Final returned:", reval.toInt32());

        if (reval.toInt32() === 1) {
            // 原始 SHA-1 哈希值（20 字节）
            const originalHash = Memory.readByteArray(this.md, 20);
            console.log("[*] Original SHA1 hash:", originalHash);

            // 修改哈希值为固定值 "1111111"
            // 将 "1111111" 转换为其对应的 ASCII 字节
            const fakeHash = "111111111111111111111111111111111111111111"; // 固定的哈希值，20 字节（160 位）
            const fakeHashBytes = fakeHash.match(/.{2}/g).map(b => parseInt(b, 16)); // 转换为字节数组

            // 写入伪造的哈希值到缓冲区
            Memory.writeByteArray(this.md, fakeHashBytes);

            // 打印伪造的哈希值
            const modifiedHash = Memory.readByteArray(this.md, 20);
            console.log("[*] Modified SHA1 hash:", modifiedHash);
        }
            // 读取原始哈希值
            }
        });
    } else {
        console.log("[*] SHA1 NOT called");
    }
    
}

setTimeout(hookMd5,2000)
setTimeout(hookSha1,2000)

function hexDumpHelper(data) {
    var hex = '';
    var byteArray = new Uint8Array(data);
    for (var i = 0; i < byteArray.length; i++) {
        hex += byteArray[i].toString(16).padStart(2, '0') + ' ';
    }
    return hex.trim();
}
```
修改前

<img src="https://github.com/user-attachments/assets/1a0554e9-718f-4aa1-bf2d-5c8369695d8c" width="30%">


修改效果

<img src="https://github.com/user-attachments/assets/e726c3e8-a31b-4118-ae2f-eda9c8fc8b0ac" width="30%">



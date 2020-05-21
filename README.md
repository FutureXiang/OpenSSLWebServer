# 基于OpenSSL的安全Web服务器
在Linux平台上利用OpenSSL实现安全的Web Server。Server能够并发处理多个请求，包括GET、POST及HEAD等。
## Usage
### Requirements
- Ubuntu >= 14.04
- OpenSSL: `sudo apt-get install libssl-dev openssl`
- G++: `sudo apt-get install g++`

### Generate certificates
Create `v3.ext`:
```
authorityKeyIdentifier=keyid,issuer
basicConstraints=CA:FALSE
keyUsage=digitalSignature, nonRepudiation, keyEncipherment, dataEncipherment
subjectAltName=@alt_names

[alt_names]
DNS.1 = [server IP addr / server URL / localhost, e.g. 192.168.10.1]
```
Run:
```sh
openssl genrsa -des3 -out rootCA_private.key 1024
# 生成CA的RSA私钥

openssl req -new -key rootCA_private.key -out rootCA_private.csr
# 生成根证书申请文件

openssl x509 -req -extensions v3_ca -days 3650  -signkey rootCA_private.key -in rootCA_private.csr -out rootCA_cert.crt
# 生成crt根证书

openssl req -x509 -new -nodes -key rootCA_private.key -sha256 -days 3650 -out rootCA_cert.pem
# 生成pem根证书


openssl req -new -sha256 -nodes -out server.csr -newkey rsa:1024 -keyout server_private.key
# 生成服务器证书密钥, 其中 Common Name 与 v3.ext 中的 DNS.1 相同, 设置为服务器地址

openssl x509 -req -in server.csr -CA rootCA_cert.pem -CAkey rootCA_private.key -CAcreateserial -out server_cert.crt -days 500 -sha256 -extfile v3.ext
# 生成crt服务器证书
```

### Build
```sh
git clone git@github.com:FutureXiang/OpenSSLWebServer.git
cd OpenSSLWebServer

vim common.h
# 修改 ROOTCERTPEM, ROOTKEYPEM, SERVERKEYPEM, SERVERPEM 为上面生成的证书和密钥地址

make
```

### Run
Requires **privilege escalation (sudo)**: `sudo ./MyWebServer`
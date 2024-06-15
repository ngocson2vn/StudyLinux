wget https://github.com/curl/curl/releases/download/curl-8_8_0/curl-8.8.0.tar.gz
tar -xf curl-8.8.0.tar.gz
cd curl-8.8.0
./configure --with-openssl
make
make install

cp /usr/lib/libcurl.so.4.8.0 /usr/lib/x86_64-linux-gnu/
cd /usr/lib/x86_64-linux-gnu/
ln -sf libcurl.so.4.8.0 libcurl.so.4
curl https://google.com
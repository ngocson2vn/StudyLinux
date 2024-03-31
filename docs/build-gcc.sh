apt -y install build-essential

# 8.3.0
wget http://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-8.3.0/gcc-8.3.0.tar.xz
tar -xf gcc-8.3.0.tar.xz
cd gcc-8.3.0
vim ./contrib/download_prerequisites
# Set base_url as below:
# base_url='http://gcc.gnu.org/pub/gcc/infrastructure/'

find -name \*.tar.\* -delete

./contrib/download_prerequisites
./configure --disable-multilib
make -j 96 && make install


# 8.3.5


# 9.5.0
wget http://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-9.5.0/gcc-9.5.0.tar.gz
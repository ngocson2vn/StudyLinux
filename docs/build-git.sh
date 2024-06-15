# To fix symlinks, must upgrade git to version 2.38.1

sudo apt install -y software-properties-common libssl-dev libcurl4-openssl-dev gettext

wget https://mirrors.edge.kernel.org/pub/software/scm/git/git-2.38.1.tar.gz
tar -xzf git-2.38.1.tar.gz
cd git-2.38.1
make prefix=/usr all
sudo make prefix=/usr install
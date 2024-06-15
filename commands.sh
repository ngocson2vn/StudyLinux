LC_CTYPE=en_US.UTF-8
LC_ALL=en_US.UTF-8

########################################################################################################################
# Memory
########################################################################################################################
cat /proc/meminfo | head -n 3
MemTotal:       527745744 kB
MemFree:        57392660 kB
MemAvailable:   361770576 kB

# Get PAGESIZE
grep KernelPageSize /proc/self/smaps | head -1
KernelPageSize:        4 kB
4 kB = 1 * 1024 = 4096 bytes

getconf PAGESIZE
4096

########################################################################################################################
# Golang
########################################################################################################################
# Install gvm
bash < <(curl -s -S -L https://raw.githubusercontent.com/moovweb/gvm/master/binscripts/gvm-installer)
source /home/laniakea/.gvm/scripts/gvm

# Install go
cd son.nguyen
apt-get download bison
dpkg -x "bison_2%3a3.0.4.dfsg-1+b1_amd64.deb" ~/.local
export PATH=~/.local/usr/bin:$PATH
exec bash -l
which bison
gvm install go1.18.4 --prefer-binary && gvm use go1.18.4 --default
go version


git config --global url."git@code.laniakea.org:".insteadOf https://code.laniakea.org/
git commit --amend --author="Son Nguyen <son.nguyen@laniakea.com>" --no-edit
git config --global user.name "Son Nguyen"
git config --global user.email "son.nguyen@laniakea.com"
export GOPATH=~/go
export GONOPROXY="code.laniakea.org/*"
export GONOSUMDB="code.laniakea.org/*"
export GOPRIVATE="code.laniakea.org/*"
exec bash -l
go install code.laniakea.org/lagrange/crontask@latest

# Install python3
sudo apt update; sudo apt install -y build-essential libssl-dev zlib1g-dev \
libbz2-dev libreadline-dev libsqlite3-dev curl \
libncursesw5-dev xz-utils tk-dev libxml2-dev libxmlsec1-dev libffi-dev liblzma-dev
pyenv install 3.8.1
export PYTHON_CONFIGURE_OPTS="--with-fpectl"
export CPPFLAGS="-I/usr/include/openssl"
export LDFLAGS="-L/usr/lib64"
pyenv install -kf 2.7.16
pyenv install -kf 3.9.0

# vimrc
set mouse-=a
set backupdir=.backup/,~/.backup/,/tmp//
set directory=.swp/,~/.swp/,/tmp//
set undodir=.undo/,~/.undo/,/tmp//

# sudo
:w !sudo tee %


# systemctl
systemctl --type=service
systemctl list-units --type=service

# ag
apt install silversearcher-ag
apt-get download silversearcher-ag
dpkg -x silversearcher-ag_1.0.2-1_amd64.deb ./silversearcher

apt-get download protobuf-compiler=v3.9.2

# Change PS1
export PS1="[\w]# "

# Open http server
python -m http.server 8080


# GPU
In order to know the current Compute Mode, use the following command

nvidia-smi --query | grep 'Compute Mode'
In order to set the Compute Mode, use the following command

nvidia-smi -c 1
Where $i could be 0, 1, 2 or 3. Meaning of these numbers are given below -

0 Default
1 Exclusive_Thread
2 Prohibited 
3 Exclusive_Process
Answer to your question

# Get Ethernet card limit
apt install ethtool
ethtool eth0

# macos
sudo lsof -i -P | grep LISTEN | grep 3306

# VSCode with Remote-SSH
Update PATH in ~/.profile
killall node

# List loaded shared libraries
cat /proc/212/maps | awk '{print $6;}' | grep '\.so' | sort | uniq

# sort for human
du -hs * | sort -hr | head -10

# Print ld.so.cache
ldconfig -p

# VSCode
# .vscode/settings.json
Set C_Cpp.default.compileCommands to activate code autocomplete
"C_Cpp.default.compileCommands": "/home/laniakea/son.nguyen/app-dev/build64_release/compile_commands.json"

# gdb pretty print
https://github.com/Microsoft/vscode-cpptools/issues/1414
https://sourceware.org/gdb/wiki/STLSupport

"setupCommands": [
    {
        "description": "Test",
        "text": "python import sys;sys.path.insert(0, '/usr/share/gcc-8/python');from libstdcxx.v6.printers import register_libstdcxx_printers;register_libstdcxx_printers(None)",
        "ignoreFailures": false
    },
    {
        "description": "Enable pretty-printing for gdb",
        "text": "-enable-pretty-printing",
        "ignoreFailures": true
    }
]

########################################################################################################################
# git
########################################################################################################################
git checkout tags/<tag_name> -b <branch_name>

# git delete untracked files
git ls-files --others --exclude-standard | xargs rm -rf
# git
git log --all --grep="message"

git remote add origin git@github.com:ngocson2vn/dissect_llama_cpp.git

# clone a specific commit
git init
git remote add origin git@code.laniakea.org:bpt/tensorflow.git
git fetch origin --depth 1 6c5b4ba75d45899bb002c9ad6c8d91663b02f206
git checkout FETCH_HEAD
git checkout -b v1.15.3

git config --global --add --bool push.autoSetupRemote true

# submodule
git submodule add https://github.com/tensorflow/tensorflow.git third_party/tensorflow

git config -f .gitmodules submodule.tensorflow.shallow true
git submodule update --init --recursive
git submodule status

########################################################################################################################
# apt
########################################################################################################################
apt list --installed

# List files the package installed onto your system
dpkg-query -L libssl-dev

apt install mariadb-client-10.3

sudo add-apt-repository -r ppa:git-core/ppa

########################################################################################################################
# Linux kernel
########################################################################################################################
# Install linux headers
apt-get install linux-headers-$(uname -r)

# Dynamic Kernel Module Support - DKMS
lsmod | grep nvidia
modinfo nvidia

brew services restart mysql
# Or, if you don't want/need a background service you can just run:
/opt/homebrew/opt/mysql/bin/mysqld_safe --datadir=/opt/homebrew/var/mysql

# Log file
/opt/homebrew/var/mysql/RMVF2G16GQ.err

# update certs
sudo apt-get install ca-certificates

########################################################################################################################
# screen
########################################################################################################################
# Kill session
screen -X -S session_name quit



########################################################################################################################
# Container
########################################################################################################################
# How to get memory limit in bytes
# Step 1: Get cgroup path
# app container
cat /proc/70/cgroup 


# Step 2: Get memory.limit_in_bytes
# app
cat /sys/fs/cgroup/memory/kubepods/burstable/pod1ab8437e-426e-4899-9a36-87bf086eb16c/4a282be6bd36b1eb73debde75e33308478135db46f66e500e4f2c28b1f1f3458/memory.limit_in_bytes
17179869184

# RSS in bytes
cat /sys/fs/cgroup/memory/kubepods/burstable/pod1ab8437e-426e-4899-9a36-87bf086eb16c/4a282be6bd36b1eb73debde75e33308478135db46f66e500e4f2c28b1f1f3458/memory.stat | grep rss

# Get the number of sockets
lscpu

########################################################################################################################
# gdb
########################################################################################################################
set scheduler-locking on
set scheduler-locking step
set print elements 0
set pagination off

# Check disassembly-flavor 
show disassembly-flavor


# Fix Failed building wheel of h5py
$ sudo ln -s /usr/include/locale.h /usr/include/xlocale.h
$ pip install Cython==0.29.36
$ pip install pkgconfig


# Fix No module named '_ctypes' when installing python 3.7.3
sudo apt install libffi-devel

ps -eo pid,etime,cmd

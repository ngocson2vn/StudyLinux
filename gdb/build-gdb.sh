apt install texinfo -y

# Step-1: Download source code.
You can download source code of all release from http://ftp.gnu.org/gnu/gdb/
$ wget "https://ftp.gnu.org/gnu/gdb/gdb-10.2.tar.gz"

# Step-2: Extract it
$ tar -xvzf gdb-10.2.tar.gz

# Step-3: Configure and Compile it.
$ cd gdb-10.2
gdb-10.2$ ./configure --prefix=/usr
gdb-10.2$ make 
# This step will take a bit of time. So you can sit back and have cup of coffee for a while. 
# Once it is completed, you can locate gdb binary located at gdb-10.2/gdb/gdb

# Step-4: Install GDB.
$ make install
# By default this will install gdb binaries in /usr/local/bin and libs in /usr/local/lib
# Congratulation, you have successfully compiled and installed GDB.

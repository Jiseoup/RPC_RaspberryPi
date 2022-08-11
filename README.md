# RPC BETWEEN RASPBERRY PI <a href="https://emoji.gg/emoji/1348_raspberrypi"><img src="https://cdn3.emoji.gg/emojis/1348_raspberrypi.png" width="40px" height="40px" alt="raspberrypi"></a>
This document describes the **Remote Procedure Call(RPC)** between `Raspberry Pi`.  
I recommend you to read [this document](https://github.com/Jiseoup/rpi_fixed_ip) and allocate fixed ip to `Raspberry Pi` before doing this.

## 1. REQUIRED INSTALLATION
We install and use the **rpcbind** package.  
Packages **nfs-common** and **nfs-kernel-server** are needed to use RPC.
```console
$ sudo apt-get update
$ sudo apt-get install rpcbind
$ sudo apt-get install nfs-common
$ sudo apt-get install nfs-kernel-server
```

You can check your RPC information through the command below.
```console
pi@raspberrypi:~ $ rpcinfo
   program version netid     address                service    owner
    100000    4    tcp6      ::.0.111               portmapper superuser
    100000    3    tcp6      ::.0.111               portmapper superuser
    100000    4    udp6      ::.0.111               portmapper superuser
    100000    3    udp6      ::.0.111               portmapper superuser
    100000    4    tcp       0.0.0.0.0.111          portmapper superuser
    100000    3    tcp       0.0.0.0.0.111          portmapper superuser
    100000    2    tcp       0.0.0.0.0.111          portmapper superuser
    100000    4    udp       0.0.0.0.0.111          portmapper superuser
    100000    3    udp       0.0.0.0.0.111          portmapper superuser
    100000    2    udp       0.0.0.0.0.111          portmapper superuser
    100000    4    local     /run/rpcbind.sock      portmapper superuser
    100000    3    local     /run/rpcbind.sock      portmapper superuser
```

## 2. GENERATE CLIENT AND SERVER STUB
First, create the work directory and move to that directory.
```console
$ mkdir RPC
$ cd RPC
```
Now, we will create a file in `.x` format.  
After that, we will generate a **stub** of the client and server through the `.x file` and **rpcgen**.
```console
$ vim rpc.x
```
### rpc.x
```xdr
program RPC_PROG {
    version RPC_VERS {
	int id(int)=1;
	string name(string)=2;
    }=1;
}=0x20000001;
```

### Generate Stub File
* -a : generate all files, including samples.
* -C : ANSI C mode.
```console
$ rpcgen -a -C rpc.x
```

You can see the generated stub file.
```console
pi@raspberrypi:~/RPC $ ls
Makefile.rpc  rpc_client.c  rpc_clnt.c  rpc.h  rpc_server.c  rpc_svc.c  rpc.x
```

## 3. EDIT CODES AND COMPILE
Edit the codes `rpc_server.c` and `rpc_client.c` and compile using `Makefile.rpc`.  
Edit the code as below.

### rpc_server.c
```c

```

### rpc_client.c
```c

```

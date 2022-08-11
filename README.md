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
#include "rpc.h"

int *
id_1_svc(int *argp, struct svc_req *rqstp)
{
	static int result;

	result = *argp; // Assign the recalled data.
	printf("INTEGER : %d is called\n", result);

	return &result;
}

char **
name_1_svc(char **argp, struct svc_req *rqstp)
{
	static char *result;

	result = *argp; // Assign the recalled data.
	printf("STRING : %s is called\n", result);
	    
	return &result;
}
```

### rpc_client.c
```c
#include "rpc.h"

void
rpc_prog_1(char *host, int a, char* b) // Add parameters. (int a, char* b)
{
	CLIENT *clnt;
	int  *result_1;
	int  id_1_arg;
	char * *result_2;
	char * name_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, RPC_PROG, RPC_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	// Assigns the data to be called to a variable.
	id_1_arg = a;
	name_1_arg = b;

	result_1 = id_1(&id_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	// When the call is successful.
	else {
	    printf("INTEGER : %d\n", *result_1);
	}

	result_2 = name_1(&name_1_arg, clnt);
	if (result_2 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	// When the call is successful.
	else{
	    printf("STRING : %s\n", *result_2);
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	// Because we added two parameters, change the condition to (argc < 4).
	if (argc < 4) {
		printf ("usage: %s server_host INTEGER STRING\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	rpc_prog_1 (host, atoi(argv[2]), argv[3]);
exit (0);
}
```

When you have finished editing the code, compile it using the command below.
* -f : Read FILE as a makefile.  
	* -f FILE, --file=FILE, --makefile=FILE
```console
$ make -f Makefile.rpc
```

You can see the generated files.
```console
pi@raspberrypi:~/RPC $ ls
Makefile.rpc  rpc_client.c  rpc_clnt.c  rpc.h       rpc_server.c  rpc_svc.c  rpc.x
rpc_client    rpc_client.o  rpc_clnt.o  rpc_server  rpc_server.o  rpc_svc.o
```

## 4. TEST THE SAMPLE CODE
We test the sample code on one `Raspberry Pi`.  
Of course, **RPC calls** from different `Raspberry Pi` are also possible.  

Open two terminals and call the `localhost` server from the client as shown in the picture below.

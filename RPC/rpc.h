/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RPC_H_RPCGEN
#define _RPC_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define RPC_PROG 0x20000001
#define RPC_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define id 1
extern  int * id_1(int *, CLIENT *);
extern  int * id_1_svc(int *, struct svc_req *);
#define name 2
extern  char ** name_1(char **, CLIENT *);
extern  char ** name_1_svc(char **, struct svc_req *);
extern int rpc_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define id 1
extern  int * id_1();
extern  int * id_1_svc();
#define name 2
extern  char ** name_1();
extern  char ** name_1_svc();
extern int rpc_prog_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RPC_H_RPCGEN */
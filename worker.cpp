#include <string.h>
#include <stdio.h>
#include "rpc.h"

char rpcBuffer[1024 * 1024];

int main()
{
	RpcInitialize(rpcBuffer, sizeof(rpcBuffer));
}

extern "C" void RpcInitialized()
{
	puts("Worker initialized");

	const char *msg = "Hello from Worker";
	RpcSend(msg, strlen(msg) + 1);
	RpcSend("PONG", 5);
}

extern "C" void RpcReceived()
{
	unsigned size;
	const void *data = RpcBeginReceive(&size);
	printf("> Game: (%u) %s\n", size, data);
	RpcEndReceive();
}



extern "C" {

	void RpcInitialize(const void *buffer, unsigned size);
	int RpcReady();
	void RpcSend(const void *data, unsigned size);
	const void *RpcBeginReceive(unsigned *size);
	void RpcEndReceive();

}


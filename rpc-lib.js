
mergeInto(LibraryManager.library, {
	RpcInitialize: function(buffer, size) {
		const rpc = {
			messageTarget: ((self || window).globalWorker || self),
			receiveBuffer: buffer,
			receiveBufferSize: size,
			receiveWritePtr: buffer,
			receiveReadPtr: buffer + (size >> 1),
			receiveSize: 0,
			ready: true,
			initialized: false,
		}

		g__rpc = rpc;

		rpc.messageTarget.onmessage = function(event) {
			const msg = event.data
			switch (msg.type) {
			case 'data':
				Module.HEAP8.set(msg.data, rpc.receiveWritePtr)
				rpc.receiveSize = msg.data.length

				{
					const t = rpc.receiveWritePtr;
					rpc.receiveWritePtr = rpc.receiveReadPtr;
					rpc.receiveReadPtr = t;
				}

				Module._RpcReceived();

				break;

			case 'init':
				if (!rpc.initialized) {
					rpc.initialized = true;
					rpc.messageTarget.postMessage({ type: 'init' })
					Module._RpcInitialized();
				}
				break;

			case 'done':
				rpc.ready = true;
				break;
			}
		}

		rpc.messageTarget.postMessage({ type: 'init' })
	},

	RpcReady: function() {
		const rpc = g__rpc;
		return (rpc.initialized && rpc.ready) ? 1 : 0;
	},

	RpcSend: function(data, size) {
		const rpc = g__rpc;
		if (!rpc.initialized || !rpc.ready) return;

		rpc.messageTarget.postMessage({
			type: 'data',
			data: Module.HEAP8.slice(data, data + size),
		})
		rpc.ready = false
	},

	RpcBeginReceive: function(size) {
		const rpc = g__rpc;
		if (rpc.receiveSize == 0) return 0;
		HEAP32[size >> 2] = rpc.receiveSize;
		return rpc.receiveReadPtr;
	},

	RpcEndReceive: function() {
		const rpc = g__rpc;
		rpc.receiveSize = 0;
		rpc.messageTarget.postMessage({
			type: 'ready',
		})
	},
});

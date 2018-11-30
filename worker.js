
self.onmessage = function() {
	switch (event.type) {
	case 'data':
		HEAP8.set(event.data.data, dst);
		Module._receive(event.data.length);
		break;
	}
}

self.postMessage({ type: 'init' })

importScripts('build/worker.js')


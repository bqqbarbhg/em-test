cmd /C emcc game.cpp -o build/game.js -O0 -s WASM=1 -s USE_WEBGL2=1 --js-library rpc-lib.js ^
	-s "EXPORTED_FUNCTIONS=['_main', '_RpcInitialized', '_RpcReceived']"

cmd /C emcc worker.cpp -o build/worker.js -O0 -s WASM=1 --js-library rpc-lib.js ^
	-s "EXPORTED_FUNCTIONS=['_main', '_RpcInitialized', '_RpcReceived']"


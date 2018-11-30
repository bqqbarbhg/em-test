#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <GLES2/gl2.h>
#include <string.h>
#include "rpc.h"

EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

void mainLoop();

char rpcBuffer[1024 * 1024];

extern "C" void RpcInitialized()
{
	puts("Game initialized");
}

extern "C" void RpcReceived()
{
}

int main()
{
	RpcInitialize(rpcBuffer, sizeof(rpcBuffer));

	EmscriptenWebGLContextAttributes attributes;
	attributes.alpha = false;
	attributes.depth = false;
	attributes.antialias = false;
	attributes.majorVersion = 2;
	attributes.minorVersion = 1;

	emscripten_webgl_init_context_attributes(&attributes);
	context = emscripten_webgl_create_context("view", &attributes);

	emscripten_webgl_make_context_current(context);

	emscripten_set_main_loop(&mainLoop, 0, false);
}

void mainLoop()
{
	unsigned size;
	const void *data = RpcBeginReceive(&size);
	if (data != NULL) {
		printf("> Worker: (%u) %s\n", size, data);
		RpcEndReceive();

		const char *msg = "Hello from Game";
		RpcSend(msg, strlen(msg) + 1);
	}

	glClearColor(float(0x64) / 0xFF, float(0x95) / 0xFF, float(0xED) / 0xFF, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


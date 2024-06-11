#include <pspkernel.h>
#include <pspdebug.h>

#include <leptonica/allheaders.h>

PSP_MODULE_INFO("convert-to-gray", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int done = 0;

int exit_callback(int arg1, int arg2, void *common) {
	done = 1;
	return 0;
}

int CallbackThread(SceSize args, void *argp) {
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

int SetupCallbacks(void) {
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0) { sceKernelStartThread(thid, 0, 0); }

	return thid;
}

int main() {
    pspDebugScreenInit();
	SetupCallbacks();

    while (!done) {
        PIX *pix = pixRead("input.png");
        PIX *pixGray = pixConvertRGBToGray(pix, 0.3, 0.5, 0.2);
        pixWrite("output.png", pixGray, IFF_PNG);
        pixDestroy(&pix);
        pixDestroy(&pixGray);
	}
    sceKernelExitGame();
    return 0;
}
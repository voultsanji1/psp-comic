#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>

/* Setup del modulo */
PSP_MODULE_INFO("ComicReader", 0, 1, 1);
PSP_MAIN_THREAD_PARAMETER(256, 256, 32, 0, NULL);

#define printf pspDebugScreenPrintf

int exit_callback(int arg1, int arg2, void *common) {
    sceKernelExitGame();
    return 0;
}

int callback_thread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

int setup_callbacks(void) {
    int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
    if(thid >= 0) sceKernelStartThread(thid, 0, 0);
    return thid;
}

int main() {
    pspDebugScreenInit();
    setup_callbacks();

    printf("PSP Comic Reader v0.1\n");
    printf("Caricamento fumetti da ms0:/PICTURE/...\n");
    printf("Premi HOME per uscire.\n");

    while(1) {
        sceDisplayWaitVblankStart();
    }

    return 0;
}

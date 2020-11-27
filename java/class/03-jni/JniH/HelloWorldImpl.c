#include "jni.h"
#include "main_HelloWorld.h"
 
//#include otherheaders
 
JNIEXPORT void JNICALL
Java_main_HelloWorld_displayHelloWorld(JNIEnv *env, jobject obj)
{
    printf("Helloworld!\n");
    return;
}

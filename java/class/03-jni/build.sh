#!/bin/bash 
echo "build start"
javac main/HelloWorld.java -h JniH
pushd ./JniH
gcc -c HelloWorldImpl.c  -I/usr/lib/jvm/java-8-openjdk-amd64/include -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux
gcc -shared -fPIC -o libHelloWorldImpl.so HelloWorldImpl.o

sudo cp libHelloWorldImpl.so  /usr/lib/x86_64-linux-gnu/jni
popd
javac main/HelloWorld.java
java main.HelloWorld


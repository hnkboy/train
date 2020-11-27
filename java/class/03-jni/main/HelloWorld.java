package main;

public class HelloWorld {

    public native void displayHelloWorld();//所有native关键词修饰的都是对本地的声明
    static {

	System.out.println("java.library.path:-----------");
	System.out.println(System.getProperty("java.library.path"));
        System.loadLibrary("HelloWorldImpl");//载入本地库
        System.out.println("测试");
    }
    public static void main(String[] args) {
        new HelloWorld().displayHelloWorld();
    }
}

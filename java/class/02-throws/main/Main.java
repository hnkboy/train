package main;

import pack2.Employee;




public class Main {
    public static void main(String args[]) {
        System.out.println("helloworld");
        try {
            test();
        } catch (Exception e){
            System.out.printf("错误");
        }
        //test1();

        try {
            printFile();
        } catch (Exception e){
            System.out.printf("错误");
        }

        try {
            printFile1();
        } catch (Exception e){
            System.out.printf("错误1");
        }
    }
    /*
     *
     * throws
     * Exception:如果出现未知错误，会跑出Exception。如果这里加了异常捕捉，调用test方法时，就要加上try...catch
     */
    private static void test() throws Exception {
        int x = 1;
        int y = 2;
        int z = 3;
        if (x + y < z) {
            System.out.printf("逻辑正确！");
        } else {
            throw new Exception("test方法有问题"); // 手动抛出一个异常
        }
    }
    /*
    private static int test1() {

        try {
            System.out.printf("try1");
            return 1;
        } finally {
            System.out.printf("try2");
            return 2;
        }
    }
    private static void printFile() throws Exception {

        try(Employee input = new Employee()) {
            input.move();
        }
    }*/
    private static void printFile()  throws Exception {
        try {
            Employee a =  new Employee();
            a.move();
        } finally{
            System.out.printf("try-finally");
        }
    }

    private static void printFile1()  throws Exception {
        int array[]={20,20,40};
        int num1=15, num2=10;
        int result=10;
        try{
            result = num1/num2;
            System.out.println("结果为 " + result);
            for(int i =5;i >=0; i--) {
                System.out.println ("数组的元素值为 " + array[i]);
            }
        }
        catch (Exception e) {
            System.out.println("触发异常 : "+e);
        }
    }
}


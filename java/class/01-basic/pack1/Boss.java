package pack1;

import pack2.t1.Test1;
import pack2.Employee;
import inter.Man;
import person.Doctor;
import java.util.logging.*;
import java.util.HashMap;
import java.util.Map;

public class Boss {
    public static void main(String args[]) {

        new Test1().move();
        final Employee em = new Employee();
        final Doctor dr = new Doctor("张三", 1, "医院", "诊断");
        em.move();
        new Man().drinkMilk();
        new Man().eatBread();
        dr.introduction();
        dr.work();
        test();
    }

    private static void test()
    {
        Map<Integer, String> map = new HashMap<>();
        map.put(1,"demo1");
        System.out.println("当前map集合中的所有的元素：" + map);
        Object put = map.put(2,"demo2");
        System.out.println("当前map集合中的所有的元素：" + map);
        if(map.get(1) != null) map.put(1,"String ");
        System.out.println("当前map集合中的所有的元素：" + map);
        // Create a Logger with class name GFG
        Logger logger = Logger.getLogger(Boss.class.getName());

        // Call info method
        logger.info("Message 1");
        logger.info("Message 2");



    }

}
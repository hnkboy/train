package pack1;

import pack2.t1.Test1;
import pack2.Employee;
import inter.Man;
import person.Doctor;
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
    }
}
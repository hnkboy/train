package inter;

public class Man implements Bread,Milk{
    //实现了Bread接口中eatBread方法
    public void eatBread(){
       System.out.println("吃面包");
     }
  //实现了Milk接口中drinkMilk方法
    public void drinkMilk(){
       System.out.println("喝牛奶");
     }
  }
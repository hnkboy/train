package person;
public class Person {
    // 名字
    protected String name;
    // 编号
    protected int id;
    // 工作环境
    protected String environment;
    // 特长
    protected String speciality;

    public Person(String myName, int myid, String myEnvironment, String mySpeciality) {
        name = myName;
        id = myid;
        environment = myEnvironment;
        speciality = mySpeciality;
    }

    /*
    * 工作地点
    */
    public void work() {
        System.out.println(name + "在" + environment + "工作" + '。');
    }

    /*
    * 工作能力
    */
    public void ability() {
        System.out.println(name + "我会" + speciality + '。');
    }

    /*
    * 自我介绍
    */
    public void introduction() {
        System.out.println("大家好！我是" + id + "号" + name + '。');
    }

}

package person;

public class Doctor extends Person{

	public Doctor(String myName, int myid, String myEnvironment, String mySpeciality) {
		super(myName, myid, myEnvironment, mySpeciality);

	}
	/*
	 * 自我介绍
	 */
	void introductionMy() {
		super.introduction();
	}
	/*
	 * 自我介绍 覆写
	 */
	public void introduction() {
		System.out.println("大家好！我是一名医生");
	}

	/*
	 * 工作职责
	 */
	public void duty() {
		System.out.println("治病救人是我的职责");
    }
}

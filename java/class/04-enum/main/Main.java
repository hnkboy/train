package main;
import types.AddressFamily;
//import types.AddressFamily;
import types.IpDscp;

public class Main {

    static {
        IpDscp a  = IpDscp.ADDRESS_IP61;
        AddressFamily aa = AddressFamily.ADDRESS_IP4;
        byte b = 0;
        byte c;
        c = a.value;

        //b =(byte)((int)b | (int)c);
        b |=  c;
        System.out.println("测试" + a.value + b + aa.value +AddressFamily.forValue(0) +IpDscp.forValue((byte)1) );
    }
    public static void main(String[] args) {

        System.out.println("value" );

    }
}

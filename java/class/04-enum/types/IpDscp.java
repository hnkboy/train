package types;

public enum IpDscp {
    ADDRESS_IP41((byte)0),
    ADDRESS_IP61((byte)1);

    public final byte value;

    IpDscp(final byte value) {
        this.value = value;
    }

    public static IpDscp forValue(final byte value) {
        for (IpDscp enumeration : IpDscp.values()) {
            if (value == enumeration.value) {
                return enumeration;
            }
        }
        return IpDscp.values()[0];
    }

}
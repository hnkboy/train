package types;

public enum AddressFamily {
    ADDRESS_IP4(0),
    ADDRESS_IP6(1);

    public final int value;

    AddressFamily(final int value) {
        this.value = value;
    }

    public static AddressFamily forValue(final int value) {
        for (AddressFamily enumeration : AddressFamily.values()) {
            if (value == enumeration.value) {
                return enumeration;
            }
        }
        return null;
    }

    public int getValue() {
        return value;
    }
}

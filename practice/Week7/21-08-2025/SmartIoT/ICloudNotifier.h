enum class Status {
    AC_ON,
    AC_OFF,
    HEATER_ON,
    HEATER_OFF,
};

class ICloudNotifier {
    public:
        virtual void notify(Status status) = 0;
        virtual ~ICloudNotifier() = default;
};
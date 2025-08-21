class IDeviceControl {
    public:
        virtual void turnHeaterOn() = 0;
        virtual void turnHeaterOff() = 0;
        virtual void turnACOn() = 0;
        virtual void turnACOff() = 0;
        virtual ~IDeviceControl() = default;
};
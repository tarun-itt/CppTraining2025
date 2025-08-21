class ISensor {
    public:
        virtual int readTemperature() = 0;
        
        virtual ~ISensor() = default;
};
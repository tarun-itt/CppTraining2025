#include <iostream>

class PIE{ //proto indo european language
    public:
    int a=1;
    int b=2;
    PIE(){
        std::cout<<"PIE called\n";
    }
    PIE(int i, int j):a(i),b(j){std::cout<<"PIE CALLED";}

   virtual  void PIEfun(){
        std::cout<<"Function of pie called\n";
    }
};

class IndoIranian: public PIE{
    public:
    int c=3;
    int d=4;
    IndoIranian(){
        PIE(10,34); //temperory object
        std::cout<<"Indo Iranian called\n";
    }
};

class VedicSanskrit: public IndoIranian{
    public:
    int e=5;
    int f=6;
    VedicSanskrit(){
        std::cout<<"vedic snaskrit called\n";
    }
};

class Avestan: public IndoIranian{
    public:
    int g=7;
    int h=8;
    Avestan(){
        std::cout<<"Avestan Called\n";
    }
};

class ClassicalSanskrit: public VedicSanskrit{
    public:
    int i=9;
    int j=10;
    ClassicalSanskrit(){
        std::cout<<"Classical Sanskrit called\n";
    }
    void PIEfun(){
        std::cout<<"Classica sanskrit version of pieFUn\n";
    }
};

class protoDravidian{
    public:
    int k=11;
    protoDravidian(){
        std::cout<<"Proto dravidian called\n";
    }
};

class Telugu:public protoDravidian,  public ClassicalSanskrit{
    public:
    int l =12;
    Telugu(){
        std::cout<<"Telugu called\n";
    }
    void PIEfun(){
        std::cout<<"Function of telugu called\n";
    }
};


int main(){
    PIE* cs = new ClassicalSanskrit();
    cs->PIEfun();
    cs->PIE::PIEfun();
    std::cout<<"\n";
    PIE t = Telugu();
    t.PIEfun();
    return 0;
}
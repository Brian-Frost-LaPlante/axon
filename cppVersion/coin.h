    #include <random> 
	using namespace std;
    bool coin(float prob) 
    {
        random_device rd; 
        mt19937 gen(rd()); 
        uniform_real_distribution<float> dis(0.0,1.0); 
        return (dis(gen)<prob);
    }

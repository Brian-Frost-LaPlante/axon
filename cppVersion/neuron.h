#include <vector>
#include<iostream>
#include <math.h>

class neuron
{
private:

	std::vector<int> spikes;
	int i;
	float V; float JE; float JI;
	float V0; float JE0; float JI0;
	float t;
	float w; float tau; float tau_s; float v_th; float ref;
	int strength;
	float refcount;

public:

	neuron(float dur, float kick, float vtau, float jtau,
					  float thresh, int str, float Vinit);
	
	void update(float in);

	float getV();
	float getJE();
	float getJI();
	std::vector<int> getSpikes();
	float getLastSpike();
	int getStrength();
};

neuron::neuron(float dur, float kick, float vtau, float jtau,
						  float thresh, int str, float Vinit)
{
	spikes.assign((int)(10*(dur+0.1)),0);
	i = 0; 
	t = 0; 
	V = Vinit; JE = 0; JI = 0;
	V0 = Vinit; JE0 = 0; JI0 = 0; 
	w = kick;
	tau = vtau; tau_s = jtau; v_th = thresh; 
	ref = 1; // This could be an input in some other version of the constructor
	refcount = 1;
	strength = str;
}

void neuron::update(float in)
{
	if(in>0)
	{
		t = 0.1;
		JE = JE+in*w;
		JE0 = JE;
		JI0 = JI;
		V0 = V;	
		V = (V0 - ((JE0-JI0)*tau_s)/(tau_s-tau))*exp(-t/tau) +
			(((JE0-JI0)*tau_s)/(tau_s-tau))*exp(-t/tau_s);
	}
	else if(in<0)
	{
		t = 0.1;
		JI = JI + (-in)*w;
		JE0 = JE;
		JI0 = JI;
		V0 = V;
		V = (V0 - ((JE0-JI0)*tau_s)/(tau_s-tau))*exp(-t/tau) +
			(((JE0-JI0)*tau_s)/(tau_s-tau))*exp(-t/tau_s);
	}
	else
	{
		t = t + 0.1;
		JE = JE0*exp(-t/tau_s);
		JI = JI0*exp(-t/tau_s);
		V = (V0 - ((JE0-JI0)*tau_s)/(tau_s-tau))*exp(-t/tau) +
			(((JE0-JI0)*tau_s)/(tau_s-tau))*exp(-t/tau_s);
	}

	if((V>v_th)&(refcount>=ref))
	{
		t = 0;
		refcount = 0;
		JE0 = JE; JI0 = JI; V = 0; V0 = 0;
		spikes.at(i) = strength;
	}
	
	i = i+1;
	refcount = refcount + 0.1;

}

float neuron::getV()
{
	return V;
}


float neuron::getJE()
{
	return JE;
}


float neuron::getJI()
{
	return JI;
}

std::vector<int> neuron::getSpikes()
{
	return spikes;
}

float neuron::getLastSpike()
{
	return (float) spikes.at(i-1);
}

int neuron::getStrength()
{
	return strength;
}

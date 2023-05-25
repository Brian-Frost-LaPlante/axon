#include "neuron.h"
#include <random>
#include "damData.h"
#include <cmath>

using namespace std;

typedef vector< vector<int> > iMatrix;

fMatrix damdata = damData();

// Poisson Train creates the global input
// It uses a uniform distribution from 0-1 and
// compares the sample to lambda. If it is less 
// thank lambda, a spike has occured.

vector<float> PoissonTrain(int T, float lambda)
{
	vector<float> global_in;
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> dis(0.0,1.0);
	global_in.assign(T,false);
	for(int i=0;i<T;i++)
	{
		global_in.at(i) = (dis(gen) < lambda);
	}
	return global_in;
}

vector<float> guess(vector<float> input)
{
	int L = input.size();
	vector<float> finalguess;
	finalguess.assign(L,0);
	vector<float> iternum;
	for(float i = 1; i<9;i++)
	{
		iternum.push_back(i);
	}

	for(int i = 0;i<(L-16);i++)
	{
		iternum.push_back(9);
	}

	for(float i = 8; i>0;i--)
	{
		iternum.push_back(i);
	}

	fMatrix guesses;
	vector<float> zvec;
	vector<float> aguess;
	zvec.assign(L,0);
	aguess.assign(9,0);
	guesses.assign(9,zvec);
	int row = 0;
	int startat = 0;
	int ind;	

	for(int i = 0; i < (L-8); i++)
	{
	ind = 0;
	for(int j = 0; j < 9; j++)
	{
		ind = ind + (int)input.at(i+j)*(pow(2,j));
	}
	
	aguess = damdata.at(ind);
		
	for(int j = 0; j < 9; j++)
	{
		(guesses.at(row%9)).at(startat + j) = aguess.at(j);
	}
	row++; startat++;
	}

	for(int i = 0; i < L; i++)
	{
		for(int j=0; j < 9; j++)
		{
			finalguess.at(i) = finalguess.at(i) + ((guesses.at(j)).at(i))/iternum.at(i);
		}
		if(finalguess.at(i) < 0.5)
		{
			finalguess.at(i) = 0;
		}
		else
		{
			finalguess.at(i) = 1;
		}
	}

	for(int i = 0;i<9;i++)
	{
	finalguess.at(i) = (guesses.at(0)).at(i);
	}
	return finalguess;
}

// NetSim is the function called for each realization
// of a network. It needs to do quite a bit. It first
// uses PoissonTrain to generate the global input. It 
// then updates the network's elements based on the 
// spikes seen at each neuron at each time.
// ins and outs contain the indices of vectors that the cells (which correspond to rows) point to. 

vector<float> NetSim(fMatrix ins, fMatrix outs, vector<neuron> cells, 
			float lambda, vector<bool> damage, int nAx)
{
	vector<float> global_in = PoissonTrain(1000, lambda);
	int dur = ((cells.front()).getSpikes()).size()-1;
	int N = cells.size();
	fMatrix AllSpikes; // this is the inputs to the neurons
	vector<float> a;
	a.assign(1000,0);
	AllSpikes.assign(nAx, a);
	AllSpikes.push_back(global_in);
	vector<int> numspikes;
	vector<float> t0;
	t0.assign(N,0);
	vector<float> tf = t0;
	numspikes.assign(N,0);
	vector<bool> first;
	first.assign(N,true);
	vector<float> meanISI;
	meanISI.assign(N,0);
	vector<float> damaged_in;

	fMatrix cellmem;
	vector<float> zflt;
	zflt.assign(99,0);
	cellmem.assign(N,zflt);

	int s_ins = 0;
	int s_outs = 0;
	float sum = 0;
	float spike = 0;

	int dsize = damage.size();
	if(dsize == 0) // don't do anything fancy if there's no damage
	{
	for(int n = 0; n<dur; n++) // This is the time loop
	{
		for(int i = 0; i<N; i++) // this is the neuron loop
		{
			sum = 0;
			s_ins = (ins.at(i)).size(); // # of neurons inputting to cell i
			for(int k = 0; k<s_ins; k++) // takes sum of inputs to feed to .update
			{
				sum = sum + (AllSpikes.at((ins.at(i)).at(k))).at(n);
			}
			
			(cells.at(i)).update(sum);
		    spike = (cells.at(i)).getLastSpike();

			if(spike != 0) //USED TO COMPUTE MEAN ISI
			{
				numspikes.at(i)++;
				if(first.at(i))
				{
					t0.at(i) = ((float)n)/10;
					first.at(i) = false;
				}
				tf.at(i) = ((float)n)/10;
			}

			s_outs = (outs.at(i)).size(); // # of outputs from cell i
			for(int j = 0; j<s_outs; j++)
			{
				(AllSpikes.at((outs.at(i)).at(j))).at(n+1) = spike;
			}
		}
	}
	}

	else
	{
	for(int n = 0; n<dur; n++) // This is the time loop
	{
		for(int i = 0; i<N; i++) // this is the neuron loop
		{
			sum = 0;
			s_ins = (ins.at(i)).size(); // # of neurons inputting to cell i
			for(int k = 0; k<s_ins; k++) // takes sum of inputs to feed to .update
			{
				sum = sum + (AllSpikes.at((ins.at(i)).at(k))).at(n);
			}
			
			(cells.at(i)).update(sum);
			
			spike = (cells.at(i)).getLastSpike();
			(cellmem.at(i)).at(44) = (cellmem.at(i)).at(44) + abs(spike);

			if(spike != 0) //USED TO COMPUTE MEAN ISI
			{
				numspikes.at(i)++;
				if(first.at(i))
				{
					t0.at(i) = ((float)n)/10;
					first.at(i) = false;
				}
				tf.at(i) = ((float)n)/10;
			}

			s_outs = (outs.at(i)).size(); // # of outputs from cell i
			for(int j = 0; j<s_outs; j++)
			{
				if(not damage.at((outs.at(i)).at(j)))
				{
					(AllSpikes.at((outs.at(i)).at(j))).at(n+1) = spike;
				}
				else
				{
					if(spike !=0)
					{
						damaged_in = guess(cellmem.at(i));
						(AllSpikes.at((outs.at(i)).at(j))).at(n+1) = 
						((float)((cells.at(i)).getStrength())*damaged_in.at(44));
					}
					else
					{
						(AllSpikes.at((outs.at(i)).at(j))).at(n+1) = 0;
					}
				}
			}
		}
	
		if(n%9==0)
		{
			for(int i = 0; i< N; i++)
			{
				(cellmem.at(i)).erase((cellmem.at(i)).begin());
				(cellmem.at(i)).push_back(0);
			}
		}
	}
	}

	//LASTLY COMPUTE MEAN ISIs

	for(int i=0;i<N;i++)
	{
		meanISI.at(i) = (tf.at(i)-t0.at(i))/numspikes.at(i);
	}

	return meanISI;

}


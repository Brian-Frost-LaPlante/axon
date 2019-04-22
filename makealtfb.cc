#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "coin.h"
using namespace std;

typedef vector< vector<int> > iMatrix;

int main()
{
	int numModules;
	int N; 
	int n; int n2;
	int ei; int c0; int c1;
	int nAx;
	int d;
	int FB = 1;
	int lmin; int lmax;
	iMatrix ins;
	iMatrix outs;
	vector<int> ilen;
	vector<int> olen;
	vector<int> ntype;
	float prob = 1.0;
	vector<int> empty;

	cout << "Enter Number of Modules" << endl;
	cin >> numModules;
	cout << "Enter '1' to add an excitatory neuron, '-1' to add inhibitory neuron, or '0' for neither" << endl;
	cin >> ei;
	cout << "Enter '1' if first neuron in each module is excitatory, '-1' if inhibitory" << endl;
	cin >> c0;
	cout << "Do the same for the second neuron in each module" << endl;
	cin >> c1;

	if(ei != 0)
	{
		N = numModules*3;
		if(FB == 0)
		{
			nAx = (numModules*3)-1;
		}
		else
		{
			nAx = (numModules*4)-1;
		}
	}
	else
	{
		N = numModules*2;
		if(FB==0)
		{
			nAx = (numModules*2)-1;
		}
		else
		{
			nAx = (numModules*3)-1;
		}
	}

	ins.assign(N,empty);
	outs.assign(N,empty);

	for(int i=0;i<N;i++)
	{
	if(ei == 0)
	{
		if(i%2 == 0)
		{
			ntype.push_back(c0);
			if(FB == 0)
			{ // FEEDFORWARD MODULES WITH NO ADDED NEURON EVEN NUMBER
				if(i!=0)
				{
					ilen.push_back(1);
					(ins.at(i)).push_back(i-1);
				}
				else
				{
					ilen.push_back(0);
				}

				olen.push_back(1);
				(outs.at(i)).push_back(i);
			}
			else
			{ // FEEDBACK MODULES WITH NO ADDED NEURON EVEN NUMBER
				if(i!=0)
				{
					ilen.push_back(2);
					(ins.at(i)).push_back(((i/2)*3)-1);
					(ins.at(i)).push_back(((i/2)*3)+1);
				}
				else
				{
					ilen.push_back(1);
					(ins.at(i)).push_back(1);
				}

				olen.push_back(1);
				(outs.at(i)).push_back((i/2)*3);
			}		
		}
		else
		{
			ntype.push_back(c1);
			if(FB == 0)
			{ // FEEDFORWARD MODULES WITH NO ADDED NEURON ODD NUMBER
				if(i!=N-1)
				{
					olen.push_back(1);
					(outs.at(i)).push_back(i);
				}
				else
				{
					olen.push_back(0);
				}

				ilen.push_back(1);
				(ins.at(i)).push_back(i-1);
			}
			else
			{ // FEEDBACK MODULES WITH NO ADDED NEURON EVEN NUMBER
				if(i!=N-1)
				{
					olen.push_back(2);
					(outs.at(i)).push_back((((i-1)/2)*3) + 1);
					(outs.at(i)).push_back((((i-1)/2)*3) + 2);
				}
				else
				{
					olen.push_back(1);
					(outs.at(i)).push_back((((i-1)/2)*3) + 1);
				}

				ilen.push_back(1);
				(ins.at(i)).push_back((((i-1)/2)*3));
			}
		}
	}
	else
	{
		if(i%3 == 0)
		{
			ntype.push_back(ei);
			if(FB == 0)
			{ // FEEDFORWARD MODULES EXTRA CELL ON THE EXTRA CELL
				olen.push_back(1);
				(outs.at(i)).push_back(i);
				ilen.push_back(0);
			}
			else
			{ // FEEDBACK MODULES EXTRA CELL ON THE EXTRA CELL
				olen.push_back(1);
				(outs.at(i)).push_back((i/3)*4);
				ilen.push_back(0);
			}
		}
		else if(i%3 == 1)
		{
			ntype.push_back(c0);
			if(FB == 0)
			{ // FEEDFORWARD MODULES EXTRA CELL ON CELL 0
				if(i!=1)
				{
					bool toss = coin(prob);
					if(toss)
					{
						ilen.push_back(2);
						(ins.at(i)).push_back(i-2);
						(ins.at(i)).push_back(i-1);
					}
					else
					{
						ilen.push_back(1);
						(ins.at(i)).push_back(i-2);	
					}
				}
				else
				{
					bool toss = coin(prob);
					if(toss)
					{
						ilen.push_back(1);
						(ins.at(i)).push_back(0);
					}
					else
					{
						ilen.push_back(0);
					}
				}
				olen.push_back(1);
				(outs.at(i)).push_back(i);
			}
			else
			{ // FEEDBACK MODULES EXTRA CELL ON CELL 0
				if(i!=1)
				{
					ilen.push_back(3);
					(ins.at(i)).push_back((((i-1)/3)*4)-1);
					(ins.at(i)).push_back((((i-1)/3)*4));
					(ins.at(i)).push_back((((i-1)/3)*4)+2);
				}
				else
				{
					ilen.push_back(2);
					(ins.at(i)).push_back(0);
					(ins.at(i)).push_back(2);
				}
				olen.push_back(1);
				(outs.at(i)).push_back((((i-1)/3)*4)+1);	
			}
		}
		else
		{
			ntype.push_back(c1);
			if(FB == 0)
			{ // FEEDFORWARD MODULES EXTRA CELL ON CELL 1
				if(i!=N-1)
				{
					olen.push_back(1);
					(outs.at(i)).push_back(i);
				}
				else
				{
					olen.push_back(0);
				}
				ilen.push_back(1);
				(ins.at(i)).push_back(i-1);

			}
			else
			{ // FEEDBACK MODULES EXTRA CELL ON CELL 1
				if(i!=N-1)
				{
					olen.push_back(2);
					(outs.at(i)).push_back((((i-2)/3)*4)+2);
					(outs.at(i)).push_back((((i-2)/3)*4)+3);
				}
				else
				{
					olen.push_back(1);
					(outs.at(i)).push_back((((i-2)/3)*4)+2);
				}
				ilen.push_back(1);
				ins.at(i).push_back((((i-2)/3)*4)+1);
			}
		}
	}
	} 


	std::ofstream out("d.cc");

	out<<"#include \"NetSim.h\""<<endl<<endl;
	out<<"int main()"<<endl<<"{"<<endl<<endl;
	out<<"float V; fMatrix ins; fMatrix outs;" <<endl<<endl;


	out << "int N = " << N << ";" << endl;
	out << "int nAx = " << nAx << ";" << endl;
	out << "vector<bool> damage;" << endl;
		for(int i=0;i<nAx;i++)
		{
			if(FB==0)
			{
				if(ei == 0)
				{ // FEEDFORWARD NO EXTRA CELL, DAMAGE ON EVEN ONES
					if(i%2 == 0)
					{
						out << "damage.push_back(true);"<<endl;
					}
					else
					{
						out << "damage.push_back(false);"<<endl;
					}
				}
				else
				{ // FEEDFORWARD EXTRA CELL, 1mod3 GETS DAMAGE
					if(i%3 == 1)
					{
						out << "damage.push_back(true);"<<endl;
					}
					else
					{
						out << "damage.push_back(false);"<<endl;
					}
					
				}
			}
			else
			{
				if(ei == 0)
				{ // FEEDBACK NO EXTRA CELL, DAMAGE ON 1mod3
					if(i%3 == 1)
					{
						out << "damage.push_back(true);"<<endl;
					}
					else
					{
						out << "damage.push_back(false);"<<endl;
					}
				}
				else
				{ // FEEDBACK EXTRA CELL, 2mod4 GETS DAMAGE
					if(i%4 == 2)
					{
						out << "damage.push_back(true);"<<endl;
					}
					else
					{
						out << "damage.push_back(false);"<<endl;
					}
				}
			}
		}
		out<<"damage.push_back(false);"<<endl; //This is for global in
	out << endl;
	for(int i=0;i<N;i++)
	{
		out<<"vector<float> i"<<i<<";vector<float> o" <<i<<";"<<endl;
		for(int k=0;k<ilen.at(i);k++)
		{
			out<<"i"<<i<<".push_back("<<(ins.at(i)).at(k)<<");"<<endl;
		}
		out<<"i"<<i<<".push_back("<<nAx<<");"<<endl;
		for(int m=0;m<olen.at(i);m++)
		{
			out<<"o"<<i<<".push_back("<<(outs.at(i)).at(m)<<");"<<endl;
		}
		out<<"ins.push_back(i"<<i<<"); outs.push_back(o"<<i<<");"<<endl;
	}

	out << endl;

	out<<"vector<float> meanISItemp; vector<float> meanISI;"<<endl;
	out<<"for(float lambda = 0.02;lambda < 0.3;lambda=lambda+0.005)"<<endl<<"{"<<endl;
	out<<"meanISI.assign(N,0);"<<endl;
	out<<"for(int i=0;i<10000;i++)"<<endl<<"{"<<endl;

	out<<"vector<neuron> n;"<<endl;
	for(int i=0;i<N;i++)
	{
		out<<"	neuron n"<<i<<" (99.9,0.5,18.0,5.0,0.2,"<<ntype.at(i)<<",.1);"<<endl;
		out<<"	n.push_back(n"<<i<<");"<<endl;
	}

	out<<"meanISItemp = NetSim(ins,outs,n,lambda,damage,nAx);"<<endl;
	out<<"meanISI.at(N-1) = meanISI.at(N-1)+meanISItemp.at(N-1);"<<endl<<"}"<<endl;
	out<<"cout << meanISI.at(N-1)/10000 << endl;" <<endl<<"}"<<endl;
	out<<"return 0;"<<endl<<"}";

	out.close();
	
	std::ofstream out2("u.cc");

	out2<<"#include \"NetSim.h\""<<endl<<endl;
	out2<<"int main()"<<endl<<"{"<<endl<<endl;
	out2<<"float V; fMatrix ins; fMatrix outs;" <<endl<<endl;


	out2 << "int N = " << N << ";" << endl;
	out2 << "int nAx = " << nAx << ";" << endl;
	out2 << "vector<bool> damage;" << endl;
	out2 << endl;
	for(int i=0;i<N;i++)
	{
		out2<<"vector<float> i"<<i<<";vector<float> o" <<i<<";"<<endl;
		for(int k=0;k<ilen.at(i);k++)
		{
			out2<<"i"<<i<<".push_back("<<(ins.at(i)).at(k)<<");"<<endl;
		}
		out2<<"i"<<i<<".push_back("<<nAx<<");"<<endl;
		for(int m=0;m<olen.at(i);m++)
		{
			out2<<"o"<<i<<".push_back("<<(outs.at(i)).at(m)<<");"<<endl;
		}
		out2<<"ins.push_back(i"<<i<<"); outs.push_back(o"<<i<<");"<<endl;
	}

	out2 << endl;

	out2<<"vector<float> meanISItemp; vector<float> meanISI;"<<endl;
	out2<<"for(float lambda=0.02;lambda<0.3;lambda=lambda+0.005)"<<endl<<"{"<<endl;
	out2<<"meanISI.assign(N,0);"<<endl;
	out2<<"for(int i=0;i<10000;i++)"<<endl<<"{"<<endl;

	out2<<"vector<neuron> n;"<<endl;
	for(int i=0;i<N;i++)
	{
		out2<<"	neuron n"<<i<<" (99.9,0.5,18.0,5.0,0.2,"<<ntype.at(i)<<",.1);"<<endl;
		out2<<"	n.push_back(n"<<i<<");"<<endl;
	}

	out2<<"meanISItemp = NetSim(ins,outs,n,lambda,damage,nAx);"<<endl;
	out2<<"meanISI.at(N-1) = meanISI.at(N-1)+meanISItemp.at(N-1);"<<endl<<"}"<<endl;
	out2<<"cout << meanISI.at(N-1)/10000 << endl;" <<endl<<"}"<<endl;
	out2<<"return 0;"<<endl<<"}";

	out2.close();
	return 0;
}

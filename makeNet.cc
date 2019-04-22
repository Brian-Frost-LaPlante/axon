#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef vector< vector<int> > iMatrix;

int main()
{
	int N;
	int n; int n2;
	int ei;
	int nAx;
	int d;
	iMatrix ins;
	iMatrix outs;
	vector<int> ilen;
	vector<int> olen;
	vector<int> ntype;

	vector<int> empty;

	cout << "Enter Number of Neurons" << endl;
	cin >> N;
	ins.assign(N,empty);
	outs.assign(N,empty);
	cout << "Enter Number of Axons" << endl;
	cin >> nAx;
	for(int i=0;i<N;i++)
	{
	cout << "Type '-1' if Neuron " << i << " is inhibitory, '1' if excitatory:" <<endl;
	cin >> ei;
	ntype.push_back(ei); 
	cout << "How many axons feed in to Neuron " << i << "?"<< endl;
	cin >> n;
	ilen.push_back(n);
		for(int j=0;j<n;j++)
		{
			cout << "What are their numbers? One at a time: " <<endl;
			cin >> n2;
			(ins.at(i)).push_back(n2);
		}
	cout << "How many axons lead out of Neuron " << i << "?" <<endl;
	cin >> n;
	olen.push_back(n);
		for(int j=0;j<n;j++)
		{
			cout << "What are their numbers? One at a time: " <<endl;
			cin >> n2;
			(outs.at(i)).push_back(n2);
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
			out << "damage.push_back(true);"<<endl;
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
	out<<"for(float lambda=0.02;lambda<0.3;lambda=lambda+0.005)"<<endl<<"{"<<endl;
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

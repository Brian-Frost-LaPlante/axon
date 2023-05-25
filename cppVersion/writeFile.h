#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef vector< vector<int> > iMatrix;

void writeFile(string title, int N, int nAx, iMatrix ins,
		 iMatrix outs, vector<int> type, vector<int> dam_inds,
		 float l, float u)
{
	ofstream out(title);
	
	 out<<"#include \"NetSim.h\""<<endl<<endl;
	 out<<"int main()"<<endl<<"{"<<endl<<endl;
     out<<"float V; fMatrix ins; fMatrix outs;" <<endl<<endl; 
     out << "int N = " << N << ";" << endl;
     out << "int nAx = " << nAx << ";" << endl;
     out << "vector<bool> damage;" << endl;
     
	 if (dam_inds.size() != 0)
	 {
	 int ind_check = 0;

	 for(int i=0;i<nAx;i++)
	 {
		if (ind_check < dam_inds.size())
		{
		if (i == dam_inds.at(ind_check))
		{
			out << "damage.push_back(true);" << endl;
			ind_check++;
		}
		else
		{
			out << "damage.push_back(false);" << endl;
		}
		}
		else
		{
			out << "damage.push_back(false);" << endl;
		}
	 }
	 out << "damage.push_back(false);";
     }

     out << endl;
     for(int i=0;i<N;i++)
     {
		 int ilen = (ins.at(i)).size();
		 int olen = (outs.at(i)).size();
         out<<"vector<float> i"<<i<<";vector<float> o" <<i<<";"<<endl;
         for(int k=0;k<ilen;k++)
         {
             out<<"i"<<i<<".push_back("<<(ins.at(i)).at(k)<<");"<<endl;
         }
         out<<"i"<<i<<".push_back("<<nAx<<");"<<endl;
         for(int m=0;m<olen;m++)
         {
             out<<"o"<<i<<".push_back("<<(outs.at(i)).at(m)<<");"<<endl;
         }
         out<<"ins.push_back(i"<<i<<"); outs.push_back(o"<<i<<");"<<endl;
     }
 
     out << endl;
 
     out<<"vector<float> meanISItemp; vector<float> meanISI;"<<endl;
     out<<"for(float lambda="<<l<<";lambda<"<<u<<";lambda=lambda+0.005)"<<endl<<"{"<<endl;
     out<<"meanISI.assign(N,0);"<<endl;
     out<<"for(int i=0;i<10000;i++)"<<endl<<"{"<<endl;
 
     out<<"vector<neuron> n;"<<endl;
     for(int i=0;i<N;i++)
     {
         out<<" neuron n"<<i<<" (99.9,0.5,18.0,5.0,0.2,"<<type.at(i)<<",.1);"<<endl;
         out<<" n.push_back(n"<<i<<");"<<endl;
     }
 
     out<<"meanISItemp = NetSim(ins,outs,n,lambda,damage,nAx);"<<endl;
     out<<"meanISI.at(N-1) = meanISI.at(N-1)+meanISItemp.at(N-1);"<<endl<<"}"<<endl;
     out<<"cout << meanISI.at(N-1)/10000 << endl;" <<endl<<"}"<<endl;
     out<<"return 0;"<<endl<<"}";

	 out.close();
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "coin.h"
#include "writeFile.h"

using namespace std;

typedef vector< vector<int> > iMatrix;

int main()
{

	int num_Modules = 5; // Number of Modules
	int type1;	    // +1 if cell 1 (in each module) is excitatory, -1 if inhibitory
	int type2;      // as above for cell 2
	bool is_FB;     // False if module is FF, true if FB
	bool is_aided;  // True if adding I to front of module
	bool is_damaged;// True if module has a damaged axon
	
	float p_E;      // Probability of E cell = 1 - probability of I cell
	float p_dam;    // Probability of damage in a layer
	float p_aid;    // Probability of aid to a damaged layer
	float p_FB;		// Probability of a FB path in each module

	int cell_u = 0; // current cell index for undamaged network
	int axon_u = 0; // current axon index for undamaged network
	int cell_i = 0; // current cell index for damaged network
	int axon_i = 0; // current axon index for damaged network

	vector<int> cells_u; // Cell types in unaided network
	vector<int> cells_i; // cell types in aided network

	iMatrix ins_u;       // First dimension index = cell number, second is which axons feed in
	iMatrix outs_u;		 // First dimension index = cell number, second is which axons feed out
	iMatrix ins_i;
	iMatrix outs_i;

	vector<int> dam_ind;  // Indices of axons with damage
	vector<int> dam_ind_i;

	cout << "Number of layers: ";
	cin >> num_Modules;
	cout << "Probability of E cell: ";
	cin >> p_E;
	cout << "Probability of damage: ";
	cin >> p_dam;
	cout << "Probability of aid: ";
	cin >> p_aid;
	cout << "Probability of feedback path: "; 
	cin >> p_FB;


	ofstream out("info.txt");
	out << num_Modules << "-Layer Network" << endl;
	out << "Probability of E cell: " << p_E << endl;
	out << "Probability of damage: " << p_dam << endl;
	out << "Probability of aid: " << p_aid << endl;
	out << "Probability of feedback path: " << p_FB << endl << endl;

	int num_E = 0;
	vector<int> FB_layers;
	vector<int> dam_layers;
	vector<int> aided_layers;

	for (int i=0; i<num_Modules; i++) // Loop through the modules
	{

		// First, "roll all dice"
		// That is, decide if this is FF/FB, cell types, damaged, aided
		bool toss_type1 = coin(p_E);
		bool toss_type2 = coin(p_E);
		if (toss_type1)
		{
			type1 = 1;
			num_E++;
		}
		else
		{
			type1 = -1;
		}
		if (toss_type2)
		{
			type2 = 1;
			num_E++;
		}
		else
		{
			type2 = -1;
		}
		is_FB = coin(p_FB);
		is_aided = coin(p_aid);
		is_damaged = coin(p_dam);		

		// Set up all potential cells in module for undamaged
		
			cells_u.push_back(type1);
			vector<int> cell1_ins;

			if (cell_u > 0) // Add feedforward from last layer, unless it is the first layer
			{
				cell1_ins.push_back(axon_u - 1);
			}
			if (is_FB)      // Add Feedback path
			{
				cell1_ins.push_back(axon_u + 1);
				FB_layers.push_back(i);
			}

			vector<int> cell1_outs;

			cell1_outs.push_back(axon_u); // cell 1 always only has one feedforward output

			if(is_damaged)
			{
				dam_ind.push_back(axon_u);
			}

			ins_u.push_back(cell1_ins);
			outs_u.push_back(cell1_outs);

			cells_u.push_back(type2);
			vector<int> cell2_ins;

			cell2_ins.push_back(axon_u); // cell 2 always gets input from cell 1 only			

			vector<int> cell2_outs;

			if (is_FB)    // Add Feedback path
			{
				cell2_outs.push_back(axon_u + 1); 
			}

			if (i != num_Modules-1) // Add output axon if necessary
			{
				if (is_FB) // index is 1 higher if FB
				{
					cell2_outs.push_back(axon_u + 2);
					axon_u = axon_u + 3;
				}
				else
				{
					cell2_outs.push_back(axon_u + 1);
					axon_u = axon_u + 2;
				}
			}
			else
			{
				if (is_FB)
				{
					axon_u = axon_u + 2;
				}
				else
				{
					axon_u = axon_u + 1;
				}
			}

			ins_u.push_back(cell2_ins);
			outs_u.push_back(cell2_outs);
			
			cell_u = cell_u + 2;

		

		// Set up all potential cells in module for damaged
			// Add cell if aided and damaged
			if (is_damaged)
			{
				dam_layers.push_back(i);
				if (is_aided)
				{
					aided_layers.push_back(i);
					cells_i.push_back(-1);
					vector<int> cell0_ins;
					
					// Nothing feeds into cell 0, just need to create this to maintain indexing

					vector<int> cell0_outs;

					cell0_outs.push_back(axon_i); // always only one output

					ins_i.push_back(cell0_ins);
					outs_i.push_back(cell0_outs);
					
					cells_i.push_back(type1);
					vector<int> cell1_ins;

					if (i != 0) // if not first module, add feedforward from last layer
					{
						cell1_ins.push_back(axon_i - 1);
					}
					cell1_ins.push_back(axon_i); // From aid neuron
					if (is_FB)
					{
						cell1_ins.push_back(axon_i + 2);
					}

					vector<int> cell1_outs;
					
					cell1_outs.push_back(axon_i + 1); // Always cell1 -> cell 2

					ins_i.push_back(cell1_ins);
					outs_i.push_back(cell1_outs);

					cells_i.push_back(type2);

					vector<int> cell2_ins;

					cell2_ins.push_back(axon_i + 1); // Always cell1 -> cell 2
					
					dam_ind_i.push_back(axon_i + 1);   // This is the damaged one!

					vector<int> cell2_outs;
					
					if (is_FB)
					{
						cell2_outs.push_back(axon_i + 2);
					}	
					if ( i!= num_Modules-1) // Add feedforward to next layer if possible
					{
						if (is_FB) // index is one larger if FB
						{
							cell2_outs.push_back(axon_i + 3);
							axon_i = axon_i + 4;
						}
						else
						{
							cell2_outs.push_back(axon_i + 2);
							axon_i = axon_i + 3;
						}
					}
					else
					{
						if (is_FB)
						{
							axon_i = axon_i + 3;
						}
						else
						{
							axon_i = axon_i + 2;
						}
					}	
					ins_i.push_back(cell2_ins);
					outs_i.push_back(cell2_outs); 
					cell_i = cell_i + 3;
				}
			}

			if (!is_damaged or !is_aided) // If we aren't adding an extra neuron, indices change
			{

				cells_i.push_back(type1);
				vector<int> cell1_ins;

				if (i != 0) // if not first module, add feedforward from last layer
				{
					cell1_ins.push_back(axon_i - 1);
				}
				if (is_FB)
				{
					cell1_ins.push_back(axon_i + 1);
				}

				vector<int> cell1_outs;
					
				cell1_outs.push_back(axon_i); // Always cell1 -> cell 2

				ins_i.push_back(cell1_ins);
				outs_i.push_back(cell1_outs);

				cells_i.push_back(type2);

				vector<int> cell2_ins;

				cell2_ins.push_back(axon_i); // Always cell1 -> cell 2

				if (is_damaged)
				{
					dam_ind_i.push_back(axon_i);
				}

				vector<int> cell2_outs;
					
				if (is_FB)
				{
					cell2_outs.push_back(axon_i + 1);
				}	
				if ( i!= num_Modules-1) // Add feedforward to next layer if possible
				{
					if (is_FB) // index is one larger if FB
					{
						cell2_outs.push_back(axon_i + 2);
						axon_i = axon_i + 3;
					}
					else
					{
						cell2_outs.push_back(axon_i + 1);
						axon_i = axon_i + 2;
					}
				}
				else
				{
					if (is_FB)
					{
						axon_i = axon_i + 2;
					}
					else
					{
						axon_i = axon_i + 1;
				}
			}		
				ins_i.push_back(cell2_ins);
				outs_i.push_back(cell2_outs);
				cell_i = cell_i + 2;
			}	

	}

	out << endl << "*** Feedback ***" << endl << endl;
	out << "There are " << FB_layers.size() << " layers with feedback paths, numbered" << endl;
	for (int i = 0; i<FB_layers.size();i++)
	{
		out << FB_layers.at(i) << endl;
	}
	out << endl << "*** Damage ***" << endl << endl;
	out << "There are " << dam_layers.size() << " layers with damage, numbered" << endl;
	for (int i = 0; i<dam_layers.size();i++)
	{
		out << dam_layers.at(i) << endl;
	}
	out << endl << "*** Aid ***" << endl << endl;
	out << "There are " << aided_layers.size() << " layers with aid, numbered" << endl;
	for (int i = 0; i<aided_layers.size();i++)
	{
		out << aided_layers.at(i) << endl;
	}
	out << endl << "*** Type ***" << endl << endl;
	out << "There are " << num_E << " excitatory neurons" << endl;
	out.close();

	vector<int> empty;

	writeFile("u0.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.02,0.04);
	writeFile("d0.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.02,0.04);
	writeFile("u1.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.04,0.06);
	writeFile("d1.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.04,0.06);
	writeFile("u2.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.06,0.08);
	writeFile("d2.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.06,0.08);
	writeFile("u3.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.08,0.1);
	writeFile("d3.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.08,0.1);
	writeFile("u4.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.1,0.12);
	writeFile("d4.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.1,0.12);
	writeFile("u5.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.12,0.14);
	writeFile("d5.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.12,0.14);
	writeFile("u6.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.14,0.16);
	writeFile("d6.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.14,0.16);
	writeFile("u7.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.16,0.18);
	writeFile("d7.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.16,0.18);
	writeFile("u8.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.18,0.2);
	writeFile("d8.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.18,0.2);
	writeFile("u9.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.2,0.22);
	writeFile("d9.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.2,0.22);
	writeFile("u10.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.22,0.24);
	writeFile("d10.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.22,0.24);
	writeFile("u11.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.24,0.26);
	writeFile("d11.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.24,0.26);
	writeFile("u12.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.26,0.28);
	writeFile("d12.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.26,0.28);
	writeFile("u13.cc",cell_u,axon_u,ins_u,outs_u,cells_u,empty,0.28,0.3);
	writeFile("d13.cc",cell_u,axon_u,ins_u,outs_u,cells_u,dam_ind,0.28,0.3);


	writeFile("ui0.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.02,0.04);
	writeFile("di0.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.02,0.04);
	writeFile("ui1.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.04,0.06);
	writeFile("di1.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.04,0.06);
	writeFile("ui2.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.06,0.08);
	writeFile("di2.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.06,0.08);
	writeFile("ui3.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.08,0.1);
	writeFile("di3.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.08,0.1);
	writeFile("ui4.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.1,0.12);
	writeFile("di4.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.1,0.12);
	writeFile("ui5.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.12,0.14);
	writeFile("di5.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.12,0.14);
	writeFile("ui6.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.14,0.16);
	writeFile("di6.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.14,0.16);
	writeFile("ui7.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.16,0.18);
	writeFile("di7.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.16,0.18);
	writeFile("ui8.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.18,0.2);
	writeFile("di8.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.18,0.2);
	writeFile("ui9.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.2,0.22);
	writeFile("di9.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.2,0.22);
	writeFile("ui10.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.22,0.24);
	writeFile("di10.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.22,0.24);
	writeFile("ui11.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.24,0.26);
	writeFile("di11.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.24,0.26);
	writeFile("ui12.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.26,0.28);
	writeFile("di12.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.26,0.28);
	writeFile("ui13.cc",cell_i,axon_i,ins_i,outs_i,cells_i,empty,0.28,0.3);
	writeFile("di13.cc",cell_i,axon_i,ins_i,outs_i,cells_i,dam_ind_i,0.28,0.3);


	return 0;
}

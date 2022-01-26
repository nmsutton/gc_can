/* * Copyright (c) 2016 Regents of the University of California. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* 3. The names of its contributors may not be used to endorse or promote
*    products derived from this software without specific prior written
*    permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* *********************************************************************************************** *
* CARLsim
* created by: (MDR) Micah Richert, (JN) Jayram M. Nageswaran
* maintained by:
* (MA) Mike Avery <averym@uci.edu>
* (MB) Michael Beyeler <mbeyeler@uci.edu>,
* (KDC) Kristofor Carlson <kdcarlso@uci.edu>
* (TSC) Ting-Shuo Chou <tingshuc@uci.edu>
* (HK) Hirak J Kashyap <kashyaph@uci.edu>
*
* CARLsim v1.0: JM, MDR
* CARLsim v2.0/v2.1/v2.2: JM, MDR, MA, MB, KDC
* CARLsim3: MB, KDC, TSC
* CARLsim4: TSC, HK
* CARLsim5: HK, JX, KC
*
* CARLsim available from http://socsci.uci.edu/~jkrichma/CARLsim/
* Ver 12/31/2016
*
*
* code added by Nate Sutton
* references:
* http://www.cplusplus.com/forum/general/34780/
* https://en.wikipedia.org/wiki/Gompertz_function
*/

// include CARLsim user interface
#include <carlsim.h>

// include stopwatch for timing
#include <stopwatch.h>

#include <vector>
#include <spike_monitor.h>
#include <math.h> // for sqrt() and other functions

// for to_string()
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

// for file out
#include <fstream>

using namespace std;

//#include <vector>
#include <math.h> // for sqrt() and other functions

#include "general_funct.cpp"
#include "move_path.cpp"
/*
#include "boundary_cells.cpp"
*/
#include "place_cells.cpp"

using namespace std;

string to_string(double x);

string to_string(double x)
{
  ostringstream ss;
  ss << x;
  return ss.str();
}

string to_string(int x)
{
  ostringstream ss;
  ss << x;
  return ss.str();
}

string int_to_string(int x)
{
  ostringstream ss;
  ss << x;
  return ss.str();
}

double GetAngle(char gc_pd) {	
	double angle;
	double PI_in_deg = 180;

	if (gc_pd == 'l') {
		angle = ((0 * PI) / PI_in_deg);
	}
	else if (gc_pd == 'd') {
		angle = ((90 * PI) / PI_in_deg);
	}
	else if (gc_pd == 'r') {
		angle = ((180 * PI) / PI_in_deg);
	}
	else if (gc_pd == 'u') {
		angle = ((270 * PI) / PI_in_deg);
	}

	return angle;
}

void SetIndices(int i, int *i_o, int g_max_x, int g_max_y, char axis, int max_i, int *d_i, double offset) {
	// calculate interneuron indices in a twisted torus shape.
	// this provides indices limited to the region bump activity occurs.
	// d_i = index distance on x- or y-axis. E.g., distance between neurons as represented
	// by indices.

	int i_size = g_max_x * g_max_y;
	int siox = g_max_x / 2; // starting index offset for x
	int sioy = g_max_y / 2; // starting index offset for y

	if (axis == 'x') {
		for (int xi = 0; xi < i_size; xi++) {
			i_o[xi] = (i - siox) + (xi % g_max_x);
			d_i[xi] = (-1 * siox) + (xi % g_max_x);
		}
	}
	if (axis == 'y') {
		for (int yi = 0; yi < i_size; yi++) {
			i_o[yi] = (i - sioy) + (yi / g_max_x);
			d_i[yi] = (-1 * sioy) + (yi / g_max_x);
		}
	}
	for (int i2 = 0; i2 < i_size; i2++) {
		if (i_o[i2] < 0) {
			i_o[i2] = i_o[i2] + max_i;
		}
		else if (i_o[i2] >= max_i) {
			i_o[i2] = i_o[i2] - max_i;	
		}
	}
}

void PrintWeightsAndFiring(P *p, double *in_firing, EIWP e) {
	int x_p = 20;
	int y_p = 20;
	int max_x = p->x_size;
	int n = 0;

	if (p->print_in_weights) {
		printf("\n\nec->in weights at time %d",e.t);
		for (int i = (y_p - 1); i >= 0; i--) {
			printf("\n");
			for (int j = 0; j < x_p; j++) {
				n = (i * max_x) + j;
				printf("[%.1f]\t",e.ecin_weights[n][n]);	
			}
		}
	}
	if (p->print_ext_weights) {
		printf("\n\next->ec weights at time %d",e.t);
		for (int i = (y_p - 1); i >= 0; i--) {
			printf("\n");
			for (int j = 0; j < x_p; j++) {
				n = (i * max_x) + j;
				printf("[%.1f]\t",e.etec_weights[n][n]);	
			}
		}
	}
	if (p->print_gc_firing) {
		printf("\nGC firing t:%d",p->t);
		for (int i = (y_p - 1); i >= 0; i--) {
			printf("\n");
			for (int j = 0; j < x_p; j++) {
				n = (i * max_x) + j;
				printf("[%.0f]\t",p->gc_firing[n]);	
			}
		}
	}
}

void PrintTempWeights(double* temp_gctoin_wts, double* temp_intogc_wts, int t) {
	int n_num;
	int i_max = 5;
	int j_max = 5;
	int max_x = 10;

	printf("\nTemp Weights (t=%d):\n",t);
	for (int i = (i_max - 1); i >= 0; i--) {
		for (int j = 0; j < j_max; j++) {
			n_num = (i * max_x) + j; // neuron number

			printf("[%f]\t",temp_gctoin_wts[n_num]);
		}
		printf("\n");
	}
}

void StoreWeights(CARLsim *sim, double *in_firing, P *p) {
	/*
		transfer weights from temp matrix to synapse values
	*/
	int i;

	for (int y = 0; y < p->y_size; y++) {
		for (int x = 0; x < p->x_size; x++) {
			i = (y * p->x_size) + x;

			// normal condition
			//sim->setWeight(1,i,i,in_firing[i],true);
			//sim->setWeight(2,i,i,in_firing[i],true);

			//sim->setWeight(1,i,i,in_firing[i],false);
			//sim->setWeight(2,i,i,in_firing[i],false);

			// for fire vs loc plot testing
			double new_weight = in_firing[i];
			new_weight = new_weight - 2;
			if (new_weight >= 0) {
				sim->setWeight(4,i,i,new_weight,true);
				sim->setWeight(1,i,i,0,true);
			  sim->setWeight(2,i,i,0,true);
			}
			else {
				//sim->setWeight(1,i,i,abs(2-new_weight),true);
			  //sim->setWeight(2,i,i,abs(2-new_weight),true);
			  sim->setWeight(1,i,i,1,true);
			  sim->setWeight(2,i,i,1,true);
			  sim->setWeight(4,i,i,0,true);
			}
		}
	}
}

void init_firing(CARLsim* sim, P *p) {
	// initialize firing with bumps

	int i;
	int init_x = p->bump_init_x;
	int init_y = p->bump_init_y;
	int bump_d = p->bump_dist;
	double mex_hat, d, new_firing;
	double firing_bumps[p->layer_size];
	for (int i = 0; i < p->layer_size; i++) {
		firing_bumps[i] = 0.0;
	}
	int bump_pos[p->num_bumps][2] = {{init_x,init_y},{(init_x+(bump_d/2)),(init_y+bump_d)},{(init_x+bump_d),init_y},{(init_x+(bump_d+(bump_d/2))),(init_y+bump_d)}};
	p->y_inter = p->y_inter_init; // y intercept
	p->s_1 = p->s_1_init; // sigma_1. Note: specific value used for equalibrium of weights over time.
	p->s_2 = p->s_2_init;
	p->s_3 = p->s_3_init;
	p->s_4 = p->s_4_init;
	p->s_5 = p->s_5_init;
	p->m = p->m_init;
	p->m2 = p->m_init2;
	p->m3 = p->m_init3;
	p->m4 = p->m_init4;
	p->a = p->a_init;
	p->scale = p->scale_init;

	// find weights for the starting bumps
	for (int y = 0; y < p->y_size; y++) {
		for (int x = 0; x < p->x_size; x++) {
			for (int b = 0; b < p->num_bumps; b++) {
				i = (y * p->x_size) + x;

				d = get_distance(x, y, bump_pos[b][0], bump_pos[b][1], 'n', p);

				if (d < p->dist_thresh) {
					mex_hat = get_mex_hat(d, p);

					new_firing = mex_hat - ((1/pow(p->dist_thresh,1.75))*8);

					firing_bumps[i] = firing_bumps[i] + new_firing;		
				}
			}
		}
	}

	for (int i = 0; i < p->layer_size; i++) {
		firing_bumps[i] = firing_bumps[i] * -1; // invert values
		if (firing_bumps[i] < 0.0) {			
			firing_bumps[i] = 0.0; // no neg values rectifier
		}
		if (p->init_bumps) {
			//in_firing[i] = firing_bumps[i];
			sim->setWeight(2,i,i,firing_bumps[i],true);
			//sim->setWeight(2,i,i,firing_bumps[i],false);
		}
	}

	// set parameters to non-initial values
	p->y_inter = p->y_inter_syn;
	p->s_1 = p->s_1_syn;
	p->s_2 = p->s_2_syn;
	p->s_3 = p->s_3_syn;
	p->s_4 = p->s_4_syn;
	p->s_5 = p->s_5_syn;
	p->m = p->m_syn;
	p->m2 = p->m_syn2;
	p->m3 = p->m_syn3;
	p->m4 = p->m_syn4;
	p->a = p->a_syn;
	p->scale = p->scale_syn;
}

char get_pd(int x, int y) {
	char pd;

	if (y % 2 == 0) {
		if (x % 2 == 0) {
			pd = 'd';
		}
		else {
			pd = 'r';
		}
	}
	else {
		if (x % 2 == 0) {
			pd = 'l';
		}
		else {
			pd = 'u';
		}		
	}

	return pd;
}

char get_pd(int i, P *p) {	
	char pd;
	int x = i % p->x_size;
	int y = i / p->x_size;

	if (y % 2 == 0) {
		if (x % 2 == 0) {
			pd = 'd';
		}
		else {
			pd = 'r';
		}
	}
	else {
		if (x % 2 == 0) {
			pd = 'l';
		}
		else {
			pd = 'u';
		}		
	}

	return pd;
}

void set_pos(P *p, char direction) {
	if (direction == 'u') {
		p->pos[1]++; 
	}
	else if (direction == 'd') {
		p->pos[1]--; 
	}
	else if (direction == 'r') {
		p->pos[0]++; 
	}
	else if (direction == 'l') {
		p->pos[0]--; 
	}

	if (p->pos[0] >= p->x_size) {
		p->pos[0] = 0;
	}
	else if (p->pos[0] < 0) {
		p->pos[0] = (p->x_size - 1);
	}
	if (p->pos[1] >= p->y_size) {
		p->pos[1] = 0;
	}
	else if (p->pos[1] < 0) {
		p->pos[1] = (p->y_size - 1);
	}

	if (p->print_move == true && direction != 'n') {
		cout << " move: " << direction << " " << p->pos[0] << " " << p->pos[1] << " t: " << p->t;
	}

	p->last_dir=direction;
}

double get_noise(P *p) {
	int rand_max = p->noise_rand_max;
	double scale = p->noise_scale;

	double rand_val = rand() % rand_max; // rand number up to rand_max
	rand_val = rand_val * scale; // scale to desired size
	//rand_val = rand_val - (scale/2); // include negative values, comment out to only have positive values

	return rand_val;
}

void count_gc_firing(P* p) {
	int nrn_size, s_num, spk_time, tot;
	for (int i = 0; i < (p->x_size*p->y_size); i++) {
		p->gc_firing[i] = 0.0; // initialize as 0
	}

	// count gc spikes
	nrn_size = p->nrn_spk.size();
	for (int i = 0; i < nrn_size; i++) {
		tot = 0;
		s_num = p->nrn_spk[i].size();
		for (int j = 0; j < s_num; j++) {
			spk_time = p->nrn_spk[i][j];
			if (spk_time >= (p->t - p->move_window) && spk_time <= p->t) {
				tot += 1;
			}
		}
		//if (p->gc_to_gc && i < (p->x_size*p->y_size)) {
		if (i < (p->x_size*p->y_size)) {
			p->gc_firing[i] = tot;
		}
	}
}

void write_firing(double *firing_matrix, string output_folder, P *p) {
	ofstream output_file;
	string filename = "output/" + output_folder + "/firing_t" + int_to_string(p->t) + ".csv";
	output_file.open(filename);

	int i_f = 0; // firing index

	if (p->t != 0) {
		for (int i = (p->x_size - 1); i >= 0; i--) {
			for (int j = 0; j < p->y_size; j++) {
				i_f = (i * p->x_size) + j;

				output_file << firing_matrix[i_f];

				if (j != (p->y_size -1)) {
					output_file << ",";
				}
			}
			if (i != 0) {
				output_file << "\n";
			}
		}
	}

  output_file.close();
}

void RecordNeuronVsLocation(CARLsim* sim, P* p, EIWP e) {
	/*
		Detect firing of a selected individual neuron and record the animal's
		position when the firing occured. Amount of firing is also recorded.

		Note: are the 10ms time bins firing is counted enough resolution for this?
	*/

	int i;

	if (p->gc_firing[p->selected_neuron] > 0) {
		// get index from position
		i = (p->pos[1] * p->x_size) + p->pos[0];

		p->firing_positions[i] = p->firing_positions[i] + p->gc_firing[p->selected_neuron];
	}

	write_firing(p->firing_positions, "firing_vs_loc", p);
}

void RecordLocationPath(P *p) {
	int pos_i = (p->pos[1] * p->x_size) + p->pos[0];

	for (int i = 0; i < p->layer_size; i++) {
		if (i == pos_i) {
			p->animal_location[i] = 5;
		}
		else {
			p->animal_location[i] = 0;	
		}
	}

	write_firing(p->animal_location, "pos_track", p);
}

void EISignal(char direction, CARLsim* sim, P* p, EIWP e) {
	/*
		Process signaling between gc exc and inh neurons.
	*/	

	double new_firing, new_weight, weight_sum, pd_fac, mex_hat;
	double pdx, pdy, gcx, gcy, d; // for distance
	int pd_i, gc_i;
	double new_firing_group[p->layer_size];
	for (int i = 0; i < p->layer_size; i++) {
		new_firing_group[i] = 0.00001;
	}
	int nrn_size, s_num, spk_time, tot; // t_y, t_x: target y and x
	double in_firing[p->x_size*p->y_size]; // gc spike amount
	for (int i = 0; i < (p->x_size*p->y_size); i++) {
		in_firing[i] = 0.0; // initialize as 0
	}

	count_gc_firing(p);

	set_pos(p, direction);

	if (p->print_move) {cout << "\n";}

	/* apply direction-based ext input first */
	for (int gc_i = 0; gc_i < p->layer_size; gc_i++) {
		if (get_pd(gc_i, p) == direction) {
			pd_fac = 1.0;
		}
		else {
			pd_fac = 0.0;
		}

		if (p->base_dir_input) {
			in_firing[gc_i] = p->gc_firing[gc_i] + pd_fac;
		}
	}

	/* place cell firing */
	if (p->pc_to_gc) {
		place_cell_firing(in_firing, p);
	}

	/* boundary cell firing */
	if (p->bc_to_gc) {
		//boundary_cell_firing(in_firing, g);
	}

	/* grid cell and interneuron synapse connections */
	for (int pdy = 0; pdy < p->y_size; pdy++) {
		for (int pdx = 0; pdx < p->x_size; pdx++) {
			if (direction == get_pd(pdx, pdy) || direction == 'n') {
				for (int gcy = 0; gcy < p->y_size; gcy++) {
					for (int gcx = 0; gcx < p->x_size; gcx++) {			
						pd_i = (pdy * p->x_size) + pdx;						
						gc_i = (gcy * p->x_size) + gcx;

						d = get_distance(pdx, pdy, gcx, gcy, direction, p);

						if (d < p->dist_thresh) { 

							mex_hat = get_mex_hat(d, p);

							new_firing = (in_firing[pd_i] * mex_hat) - ((1/pow(p->dist_thresh,1.75))*8);

							new_firing_group[gc_i] = new_firing_group[gc_i] + new_firing;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < p->layer_size; i++) {
		if (p->gc_to_gc) {
			//new_firing_group[i] = -1 * new_firing_group[i];
			if (new_firing_group[i] > 0) {
				new_firing_group[i] = 0; // only negative values for IN weights
			}
			in_firing[i] = new_firing_group[i] + (p->dist_thresh*1.7);
			//in_firing[i] = new_firing_group[i] + (p->dist_thresh*2.6);
			//in_firing[i] = new_firing_group[i] - (p->dist_thresh*3.7);
			//in_firing[i] = in_firing[i] * .35;
			in_firing[i] = 0;//new_firing_group[i];
		}
		// original tau derivative
		in_firing[i] = p->asig_a * exp(-1*(in_firing[i]/p->asig_b))+p->asig_c;
		// non zero firing rectifier
		if (in_firing[i] < 0) {
			in_firing[i] = 0;
		}
		// add random noise for realism		
		if (p->noise_active == true) {
			sim->setWeight(3,i,i,get_noise(p),true);
		}
	}

	PrintWeightsAndFiring(p, in_firing, e);
	StoreWeights(sim, in_firing, p);
}

int main() {
	struct P p;	
	// keep track of execution time
	Stopwatch watch;

	// ---------------- CONFIG STATE -------------------
	// create a network on GPU
	int numGPUs = 1;
	int randSeed = 42;
	CARLsim sim("gc can", GPU_MODE, USER, numGPUs, randSeed);
	int n_num;
	bool man_move_det = false;
	char pd[p.x_size*p.y_size] = { 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u' }; 
	std::vector<std::vector<float>> etec_weights;
	std::vector<std::vector<float>> ecin_weights;
	double base_w;
	struct MOVE move;
	struct EIWP eiwp;
	double temp_gctoin_wts[p.x_size*p.y_size]; // temp matrix for GC weights
	double temp_intogc_wts[p.x_size*p.y_size]; // temp matrix for IN weights
	double base_input_weight = 0.0;
	double noise_input_weight = 0.0;
	eiwp.pd = pd; 

	// configure the network
	Grid3D grid_ext(p.x_size,p.y_size,1); // external input
	Grid3D grid_exc(p.x_size,p.y_size,1); // GCs
	Grid3D grid_inh(p.x_size,p.y_size,1); // interneurons
	Grid3D grid_nos(p.x_size,p.y_size,1); // noise
	Grid3D grid_pcs(p.x_size,p.y_size,1); // PCs
	int gext=sim.createSpikeGeneratorGroup("ext_input", grid_ext, EXCITATORY_NEURON);
	int gexc=sim.createGroup("gc_exc", grid_exc, EXCITATORY_NEURON);
	int ginh=sim.createGroup("gc_inh", grid_inh, INHIBITORY_NEURON);
	int gnos=sim.createSpikeGeneratorGroup("noise", grid_nos, EXCITATORY_NEURON);
	int gpcs=sim.createSpikeGeneratorGroup("place", grid_pcs, EXCITATORY_NEURON);
	//sim.setNeuronParameters(gexc, 0.02f, 0.2f, -65.0f, 8.0f); // RS
	sim.setNeuronParameters(gexc, 0.1f, 0.2f, -65.0f, 2.0f); // RS
	sim.setNeuronParameters(ginh, 0.1f, 0.2f, -65.0f, 2.0f); // FS
	if (p.base_input == true) {
		base_input_weight = p.base_input_weight;
	}
	sim.connect(gext, gexc, "one-to-one", base_input_weight, 1.0f); // using one-to-one for faster testing than full conn
	sim.connect(gexc, ginh, "one-to-one", p.base_intern_weight, 1.0f);
	sim.connect(ginh, gexc, "one-to-one", p.base_intern_weight, 1.0f);
	if (p.noise_active == true) {
		noise_input_weight = p.noise_input_weight;
	}
	sim.connect(gnos, gexc, "one-to-one", noise_input_weight, 1.0f);
	sim.connect(gpcs, gexc, "one-to-one", 0.0f, 1.0f);
	eiwp.base_w = base_w;
	sim.setConductances(true); // COBA mode; setConductances = true

	// ---------------- SETUP STATE -------------------
	// build the network
	watch.lap("setupNetwork");
	sim.setupNetwork();

	SpikeMonitor* SMext = sim.setSpikeMonitor(gext, "DEFAULT");
	SpikeMonitor* SMexc = sim.setSpikeMonitor(gexc, "DEFAULT");
	SpikeMonitor* SMinh = sim.setSpikeMonitor(ginh, "DEFAULT");
	SpikeMonitor* SMnos = sim.setSpikeMonitor(gnos, "DEFAULT");
	ConnectionMonitor* CMetec = sim.setConnectionMonitor(gext, gexc, "DEFAULT");
	ConnectionMonitor* CMecin = sim.setConnectionMonitor(gexc, ginh, "DEFAULT");
	ConnectionMonitor* CMinec = sim.setConnectionMonitor(ginh, gexc, "DEFAULT");
	ConnectionMonitor* CMnsec = sim.setConnectionMonitor(gnos, gexc, "DEFAULT");	

	//setup some baseline input
	PoissonRate in(grid_ext.N);
	in.setRates(400.0f); //in.setRates(30.0f); //in.setRates(15.0f);
	sim.setSpikeRate(gext,&in);

	// add random noise for realism		
	if (p.noise_active == true) {
		PoissonRate noise(grid_nos.N);
		noise.setRates(25.0f);
		sim.setSpikeRate(gnos,&in);
	}

	PoissonRate pc_in(grid_ext.N);
	pc_in.setRates(50.0f); //in.setRates(30.0f); //in.setRates(15.0f);
	sim.setSpikeRate(gpcs,&pc_in);

	//sim.setSpikeRate(gpcs,1.0f);
	//sim.setExternalCurrent(gexc, 5.0f);
	//sim.setWeight(4,465,465,1.0,true);

	// ---------------- RUN STATE -------------------
	SMext->startRecording();
	SMexc->startRecording();
	SMinh->startRecording();
	SMnos->startRecording();

	SMexc->setPersistentData(true); // keep prior firing when recording is stopped and restarted

	// set activity bump initialization
	init_firing(&sim, &p);

	for (int t=0; t<p.sim_time; t++) {	
		eiwp.t = t;
		p.t = t; // redundent time variable. TODO: consolidate with eiwp.

		// run for 1 ms, don't generate run stats
		sim.runNetwork(0,1,false);

		// process movement
		if (t % p.move_window == 0) {
			// store firing in vector
			SMexc->stopRecording();
			p.nrn_spk = SMexc->getSpikeVector2D();
			SMexc->startRecording();
			// store weights in vector
			ecin_weights = CMecin->takeSnapshot();	
			eiwp.ecin_weights = ecin_weights;	
			etec_weights = CMetec->takeSnapshot();	
			eiwp.etec_weights = etec_weights;

			move_path_bound_test(&sim, eiwp, &p);
			
			//move_path2(&sim, eiwp, &p);
			//straight_path(&sim, eiwp, &p);

			if (p.record_fire_vs_pos) {
				RecordNeuronVsLocation(&sim, &p, eiwp);
			}
			if (p.record_pos_track) {
				RecordLocationPath(&p);
			}
		}

		//if (p.print_time && t % 100 == 0) {printf("t: %dms loc x:%d y:%d\n",t,p.pos[0],p.pos[1]);}
		if (p.print_time && ((t < 1000 && t % 100 == 0) || (t % 1000 == 0))) {printf("t: %dms\n",t);}
	}

	SMext->stopRecording();
	SMexc->stopRecording();
	SMinh->stopRecording();
	SMnos->stopRecording();

	// print firing stats (but not the exact spike times)
	printf("\n\n");
	SMext->print(false);
	SMexc->print(false);
	SMinh->print(false);
	
	return 0;
}
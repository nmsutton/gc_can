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
*/

// include CARLsim user interface
#include <carlsim.h>

// include stopwatch for timing
#include <stopwatch.h>

#include <vector>
#include <spike_monitor.h>
#include <math.h> // for sqrt() and other functions

#define PI 3.14159265

using namespace std;

struct EEWP
{
	int x, y;
	int max_x = 10;
	int max_y = 10;
	float i_ext;
	char ext_pd;
	char *pd;
	std::vector<std::vector<float>> etec_weights;
};

struct EIWP
{
	int x, y, spk_tot;
	int max_x = 10;
	int max_y = 10;
	float gc_spk;
	char gc_pd;
	char *pd; 
	std::vector<std::vector<float>> ecin_weights;
	int conn_groups = 1; // exc -> inh
	int conn_groups2 = 2; // inh -> exc
	int spk_thresh = 3;
	int group_size = 9;
};

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

void SetIndices(int i, int *i_o, int i_size, char axis, int max_i, int *d_i) {
	// calculate interneuron indices in a twisted torus shape.
	// this provides indices limited to the region bump activity occurs.
	// d_i = index distance on x- or y-axis. E.g., distance between neurons as represented
	// by indices.

	if (axis == 'x') {
		i_o[0] = i - 1;
		d_i[0] = -1;
		i_o[1] = i;
		d_i[1] = 0;
		i_o[2] = i + 1;
		d_i[2] = 1;
		i_o[3] = i - 1;
		d_i[3] = -1;
		i_o[4] = i;
		d_i[4] = 0;
		i_o[5] = i + 1;
		d_i[5] = 1;
		i_o[6] = i - 1;
		d_i[6] = -1;
		i_o[7] = i;
		d_i[7] = 0;
		i_o[8] = i + 1;				
		d_i[8] = 1;
	}
	if (axis == 'y') {
		i_o[0] = i - 1;
		d_i[0] = -1;
		i_o[1] = i - 1;
		d_i[1] = -1;
		i_o[2] = i - 1;
		d_i[2] = -1;
		i_o[3] = i;
		d_i[3] = 0;
		i_o[4] = i;
		d_i[4] = 0;
		i_o[5] = i;
		d_i[5] = 0;
		i_o[6] = i + 1;
		d_i[6] = 1;
		i_o[7] = i + 1;
		d_i[7] = 1;
		i_o[8] = i + 1;				
		d_i[8] = 1;
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

void ExtExcWeightProcessor(CARLsim* sim, EEWP eewp) {
	/*
		n_num = neuron number
		i_ext = external input
		ext_pd = external input preferred direction
		pd[] = grid cells' preferred directions
	*/
	int n_num = (eewp.y * eewp.max_x) + eewp.x; // neuron number in 10x10 matrix. hardcoded for convenience but can make dynamic later
	int conn_groups = 0; // ext -> exc

	float new_weight = eewp.etec_weights[n_num][n_num];
	if (eewp.pd[n_num] == eewp.ext_pd) {
		// matching pd found
		// TODO: add scale based on speed coded in external input
		new_weight = new_weight * 1.5f;

		if (new_weight > 0.2f) {
			// set max weight
			new_weight = 0.2f;
		}
	}
	else {
		// let non-matching pd return back to usual weight if no external
		// signal with matching pd is found.
		// TODO: check that this ext->ect connection can lower weights in a
		// biologically realistic way. 
		// Typically a neural connection can only be excitatory or inhibitory
		// but possibly that only refers to firing and not synapse strengths.
		new_weight = new_weight * 0.5f;

		if (new_weight < 0.0f) {
			// set min weight
			new_weight = 0.0f;
		}		
	}
	sim->setWeight(conn_groups,n_num,n_num,new_weight,true);
}

void ExcInhWeightProcessor(CARLsim* sim, EIWP e) {
	/*
		n_num = neuron number
		pd[] = grid cells' preferred directions
	*/
	int n_num = (e.y * e.max_x) + e.x;
	int disp_i;
	double x_offset, y_offset; // offsets are from pd.
	int g_max_x = 3; // bump group max x neurons
	int g_max_y = 3; // bump group max y neurons
	double angle, sigma, max_syn_wt, exc_surr_dist, zero_div;
	double dist = 0, w = 0;
	int i_x[g_max_x*g_max_y]; // interneuron index x
	int i_y[g_max_x*g_max_y]; // interneuron index y
	int d_x[g_max_x*g_max_y]; // neuron distance on x-axis
	int d_y[g_max_x*g_max_y];	

	angle = GetAngle(e.gc_pd);
	SetIndices(e.x, i_x, (g_max_x*g_max_y), 'x', e.max_x, d_x);
	SetIndices(e.y, i_y, (g_max_x*g_max_y), 'y', e.max_y, d_y);

	//if (e.gc_spk > e.spk_thresh) {
	for (int i = 0; i < e.group_size; i++) {
		// TODO: consider adding speed external input variable to adjust weight
		
		x_offset = 0.0; //cos(angle);
		y_offset = 0.0; //sin(angle);
		exc_surr_dist = 0;//9; // distance of the excitatory surround from the position of presynaptic neuron (solanka, 2015)
		sigma = 0.7; //0.0834; // width of the Gaussian profile value from (solanka, 2015)
		max_syn_wt = 1; //5; // maximum synaptic weight value from (solanka, 2015)
		zero_div = 0.000001; // avoid issue with division by 0

		dist = sqrt(pow((d_x[i] - x_offset),2)+pow((d_y[i] - y_offset + zero_div),2));

		w = max_syn_wt * exp((-1*pow((dist - exc_surr_dist),2))/(2*pow(sigma,2))); // weight calc with Gaussian function
		
		/*disp_i = 5;
		if (i == disp_i) {
			printf("\na: %f sqrt(pow((%d - %d - %f),2)+pow((%d - %d - %f),2))",angle,e.x,i_x[i],x_offset,e.y,i_y[i],y_offset);
			printf("\n%f * exp((-1*pow(%f,2))/(2*pow(%f,2)))",max_syn_wt,dist,sigma);
			printf("\ndisp_i: %d i: %d w: %f dist: %f e.x: %d, e.y: %d", disp_i, i, w, dist, e.x, e.y);
		}*/
		//printf("\nix: %d iy: %d w: %f d: %f sqrt(pow((%d - %f),2)+pow((%d - %f),2))",i_x[i],i_y[i],w,dist,d_x[i],x_offset,d_y[i],y_offset);
		printf("\nix: %d iy: %d d: %f w: %f exp((-1*pow(%f,2))/(2*pow(%f,2)))",i_x[i],i_y[i],dist,w,dist,sigma);
		//printf("\n%f %f",(-1*pow((dist - exc_surr_dist),2)),(2*pow(sigma,2)));
	}

	float new_weight = e.ecin_weights[n_num][n_num];
	if (e.gc_spk > e.spk_thresh) {
		// matching pd found
		new_weight = new_weight * 0.8f * (e.gc_spk - e.spk_thresh);

		if (new_weight > 0.2f) {
			// set max weight
			new_weight = 0.2f;
		}
	}
	else {
		new_weight = new_weight * 1.2f * (e.gc_spk - e.spk_thresh);

		if (new_weight < 0.0f) {
			// set min weight
			new_weight = 0.0f;
		}
	}
	sim->setWeight(e.conn_groups,n_num,n_num,new_weight,true);
	sim->setWeight(e.conn_groups2,n_num,n_num,new_weight,true);
}

void MotorControl(int *loc, char move) {
	// control animal movement

	if (move == 'r') {
		loc[0] = loc[0] + 1;
	}
	else if (move == 'l') {
		loc[0] = loc[0] - 1;
	}	
	else if (move == 'u') {
		loc[1] = loc[1] + 1;
	}
	else if (move == 'd') {
		loc[1] = loc[1] - 1;
	}
}

int main() {
	// keep track of execution time
	Stopwatch watch;

	// ---------------- CONFIG STATE -------------------
	// create a network on GPU
	int numGPUs = 1;
	int randSeed = 42;
	CARLsim sim("gc can", GPU_MODE, USER, numGPUs, randSeed);
	int sim_time = 3000;
	vector<vector<int>> nur_spk1_1;
	int n_num;
	int s_num;
	int spk_time;
	int spk_tot = 0;
	bool man_move_det = false;
	char pd[100] = { 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u' }; 
	std::vector<std::vector<float>> etec_weights;
	std::vector<std::vector<float>> ecin_weights;
	float int_w;
	int loc[2] = {0, 0}; // x, y location
	int slow_rate;
	int speed_control;
	int move_time;
	bool move_active;
	struct EEWP eewp;
	struct EIWP eiwp;

	// configure the network
	Grid3D grid_ext(10,10,1); // external input
	Grid3D grid_exc(10,10,1); // GCs
	Grid3D grid_inh(10,10,1); // interneurons
	int gext=sim.createSpikeGeneratorGroup("ext_input", grid_ext, EXCITATORY_NEURON);
	int gexc=sim.createGroup("gc_exc", grid_exc, EXCITATORY_NEURON);
	int ginh=sim.createGroup("gc_inh", grid_inh, INHIBITORY_NEURON);
	sim.setNeuronParameters(gexc, 0.02f, 0.2f, -65.0f, 8.0f); // RS
	sim.setNeuronParameters(ginh, 0.1f, 0.2f, -65.0f, 2.0f); // FS
	sim.connect(gext, gexc, "one-to-one", 0.05f, 1.0f); // using one-to-one for faster testing than full conn
	int_w = 0.1f;
	sim.connect(gexc, ginh, "one-to-one", RangeWeight(int_w), 1.0f);
	sim.connect(ginh, gexc, "one-to-one", RangeWeight(int_w), 1.0f);

	sim.setConductances(true); // COBA mode; setConductances = true

	// ---------------- SETUP STATE -------------------
	// build the network
	watch.lap("setupNetwork");
	sim.setupNetwork();

	SpikeMonitor* SMext = sim.setSpikeMonitor(gext, "DEFAULT");
	SpikeMonitor* SMexc = sim.setSpikeMonitor(gexc, "DEFAULT");
	SpikeMonitor* SMinh = sim.setSpikeMonitor(ginh, "DEFAULT");
	ConnectionMonitor* CMetec = sim.setConnectionMonitor(gext, gexc, "DEFAULT");
	ConnectionMonitor* CMecin = sim.setConnectionMonitor(gexc, ginh, "DEFAULT");
	ConnectionMonitor* CMinec = sim.setConnectionMonitor(ginh, gexc, "DEFAULT");	

	//setup some baseline input
	PoissonRate in(grid_ext.N);
	in.setRates(15.0f);
	sim.setSpikeRate(gext,&in);

	// initial weights
    for (int i; i < 100; i++) {
    	if (i != 0 && i != 1 && i != 10 && i != 11) {
    		sim.setWeight(1,i,i,0.001f,true);
    		sim.setWeight(2,i,i,0.001f,true);
    	}
    	else {
    		sim.setWeight(1,i,i,0.01f,true);
    		sim.setWeight(2,i,i,0.01f,true);
    	}
    }

	// ---------------- RUN STATE -------------------
	SMext->startRecording();
	SMexc->startRecording();
	SMinh->startRecording();

	for (int t=0; t<sim_time; t++) {	
		// run for 1 ms, don't generate run stats
		sim.runNetwork(0,1,false);

		// animal movements
		// speed control limits pace of movements
		slow_rate = 4; // rate movement is slowed
		speed_control = t % slow_rate;
		move_time = 0;
		move_active = false;
		if (speed_control == move_time) {
			move_active = true;
		}

		// configure movement
		if (t < 200 && move_active) {
			MotorControl(loc, 'r');
		}
		else if (t < 600 && move_active) {
			MotorControl(loc, 'u');
		}
		else if (t < 1800 && move_active) {
			MotorControl(loc, 'r');
		}
		else if (t < 2600 && move_active) {
			MotorControl(loc, 'u');
		}
		else if (t < 3400 && move_active) {
			MotorControl(loc, 'l');
		}
		else if (t < 4200 && move_active) {
			MotorControl(loc, 'd');
		}
		else if (t < 5000 && move_active) {
			MotorControl(loc, 'r');
		}
		else if (t < 5800 && move_active) {
			MotorControl(loc, 'u');
		}
		else if (t < 6600 && move_active) {
			MotorControl(loc, 'l');
		}		
		else if (t < 7400 && move_active) {
			MotorControl(loc, 'r');
		}
		else if (t < 7800 && move_active) {
			MotorControl(loc, 'u');
		}
		else if (t < 8200 && move_active) {
			MotorControl(loc, 'r');
		}
		else if (t < 9000 && move_active) {
			MotorControl(loc, 'd');
		}
		else if (t >= 9000 && t < 9400 && move_active) {
			MotorControl(loc, 'r');
		}
		else if (t >= 9400 && t < 10000 && move_active) {
			MotorControl(loc, 'u');
		}		

		// print locations
		if (t % 1000 == 0) {
			printf("\ntime %d location x:%d, y:%d", t, loc[0], loc[1]);
		}		
		if (t == (sim_time - 1)) {
			printf("\n\n");
		}

		if (t == 0) {
			sim.setWeight(0,0,0,0.1f,true);
			sim.setWeight(0,1,1,0.1f,true);
			sim.setWeight(0,10,10,0.2f,true);
			sim.setWeight(0,11,11,0.1f,true);
		}
		if (t == 1000) {
			// count spikes
			int nrn_counted = 11;
			SMexc->stopRecording();
			nur_spk1_1 = SMexc->getSpikeVector2D();
			SMexc->startRecording();
			n_num = nur_spk1_1.size();
			for (int i; i < n_num; i++) {
				s_num = nur_spk1_1[i].size();
				for (int j; j < s_num; j++) {
					if (i == nrn_counted) {
						spk_time = nur_spk1_1[i][j];
						if (spk_time >= 500 && spk_time <= 1000) {
							spk_tot += 1;
						}
					}
				}
			}
			printf("\ntotal spikes in 1s: %d\n", nur_spk1_1[nrn_counted].size());							
			printf("total spikes in 500ms window: %d\n", spk_tot);	

			for (int i = 0; i < (eewp.max_x * eewp.max_y); i++) {
				// store synapse values
				// iterate trough all grid cells
				etec_weights = CMetec->takeSnapshot();	
				eewp.x = i % eewp.max_x;
				eewp.y = i / eewp.max_x;
				eewp.i_ext = 0;
				eewp.ext_pd = 'u';
				eewp.pd = pd;
				eewp.etec_weights = etec_weights;
				ExtExcWeightProcessor(&sim, eewp);

				ecin_weights = CMecin->takeSnapshot();	
				eiwp.x = i % eewp.max_x;
				eiwp.y = i / eewp.max_x;
				printf("\nii:%d x: %d y: %d eiwp.x: %d", i, eiwp.x, eiwp.y, eiwp.x);
				eiwp.gc_spk = 0;
				eiwp.gc_pd = 'u';
				eiwp.pd = pd; 
				eiwp.ecin_weights = ecin_weights;
				eiwp.spk_tot = spk_tot;
				ExcInhWeightProcessor(&sim, eiwp);
			}

			// manual movement example
			if (man_move_det == true && spk_tot > 4) {
				sim.setWeight(0,0,0,0.05f,true);
				sim.setWeight(0,1,1,0.05f,true);
				sim.setWeight(0,10,10,0.05f,true);
				sim.setWeight(0,11,11,0.05f,true);
				sim.setWeight(0,20,20,0.1f,true);
				sim.setWeight(0,21,21,0.1f,true);
				sim.setWeight(0,30,30,0.1f,true);
				sim.setWeight(0,31,31,0.1f,true);
				printf("movement change activated");
			}	
		}
	}
	SMext->stopRecording();
	SMexc->stopRecording();
	SMinh->stopRecording();

	int nur_spk0 = SMexc->getNeuronNumSpikes(0);
	int nur_spk1 = SMexc->getNeuronNumSpikes(1);
	int nur_spk10 = SMexc->getNeuronNumSpikes(10);
	int nur_spk11 = SMexc->getNeuronNumSpikes(11);
	int nur_spk20 = SMexc->getNeuronNumSpikes(20);
	int nur_spk21 = SMexc->getNeuronNumSpikes(21);
	int nur_spk30 = SMexc->getNeuronNumSpikes(30);
	int nur_spk31 = SMexc->getNeuronNumSpikes(31);
	printf("neuron 0 spikes = %d\n", nur_spk0);
	printf("neuron 1 spikes = %d\n", nur_spk1);
	printf("neuron 10 spikes = %d\n", nur_spk0);
	printf("neuron 11 spikes = %d\n", nur_spk1);
	printf("neuron 20 spikes = %d\n", nur_spk20);
	printf("neuron 21 spikes = %d\n", nur_spk21);
	printf("neuron 30 spikes = %d\n", nur_spk30);
	printf("neuron 31 spikes = %d\n", nur_spk31);

	//vector<vector<int>> nur_spk1_1 = SMexc->getSpikeVector2D();
	//printf("neuron 0 spikes = %d\n", nur_spk1_1[1].size());

	// print firing stats (but not the exact spike times)
	SMext->print(false);
	SMexc->print(false);
	SMinh->print(false);

	//CMetec->printSparse();
	//CMecin->printSparse();
	//CMinec->printSparse();

	etec_weights = CMetec->takeSnapshot();
	printf("etec_weights[11][11] = %f\n", etec_weights[11][11]);

	ecin_weights = CMecin->takeSnapshot();
	printf("ecin_weights[11][11] = %f\n", ecin_weights[11][11]);
	
	return 0;
}
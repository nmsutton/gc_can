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

#define PI 3.14159265

using namespace std;

string to_string(double x);

struct EIWP
{
	// exc -> inh synaptic weight relevant parameters

	int x, y, t, spk_tot;
	int max_x = 10;
	int max_y = 10;
	float gc_spk;
	char gc_pd;
	char *pd; 
	std::vector<std::vector<float>> ecin_weights;
	int conn_groups = 1; // exc -> inh
	int conn_groups2 = 2; // inh -> exc
	int spk_thresh = 3;
	int group_size = 25;
	double base_w;
};

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

int SetTarget(int i, int max_i, int offset) {
	/*
		Set target neuron index
	*/

	int i2 = i - offset;

	if (i2 < 0) {
		i2 = i2 + max_i;
	}
	else if (i2 >= max_i) {
		i2 = i2 - max_i;	
	}

	return i2;
}

void PrintWeightsAndFiring(EIWP e, int *spk_tot) {
	int x_p = 5;
	int y_p = 5;
	int max_x = 10;
	int n = 0;

	printf("\n\nexc->inh weights at time %d",e.t);
	for (int i = (y_p - 1); i >= 0; i--) {
		printf("\n");
		for (int j = 0; j < x_p; j++) {
			n = (i * max_x) + j;
			printf("[%f]\t",e.ecin_weights[n][n]);	
		}
	}
	printf("\nGC firing");
	for (int i = (y_p - 1); i >= 0; i--) {
		printf("\n");
		for (int j = 0; j < x_p; j++) {
			n = (i * max_x) + j;
			printf("[%d]\t",spk_tot[n]);	
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

void TransformWeights(double* temp_gctoin_wts, double* temp_intogc_wts, EIWP e) {
	/* 
		adjustments for interneuron weights rather than weight formula's original exc->exc connections
	*/

	int layer_size = e.max_x*e.max_y;
	double w;
	double max_syn_wt = e.base_w; //1; //5; // maximum synaptic weight value from (solanka, 2015)

	for (int i = 0; i < layer_size; i++) {
		w = temp_gctoin_wts[i];

		//w = w * 0.12777;
		//w = w * (1/60);
		w = (1 / w); // flipped scale for less inh. instead of more exc.
		//w = pow((w * 0.3),4); // pow((w * 0.1),2); // scaling factor for intended synapse weights. this is just for testing
		w = pow((w * 15.5),60);
		//w = pow((w * 0.3),12);
		//w = w * .1;

		if (w > max_syn_wt) {
			w = max_syn_wt; // set max weight
		}
		
		//w = w * (1 / (double) e.group_size); // scale influence by number of neurons in local area affected
		temp_gctoin_wts[i] = w;
	}
}

void StoreWeights(CARLsim* sim, double* temp_gctoin_wts, double* temp_intogc_wts, EIWP e) {
	/*
		transfer weights from temp matrix to synapse values
	*/
	int n_num;

	for (int y = 0; y < e.max_y; y++) {
		for (int x = 0; x < e.max_x; x++) {
			n_num = (y * e.max_x) + x;

			sim->setWeight(1,n_num,n_num,temp_gctoin_wts[n_num],true);
			sim->setWeight(2,n_num,n_num,temp_gctoin_wts[n_num],true);
		}
	}
}

void ExcInhWeightProcessor(CARLsim* sim, EIWP e, vector<vector<int>> &nrn_spk, 
	double* temp_gctoin_wts, double* temp_intogc_wts) {
	/*
		n_num = neuron number
		pd[] = grid cells' preferred directions

		This code has the equivalent of the distance formula d = sqrt((e_x - i_x - o_x)^2+(e_y - i_y - o_y)^2)
		where e_x = GC x, i_x = IN x, o_x = offset bias x. However, it is coded in a way here that reduces
		the number of calculations needed for the limited bump activity area to save computational time.
		The original formula can be cited as being applied nonetheless.
	*/
	int e_num, t_num, i_num, disp_i;
	double x_offset, y_offset; // offsets are from pd.
	int g_max_x = 5; // bump group max x neurons
	int g_max_y = 5; // bump group max y neurons
	double angle, sigma, max_syn_wt, exc_surr_dist, zero_div, y_axis_shf;
	double dist = 0, w = 0;
	int i_x[g_max_x*g_max_y]; // interneuron index x
	int i_y[g_max_x*g_max_y]; // interneuron index y
	int d_x[g_max_x*g_max_y]; // neuron distance on x-axis
	int d_y[g_max_x*g_max_y];	
	int t_y, t_x, nrn_size, s_num, spk_time, tot; // t_y, t_x: target y and x
	int spk_tot[e.max_x*e.max_y]; // spike total in window
	for (int i = 0; i < (e.max_x*e.max_y); i++) {
		spk_tot[i] = 0; // initialize as 0
	}
	double speed_factor;
	bool print_on = false; // neurons to print to screen
	if ((e.x==1&&e.y==1) || (e.x==1&&e.y==2)) {
		//print_on = true;
	}
	bool select_xy = false;
	if (e.x==1&&e.y==1) {
		select_xy = true;
	}
	bool select_tnum = false;
	int tnum_print;
	string calc = "";

	// compute pd angle and set indices accordingly
	angle = GetAngle(e.gc_pd);		
	x_offset = cos(angle);
	y_offset = sin(angle);
	SetIndices(e.x, i_x, g_max_x, g_max_y, 'x', e.max_x, d_x, x_offset);
	SetIndices(e.y, i_y, g_max_x, g_max_y, 'y', e.max_y, d_y, y_offset);

	// count spikes
	nrn_size = nrn_spk.size();
	for (int i = 0; i < nrn_size; i++) {
		tot = 0;
		s_num = nrn_spk[i].size();
		for (int j = 0; j < s_num; j++) {
			spk_time = nrn_spk[i][j];
			if (spk_time >= (e.t - 500) && spk_time <= e.t) {
				tot += 1;
			}
		}
		spk_tot[i] = tot;
	}

	// print to screen
	if (print_on) {
		int nrn_counted = (e.y * e.max_x) + e.x;
		printf("\nx %d y %d total spikes in 1s: %d",e.x,e.y,nrn_spk[nrn_counted].size());
		printf("\nx %d y %d total spikes in 500ms window: %d\n",e.x,e.y,spk_tot[nrn_counted]);
	}

	for (int i = 0; i < e.group_size; i++) {
		e_num = (e.y * e.max_x) + e.x; // exc neuron number
		//t_x = SetTarget(e.x, e.max_x, x_offset);
		//t_y = SetTarget(e.y, e.max_y, y_offset);		
		t_x = SetTarget((e.x + d_x[i]), e.max_x, x_offset);
		t_y = SetTarget((e.y + d_y[i]), e.max_y, y_offset);		
		t_num = (t_y * e.max_x) + t_x; // target neuron number
		select_tnum = false;
		tnum_print = 21;
		if (t_num == tnum_print) {
			select_tnum = true;
		}
		exc_surr_dist = 0; //9; // distance of the excitatory surround from the position of presynaptic neuron (solanka, 2015)
		sigma = 0.5;//0.7; //0.0834; // width of the Gaussian profile value from (solanka, 2015)
		speed_factor = spk_tot[e_num] * 0.167; // factor representing speed perception by firing rate
		zero_div = 0.000001; // avoid issue with division by 0

		dist = sqrt(pow((d_x[i]),2)+pow((d_y[i] + zero_div),2));

		w = speed_factor * exp((-1*pow((dist - exc_surr_dist),2))/(2*pow(sigma,2))); // weight calc with Gaussian function
		if (select_xy) {
			if (false) {//print_on) {
				printf("\nweight: %f %f * exp((-1*pow((%f - %f),2))/(2*pow(%f,2)))",w,speed_factor,dist,exc_surr_dist,sigma);
			}
		}

		/*
			// mexican hat
			// from https://en.wikipedia.org/wiki/Ricker_wavelet
			// online plotting: https://www.desmos.com/calculator
		*/

		
		//w = (1 / (PI * pow(sigma,2))) * (1 - (0.5 * (dist / pow(sigma,2)))) * (exp(-1 * (dist / (2 * pow(sigma,2)))));
		//y_axis_shf = 2.7;
		//sigma = 0.8;
		//w = y_axis_shf + speed_factor * ((2 / sqrt(3*sigma*pow(PI,.25))) * (1-pow((dist/sigma),2)) * exp(-1*(pow(dist,2)/(2*pow(sigma,2)))));
		//w = y_axis_shf + speed_factor * ((2 / sqrt(3*sigma*pow(PI,.25))) * (1-pow((dist/sigma),2)) * exp(-1*(pow(dist,2)/(5*pow(sigma,2)))));
		double s1 = 0.5;
		double s2 = 0.5;
		double s3 = 0.3;
		y_axis_shf = 0.6;
		w = y_axis_shf + speed_factor * ((2 / sqrt(3*s1*pow(PI,.25))) * (1-pow(((dist*.3)/s2),2)) * exp(-1*(pow((dist*.3),2)/(2*pow(s3,2)))));
		

		//i_num = (t_y * e.max_x) + t_x;		

		if (print_on) {
			//printf("\ni: %d t_x: %d t_y: %d xo: %f yo: %f d: %f w: %f sw: %f in: %d",i,t_x,t_y,x_offset,y_offset,dist,w,e.ecin_weights[e_num][e_num],i_num);
		}
		if (select_tnum) {//select_xy) {
			if (false) {
				//printf("\ni: %d x: %d y: %d t_num: %d xo: %f yo: %f d: %f w: %f",i,e.x,e.y,t_num,x_offset,y_offset,dist,w);
				printf("\ni: %d x: %d y: %d dx: %d dy: %d tx: %d ty: %d tn: %d d: %f w: %f 1: %f 2: %f 3: >%f 4: %f st: %d",i,e.x,e.y,d_x[i],d_y[i],t_x,t_y,t_num,dist,w,(1 / w),pow(((1 / w) * 0.1),2),max_syn_wt,pow(((1 / w) * 0.1),2) * (1 / (double) e.group_size),spk_tot[e_num]);
			}
		}

		temp_gctoin_wts[t_num] = temp_gctoin_wts[t_num] + w;

		if (select_xy) {
			if (false) {
				calc = calc + "\ttx " + to_string((long int) t_x) + " ty " + to_string((long int) t_y) + " + " + to_string((long double) w);
				if (t_x == e.x + 2) {calc = calc + "\n";}
			}
			if (false) {
				calc = calc + " + " + to_string((long double) w);
			}
		}
		if (select_tnum) {
			printf("\nweight: %f %f * exp((-1*pow((%f - %f),2))/(2*pow(%f,2))) = %f",w,speed_factor,dist,exc_surr_dist,sigma,w);
			cout << " | x " << e.x << " y " << e.y << " w " << w << " d " << dist;
			//cout << " + " << w;
		}
		if (select_tnum && e.x == 0) {
			//cout << "\n";
		}
	}

	if (select_xy) {
		cout << "\n" << calc;
		//cout << "\n" << to_string((long double) temp_gctoin_wts[t_num]);
	}

	// set weight for each e.x + e.y given the w
	// move setWeight outside of the e.group_size loop but use the w from the loop.
	//t_x = SetTarget(e.x, e.max_x, x_offset);
	//t_y = SetTarget(e.y, e.max_y, y_offset);
	/*
	if (e.x == 0) {printf("\n");}
	printf("\nx: %d y: %d | t_x: %d t_y: %d | xo: %f yo: %f",e.x,e.y,t_x,t_y,x_offset,y_offset);
	*/

	//if ((e.x==1&&e.y==2)) { //(print_on) {
		//PrintWeightsAndFiring(e, spk_tot);
	//}
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

void BumpInit(CARLsim* sim) {
	/*
		Initialize activity bump
		Sets interneuron weights to initial value to create an activity bump centered at neuron
		x: 1, y: 1.
	*/

	double rate = .25;
	double f1 = .0003;
	double f2 = .4;
	double f3 = .8;

	sim->setWeight(1,11,11,rate*f1,true);
	sim->setWeight(2,11,11,rate*f1,true);
	sim->setWeight(1,1,1,rate*f2,true);
	sim->setWeight(2,1,1,rate*f2,true);
	sim->setWeight(1,10,10,rate*f2,true);
	sim->setWeight(2,10,10,rate*f2,true);
	sim->setWeight(1,12,12,rate*f2,true);
	sim->setWeight(2,12,12,rate*f2,true);		
	sim->setWeight(1,21,21,rate*f2,true);
	sim->setWeight(2,21,21,rate*f2,true);
	sim->setWeight(1,0,0,rate*f3,true);
	sim->setWeight(2,0,0,rate*f3,true);
	sim->setWeight(1,2,2,rate*f3,true);
	sim->setWeight(2,2,2,rate*f3,true);
	sim->setWeight(1,20,20,rate*f3,true);
	sim->setWeight(2,20,20,rate*f3,true);
	sim->setWeight(1,22,22,rate*f3,true);
	sim->setWeight(2,22,22,rate*f3,true);
}

void MoveCommand(CARLsim* sim, int x, int y, double speed) {
	sim->setWeight(0,x,y,speed,true);
}

int main() {
	// keep track of execution time
	Stopwatch watch;

	// ---------------- CONFIG STATE -------------------
	// create a network on GPU
	int numGPUs = 1;
	int randSeed = 42;
	CARLsim sim("gc can", GPU_MODE, USER, numGPUs, randSeed);
	int sim_time = 7001;
	double move_weight = 0.3; // synaptic weight used to signal movement command
	int n_num;
	bool man_move_det = false;
	static const int x_cnt = 10; // number of cells on x-axis
	static const int y_cnt = 10; // number of cells on y-axis
	char pd[x_cnt*y_cnt] = { 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u' }; 
	std::vector<std::vector<float>> etec_weights;
	std::vector<std::vector<float>> ecin_weights;
	vector<vector<int>> nrn_spk;
	double base_w;
	int loc[2] = {0, 0}; // x, y location
	int slow_rate;
	int speed_control;
	int move_time;
	bool move_active;
	struct EIWP eiwp;
	double temp_gctoin_wts[x_cnt*y_cnt]; // temp matrix for GC weights
	double temp_intogc_wts[x_cnt*y_cnt]; // temp matrix for IN weights

	eiwp.pd = pd; 

	// configure the network
	Grid3D grid_ext(10,10,1); // external input
	Grid3D grid_exc(10,10,1); // GCs
	Grid3D grid_inh(10,10,1); // interneurons
	int gext=sim.createSpikeGeneratorGroup("ext_input", grid_ext, EXCITATORY_NEURON);
	int gexc=sim.createGroup("gc_exc", grid_exc, EXCITATORY_NEURON);
	int ginh=sim.createGroup("gc_inh", grid_inh, INHIBITORY_NEURON);
	sim.setNeuronParameters(gexc, 0.02f, 0.2f, -65.0f, 8.0f); // RS
	sim.setNeuronParameters(ginh, 0.1f, 0.2f, -65.0f, 2.0f); // FS
	sim.connect(gext, gexc, "one-to-one", 0.08f, 1.0f); // using one-to-one for faster testing than full conn
	base_w = 0.5f; // baseline weight for random background noise
	sim.connect(gexc, ginh, "one-to-one", RangeWeight(base_w), 1.0f);
	sim.connect(ginh, gexc, "one-to-one", RangeWeight(base_w), 1.0f);
	eiwp.base_w = base_w;

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
	in.setRates(30.0f); //in.setRates(15.0f);
	sim.setSpikeRate(gext,&in);

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
		/*if (t % 1000 == 0) {
			printf("\ntime %d location x:%d, y:%d", t, loc[0], loc[1]);
		}
		if (t == (sim_time - 1)) {
			printf("\n\n");
		}*/

		if (t == 0) {
			BumpInit(&sim); // set activity bump initialization
		}
		if (t == 1000 || t == 2000 || t == 3000 || t == 4000 || t == 5000 || t == 6000 || t == 7000) {
			// store firing in vector
			SMexc->stopRecording();
			nrn_spk = SMexc->getSpikeVector2D();
			SMexc->startRecording();
			ecin_weights = CMecin->takeSnapshot();	
			eiwp.ecin_weights = ecin_weights;		


			if (t == 1000) {
				MoveCommand(&sim,11,11,move_weight); // send movement signal
			}
			if (t == 2000) {
				MoveCommand(&sim,11,11,0.08);
			}
			if (t == 4000) {
				MoveCommand(&sim,21,21,move_weight);
			}
			if (t == 5000) {
				MoveCommand(&sim,21,21,0.08);
			}

			if (t == 1000 || t == 3000 || t == 4000 || t == 6000 || t == 7000) {
				// display activity

				/*--------Print Weights and Firing--------*/
				int nrn_size, tot, s_num, spk_time;
				int spk_tot[10*10];
				eiwp.t = t;

				// count spikes
				nrn_size = nrn_spk.size();
				for (int i = 0; i < nrn_size; i++) {
					tot = 0;
					s_num = nrn_spk[i].size();
					for (int j = 0; j < s_num; j++) {
						spk_time = nrn_spk[i][j];
						if (spk_time >= (t - 500) && spk_time <= t) {
							tot += 1;
						}
					}
					spk_tot[i] = tot;
				}

				//PrintWeightsAndFiring(eiwp, spk_tot);
				/*----------------------------------------*/
			}		

			if (t == 2000 || t == 5000) {
				// process movement

				// clear temp matrices
				for (int i = 0; i < (eiwp.max_x * eiwp.max_y); i++) {
					temp_gctoin_wts[i] = 0.0;
					temp_intogc_wts[i] = 0.0;
				}

				for (int i = 0; i < (eiwp.max_x * eiwp.max_y); i++) {			
					eiwp.x = i % eiwp.max_x;
					eiwp.y = i / eiwp.max_x;
					eiwp.t = t;
					//if ((eiwp.x==1&&eiwp.y==1) || (eiwp.x==1&&eiwp.y==2)) {printf("\n\nt: %d ii:%d x: %d y: %d eiwp.x: %d",t, i, eiwp.x, eiwp.y, eiwp.x);}
					eiwp.gc_pd = pd[i];
					ExcInhWeightProcessor(&sim, eiwp, nrn_spk, temp_gctoin_wts, temp_intogc_wts);
				}		

				TransformWeights(temp_gctoin_wts, temp_intogc_wts, eiwp);	

				StoreWeights(&sim, temp_gctoin_wts, temp_intogc_wts, eiwp);
			}

			//PrintTempWeights(temp_gctoin_wts, temp_intogc_wts, t);	

			/*--------Print Weights and Firing--------*/
			int nrn_size, tot, s_num, spk_time;
			int spk_tot[10*10];
			eiwp.t = t;

			// count spikes
			nrn_size = nrn_spk.size();
			for (int i = 0; i < nrn_size; i++) {
				tot = 0;
				s_num = nrn_spk[i].size();
				for (int j = 0; j < s_num; j++) {
					spk_time = nrn_spk[i][j];
					if (spk_time >= (t - 500) && spk_time <= t) {
						tot += 1;
					}
				}
				spk_tot[i] = tot;
			}

			PrintWeightsAndFiring(eiwp, spk_tot);				
			/*----------------------------------------*/

			printf("\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
		}
	}
	SMext->stopRecording();
	SMexc->stopRecording();
	SMinh->stopRecording();

	// print firing stats (but not the exact spike times)
	printf("\n\n");
	SMext->print(false);
	SMexc->print(false);
	SMinh->print(false);
	
	return 0;
}
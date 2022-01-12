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

using namespace std;

#include <vector>
#include <math.h> // for sqrt() and other functions

#include "general_funct.cpp"
#include "move_path.cpp"
/*
#include "boundary_cells.cpp"
#include "place_cells.cpp"
*/

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

/*void PrintWeightsAndFiring(EIWP e, int *gc_firing) {
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
			printf("[%d]\t",gc_firing[n]);	
		}
	}
}*/

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

void TransformWeights(double* temp_gctoin_wts, double* temp_intogc_wts, EIWP e, P *p) {
	/* 
		adjustments for interneuron weights rather than weight formula's original exc->exc connections
	*/

	int layer_size = p->x_size*p->y_size;
	double w;
	double max_syn_wt = 0.8; //e.base_w; //1; //5; // maximum synaptic weight value from (solanka, 2015)

	for (int i = 0; i < layer_size; i++) {
		w = temp_gctoin_wts[i];

		w = (1 / w); // flipped scale for less inh. instead of more exc.
		
		//
		//	In practice I found, pow((w * t1), t2), t1 is min weight with steep curve increase. t2 is the steepness.
		//	E.g., for original weights ranging from 18 to 15.5, t1 = 15.5 will cause big increase close to ~16 and
		//	t2 = 50 creates a very high curve steepness.
		//
		w = pow((w * 15.5),60); // scaling factor for intended synapse weights. this is just for testing
		//w = pow((w * 15.5),45);
		//w = pow((w * 0.3),4); // pow((w * 0.1),2); 

		if (w > max_syn_wt) {
			w = max_syn_wt; // set max weight
		}
		
		temp_gctoin_wts[i] = w;
	}
}

void StoreWeights(CARLsim *sim, double *gc_firing, P *p) {
	/*
		transfer weights from temp matrix to synapse values
	*/
	int i;

	for (int y = 0; y < p->y_size; y++) {
		for (int x = 0; x < p->x_size; x++) {
			i = (y * p->x_size) + x;

			sim->setWeight(1,i,i,gc_firing[i],true);
			sim->setWeight(2,i,i,gc_firing[i],true);
		}
	}
}

/*void ExcInhWeightProcessor(CARLsim* sim, EIWP e, vector<vector<int>> nrn_spk, 
	double* temp_gctoin_wts, double* temp_intogc_wts) {
	//
	//	n_num = neuron number
	//	pd[] = grid cells' preferred directions
	//
	//	This code has the equivalent of the distance formula d = sqrt((e_x - i_x - o_x)^2+(e_y - i_y - o_y)^2)
	//	where e_x = GC x, i_x = IN x, o_x = offset bias x. However, it is coded in a way here that reduces
	//	the number of calculations needed for the limited bump activity area to save computational time.
	//	The original formula can be cited as being applied nonetheless.
	//
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
	int gc_firing[p->x_size*p->y_size]; // spike total in window
	for (int i = 0; i < (p->x_size*p->y_size); i++) {
		gc_firing[i] = 0; // initialize as 0
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
	SetIndices(e.x, i_x, g_max_x, g_max_y, 'x', p->x_size, d_x, x_offset);
	SetIndices(e.y, i_y, g_max_x, g_max_y, 'y', p->y_size, d_y, y_offset);

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
		if (i < (p->x_size*p->y_size)) {
			gc_firing[i] = tot;
		}
		if (e.t < 3000) {
			//printf("%f\n",nrn_size);
		}
	}

	// print to screen
	if (print_on) {
		int nrn_counted = (e.y * p->x_size) + e.x;
		printf("\nx %d y %d total spikes in 1s: %d",e.x,e.y,nrn_spk[nrn_counted].size());
		printf("\nx %d y %d total spikes in 500ms window: %d\n",e.x,e.y,gc_firing[nrn_counted]);
	}

	for (int i = 0; i < e.group_size; i++) {
		e_num = (e.y * p->x_size) + e.x; // exc neuron number
		//t_x = SetTarget(e.x, p->x_size, x_offset);
		//t_y = SetTarget(e.y, p->y_size, y_offset);		
		t_x = SetTarget((e.x + d_x[i]), p->x_size, x_offset);
		t_y = SetTarget((e.y + d_y[i]), p->y_size, y_offset);		
		t_num = (t_y * p->x_size) + t_x; // target neuron number
		select_tnum = false;
		tnum_print = 21;
		if (t_num == tnum_print) {
			select_tnum = true;
		}
		exc_surr_dist = 0; //9; // distance of the excitatory surround from the position of presynaptic neuron (solanka, 2015)
		sigma = 0.5;//0.7; //0.0834; // width of the Gaussian profile value from (solanka, 2015)
		speed_factor = gc_firing[e_num] * 0.0835;//0.167; // factor representing speed perception by firing rate
		zero_div = 0.000001; // avoid issue with division by 0

		dist = sqrt(pow((d_x[i]),2)+pow((d_y[i] + zero_div),2));

		w = speed_factor * exp((-1*pow((dist - exc_surr_dist),2))/(2*pow(sigma,2))); // weight calc with Gaussian function
		if (select_xy) {
			if (false) {//print_on) {
				printf("\nweight: %f %f * exp((-1*pow((%f - %f),2))/(2*pow(%f,2)))",w,speed_factor,dist,exc_surr_dist,sigma);
			}
		}

		//
			// mexican hat
			// from https://en.wikipedia.org/wiki/Ricker_wavelet
			// online plotting: https://www.desmos.com/calculator
		//

		
		//w = (1 / (PI * pow(sigma,2))) * (1 - (0.5 * (dist / pow(sigma,2)))) * (exp(-1 * (dist / (2 * pow(sigma,2)))));
		//y_axis_shf = 2.7;
		//sigma = 0.8;
		//w = y_axis_shf + speed_factor * ((2 / sqrt(3*sigma*pow(PI,.25))) * (1-pow((dist/sigma),2)) * exp(-1*(pow(dist,2)/(2*pow(sigma,2)))));
		//w = y_axis_shf + speed_factor * ((2 / sqrt(3*sigma*pow(PI,.25))) * (1-pow((dist/sigma),2)) * exp(-1*(pow(dist,2)/(5*pow(sigma,2)))));
		y_axis_shf = 0.655; //0.6;

		double s1 = 0.5;

		double scale_fac = 0.3;
		double scale_fac2 = 0.5; // 1;
		double s2 = 0.5;

		double scale_fac3 = 8; //12; // 2;
		double s3 = 0.3;				
		speed_factor = speed_factor * 2;//1.34;

		w = y_axis_shf + ((2 / sqrt(3*s1*pow(PI,.25))) * (scale_fac2-pow(((dist*scale_fac)/s2),2)) * (speed_factor * (exp(-1*(scale_fac*pow(dist,2))/(scale_fac3*pow(s3,2))))));
		//w = w + 0.000001 // avoid 0.0 as weight

		//i_num = (t_y * p->x_size) + t_x;		

		if (print_on) {
			//printf("\ni: %d t_x: %d t_y: %d xo: %f yo: %f d: %f w: %f sw: %f in: %d",i,t_x,t_y,x_offset,y_offset,dist,w,e.ecin_weights[e_num][e_num],i_num);
		}
		if (select_tnum) {//select_xy) {
			if (false) {
				//printf("\ni: %d x: %d y: %d t_num: %d xo: %f yo: %f d: %f w: %f",i,e.x,e.y,t_num,x_offset,y_offset,dist,w);
				printf("\ni: %d x: %d y: %d dx: %d dy: %d tx: %d ty: %d tn: %d d: %f w: %f 1: %f 2: %f 3: >%f 4: %f st: %d",i,e.x,e.y,d_x[i],d_y[i],t_x,t_y,t_num,dist,w,(1 / w),pow(((1 / w) * 0.1),2),max_syn_wt,pow(((1 / w) * 0.1),2) * (1 / (double) e.group_size),gc_firing[e_num]);
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
			//printf("\nweight: %f %f * exp((-1*pow((%f - %f),2))/(2*pow(%f,2))) = %f",w,speed_factor,dist,exc_surr_dist,sigma,w);
			//cout << " | x " << e.x << " y " << e.y << " w " << w << " d " << dist;
			//cout << " + " << w;
		}
		if (select_tnum && e.x == 0) {
			//cout << "\n";
		}
	}

	//if (select_xy) {
		//cout << "\n" << calc;
		//cout << "\n" << to_string((long double) temp_gctoin_wts[t_num]);
	//}

	// set weight for each e.x + e.y given the w
	// move setWeight outside of the e.group_size loop but use the w from the loop.
	//t_x = SetTarget(e.x, p->x_size, x_offset);
	//t_y = SetTarget(e.y, p->y_size, y_offset);
	//
	//if (e.x == 0) {printf("\n");}
	//printf("\nx: %d y: %d | t_x: %d t_y: %d | xo: %f yo: %f",e.x,e.y,t_x,t_y,x_offset,y_offset);
	//

	//if ((e.x==1&&e.y==2)) { //(print_on) {
		//PrintWeightsAndFiring(e, gc_firing);
	//}
}*/

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

void init_firing(CARLsim* sim, P *p) {
	// initialize firing

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
			//gc_firing[i] = firing_bumps[i];
			sim->setWeight(2,i,i,firing_bumps[i],true);
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

void MoveCommand(CARLsim* sim, double speed, EIWP* e, MOVE* m) {
	/*
		Update weights with the effects of movement
	*/
	int m_start; // move start time
	char m_direct; // move direction

	/*int n_num = m->move_action[0];
	int move_start = m->move_action[1];
	char move_pd = e->pd[n_num];*/

	/*if ((e->t >= move_start) && (e->t <= (move_start + m->move_time))) {
		sim->setWeight(0,n_num,n_num,speed,true);
		cout << "\nmovement command sent t: " << e->t << " nrn: " << n_num << " weight: " << speed;
	}
	else {
		sim->setWeight(0,n_num,n_num,m->default_weight,true);
	}*/

	// match time with direction
	for (int i = 0; i < m->move_times.size(); i++) {
		if (e->t == m->move_times[i]) {
			m_start = m->move_times[i];
			m_direct = m->move_direct[i];
		}
	}

	// apply weight to matching pd neurons
	for (int i = 0; i < 100; i++) {
		if (e->pd[i] == m_direct) {
			if ((e->t >= m_start) && (e->t <= (m_start + m->move_time))) {
				sim->setWeight(0,i,i,speed,true);
				//printf("\next input applied t:%d n:%d d:%c",e->t,i,m_direct);
			}
		}
	}

	// reset to default ext input after certain time period
	for (int i = 0; i < m->move_times.size(); i++) {
		if (e->t == (m->move_times[i] + 1000)) {
			for (int j = 0; j < 100; j++) {
				m_direct = m->move_direct[i];
				if (e->pd[j] == m_direct) {
					sim->setWeight(0,j,j,m->default_weight,true);
					//printf("\next input reset t:%d n:%d d:%c",e->t,i,m_direct);
				}				
			}
		}
	}
}

void MovePath(CARLsim* sim, MOVE* m, EIWP* e) {
	/*
		Movement path
	*/

	int t = e->t;
	int speed_control = t % m->slow_rate;
	int move_time = 0;
	int n_num, x, y, t_move;
	bool move_active = false;
	if (speed_control == move_time) {
		move_active = true;
	}

	// configure movements
	/*
		how to add a movement:
		1. add entry under set movements
		2. add entry under times to process
	*/
	/*------------------------------------*/
	// 1. set movements
	t_move = 1000;
	if (t >= t_move && t < (t_move+400) && move_active) {
		MotorControl(m->loc, 'u');
	}
	t_move = 4000;
	if (t >= t_move && t < (t_move+400) && move_active) {
		MotorControl(m->loc, 'r');
	}
	/*t_move = 6000;
	if (t >= t_move && t < (t_move+400) && move_active) {
		MotorControl(m->loc, 'r');
	}
	t_move = 6400;
	if (t >= t_move && t < (t_move+400) && move_active) {
		MotorControl(m->loc, 'u');
	}*/	

	// 2. times to process movement weights
	/*move_times.push_back(1000);
	move_times.push_back(4000);
	move_times.push_back(7000);*/
	/*------------------------------------*/

	// print locations
	if (t % 1000 == 0) {
		printf("\ntime %d loc x:%d, y:%d nrn x:%d y:%d", t, m->loc[0], m->loc[1], m->loc[0] / 100, m->loc[1] / 100);
	}
	/*if (t == (e->sim_time - 1)) {
		printf("\n\n");
	}*/

	// process movement
	/*x = m->loc[0] / 100;
	y = m->loc[1] / 100;
	n_num = (y * e->max_x) + x;*/

	for (int i = 0; i < m->move_times.size(); i++) {
		if (t == m->move_times[i] || t == m->move_times[i] + 1000) {
			// perform movement commands
			MoveCommand(sim,m->move_weight,e,m);
		}
	}
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

	if (p->print_move == true && (direction == 'u' || direction == 'd' || direction == 'l' || direction == 'r')) {
		cout << " move: " << direction;
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

void EISignal(char direction, CARLsim* sim, P* p) {
	/*
		Process signaling between gc exc and inh neurons.
	*/	

	double new_firing, new_weight, weight_sum, pd_fac, mex_hat;
	double pdx, pdy, gcx, gcy, d; // for distance
	int pd_i, gc_i;
	double pd_facs[p->layer_size];
	double new_firing_group[p->layer_size];
	for (int i = 0; i < p->layer_size; i++) {
		new_firing_group[i] = 0.00001;
	}
	int nrn_size, s_num, spk_time, tot; // t_y, t_x: target y and x
	double gc_firing[p->x_size*p->y_size]; // gc spike amount
	for (int i = 0; i < (p->x_size*p->y_size); i++) {
		gc_firing[i] = 0; // initialize as 0
	}

	// count spikes
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
		if (i < (p->x_size*p->y_size)) {
			gc_firing[i] = tot;
		}
	}

	set_pos(p, direction);

	if (p->print_move) {cout << "\n";}

	/* apply ext input first */
	for (int gc_i = 0; gc_i < p->layer_size; gc_i++) {
		if (get_pd(gc_i, p) == direction) {
			pd_fac = 1.0;
		}
		else {
			pd_fac = 0.0;
		}

		if (p->base_input) {
			gc_firing[gc_i] = gc_firing[gc_i] + pd_fac;
		}
	}

	/* place cell firing */
	if (p->pc_to_gc) {
		//place_cell_firing(gc_firing, g);
	}

	/* boundary cell firing */
	if (p->bc_to_gc) {
		//boundary_cell_firing(gc_firing, g);
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

							new_firing = (gc_firing[pd_i] * mex_hat) - ((1/pow(p->dist_thresh,1.75))*8);

							new_firing_group[gc_i] = new_firing_group[gc_i] + new_firing;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < p->layer_size; i++) {
		if (p->gc_to_gc) {
			if (new_firing_group[i] > 0) {
				new_firing_group[i] = 0; // only negative values for IN weights
			}
			gc_firing[i] = new_firing_group[i] + (p->dist_thresh*1.7);
		}

		// original tau derivative
		gc_firing[i] = p->asig_a * exp(-1*(gc_firing[i]/p->asig_b))+p->asig_c;
		// non zero firing rectifier
		if (gc_firing[i] < 0) {
			gc_firing[i] = 0;
		}
		// add random noise for realism		
		if (p->noise_active == true) {
			gc_firing[i] = gc_firing[i] + get_noise(p);
		}
	}

	StoreWeights(sim, gc_firing, p);
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
	int sim_time = 1001;//10001;
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
	eiwp.pd = pd; 
	eiwp.sim_time = sim_time;

	// configure the network
	Grid3D grid_ext(p.x_size,p.y_size,1); // external input
	Grid3D grid_exc(p.x_size,p.y_size,1); // GCs
	Grid3D grid_inh(p.x_size,p.y_size,1); // interneurons
	int gext=sim.createSpikeGeneratorGroup("ext_input", grid_ext, EXCITATORY_NEURON);
	int gexc=sim.createGroup("gc_exc", grid_exc, EXCITATORY_NEURON);
	int ginh=sim.createGroup("gc_inh", grid_inh, INHIBITORY_NEURON);
	sim.setNeuronParameters(gexc, 0.02f, 0.2f, -65.0f, 8.0f); // RS
	sim.setNeuronParameters(ginh, 0.1f, 0.2f, -65.0f, 2.0f); // FS
	//sim.connect(gext, gexc, "one-to-one", 0.08f, 1.0f); // using one-to-one for faster testing than full conn
	sim.connect(gext, gexc, "one-to-one", 0.5f, 1.0f); // using one-to-one for faster testing than full conn
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
	in.setRates(400.0f); //in.setRates(30.0f); //in.setRates(15.0f);
	sim.setSpikeRate(gext,&in);

	// ---------------- RUN STATE -------------------
	SMext->startRecording();
	SMexc->startRecording();
	SMinh->startRecording();

	SMexc->setPersistentData(true); // keep prior firing when recording is stopped and restarted

	// set activity bump initialization
	init_firing(&sim, &p);

	for (int t=0; t<sim_time; t++) {	
		eiwp.t = t;
		p.t = t; // redundent time variable. TODO: consolidate with eiwp.

		// run for 1 ms, don't generate run stats
		sim.runNetwork(0,1,false);

		// store firing in vector
		SMexc->stopRecording();
		p.nrn_spk = SMexc->getSpikeVector2D();
		SMexc->startRecording();
		// store weights in vector
		ecin_weights = CMecin->takeSnapshot();	
		eiwp.ecin_weights = ecin_weights;	

		if (t % p.move_window) {
			// process movement

			// clear temp matrices
			for (int i = 0; i < (eiwp.max_x * eiwp.max_y); i++) {
				temp_gctoin_wts[i] = 0.0;
				temp_intogc_wts[i] = 0.0;
			}

			/*for (int i = 0; i < (eiwp.max_x * eiwp.max_y); i++) {			
				eiwp.x = i % eiwp.max_x;
				eiwp.y = i / eiwp.max_x;
				//if ((eiwp.x==1&&eiwp.y==1) || (eiwp.x==1&&eiwp.y==2)) {printf("\n\nt: %d ii:%d x: %d y: %d eiwp.x: %d",t, i, eiwp.x, eiwp.y, eiwp.x);}
				eiwp.gc_pd = pd[i];
				ExcInhWeightProcessor(&sim, eiwp, nrn_spk, temp_gctoin_wts, temp_intogc_wts);
			}		

			TransformWeights(temp_gctoin_wts, temp_intogc_wts, eiwp);	

			StoreWeights(&sim, temp_gctoin_wts, temp_intogc_wts, eiwp);*/

			move_path_bound_test(&sim, eiwp, &p);
		}

		// create movement path
		MovePath(&sim, &move, &eiwp);				

		if (t % 1000 == 0 && t != 0) {
			//PrintTempWeights(temp_gctoin_wts, temp_intogc_wts, t);	

			/*--------Print Weights and Firing--------*/
			/*int nrn_size, tot, s_num, spk_time;
			int gc_firing[10*10];
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
				gc_firing[i] = tot;
			}

			PrintWeightsAndFiring(eiwp, gc_firing);			

			printf("\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _");*/
			/*----------------------------------------*/
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
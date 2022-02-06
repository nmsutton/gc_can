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

//#include <periodic_spikegen.h>
//#include "/comp_neuro/Software/CARLsim6/tools/spike_generators/carlsim_spike_generators_api.h"
//#include "/home/nmsutton/CARLsim6/include/periodic_spikegen.h"
#include "periodic_spikegen_custom.cpp"

// include stopwatch for timing
//#include <stopwatch.h>

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

/*void setWeightCustom(short int connId, int neurIdPre, int neurIdPost, float weight, bool updateWeightRange) {
	assert(connId>=0 && connId<getNumConnections());
	assert(weight>=0.0f);

	assert(neurIdPre >= 0  && neurIdPre < getGroupNumNeurons(connectConfigMap[connId].grpSrc));
	assert(neurIdPost >= 0 && neurIdPost < getGroupNumNeurons(connectConfigMap[connId].grpDest));

	float maxWt = fabs(connectConfigMap[connId].maxWt);
	float minWt = 0.0f;

	// inform user of acton taken if weight is out of bounds
	bool needToPrintDebug = (weight>maxWt || weight<minWt);

	int netId = groupConfigMDMap[connectConfigMap[connId].grpDest].netId;
	int postlGrpId = groupConfigMDMap[connectConfigMap[connId].grpDest].lGrpId;
	int prelGrpId = groupConfigMDMap[connectConfigMap[connId].grpSrc].lGrpId;

	fetchPreConnectionInfo(netId);
	fetchConnIdsLookupArray(netId);
	fetchSynapseState(netId);

	if (updateWeightRange) {
		// if this flag is set, we need to update minWt,maxWt accordingly
		// will be saving new maxSynWt and copying to GPU below
//		connInfo->minWt = fmin(connInfo->minWt, weight);
		maxWt = fmax(maxWt, weight);
		if (needToPrintDebug) {
			KERNEL_DEBUG("setWeight(%d,%d,%d,%f,%s): updated weight ranges to [%f,%f]", connId, neurIdPre, neurIdPost,
				weight, (updateWeightRange?"true":"false"), minWt, maxWt);
		}
	} else {
		// constrain weight to boundary values
		// compared to above, we swap minWt/maxWt logic
		weight = fmin(weight, maxWt);
		weight = fmax(weight, minWt);
		if (needToPrintDebug) {
			KERNEL_DEBUG("setWeight(%d,%d,%d,%f,%s): constrained weight %f to [%f,%f]", connId, neurIdPre, neurIdPost,
				weight, (updateWeightRange?"true":"false"), weight, minWt, maxWt);
		}
	}

	// find real ID of pre- and post-neuron
	int neurIdPreReal = groupConfigs[netId][prelGrpId].lStartN + neurIdPre;
	int neurIdPostReal = groupConfigs[netId][postlGrpId].lStartN + neurIdPost;

	// iterate over all presynaptic synapses until right one is found
	bool synapseFound = false;
	int pos_ij = managerRuntimeData.cumulativePre[neurIdPostReal];
	for (int j = 0; j < managerRuntimeData.Npre[neurIdPostReal]; pos_ij++, j++) {
		SynInfo* preId = &(managerRuntimeData.preSynapticIds[pos_ij]);
		int pre_nid = GET_CONN_NEURON_ID((*preId));
		if (GET_CONN_NEURON_ID((*preId)) == neurIdPreReal) {
			assert(managerRuntimeData.connIdsPreIdx[pos_ij] == connId); // make sure we've got the right connection ID

			managerRuntimeData.wt[pos_ij] = isExcitatoryGroup(connectConfigMap[connId].grpSrc) ? weight : -1.0 * weight;
			managerRuntimeData.maxSynWt[pos_ij] = isExcitatoryGroup(connectConfigMap[connId].grpSrc) ? maxWt : -1.0 * maxWt;

			if (netId < CPU_RUNTIME_BASE) {
#ifndef __NO_CUDA__
				// need to update datastructures on GPU runtime
				CUDA_CHECK_ERRORS(cudaMemcpy(&runtimeData[netId].wt[pos_ij], &managerRuntimeData.wt[pos_ij], sizeof(float), cudaMemcpyHostToDevice));
				if (runtimeData[netId].maxSynWt != NULL) {
					// only copy maxSynWt if datastructure actually exists on the GPU runtime
					// (that logic should be done elsewhere though)
					CUDA_CHECK_ERRORS(cudaMemcpy(&runtimeData[netId].maxSynWt[pos_ij], &managerRuntimeData.maxSynWt[pos_ij], sizeof(float), cudaMemcpyHostToDevice));
				}
#else
				assert(false);
#endif
			} else {
				// need to update datastructures on CPU runtime
				memcpy(&runtimeData[netId].wt[pos_ij], &managerRuntimeData.wt[pos_ij], sizeof(float));
				if (runtimeData[netId].maxSynWt != NULL) {
					// only copy maxSynWt if datastructure actually exists on the CPU runtime
					// (that logic should be done elsewhere though)
					memcpy(&runtimeData[netId].maxSynWt[pos_ij], &managerRuntimeData.maxSynWt[pos_ij], sizeof(float));
				}
			}

			// synapse found and updated: we're done!
			synapseFound = true;
			break;
		}
	}

	if (!synapseFound) {
		KERNEL_WARN("setWeight(%d,%d,%d,%f,%s): Synapse does not exist, not updated.", connId, neurIdPre, neurIdPost,
			weight, (updateWeightRange?"true":"false"));
	}
}*/

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

void PrintWeightsAndFiring(P *p) {
	int x_p = 19;//20;
	int y_p = 19;//20;
	int max_x = p->x_size;
	int n = 0;

	if (p->print_in_weights) {
		printf("\n\nec->in weights at time %d",p->t);
		for (int i = (y_p - 1); i >= 0; i--) {
			printf("\n");
			for (int j = 0; j < x_p; j++) {
				n = (i * max_x) + j;
				//printf("[%.2f]",p->weights_in[n][n]);	
				printf("[%.2f]",p->inec_weights[n][n]);	
				//printf("[%.4f]",p->weights_in[31][n]);	
			}
		}
	}
	/*if (p->print_ext_weights) {
		printf("\n\next->ec weights at time %d",e.t);
		for (int i = (y_p - 1); i >= 0; i--) {
			printf("\n");
			for (int j = 0; j < x_p; j++) {
				n = (i * max_x) + j;
				printf("[%.1f]\t",e.etec_weights[n][n]);	
			}
		}
	}*/
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

void StoreWeights(CARLsim *sim, double *in_weights, P *p) {
	/*
		transfer weights from temp matrix to synapse values
	*/
	int i;

	for (int y = 0; y < p->y_size; y++) {
		for (int x = 0; x < p->x_size; x++) {
			i = (y * p->x_size) + x;

			if (!p->fire_vs_pos_test_mode) {
				// normal, non-testing, mode
			  //sim->setWeight(1,i,i,in_weights[i],true);
			  sim->setWeight(2,i,i,in_weights[i],true);
			}
			else {
				// for fire vs loc plot testing
				double new_weight = in_weights[i];
				new_weight = new_weight - 2;
				// following generates PC firing for excitatory mex hat portion and IN firing for inhib. mex hat.
				if (new_weight >= 0) {
					sim->setWeight(3,i,i,new_weight,true);
					sim->setWeight(1,i,i,0,true);
				  sim->setWeight(2,i,i,0,true);
				}
				else {
				  sim->setWeight(1,i,i,1,true);
				  sim->setWeight(2,i,i,1,true);
				  sim->setWeight(3,i,i,0,true);
				}
			}
		}
	}
}

double adj_weight(double value) {
	// This is designed to make the synaptic weight response more linear
	value = value * 0.85+(.25*exp(-((10*pow(value-0.5,2))/(2*pow(1.05,2)))));
	//value = 1;
	return value;
}

void init_firing2(CARLsim* sim, P *p) {
	// set values for 2d weight matrix for IN->GC connections
	double mex_hat, d;
	int i, j;

	// generate weights
	for (int y_in = 0; y_in < p->y_size; y_in++) {
		for (int x_in = 0; x_in < p->x_size; x_in++) {
			for (int y_gc = 0; y_gc < p->y_size; y_gc++) {
				for (int x_gc = 0; x_gc < p->x_size; x_gc++) {			
					i = (y_in * p->x_size) + x_in; // in neuron	
					j = (y_gc * p->x_size) + x_gc; // gc neuron
							
					if (i == 31) {						
						d = get_distance(x_in, y_in, x_gc, y_gc, 'n', p);

						if (d < p->dist_thresh) { 
							mex_hat = get_mex_hat(d, p);
							if (mex_hat > 0) {
								p->weights_in[i][j] = mex_hat;
							}
							else {
								p->weights_in[i][j] = 0.0;
							}
						}
						else {
							p->weights_in[i][j] = p->non_range_weight; 
						}
					}
					else {
						p->weights_in[i][j] = p->non_range_weight;
					}
				}
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
	double weights_bumps[p->layer_size];
	for (int i = 0; i < p->layer_size; i++) {
		weights_bumps[i] = 0.3;
	}
	int bump_pos[p->num_bumps][2] = {{init_x,init_y},
	{(init_x+bump_d),init_y},
	{init_x,(init_y+bump_d)},
	{(init_x+bump_d),(init_y+bump_d)}};
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
					//new_firing = weights_bumps[i] * mex_hat;// - ((1/pow(p->dist_thresh,1.75))*8);
					weights_bumps[i] = weights_bumps[i] * mex_hat;		
				}
			}
		}
	}

	for (int i = 0; i < p->layer_size; i++) {
		//weights_bumps[i] = weights_bumps[i] * -1; // invert values
		if (weights_bumps[i] < 0.0) {			
			weights_bumps[i] = 0.0; // no neg values rectifier
		}
		weights_bumps[i] = adj_weight(weights_bumps[i]);
		//weights_bumps[i] = weights_bumps[i] + (p->dist_thresh*1.7);
		if (p->init_bumps) {
			sim->setWeight(2,i,i,weights_bumps[i],true);
			//p->weights_in[i][i] = weights_bumps[i];
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
	for (int i = 0; i < (p->layer_size); i++) {
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
		//if (p->gc_to_gc && i < (p->layer_size)) {
		if (i < (p->layer_size)) {
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

void RecordLocationPath(P *p, string rec_type) {
	int pos_i = (p->pos[1] * p->x_size) + p->pos[0];

	for (int i = 0; i < p->layer_size; i++) {
		if (rec_type != "all") {
			if (i == pos_i) {
				p->animal_location[i] = 5;
			}
			else {
				p->animal_location[i] = 0;
			}
		}
		else if (i == pos_i) {
			p->animal_location_all[i] = p->animal_location_all[i] + 1;
		}
	}

	if (rec_type != "all") {
		write_firing(p->animal_location, "pos_track", p);
	}
	else {
		write_firing(p->animal_location_all, "pos_track_all", p);
	}
}

void SetDirWeights(char direction, CARLsim* sim, P *p) {
	// set weights for ext-dir input
	for (int i = 0; i < p->layer_size; i++) {
		if (get_pd(i, p) == direction) {
			sim->setWeight(4,i,i,1.0,true);
		}
		else {
			sim->setWeight(4,i,i,0.0,true);
		}
	}
}

void SetInExcMatrix(char direction, CARLsim* sim, P *p) {
	// set values for 2d weight matrix for IN->GC connections
	double mex_hat, d;
	int i, j;

	// generate weights
	for (int y_in = 0; y_in < p->y_size; y_in++) {
		for (int x_in = 0; x_in < p->x_size; x_in++) {
			for (int y_gc = 0; y_gc < p->y_size; y_gc++) {
				for (int x_gc = 0; x_gc < p->x_size; x_gc++) {			
					i = (y_in * p->x_size) + x_in; // in neuron	
					j = (y_gc * p->x_size) + x_gc; // gc neuron
							
					if (direction == get_pd(x_in, y_in) || direction == 'n') {						
						d = get_distance(x_in, y_in, x_gc, y_gc, direction, p);
						//printf("dist:%f\n",d);

						if (d < p->dist_thresh) { 
							mex_hat = get_mex_hat(d, p);
							if (i < 100) {
								//printf("mh:%d %d\n",i,j);
							}
							if (mex_hat > 0) {
								p->weights_in[i][j] = mex_hat;
								//printf("mh:%d %d\n",i,j);
							}
							else {
								p->weights_in[i][j] = 0.0;
							}
						}
						else {
							p->weights_in[i][j] = p->non_range_weight; 
						}
					}
					else {
						p->weights_in[i][j] = p->non_range_weight;
					}
				}
			}
		}
	}
}

// custom ConnectionGenerator
class MexHatConnection : public ConnectionGenerator {
public:
    vector<vector<double>> weights_in;
    MexHatConnection(P *p) {
    	//this->test3 = test;
    	this->weights_in = p->weights_in;
    }
    ~MexHatConnection() {}
 
    // the pure virtual function inherited from base class
    // note that weight, maxWt, delay, and connected are passed by reference
    void connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j, float& weight, float& maxWt,
            float& delay, bool& connected) {
    		//connected = 1;
    		connected = (i == j); // one-to-one
        weight = this->weights_in[i][j];
        maxWt = 10.0f;
        delay = 1; 
    }
};

void EISignal(char direction, CARLsim* sim, P* p, EIWP e) {
	/*
		Process signaling between gc exc and inh neurons.
	*/	

	double new_firing, new_weight, weight_sum, pd_fac, mex_hat;
	double x_in, y_in, x_gc, y_gc, d; // for distance
	int i_in, i_gc;
	/*vector<vector<double>> weights_in_new(p->layer_size, vector<double>(p->layer_size));
	//double weights_in_new[p->layer_size];
	for (int i = 0; i < p->layer_size; i++) {
		weights_in_new[i][i] = 0.00001;
	}*/
	int nrn_size, s_num, spk_time, tot; // t_y, t_x: target y and x
	/*double in_weights[p->layer_size]; // inhibitory weights
	for (int i = 0; i < (p->layer_size); i++) {
		in_weights[i] = p->gc_firing[i];//0.0;
	}*/
	bool gc_to_gc = false;
	if (p->gc_to_gc == true && p->t > 100) {
		gc_to_gc = true; // allow time for initial bumps to form
	}

	count_gc_firing(p);

	set_pos(p, direction);

	if (p->base_dir_input) {
		SetDirWeights(direction, sim, p);
	}

	/*if (p->gc_to_gc) {
		SetInExcMatrix(direction, sim, p);
	}*/

	if (p->print_move) {cout << "\n";}

	/* place cell firing */
	if (p->pc_to_gc) {
		place_cell_firing(sim, p);
	}

	/* boundary cell firing */
	if (p->bc_to_gc) {
		//boundary_cell_firing(in_weights, g);
	}

	/* grid cell and interneuron synapse connections */
	if (gc_to_gc) {
		for (int i = 0; i < p->layer_size; i++) {
			p->weights_in[i][i] = 0.0; // reset weights
			p->weights_in_upd[i][i] = false;
		}

		for (int y_in = 0; y_in < p->y_size; y_in++) {
			for (int x_in = 0; x_in < p->x_size; x_in++) {
				if (direction == get_pd(x_in, y_in) || direction == 'n') {
					for (int y_gc = 0; y_gc < p->y_size; y_gc++) {
						for (int x_gc = 0; x_gc < p->x_size; x_gc++) {			
							i_in = (y_in * p->x_size) + x_in;						
							i_gc = (y_gc * p->x_size) + x_gc;
							d = get_distance(x_in, y_in, x_gc, y_gc, direction, p);
							//if (d < p->dist_thresh) { 
							if (i_in == 31 && d < p->dist_thresh) { 
								mex_hat = get_mex_hat(d, p);
								//new_firing = (in_weights[i_in] * mex_hat)*.02;// - ((1/pow(p->dist_thresh,1.75))*8);
								//new_firing = .01;
								new_firing = (((11-p->gc_firing[i_in])*(1/11)) + mex_hat)*(.1);//*.2;
								p->weights_in[i_gc][i_gc] = p->weights_in[i_gc][i_gc] + new_firing;
								if (i_in < 40) {
									//printf("%d %d\n",i_in,i_gc);
								}
								//printf("%f %f\n",d,mex_hat);
								p->weights_in_upd[i_gc][i_gc] = true;
							}
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < p->layer_size; i++) {
		if (gc_to_gc) {
			if (p->weights_in_upd[i][i] == false) {
				p->weights_in[i][i] = 2.0;//0.5; // default for no update
			}
			sim->setWeight(2,i,i,p->weights_in[i][i],true);
		}
		if (p->noise_active == true) {
			sim->setWeight(0,i,i,get_noise(p),true); // add random noise for realism
		}
	}
}

int main() {
	struct P p;	

	// keep track of execution time
	//Stopwatch watch;

	// ---------------- CONFIG STATE -------------------
	// create a network on GPU
	int numGPUs = 1;
	int randSeed = 42;
	CARLsim sim("gc can", GPU_MODE, USER, numGPUs, randSeed);
	//CARLsim sim("gc can", CPU_MODE, USER, numGPUs, randSeed);
	//CARLsim sim("gc can", CPU_MODE, USER);
	int n_num;
	bool man_move_det = false;
	char pd[p.x_size*p.y_size] = { 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'd', 'r', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u', 'l', 'u' }; 
	std::vector<std::vector<float>> etec_weights;
	std::vector<std::vector<float>> inec_weights;
	struct MOVE move;
	struct EIWP eiwp;
	double temp_gctoin_wts[p.x_size*p.y_size]; // temp matrix for GC weights
	double temp_intogc_wts[p.x_size*p.y_size]; // temp matrix for IN weights
	double base_input_weight = 0.0;
	double noise_addit_freq = 0.0;
	if (p.noise_active) {
		noise_addit_freq = p.noise_addit_freq;
	}
	eiwp.pd = pd; 
	for (int i = 0; i < (p.x_size*p.y_size); i++) {
		p.animal_location_all[i] = 0.0; // initialize
	}
	// initialize matrix
	vector<vector<double>> weights_in_temp(p.layer_size, vector<double>(p.layer_size)); // set size
	vector<vector<bool>> weights_in_upd_temp(p.layer_size, vector<bool>(p.layer_size)); // set size
	p.weights_in = weights_in_temp;
	p.weights_in_upd = weights_in_upd_temp;
	for (int i = 0; i < p.layer_size; i++) {
		p.weights_in[i][i] = 0.0; // only init one-to-one connections
	}
	/*for (int i = 0; i < p.layer_size; i++) {
		for (int j = 0; j < p.layer_size; j++) {
			p.weights_in[i][j] = 0.0;
		}
	}*/

	// configure the network
	Grid3D grid_ext_base(p.x_size,p.y_size,1); // external input
	Grid3D grid_ext_base_dir(p.x_size,p.y_size,1); // external dir input
	Grid3D grid_exc(p.x_size,p.y_size,1); // GCs
	Grid3D grid_inh(p.x_size,p.y_size,1); // interneurons
	Grid3D grid_nos(p.x_size,p.y_size,1); // noise
	Grid3D grid_pcs(p.x_size,p.y_size,1); // PCs
	int gebs=sim.createSpikeGeneratorGroup("ext_base", grid_ext_base, EXCITATORY_NEURON);
	int gexc=sim.createGroup("gc_exc", grid_exc, EXCITATORY_NEURON);
	int ginh=sim.createGroup("gc_inh", grid_inh, INHIBITORY_NEURON);
	int gpcs=sim.createSpikeGeneratorGroup("place", grid_pcs, EXCITATORY_NEURON);
	int gedr=sim.createSpikeGeneratorGroup("ext_dir", grid_ext_base_dir, EXCITATORY_NEURON);
	//sim.setNeuronParameters(gexc, 0.02f, 0.2f, -65.0f, 8.0f); // RS
	sim.setNeuronParameters(gexc, 0.1f, 0.2f, -65.0f, 2.0f); // RS
	sim.setNeuronParameters(ginh, 0.1f, 0.2f, -65.0f, 2.0f); // FS
	if (p.base_input == true) {
		base_input_weight = p.base_input_weight;
	}
	SetInExcMatrix('u', &sim, &p);
	MexHatConnection* MexHatConn = new MexHatConnection(&p);	
	sim.connect(gebs, gexc, "one-to-one", base_input_weight, 1.0f); // 1; using one-to-one for faster testing than full conn
	sim.connect(gexc, ginh, "one-to-one", p.base_gc_to_in_weight, 1.0f); // 2;
	sim.connect(ginh, gexc, "one-to-one", 0.0f, 1.0f); // 3;
	//sim.connect(ginh, gexc, MexHatConn, SYN_FIXED); // 3;
	sim.connect(gpcs, gexc, "one-to-one", 0.0f, 1.0f); // 4;
	sim.connect(gedr, gexc, "one-to-one", 0.0f, 1.0f); // 5;
	sim.setConductances(true); // COBA mode; setConductances = true

	// baseline input
	PeriodicSpikeGenerator ext_base_in((12.0f+noise_addit_freq), true);
	sim.setSpikeGenerator(gebs, &ext_base_in);	

	// PC input
	PeriodicSpikeGenerator ext_dir_in(10.0f, true);
	sim.setSpikeGenerator(gedr, &ext_dir_in);

	// ext dir input
	PeriodicSpikeGenerator pc_in(40.0f, true);
	sim.setSpikeGenerator(gpcs, &pc_in);

	// ---------------- SETUP STATE -------------------
	// build the network
	//watch.lap("setupNetwork");
	sim.setupNetwork();

	//SpikeMonitor* SMext = sim.setSpikeMonitor(gebs, "DEFAULT");
	SpikeMonitor* SMexc = sim.setSpikeMonitor(gexc, "DEFAULT");
	SpikeMonitor* SMinh = sim.setSpikeMonitor(ginh, "DEFAULT");
	//ConnectionMonitor* CMetec = sim.setConnectionMonitor(gebs, gexc, "DEFAULT");
	ConnectionMonitor* CMecin = sim.setConnectionMonitor(gexc, ginh, "DEFAULT");
	ConnectionMonitor* CMinec = sim.setConnectionMonitor(ginh, gexc, "DEFAULT");	

	// ---------------- RUN STATE -------------------
	//SMext->startRecording();
	SMexc->startRecording();
	SMinh->startRecording();

	SMexc->setPersistentData(true); // keep prior firing when recording is stopped and restarted

	// set activity bump initialization
	if (p.init_bumps) {
		init_firing(&sim, &p);
	}

	for (int t=0; t<p.sim_time; t++) {	
		eiwp.t = t;
		p.t = t; // redundent time variable. TODO: consolidate with eiwp.

		// run for 1 ms, don't generate run stats
		sim.runNetwork(0,1,false);

		// process movement
		if (t % p.move_window == 0) {
		//if (t % p.move_window == 0 && t > 100) {
			// store firing in vector
			SMexc->stopRecording();
			p.nrn_spk = SMexc->getSpikeVector2D();
			SMexc->startRecording();
			// store weights in vectors
			inec_weights = CMinec->takeSnapshot();	
			p.inec_weights = inec_weights;	
			//etec_weights = CMetec->takeSnapshot();	
			//p.etec_weights = etec_weights;

			//p.weights_in[31][0] = p.weights_in[31][0] + 1.0;

			if (t != 0) { // if statement avoids this when no spikes have yet been recorded
				move_path_bound_test(&sim, eiwp, &p);
			}
			
			//move_path2(&sim, eiwp, &p);
			//straight_path(&sim, eiwp, &p);

			PrintWeightsAndFiring(&p);

			if (p.record_fire_vs_pos) {
				RecordNeuronVsLocation(&sim, &p, eiwp);
			}
			if (p.record_pos_track) {
				RecordLocationPath(&p, "current");
			}
			if (p.record_pos_track_all) {
				RecordLocationPath(&p, "all");
			}
		}

		//if (p.print_time && t % 100 == 0) {printf("t: %dms loc x:%d y:%d\n",t,p.pos[0],p.pos[1]);}
		if (p.print_time && ((t < 1000 && t % 100 == 0) || (t % 1000 == 0))) {printf("t: %dms\n",t);}
	}

	//SMext->stopRecording();
	SMexc->stopRecording();
	SMinh->stopRecording();

	// print firing stats (but not the exact spike times)
	printf("\n\n");
	//SMext->print(false);
	SMexc->print(false);
	SMinh->print(false);
	
	return 0;
}
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
#include <neuron_monitor_core.h>
#include <vector>
#include <spike_monitor.h>
#include <math.h> // for sqrt() and other functions
#include <string> // for to_string()
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream> // for file out
using namespace std;
#include <math.h> // for sqrt() and other functions
#include "../data/ext_dir_initial.cpp"
#include "../data/ext_dir.cpp"
#include "../data/init_firings.cpp"
#include "../data/synapse_weights.cpp"
#include "../general_params.cpp"
#include "../place_cells.cpp"
#include "../general_funct.cpp"
#include "../move_path.cpp"
//#include "boundary_cells.cpp"

#if hopper_run
#else
	#if import_animal_data
		//#include "../data/anim_angles_191108_S1_lightVSdarkness_cells11and12.cpp"
		//#include "../data/anim_speeds_191108_S1_lightVSdarkness_cells11and12.cpp"
		#include "../data/anim_angles.cpp"
		#include "../data/anim_speeds.cpp"
	#endif
#endif

int main() {
	// ---------------- CONFIG STATE -------------------
	// create a network on GPU
	struct P p;	
	int numGPUs = 1;
	int randSeed = 42;
	CARLsim sim("gc can", GPU_MODE, USER, numGPUs, randSeed);
	//CARLsim sim("gc can", CPU_MODE, USER);
	int n_num;
	std::vector<std::vector<float>> inec_weights;
	double noise_addit_freq = 0.0;
	if (p.noise_active) {noise_addit_freq = p.noise_addit_freq;}
	for (int i = 0; i < (p.x_size*p.y_size); i++) {
		p.animal_location_all[i] = 0.0; // initialize
	}
	// initialize matrix
	vector<vector<double>> weights_in_temp(p.layer_size, vector<double>(p.layer_size)); // set size
	p.weights_in = weights_in_temp;
	for (int i = 0; i < p.layer_size; i++) {
		for (int j = 0; j < p.layer_size; j++) {p.weights_in[i][j] = 0.0;}
	}
	vector<float> temp_vector(p.layer_size); // set vector size
	p.ext_dir = temp_vector;
	p.pc_activity = temp_vector;
	#if hopper_run
		#if import_animal_data
			vector<double> anim_angles = ParseCSV(p.anim_angles_csv);
			vector<double> anim_speeds = ParseCSV(p.anim_speeds_csv);
		#endif
	#endif

	#include "../generate_config_state.cpp" // include file that contains generation of groups and their properties

	// ---------------- SETUP STATE -------------------
	// build the network
	sim.setupNetwork();
	setInitExtDir(&p); // Initial excitatory current to GCs
	sim.setExternalCurrent(EC_LI_II_Multipolar_Pyramidal, ext_dir_initial);
	//sim.setExternalCurrent(MEC_LII_Basket_Speed, ext_dir_initial);
	SpikeMonitor* SMexc = sim.setSpikeMonitor(MEC_LII_Stellate, "DEFAULT");
	SpikeMonitor* SMinh = sim.setSpikeMonitor(MEC_LII_Basket, "DEFAULT");
	SpikeMonitor* SMext = sim.setSpikeMonitor(EC_LI_II_Multipolar_Pyramidal, "DEFAULT");
	SpikeMonitor* SMspe = sim.setSpikeMonitor(MEC_LII_Basket_Speed, "DEFAULT");
	if (p.record_spikes_file) {p.spikes_output_file.open(p.spikes_output_filepath);}
	if (p.record_highrestraj) {p.highres_pos_x_file.open(p.highres_pos_x_filepath);}
	if (p.record_highrestraj) {p.highres_pos_y_file.open(p.highres_pos_y_filepath);}

	// ---------------- RUN STATE -------------------
	SMexc->startRecording();
	SMexc->setPersistentData(true); // keep prior firing when recording is stopped and restarted
	SMinh->startRecording();
	SMinh->setPersistentData(true);
	SMext->startRecording();
	SMext->setPersistentData(true);
	SMspe->startRecording();
	SMspe->setPersistentData(true);
	for (int i = 0; i < p.layer_size; i++) {
		p.gc_firing[i] = init_firings[i]; // set initial firing
	}
	
	#if import_animal_data
		//printf("%f\n",anim_speeds[100]);
		animal_data_vars(&sim, &p, &anim_angles, &anim_speeds);
	#endif	

	for (int t=0; t<p.sim_time; t++) {	
		p.t = t;
		// Disable initial current to GCs settings
		if (t == 2) {
			setExtDir(&p,270,0.04,0);
			sim.setExternalCurrent(EC_LI_II_Multipolar_Pyramidal, p.ext_dir);
			//setExtDir(&p,270,0.04,1);
			//sim.setExternalCurrent(MEC_LII_Basket_Speed, p.ext_dir);
		}
		if (p.move_test==0) {sim.runNetwork(0,1,false);} // run for 1 ms, don't generate run stats
		/*
		SMexc->stopRecording();
		p.nrn_spk = SMexc->getSpikeVector2D(); // store firing in vector
		SMexc->startRecording();
		*/
		if (p.move_test==0) {
			straight_path(&sim, &p); // process movement
			//move_path3(&sim, &p);
			//move_animal(&sim, &p, &anim_angles, &anim_speeds);
			//move_circles(&sim, &p);
			//rand_path(&sim, &p);
		}
		if (p.move_test==1) {move_test(&sim, &p, &anim_angles, &anim_speeds);}
		PrintWeightsAndFiring(&p);
		RecordNeuronVsLocation(&sim, &p);
		if (p.record_highrestraj) {HighResTraj(&sim, &p);}
		if (p.record_pos_track) {RecordLocationPath(&p, "current");}
		if (p.record_pos_track_all) {RecordLocationPath(&p, "all");}
		if (p.print_time && ((t < 1000 && t % 100 == 0) || (t % 1000 == 0))) {printf("t: %dms\n",t);}
	}
	SMexc->stopRecording();
	SMext->stopRecording();
	SMinh->stopRecording();
	SMspe->stopRecording();
	printf("\n\n");
	SMexc->print(false); // print firing stats (but not the exact spike times)
	SMext->print(false);
	SMinh->print(false);
	SMspe->print(false);
	if (p.record_spikes_file) {p.spikes_output_file.close();}
	if (p.record_highrestraj) {p.highres_pos_x_file.close();}
	if (p.record_highrestraj) {p.highres_pos_y_file.close();}

	return 0;
}
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
//#include <stopwatch.h> // include stopwatch for timing
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
#include "data/ext_dir_initial.cpp"
#include "data/ext_dir.cpp"
#include "data/ii_initial.cpp"
#include "data/init_firings.cpp"
#include "data/mex_hat.cpp"
#include "general_params.cpp"
#include "general_funct.cpp"
#include "move_path.cpp"
//#include "boundary_cells.cpp"
//#include "place_cells.cpp"

int main() {
	struct P p;	
	// keep track of execution time
	//Stopwatch watch;
	// ---------------- CONFIG STATE -------------------
	// create a network on GPU
	int numGPUs = 1;
	int randSeed = 42;
	CARLsim sim("gc can", GPU_MODE, USER, numGPUs, randSeed);
	//CARLsim sim("gc can", CPU_MODE, USER);
	int n_num;
	std::vector<std::vector<float>> etec_weights;
	std::vector<std::vector<float>> inec_weights;
	double base_input_weight = 0.0;
	double noise_addit_freq = 0.0;
	if (p.noise_active) {noise_addit_freq = p.noise_addit_freq;}
	for (int i = 0; i < (p.x_size*p.y_size); i++) {
		p.animal_location_all[i] = 0.0; // initialize
	}
	// initialize matrix
	vector<vector<double>> weights_in_temp(p.layer_size, vector<double>(p.layer_size)); // set size
	p.weights_in = weights_in_temp;
	for (int i = 0; i < p.layer_size; i++) {
		for (int j = 0; j < p.layer_size; j++) {
			p.weights_in[i][j] = 0.0;
		}
	}

	// configure the network
	Grid3D grid_ext_base(p.x_size,p.y_size,1); // external input
	Grid3D grid_ext_dir(p.x_size,p.y_size,1); // external dir input
	Grid3D grid_exc(p.x_size,p.y_size,1); // GCs
	Grid3D grid_inh(p.x_size,p.y_size,1); // interneurons
	Grid3D grid_pcs(p.x_size,p.y_size,1); // PCs
	int gebs=sim.createSpikeGeneratorGroup("ext_base", grid_ext_base, EXCITATORY_NEURON);
	//int gedr=sim.createSpikeGeneratorGroup("ext_dir", grid_ext_dir, EXCITATORY_NEURON);	
	int gedr=sim.createGroup("ext_dir", grid_ext_dir, EXCITATORY_NEURON);	
	int gexc=sim.createGroup("gc_exc", grid_exc, EXCITATORY_NEURON);
	int ginh=sim.createGroup("gc_inh", grid_inh, INHIBITORY_NEURON);
	int gpcs=sim.createSpikeGeneratorGroup("place", grid_pcs, EXCITATORY_NEURON);
	sim.setNeuronParameters(gedr, 0.1f, 0.2f, -65.0f, 2.0f); // FS
	//sim.setNeuronParameters(gexc, 0.02f, 0.2f, -65.0f, 8.0f); // RS
	sim.setNeuronParameters(gexc, 0.1f, 0.2f, -65.0f, 2.0f); // RS
	sim.setNeuronParameters(ginh, 0.1f, 0.2f, -65.0f, 2.0f); // FS
	if (p.base_input == true) {base_input_weight = p.base_input_weight;}
	setInExcConns(&sim, &p);
	MexHatConnection* MexHatConn = new MexHatConnection(&p);	
	sim.connect(gebs, gexc, "one-to-one", base_input_weight, 1.0f); // 0 BASE
	sim.connect(gexc, ginh, "one-to-one", p.base_gc_to_in_weight, 1.0f); // 1 GC->IN
	//sim.connect(ginh, gexc, "one-to-one", 0.0f, 1.0f); // 2 IN->GC
	sim.connect(ginh, gexc, MexHatConn, SYN_FIXED); // 2 IN->GC one-to-many
	sim.connect(gpcs, gexc, "one-to-one", 0.0f, 1.0f); // 3 PCs
	sim.connect(gedr, gexc, "one-to-one", 1.0f, 1.0f); // 4 DIR
	// tau of receptors set to 10 for testing
	sim.setConductances(true,10,10,10,10); // COBA mode; setConductances = true

	// ---------------- SETUP STATE -------------------
	// build the network
	//watch.lap("setupNetwork");
	sim.setupNetwork();

	// Initial excitatory current to GCs
	//sim.setExternalCurrent(gedr, ext_dir_initial);
	sim.setExternalCurrent(gedr, ext_dir_initial);
	// Initial inhibitory current to GCs
	//setInitInhCurr(&p);
	//sim.setExternalCurrent(ginh, ii_initial);
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
	for (int i = 0; i < p.layer_size; i++) {
		p.gc_firing[i] = init_firings[i]; // set initial firing
	}

	for (int t=0; t<p.sim_time; t++) {	
		p.t = t;
		// Disable initial current to GCs settings
		if (t == 2) {
			setInitExtDir(&p);
			sim.setExternalCurrent(gexc, ext_dir);
		}
		// run for 1 ms, don't generate run stats
		sim.runNetwork(0,1,false);
		SMexc->stopRecording();
		p.nrn_spk = SMexc->getSpikeVector2D(); // store firing in vector
		SMexc->startRecording();
		SMinh->stopRecording();
		p.in_nrn_spk = SMinh->getSpikeVector2D();
		SMinh->startRecording();
		inec_weights = CMinec->takeSnapshot();
		p.inec_weights = inec_weights; // store weights in vectors
		// process movement		
		move_path_bound_test(&sim, &p);	
		PrintWeightsAndFiring(&p);
		if (p.record_fire_vs_pos) {RecordNeuronVsLocation(&sim, &p);}
		if (p.record_pos_track) {RecordLocationPath(&p, "current");}
		if (p.record_pos_track_all) {RecordLocationPath(&p, "all");}
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
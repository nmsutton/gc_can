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
#include "data/init_firings.cpp"
#include "data/mex_hat.cpp"
#include "general_params.cpp"
#include "place_cells.cpp"
#include "general_funct.cpp"
#include "move_path.cpp"
//#include "boundary_cells.cpp"

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

	// configure the network
	Grid3D grid_ext_dir(p.x_size,p.y_size,1); // external dir input
	Grid3D grid_exc(p.x_size,p.y_size,1); // GCs
	Grid3D grid_inh(p.x_size,p.y_size,1); // interneurons
	Grid3D grid_pcs(p.x_size,p.y_size,1); // PCs
	int gedr=sim.createGroup("ext_dir", grid_ext_dir, EXCITATORY_NEURON);	
	int gexc=sim.createGroup("gc_exc", grid_exc, EXCITATORY_NEURON);
	int ginh=sim.createGroup("gc_inh", grid_inh, INHIBITORY_NEURON);
	int gpcs=sim.createGroup("place", grid_pcs, EXCITATORY_NEURON);
	//sim.setNeuronParameters(gedr, 0.02f, 0.2f, -65.0f, 8.0f); // RS // 0.02f, 0.2f, -65.0f, 8.0f); // RS
	sim.setNeuronParameters(gedr, 100.0f, 0.7f, -60.0f, -40.0f, 0.03f, -2.0f, 35.0f, -50.0f, 100.0f); // RS // C,k,vr,vt,a,b,vpeak,c,d
	//sim.setNeuronParameters(gexc, 0.1f, 0.2f, -65.0f, 2.0f); // FS
	sim.setNeuronParameters(gexc, 0.02f, 0.2f, -65.0f, 8.0f); // RS
	//sim.setNeuronParameters(gexc, 100.0f, 0.7f, -60.0f, -40.0f, 0.03f, -2.0f, 35.0f, -50.0f, 100.0f); // RS // C,k,vr,vt,a,b,vpeak,c,d
	//sim.setNeuronParameters(ginh, 0.1f, 0.2f, -65.0f, 2.0f); // FS
	sim.setNeuronParameters(ginh, 20.0f, 1.0f, -55.0f, -40.0f, 0.15f, 8.0f, 25.0f, -55.0f, 200.0f); // FS // C,k,vr,vt,a,b,vpeak,c,d
	sim.setNeuronParameters(gpcs, 0.02f, 0.2f, -65.0f, 8.0f); // RS
	//sim.setNeuronParameters(gpcs, 100.0f, 0.7f, -60.0f, -40.0f, 0.03f, -2.0f, 35.0f, -50.0f, 100.0f); // RS // C,k,vr,vt,a,b,vpeak,c,d
	setInExcConns(&sim, &p);
	MexHatConnection* MexHatConn = new MexHatConnection(&p);	
	/*
	sim.connect(gedr, gexc, "one-to-one", 1.0f, 1.0f, RangeDelay(1), RadiusRF(-1), SYN_PLASTIC, 1.0f, 0.0f); // 0 DIR
	sim.connect(gexc, ginh, "one-to-one", 1.0f, 1.0f, RangeDelay(1), RadiusRF(-1), SYN_PLASTIC, 1.0f, 0.0f); // 1 GC->IN
	sim.connect(ginh, gexc, MexHatConn, SYN_FIXED, 1.0f, 0.0f); // 2 IN->GC one-to-many
	sim.connect(gpcs, gexc, "one-to-one", 1.0f, 1.0f, RangeDelay(1), RadiusRF(-1), SYN_PLASTIC, 1.0f, 0.0f); // 3 PCs
	*/
	//sim.connect(gedr, gexc, "one-to-one", 1.0f, 1.0f); // 0 DIR
	sim.connect(gedr, gexc, "one-to-one", 1.0f, 1.0f, RangeDelay(1), RadiusRF(-1), SYN_PLASTIC, 1.0f, 0.0f); // 0 DIR
	//sim.connect(gexc, ginh, "one-to-one", 1.0f, 1.0f); // 1 GC->IN
	sim.connect(gexc, ginh, "one-to-one", 20.0f, 1.0f, RangeDelay(1), RadiusRF(-1), SYN_PLASTIC, 1.0f, 0.0f); // 1 GC->IN
	//sim.connect(ginh, gexc, "one-to-one", 1.0f, 1.0f, RangeDelay(1), RadiusRF(-1), SYN_PLASTIC, 1.0f, 0.0f); // 1 GC->IN
	//sim.connect(ginh, gexc, MexHatConn, SYN_FIXED); // 2 IN->GC one-to-many
	sim.connect(ginh, gexc, MexHatConn, SYN_FIXED, 1.0f, 0.0f); // 2 IN->GC one-to-many
	//sim.connect(gpcs, gexc, "one-to-one", 1.0f, 1.0f); // 3 PCs
	sim.connect(gpcs, gexc, "one-to-one", 0.0f, 1.0f, RangeDelay(1), RadiusRF(-1), SYN_PLASTIC, 1.0f, 0.0f); // 3 PCs
	// tau of receptors set to 10 for testing
	//sim.setConductances(true,10,10,10,10); // COBA mode; setConductances = true
	//sim.setConductances(true,5,150,6,150); // COBA mode; setConductances = true
	//sim.setConductances(true,5,50,6,50); // COBA mode; setConductances = true
	sim.setConductances(true); // COBA mode; setConductances = true

	// ---------------- SETUP STATE -------------------
	// build the network
	sim.setupNetwork();
	// Initial excitatory current to GCs
	setInitExtDir(&p);
	sim.setExternalCurrent(gedr, ext_dir_initial);
	SpikeMonitor* SMexc = sim.setSpikeMonitor(gexc, "DEFAULT");

	// ---------------- RUN STATE -------------------
	SMexc->startRecording();
	SMexc->setPersistentData(true); // keep prior firing when recording is stopped and restarted
	for (int i = 0; i < p.layer_size; i++) {
		p.gc_firing[i] = init_firings[i]; // set initial firing
	}

	for (int t=0; t<p.sim_time; t++) {	
		p.t = t;
		// Disable initial current to GCs settings
		if (t == 2) {
			setExtDir(&p,'l',0.04);
			sim.setExternalCurrent(gedr, p.ext_dir);
		}
		sim.runNetwork(0,1,false); // run for 1 ms, don't generate run stats
		SMexc->stopRecording();
		p.nrn_spk = SMexc->getSpikeVector2D(); // store firing in vector
		SMexc->startRecording();
		//straight_path(&sim, &p); // process movement
		move_path3(&sim, &p);
		PrintWeightsAndFiring(&p);
		if (p.record_fire_vs_pos) {RecordNeuronVsLocation(&sim, &p);}
		if (p.record_pos_track) {RecordLocationPath(&p, "current");}
		if (p.record_pos_track_all) {RecordLocationPath(&p, "all");}
		if (p.print_time && ((t < 1000 && t % 100 == 0) || (t % 1000 == 0))) {printf("t: %dms\n",t);}
	}
	SMexc->stopRecording();
	printf("\n\n");
	SMexc->print(false); // print firing stats (but not the exact spike times)
	
	return 0;
}
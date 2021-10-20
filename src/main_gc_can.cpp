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

using namespace std;

void InterneuronWeightProcessor(CARLsim* sim, int ni, int nj, float i_ext) {
	sim->setWeight(0,0,0,0.05f,true);
}

// custom ConnectionGenerator
class MyConnection : public ConnectionGenerator {
public:
    MyConnection() {}
    ~MyConnection() {}
 
    void connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j, float& weight, float& maxWt,
            float& delay, bool& connected) {

        connected = true;
        float wt = 0.001f;
        float wt2 = 0.01f;
        delay = 1;

        if (j == 0 || j == 1 || j == 10 || j == 11) {
        	weight = wt;
        	maxWt = wt;
    	}
    	else {
        	weight = wt2;
        	maxWt = wt2;
    	}
    }
};

int main() {
	// keep track of execution time
	Stopwatch watch;

	// ---------------- CONFIG STATE -------------------
	// create a network on GPU
	int numGPUs = 1;
	int randSeed = 42;
	CARLsim sim("gc can", CPU_MODE, USER, numGPUs, randSeed);
	vector<vector<int>> nur_spk1_1;
	int n_num;
	int s_num;
	int spk_time;
	int spk_tot = 0;
	bool man_move_det = false;

	// configure the network
	Grid3D grid_ext(10,10,1); // external input
	Grid3D grid_exc(10,10,1); // GCs
	Grid3D grid_inh(10,10,1); // interneurons
	int gext=sim.createSpikeGeneratorGroup("ext_input", grid_ext, EXCITATORY_NEURON);
	int gexc=sim.createGroup("gc_exc", grid_exc, EXCITATORY_NEURON);
	int ginh=sim.createGroup("gc_inh", grid_inh, INHIBITORY_NEURON);
	sim.setNeuronParameters(gexc, 0.02f, 0.2f, -65.0f, 8.0f); // RS
	sim.setNeuronParameters(ginh, 0.1f, 0.2f, -65.0f, 2.0f); // FS
	sim.connect(gext, gexc, "one-to-one", 0.05f, 1.0f);
	float int_w = 0.01f;
	sim.connect(gexc, ginh, "full", RangeWeight(int_w), 1.0f);
	sim.connect(ginh, gexc, "full", RangeWeight(int_w), 1.0f);

	sim.setConductances(true); // COBA mode; setConductances = true

	// create an instance of MyConnection class and pass it to CARLsim::connect
    MyConnection* myConn = new MyConnection;
    sim.connect(gexc, ginh, myConn, SYN_PLASTIC);
    sim.connect(ginh, gexc, myConn, SYN_PLASTIC);

	// ---------------- SETUP STATE -------------------
	// build the network
	watch.lap("setupNetwork");
	sim.setupNetwork();

	SpikeMonitor* SMext = sim.setSpikeMonitor(gext, "DEFAULT");
	SpikeMonitor* SMexc = sim.setSpikeMonitor(gexc, "DEFAULT");
	//SpikeMonitor* SMexcind = sim.setSpikeMonitor(gexc, "DEFAULT");
	SpikeMonitor* SMinh = sim.setSpikeMonitor(ginh, "DEFAULT");
	ConnectionMonitor* CMei = sim.setConnectionMonitor(ginh, gexc, "DEFAULT");
	ConnectionMonitor* CMetec = sim.setConnectionMonitor(gext, gexc, "DEFAULT");

	//setup some baseline input
	PoissonRate in(grid_ext.N);
	in.setRates(15.0f);
	sim.setSpikeRate(gext,&in);

	// ---------------- RUN STATE -------------------
	SMext->startRecording();
	SMexc->startRecording();
	//SMexcind->startRecording();
	SMinh->startRecording();

	//SMexcind->setMode(AER);

	for (int t=0; t<10000; t++) {	
		// run for 1 ms, don't generate run stats
		sim.runNetwork(0,1,false);

		if (t == 0) {
			sim.setWeight(0,0,0,0.1f,true);
			sim.setWeight(0,1,1,0.1f,true);
			sim.setWeight(0,10,10,0.2f,true);
			sim.setWeight(0,11,11,0.1f,true);
		}
		if (t == 1000) {
			SMexc->stopRecording();
			nur_spk1_1 = SMexc->getSpikeVector2D();
			SMexc->startRecording();
			n_num = nur_spk1_1.size();
			for (int i; i < n_num; i++) {
				s_num = nur_spk1_1[i].size();
				for (int j; j < s_num; j++) {
					if (i == 10) {
						spk_time = nur_spk1_1[i][j];
						if (spk_time >= 500 && spk_time <= 1000) {
							spk_tot += 1;
						}
					}
				}
			}
			printf("total spikes in 1s: %d\n", nur_spk1_1[10].size());							
			printf("total spikes in 500ms window: %d\n", spk_tot);	
			InterneuronWeightProcessor(&sim, 0, 0, 0);
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
		/*if (t == 5000) {
			SMext->stopRecording();
			SMexc->stopRecording();
			SMinh->stopRecording();
			SMext->print(false);
			SMexc->print(false);
			SMinh->print(false);
			SMext->startRecording();
			SMexc->startRecording();
			SMinh->startRecording();
		}*/
	}
	SMext->stopRecording();
	SMexc->stopRecording();
	//SMexcind->stopRecording();
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

	CMetec->printSparse();
	//CMee->printSparse();
	//CMei->printSparse();
	
	return 0;
}
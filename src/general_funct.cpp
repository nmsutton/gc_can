/*
	General functions
*/

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

void PrintWeightsAndFiring(P *p) {
	int x_p = 19;//20;
	int y_p = 19;//20;
	int max_x = p->x_size;
	int n = 0;
	int sel_cell = 31; // selected cell to report on

	if (p->print_in_weights) {
		printf("\n\nec->in weights at time %d",p->t);
		for (int i = (y_p - 1); i >= 0; i--) {
			printf("\n");
			for (int j = 0; j < x_p; j++) {
				n = (i * max_x) + j;
				//printf("[%.2f]",p->weights_in[n][n]);	
				printf("[%.3f]",p->inec_weights[n][n]);	
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
	if (p->print_in_firing) {
		printf("\nIN firing t:%d",p->t);
		for (int i = (y_p - 1); i >= 0; i--) {
			printf("\n");
			for (int j = 0; j < x_p; j++) {
				n = (i * max_x) + j;
				printf("[%.0f]\t",p->in_firing[n]);	
			}
		}
	}	
	if (p->print_gc_firing) {
		printf("\nGC firing t:%d",p->t);
		for (int i = (y_p - 1); i >= 0; i--) {
			printf("\n");
			for (int j = 0; j < x_p; j++) {
				n = (i * max_x) + j;
				printf("[%.0f]\t",p->gc_firing_bin[n]);	
			}
		}
	}
}

char get_pd(int i, P *p) {	
	char pd = 'n';
	int x = i % p->x_size;
	int y = i / p->x_size;

	if (y % 2 == 0) {
		if (x % 2 == 0) {
			pd = 'd';
		}
		else {
			pd = 'u';
		}
	}
	else {
		if (x % 2 == 0) {
			pd = 'r';
		}
		else {
			pd = 'l';
		}		
	}

	return pd;
}

char get_opp_pd(int i, P *p) {	
	/* returns opposite preferred direction */
	char pd;
	int x = i % p->x_size;
	int y = i / p->x_size;

	if (y % 2 == 0) {
		if (x % 2 == 0) {
			pd = 'u';
		}
		else {
			pd = 'd';
		}
	}
	else {
		if (x % 2 == 0) {
			pd = 'l';
		}
		else {
			pd = 'r';
		}		
	}

	return pd;
}

void set_pos(P *p, char direction) {
	if (direction == 'u') {
		p->pos[1] = p->pos[1] + p->move_increment; 
	}
	else if (direction == 'd') {
		p->pos[1] = p->pos[1] - p->move_increment; 
	}
	else if (direction == 'r') {
		p->pos[0] = p->pos[0] + p->move_increment; 
	}
	else if (direction == 'l') {
		p->pos[0] = p->pos[0] - p->move_increment; 
	}

	if (p->pos[0] >= p->x_size) {
		p->pos[0] = 0;
		//printf("%f >= %d\n",p->pos[0],p->x_size);
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
	double base_input_weight = p->base_input_weight;

	double rand_val = rand() % rand_max; // rand number up to rand_max
	rand_val = rand_val * scale; // scale to desired size
	rand_val = ((rand_max*scale)/2)-rand_val; // rand val centered at 0	
	rand_val = rand_val + base_input_weight; // rand val centered at base_input_weight
	if (rand_val < 0) {rand_val = 0;}

	return rand_val;
}

void count_firing(P* p, double *firing_matrix, vector<vector<int>> spike_recorder) {
	int nrn_size, s_num, spk_time, tot;
	for (int i = 0; i < (p->layer_size); i++) {
		firing_matrix[i] = 0.0; // initialize as 0
	}

	// count gc spikes
	nrn_size = spike_recorder.size();
	for (int i = 0; i < nrn_size; i++) {
		tot = 0;
		s_num = spike_recorder[i].size();
		for (int j = 0; j < s_num; j++) {
			spk_time = spike_recorder[i][j];
			if (spk_time >= (p->t - p->firing_bin) && spk_time <= p->t) {
				tot += 1;
			}
		}
		if (i < (p->layer_size)) {
			firing_matrix[i] = tot;
		}
	}
}

void find_spikes(P* p, double *firing_matrix, vector<vector<int>> spike_recorder) {
	int nrn_size, s_num, spk_time, tot;
	for (int i = 0; i < (p->layer_size); i++) {
		firing_matrix[i] = 0.0; // initialize as 0
	}

	// count gc spikes
	nrn_size = spike_recorder.size();
	for (int i = 0; i < nrn_size; i++) {
		tot = 0;
		s_num = spike_recorder[i].size();
		for (int j = 0; j < s_num; j++) {
			spk_time = spike_recorder[i][j];
			if (spk_time == (p->t - 1)) {
				firing_matrix[i] = 1;
			}
		}
	}
}

void write_firing(double *firing_matrix, string output_folder, P *p) {
	ofstream output_file;
	//string filename = "output/" + output_folder + "/firing_t" + int_to_string(p->t) + ".csv";
	string filename = "/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can/output/" + output_folder + "/firing_t" + int_to_string(p->t) + ".csv";
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

void RecordNeuronVsLocation(CARLsim* sim, P* p) {
	/*
		Detect firing of a selected individual neuron and record the animal's
		position when the firing occured. Amount of firing is also recorded.

		Note: are the 10ms time bins firing is counted enough resolution for this?
	*/
	double i_d;
	int i;

	//if (p->gc_firing[p->selected_neuron] > 0) {
	if (p->gc_firing_bin[p->selected_neuron] > 0) {
		// get index from position
		i_d = (p->pos[1] * p->x_size) + p->pos[0];
		i = floor(i_d);

		//p->firing_positions[i] = p->firing_positions[i] + p->gc_firing[p->selected_neuron];
		//p->firing_positions[i] = p->firing_positions[i] + p->gc_firing_bin[p->selected_neuron];
		p->firing_positions[i] = p->firing_positions[i] + 0.5;
	}

	write_firing(p->firing_positions, "firing_vs_loc", p);
}

void RecordLocationPath(P *p, string rec_type) {
	double pos_i = (floor(p->pos[1]) * p->x_size) + floor(p->pos[0]);

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
			p->animal_location_all[i] = p->animal_location_all[i] + 0.1;
		}
	}

	if (rec_type != "all") {
		write_firing(p->animal_location, "pos_track", p);
	}
	else {
		write_firing(p->animal_location_all, "pos_track_all", p);
	}
}

void setInExcConns(CARLsim* sim, P *p) {
	// set inital connection status (0 or 1) in 2d weight matrix for IN->GC connections

	// assign connectivity
	for (int i = 0; i < p->layer_size; i++) {
		for (int j = 0; j < p->layer_size; j++) {
			if (mex_hat[i][j] != 0.0) {
				p->weights_in[i][j] = 1;
			}
		}
	}
}

// custom ConnectionGenerator
class MexHatConnection : public ConnectionGenerator {
public:
    vector<vector<double>> weights_in;
    MexHatConnection(P *p) {
    	this->weights_in = p->weights_in; // set matrix size
    }
    ~MexHatConnection() {}
 
    // the pure virtual function inherited from base class
    // note that weight, maxWt, delay, and connected are passed by reference
    void connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j, float& weight, float& maxWt,
            float& delay, bool& connected) {
    		if (this->weights_in[i][j] == 1.0) {
    			connected = 1; // only connect where matrix value is 1.0
    		}
        weight = mex_hat[i][j]*1.4;
        maxWt = 10.0f;
        delay = 1; 
    }
};

void setInitExtDir(P* p) {
	for (int i = 0; i < p->layer_size; i++) {
		ext_dir_initial[i] = ext_dir_initial[i]*1;
	}
}

void setExtDir(P* p, char dir, double speed) {
	for (int i = 0; i < p->layer_size; i++) {
		if (get_pd(i, p) == dir) {
			p->ext_dir[i] = p->base_ext*pow((1+speed),p->speed_mult);
		}
		//else if (get_opp_pd(i, p) == dir) {
		//	p->ext_dir[i] = p->base_ext*pow((1-speed),p->speed_mult);
		//}
		else {
			p->ext_dir[i] = p->base_ext;
		}
		//printf("%f,",p->ext_dir[i]);		
	}
}

void EISignal(char direction, CARLsim* sim, P* p) {
	/*
		Apply external input
	*/	
	double noise;

	//find_spikes(p, p->gc_firing, p->nrn_spk);
	count_firing(p, p->gc_firing_bin, p->nrn_spk);
	//count_firing(p, p->in_firing, p->in_nrn_spk);
	//if (p->t % 2 == 0) { // movement delay accounting for firing bin size
	if (true) { // movement delay accounting for firing bin size
		set_pos(p, direction); if (p->print_move) {cout << "\n";}
		//printf("t: %d; m: %f ",p->t,p->mi);
	}

	// set velocity of movement
	if (p->t > 2) {
		//setExtDir(p,direction,0.24);
		setExtDir(p,direction,0.24);//0.20);
		sim->setExternalCurrent(1, p->ext_dir);
	}	

	// noise
	if (p->noise_active) {
		for (int i = 0; i < p->layer_size; i++) {
			// add random noise for realism		
			noise = get_noise(p);
			sim->setWeight(0,i,i,noise,true);
		}
	}
}
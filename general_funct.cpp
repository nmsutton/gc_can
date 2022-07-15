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
				printf("[%.3f]",p->inec_weights[n][n]);	
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

double get_pd(int i, P *p) {	
	double pd = 0;
	int x = i % p->x_size;
	int y = i / p->x_size;

	if (y % 2 == 0) {
		if (x % 2 == 0) {pd = 180;}
		else {pd = 0;}
	}
	else {
		if (x % 2 == 0) {pd = 90;}
		else {pd = 270;}		
	}

	return pd;
}

double get_opp_pd(int i, P *p) {	
	/* returns opposite preferred direction */
	double pd;
	int x = i % p->x_size;
	int y = i / p->x_size;

	if (y % 2 == 0) {
		if (x % 2 == 0) {pd = 0;}
		else {pd = 180;}
	}
	else {
		if (x % 2 == 0) {pd = 270;}
		else {pd = 90;}		
	}

	return pd;
}

vector<double> find_ver_hor(double angle) {
	/*
		Translate angle into proportion of horizonal and vertical movement
		needed to create movement in the direction of the angle.
	*/
	vector<double> ver_hor;
	double ver, hor, ang_adj;
	if (angle < 90) {
		ang_adj = 90 - angle;
		ver = ang_adj;
		hor = 90 - ang_adj;
	}
	else if (angle >= 90 and angle < 180) {
		ang_adj = angle - 90;
		ver = -ang_adj;
		hor = 90 - ang_adj;
	}
	else if (angle >= 180 and angle < 270) {
		ang_adj = angle - 180;
		ver = -90 + ang_adj;
		hor = -ang_adj;
	}
	else if (angle >= 270 and angle <= 360) {
		ang_adj = angle - 270;
		ver = ang_adj;
		hor = -90 + ang_adj;
	}

	ver = -(ver/90);
	hor = (hor/90);
	ver_hor.push_back(ver);
	ver_hor.push_back(hor);

	return ver_hor;
}

void set_pos(P *p, double angle) {
	/*
		Angle should be between 0-360 degrees.
	*/
	vector<double> ver_hor = find_ver_hor(angle);
	p->pos[0] = p->pos[0] + (ver_hor[1] * p->move_increment);
	p->pos[1] = p->pos[1] + (ver_hor[0] * p->move_increment);

	// wrap around twisted taurus
	if (p->pos[0] >= p->x_size) {
		p->pos[0] = p->x_size - p->pos[0];
	}
	else if (p->pos[0] < 0) {
		p->pos[0] = p->x_size + p->pos[0];
	}
	if (p->pos[1] >= p->y_size) {
		p->pos[1] = p->y_size - p->pos[1];
	}
	else if (p->pos[1] < 0) {
		p->pos[1] = p->y_size + p->pos[1];
	}

	if (p->print_move == true) {
		cout << " move: " << angle << " " << p->pos[0] << " " << p->pos[1] << " t: " << p->t;
	}
}

double get_noise(P *p) {
	int rand_max = p->noise_rand_max;
	double scale = p->noise_scale;
	double centered_val = 1.0; // value to center random value around

	double rand_val = rand() % rand_max; // rand number up to rand_max
	rand_val = rand_val * scale; // scale to desired size
	rand_val = ((rand_max*scale)/2)-rand_val; // rand val centered at 0	
	rand_val = centered_val + rand_val; // rand val centered at centered_val
	if (rand_val < 0) {rand_val = 0;}

	return rand_val;
}

void write_spikes(P* p, int i) {
	/*
		Write spikes to file
	*/
	int x = i % p->x_size;
	int y = i / p->x_size;
	p->spikes_output_file << p->t;
	p->spikes_output_file << ",";
	p->spikes_output_file << x;
	p->spikes_output_file << ",";
	p->spikes_output_file << y;
	p->spikes_output_file << "\n";
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
	//string filename = "/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can/output/" + output_folder + "/firing_t" + int_to_string(p->t) + ".csv";
	string filename = "output/" + output_folder + "/firing_t" + int_to_string(p->t) + ".csv";
	output_file.open(filename);

	int i_f = 0; // firing index

	if (p->t != 0) {
		//for (int i = (p->x_size - 1); i >= 0; i--) {
		for (int i = 0; i < p->x_size; i++) {
			for (int j = 0; j < p->y_size; j++) {
				i_f = (i * p->x_size) + j;

				output_file << firing_matrix[i_f];

				if (j != (p->y_size -1)) {
					output_file << ",";
				}
			}
			//if (i != 0) {
			if (i != p->y_size) {
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
	*/
	double i_d;
	int i;

	//if (p->gc_firing[p->selected_neuron] > 0) {
	if (p->gc_firing_bin[p->selected_neuron] > 0) {
		// get index from position
		//i_d = (p->pos[1] * p->x_size) + p->pos[0];
		//i = floor(i_d);
		i = (floor(p->pos[1]) * p->x_size) + floor(p->pos[0]);
		p->firing_positions[i] = p->firing_positions[i] + p->fvp_act_lvl;		
		if (p->record_spikes_file) {
			write_spikes(p, i);
		}
	}

	write_firing(p->firing_positions, "firing_vs_loc", p);
}

void HighResTraj(CARLsim* sim, P* p) {
	// write pos x,y. to be removed when real traj is in sync.
	if (p->gc_firing_bin[p->selected_neuron] > 0) {
		// write spike x,y
	}
}

void RecordLocationPath(P *p, string rec_type) {
	double pos_i = (floor(p->pos[1]) * p->x_size) + floor(p->pos[0]);

	for (int i = 0; i < p->layer_size; i++) {
		if (rec_type != "all") {
			if (i == pos_i) {
				p->animal_location[i] = p->al_act_lvl;
			}
			else {
				p->animal_location[i] = 0;
			}
		}
		else if (i == pos_i) {
			p->animal_location_all[i] = p->animal_location_all[i] + p->ala_act_lvl;
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
	int counter = 0;

	// assign connectivity
	for (int i = 0; i < p->layer_size; i++) {
		for (int j = 0; j < p->layer_size; j++) {
			//if (mex_hat[i][j] != 0.0) {
			//if ((double) mex_hat[i][j] >= 0.006) {
			if ((double) mex_hat[i][j] >= 0.002) {
				p->weights_in[i][j] = 1;
				//printf("i:%d j:%d\n",i,j);
				counter++;
			}
		}
	}
	printf("counter:%d\n",counter);
}

// custom ConnectionGenerator
class MexHatConnection : public ConnectionGenerator {
public:
    vector<vector<double>> weights_in;
    double mex_hat_multi;
    int conn_offset, conn_dist;
    MexHatConnection(P *p) {
    	this->weights_in = p->weights_in; // set matrix
    	this->mex_hat_multi = p->mex_hat_multi;
    	this->conn_offset = p->conn_offset;
    	this->conn_dist = p->conn_dist;
    }
    ~MexHatConnection() {}
 
    // the pure virtual function inherited from base class
    // note that weight, maxWt, delay, and connected are passed by reference
    void connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j, float& weight, float& maxWt,
            float& delay, bool& connected) {
    		// adjust i for multiple neuron types combine into a group
    		int i_adj = (i * this->conn_dist) + this->conn_offset;

    		// assign connections
    		//if (this->weights_in[i][j] == 1.0) {
    		if (this->weights_in[i_adj][j] == 1.0) {
    			connected = 1; // only connect where matrix value is 1.0 
    			/*if (i_adj>899) {
    				printf("i:%d j:%d i_adj:%d\n",i,j,i_adj);
    			}*/
    			//printf("i:%d j:%d i_adj:%d\n",i,j,i_adj);
    		}
    		else {
    			connected = 0;
    		}
        //weight = mex_hat[i][j]*mex_hat_multi;
        weight = mex_hat[i_adj][j]*mex_hat_multi;
        weight = weight + -0.012;//-0.022;//-0.042;//-0.012;//-0.022;//0.5;//0.0;                
        //weight = mex_hat[i_adj][j]*mex_hat_multi;
        //if (weight < 0) {weight = 0;}
        maxWt = 10000.0f;
        delay = 1; 
    }
};

class SomeToSomeConnection : public ConnectionGenerator {
public:
    vector<vector<double>> weights_in;
    double mex_hat_multi;
    int conn_offset, conn_dist;
    float gc_to_in_wt;
    SomeToSomeConnection(P *p) {
    	this->weights_in = p->weights_in; // set matrix
    	this->mex_hat_multi = p->mex_hat_multi;
    	this->conn_offset = p->conn_offset;
    	this->conn_dist = p->conn_dist;
    	this->gc_to_in_wt = p->gc_to_in_wt;
    }
    ~SomeToSomeConnection() {}
 
    // the pure virtual function inherited from base class
    // note that weight, maxWt, delay, and connected are passed by reference
    void connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j, float& weight, float& maxWt,
            float& delay, bool& connected) {
    		// adjust i and j for multiple neuron types combine into a group
    		//int i_adj = (i * this->conn_dist) + this->conn_offset;
    		//int j_adj = (j * this->conn_dist) + this->conn_offset;

    		// assign connections
    		if (i == ((j * this->conn_dist) + this->conn_offset)) {
    			connected = 1;
    			//printf("i:%d j:%d\n",i,j);
    		}
    		else {
    			connected = 0;
    		}
        weight = gc_to_in_wt;
        maxWt = 10000.0f;
        delay = 1; 
    }
};

void setInitExtDir(P* p) {
	for (int i = 0; i < p->layer_size; i++) {
		ext_dir_initial[i] = ext_dir_initial[i]*p->dir_init_multi;
	}
}

vector<double> directional_speeds(P* p, double angle, double speed) {
	/*
		This function translates an angle and speed into what speed in 
		4 compass directions (N,E,S,W) can create that movement.
	*/
	vector<double> ver_hor = find_ver_hor(angle);
	double ver = ver_hor[0];
	double hor = ver_hor[1];
	double N,E,S,W;N=1;E=1;S=1;W=1;
	double speed_adj = pow(speed,p->speed_mult);
	if (speed == 0 && p->speed_mult == 0) {
		speed_adj = 0; // avoid pow(0,0) when result of 0 is wanted
	}

	if (ver >= 0) {
		N += abs(ver)*speed_adj;
		//N += pow(abs(ver),p->speed_mult)*speed;
	}
	else {
		S += abs(ver)*speed_adj;
		//S += pow(abs(ver),p->speed_mult)*speed;
	}
	if (hor <= 0) {
		E += abs(hor)*speed_adj;
		//E += pow(abs(hor),p->speed_mult)*speed;
	}
	else {
		W += abs(hor)*speed_adj;
		//W += pow(abs(hor),p->speed_mult)*speed;
	}
	vector<double> speeds = {N,E,S,W};
	//vector<double> speeds = {E,N,W,S};
	//printf("t:%d N:%f E:%f S:%f W:%f h:%f v:%f sm:%f s:%f p:%f r:%f\n",p->t,N,E,S,W,hor,ver,p->speed_mult,speed,pow(abs(hor),p->speed_mult),speed_adj);

	return speeds;
}

void setExtDir(P* p, double angle, double speed) {
	double noise;	
	vector<double> speeds = directional_speeds(p, angle, speed);

	for (int i = 0; i < p->layer_size; i++) {
		if (get_pd(i, p) == 0) {
			p->ext_dir[i] = p->base_ext*speeds[0];
		}
		else if (get_pd(i, p) == 90) {
			p->ext_dir[i] = p->base_ext*speeds[1];
		}
		else if (get_pd(i, p) == 180) {
			p->ext_dir[i] = p->base_ext*speeds[2];
		}
		else if (get_pd(i, p) == 270) {
			p->ext_dir[i] = p->base_ext*speeds[3];
		}
	}

	// noise
	if (p->noise_active) {
		for (int i = 0; i < p->layer_size; i++) {		
			noise = get_noise(p); // add random noise for realism
			p->ext_dir[i] = p->ext_dir[i]*noise; // change external input by noise value
		}
	} 
	
	//printf("t:%d n:%f e:%f s:%f w:%f\n",p->t,speeds[0],speeds[1],speeds[2],speeds[3]);
}

void general_input(double angle, CARLsim* sim, P* p) {
	set_pos(p, angle);

	// place cell input
	place_cell_firing(sim, p);
}

void EISignal(double angle, CARLsim* sim, P* p) {
	/*
		Apply external input
	*/	
	count_firing(p, p->gc_firing_bin, p->nrn_spk);
	if (p->print_move) {cout << "\n";}

	// set velocity of movement
	if (p->t > 2) {
		setExtDir(p,angle,p->const_speed);//0.20);
		sim->setExternalCurrent(0, p->ext_dir);
	}	
}
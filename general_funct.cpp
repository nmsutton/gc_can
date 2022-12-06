/*
	General functions

	References: https://stackoverflow.com/questions/34218040/how-to-read-a-csv-file-data-into-an-array
	https://iq.opengenus.org/split-string-in-cpp/
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
vector<double> find_ver_hor(P *p, double angle, double* h) {
	//
	//	Translate angle and distance into proportion of horizonal and 
	//  vertical movement needed to create movement in the direction of the angle.
	//  Distance is hypotenuse of right triangle with ver (vertical rise)
	//  and hor (horizontal run) as sides. Given angle and hypotenuse the
	//  sides are found using the Pythagorean theorem. h = hypotenuse of triangle.
	//  Reference: https://www.mathsisfun.com/algebra/trig-finding-side-right-triangle.html
	//
	angle = (angle/360)*2*PI; // convert from degrees to radians
	//angle = ((angle+180)/360)*2*PI; // convert from degrees to radians
	vector<double> ver_hor; double x, y;

	if (angle < (PI/2)) {
		x = sin(angle) * *h;
		y = sqrt(pow(*h,2)-pow(x,2));
	}
	else if (angle >= (PI/2) and angle < PI) {
		x = cos(angle-(PI/2)) * *h;
		y = sqrt(pow(*h,2)-pow(x,2)) * -1;
	}
	else if (angle >= PI and angle < (PI*1.5)) {
		x = cos((PI*1.5)-angle) * *h * -1;
		y = sqrt(pow(*h,2)-pow(x,2)) * -1;
	}
	else if (angle >= (PI*1.5) and angle <= (PI*2)) {
		x = cos(angle-(PI*1.5)) * *h * -1;
		y = sqrt(pow(*h,2)-pow(x,2));
	}

	ver_hor.push_back(y);
	ver_hor.push_back(x);

	return ver_hor;
}

void set_pos(P *p, double angle) {
	/*
		Angle should be between 0-360 degrees.
	*/
	vector<double> ver_hor = find_ver_hor(p, angle, &p->move_increment);
	p->pos[0] = p->pos[0] + ver_hor[1];
	p->pos[1] = p->pos[1] + ver_hor[0];
	angle = angle + p->grid_pattern_rot;
	if (angle>360) {angle=360-angle;}
	if (angle<0)   {angle=angle+360;}
	ver_hor = find_ver_hor(p, angle, &p->move_increment);
	p->bpos[0] = p->bpos[0] + (ver_hor[1] * p->grid_pattern_scale);
	p->bpos[1] = p->bpos[1] + (ver_hor[0] * p->grid_pattern_scale);
	//printf("angle: %f %f ver_hor[1]:%f %f\n",angle,p->pos[0],ver_hor[1],p->move_increment);
	//printf("%f ver_hor[0]:%f %f\n",p->pos[1],ver_hor[1],p->move_increment);

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
	if (p->bpos[0] >= p->x_size) {
		p->bpos[0] = p->x_size - p->bpos[0];
	}
	else if (p->bpos[0] < 0) {
		p->bpos[0] = p->x_size + p->bpos[0];
	}
	if (p->bpos[1] >= p->y_size) {
		p->bpos[1] = p->y_size - p->bpos[1];
	}
	else if (p->bpos[1] < 0) {
		p->bpos[1] = p->y_size + p->bpos[1];
	}
	//taurus_wrap(P *p, double *x, double *y)

	if (p->print_move == true) {
		cout << " move: " << angle << " " << p->pos[0] << " " << p->pos[1] << " t: " << p->t;
	}
}

void taurus_wrap(P *p, double* x, double* y) {
	if (*x >= p->x_size) {
		*x = p->x_size - *x;
	}
	else if (*x < 0) {
		*x = p->x_size + *x;
	}
	if (*y >= p->y_size) {
		*y = p->y_size - *y;
	}
	else if (*y < 0) {
		*y = p->y_size + *y;
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
	//printf("rand_val: %f\n",rand_val);

	return rand_val;
}

void write_sel_nrn_spks(P* p, string n_type) {
	/*
		Write to file spikes from selected neuron to monitor
	*/
	if (n_type=="grid_cell") {
		p->spikes_output_file.close(); // reload file to save intermediate results
		p->spikes_output_file.open(p->spikes_output_filepath, std::ios_base::app);
		p->spikes_output_file << p->t;
		p->spikes_output_file << "\n";		
	}
	else if (n_type=="interneuron") {
		p->in_spikes_output_file.close();
		p->in_spikes_output_file.open(p->in_spikes_output_filepath, std::ios_base::app);
		p->in_spikes_output_file << p->t;
		p->in_spikes_output_file << "\n";		
	}
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
			if (spk_time >= (p->t - p->timestep) && spk_time <= p->t) {
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

void write_rate_map(double *firing_matrix, string output_folder, P *p) {
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
	if (p->move_animal_onlypos) {p->record_spikes_file=0;p->record_in_spikes_file=0;} // avoid extra spike file writing during onlypos
	if (p->record_fire_vs_pos || p->record_spikes_file) {
		int pi; // animal position index in GC layer
		int i = p->selected_neuron; // neuron selected to record
		int j = p->nrn_spk[i].size(); // all spikes of selected neuron

		if (j > 0 && p->nrn_spk[i][j-1] == p->t) { // get index from position
			if (p->record_fire_vs_pos) {
				pi = (floor(p->pos[1]) * p->x_size) + floor(p->pos[0]);
				//p->firing_positions[pi] = p->firing_positions[pi] + 1;		
			}
			if (p->record_spikes_file) {write_sel_nrn_spks(p, "grid_cell");}
		}
	}

	if (p->move_animal_aug) {
		int pi, j;

		if (p->t % p->timestep == 0) {
			pi = (floor(p->pos[1]) * p->x_size) + floor(p->pos[0]);
			p->locations_visited[pi] = p->locations_visited[pi] + 1;
			//printf("pi:%d a:%d\n",pi,p->locations_visited[pi]);
		}
	}

	if (p->record_in_spikes_file) {
		int i = p->selected_in_neuron; // neuron selected to record
		int j = p->in_nrn_spk[i].size(); // all spikes of selected neuron

		if (j > 0 && p->in_nrn_spk[i][j-1] == p->t) { // get index from position
			write_sel_nrn_spks(p, "interneuron");
		}
	}

	//if (p->record_fire_vs_pos) {write_rate_map(p->firing_positions, "firing_vs_loc", p);}
}

void HighResTraj(CARLsim* sim, P* p) {
	/* 
		Record high resolution position data of spikes. 
	*/
	
	p->highres_pos_x_file << p->pos[0];
	p->highres_pos_x_file << "\n";
	p->highres_pos_y_file << p->pos[1];
	p->highres_pos_y_file << "\n";	
	
	/*
	if (p->t % 5000 == 0 || p->t == (int) (p->sim_time-1)) {
		p->highres_pos_x_file << p->pos_x.str();
		p->highres_pos_y_file << p->pos_y.str();
		p->pos_x.str("");
		p->pos_y.str("");
	}
	else {
		p->pos_x << p->pos[0];
		p->pos_x << "\n";
		p->pos_y << p->pos[1];
		p->pos_y << "\n";
	}
	*/
}

void RecordLocationPath(P *p, string rec_type) {
	double pos_i = (floor(p->pos[1]) * p->x_size) + floor(p->pos[0]);
	//printf("x:%f y:%f\n",p->pos[0],p->pos[1]);

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
		write_rate_map(p->animal_location, "pos_track", p);
	}
	else {
		write_rate_map(p->animal_location_all, "pos_track_all", p);
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
	double speed_adj = speed;
	if (speed == 0) {
		speed_adj = 0; // avoid pow(0,0) when result of 0 is wanted
	}
	vector<double> ver_hor = find_ver_hor(p, angle, &speed_adj);
	double ver = ver_hor[0];
	double hor = ver_hor[1];
	double N,E,S,W;N=1;E=1;S=1;W=1;

	if (ver >= 0) {
		N += abs(ver);
	}
	else {
		S += abs(ver);
	}
	if (hor <= 0) {
		E += abs(hor);
	}
	else {
		W += abs(hor);
	}
	vector<double> speeds = {N,E,S,W};
	//vector<double> speeds = {E,N,W,S};
	//printf("t:%d N:%f E:%f S:%f W:%f h:%f v:%f s:%f r:%f\n",p->t,N,E,S,W,hor,ver,speed,speed_adj);

	return speeds;
}

void setExtDir(P* p, double angle, double speed, int sc) {
	double noise;	
	angle = angle + p->grid_pattern_rot;
	if (angle>360) {angle=360-angle;}	
	if (angle<0)   {angle=angle+360;}	
	vector<double> speeds = directional_speeds(p, angle, speed);
	if (sc == 2) {for (int i = 0; i < 4; i++) {speeds[i]--;}}
	//if (sc == true) {for (int i = 0; i < 4; i++) {speeds[i]=speeds[i]-0.695;}}
	if (sc == 1) {
		speeds[0]=speed;speeds[1]=speed;speeds[2]=speed;speeds[3]=speed;
	}
	//speeds[0]=2;speeds[1]=2;speeds[2]=2;speeds[3]=2;
	//if (sc == true) {for (int i = 0; i < 4; i++) {speeds[i]--;}}
	//if (sc == true) {speeds[0]=0.01;speeds[1]=0.01;speeds[2]=0.01;speeds[3]=0.01;}

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
		//printf("ext input\n");
		setExtDir(p,angle,p->speed_signaling,0);//0.20);
		sim->setExternalCurrent(p->EC_LI_II_Multipolar_Pyramidal_Group, p->ext_dir);
		//printf("p->ext_dir: %f\n",p->ext_dir);
		//printf("speed cells\n");
		if (p->spin2in_active) {
			setExtDir(p,angle,p->spdin2in_curr,2);//100.0,1);//0.075,1);//0.20);
			//setExtDir(p,angle,0.0,2);
			sim->setExternalCurrent(p->MEC_LII_Basket_Speed_Group, p->ext_dir);
		}
		if (p->spex2in_active) {	
			setExtDir(p,angle,p->spdex2in_curr,1);//100.0,1);//0.075,1);//0.20);
			sim->setExternalCurrent(p->MEC_LII_Stellate_Speed_Group, p->ext_dir);
		}
	}	
}

vector<double> SplitStr(string str)
{
	vector<double> entries;
	string deli = ",";
    int start = 0;
    int end = str.find(deli);
    while (end != -1) {
        entries.push_back(stod(str.substr(start, end - start)));
        start = end + deli.size();
        end = str.find(deli, start);
    }
    entries.push_back(stod(str.substr(start, end - start)));

    return entries;
}

vector<double> ParseCSV(string filepath)
{
    ifstream data(filepath);
    string line;
    vector<double> parsedRow;
	if(!data.is_open()) {cout << "Failed to open file" << endl;}
    while(getline(data,line)) {parsedRow.push_back(stod(line));}

    return parsedRow;
};

void ParseCentSurrCSV(string filepath, vector<vector<double>> *cent_surr)
{
	ifstream data(filepath);
    string line;
    vector<double> parsedRow;
	if(!data.is_open()) {cout << "Failed to open file" << endl;}
	while(getline(data,line)) {cent_surr->push_back(SplitStr(line));}
};
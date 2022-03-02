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
        weight = mex_hat[i][j]*1;
        maxWt = 10.0f;
        delay = 1; 
    }
};

void setInitExtDir(P* p) {
	for (int i = 0; i < p->layer_size; i++) {
		ext_dir_initial[i] = ext_dir_initial[i]*1;
	}
}

void setExtDirOld(P* p) {
	for (int i = 0; i < p->layer_size; i++) {
		ext_dir[i] = p->base_ext*pow(ext_dir[i],3.0);
	}
}

void setExtDir(P* p, char dir, double speed) {
	/*double dir_angle;

	if (dir == 'u') {
		dir_angle = 0.5*PI;
	}
	else if (dir == 'r') {
		dir_angle = 1*PI;
	}
	else if (dir == 'd') {
		dir_angle = 1.5*PI;
	}
	else if (dir == 'l') {
		dir_angle = 2.0*PI;
	}
	else {
		dir_angle = 0.0;
	}*/

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
		printf("%f,",p->ext_dir[i]);		
	}
}
/*
void setInitInhCurr(P* p) {
	for (int i = 0; i < p->layer_size; i++) {
		ii_initial[i] = ii_initial[i]*1;
	}
}
*/
void EISignal(char direction, CARLsim* sim, P* p) {
	/*
		Apply external input
	*/	
	find_spikes(p, p->gc_firing, p->nrn_spk);
	count_firing(p, p->gc_firing_bin, p->nrn_spk);
	count_firing(p, p->in_firing, p->in_nrn_spk);
	set_pos(p, direction); if (p->print_move) {cout << "\n";}

	double noise;
	if (p->noise_active) {
		for (int i = 0; i < p->layer_size; i++) {
			// add random noise for realism		
			noise = get_noise(p);
			sim->setWeight(0,i,i,noise,true);
		}
	}
}

double get_mex_hat(double d, P *p) {
	double y_inter = p->y_inter;
	double s1 = p->s_1;
	double s2 = p->s_2;
	double s3 = p->s_3;
	double s4 = p->s_4;
	double s5 = p->s_5;
	double m1 = p->m;
	double m2 = p->m2;
	double m3 = p->m3;
	double m4 = p->m4;
	double a = p->a;
	double scale = p->scale;
	double mex_hat;

	/*mex_hat = y_inter + scale * 
	((1-(pow((m1*d)/s1,2))) *
	(exp(-1*(m3*pow(d,2))/(12*pow(s3,2)))));*/

	//mex_hat = scale * (y_inter - (exp(-((m1*pow(d,2))/(2*pow(s1,2))))-m2*exp(-pow(d,2)/(2*pow(s2,2)))));

	mex_hat = y_inter-(scale*(exp(-((m1*pow(d,2))/(2*pow(s1,2))))
		-m2*exp(-pow(d,2)/(2*pow(s2,2)))));
	//printf("%f-(%f*(exp(-((%f*pow(%f,2))/(2*pow(%f,2))))-%f*exp(-pow(%f,2)/(2*pow(%f,2)))))\n",y_inter,scale,m1,d,s1,m2,d,s2);

	/*if (d >1.9 && d < 2.1) {
		printf("%f %f\n",d,mex_hat);
	}*/
	if (mex_hat < 0) {
		mex_hat = 0;
	}

	return mex_hat;
}

double get_distance(int x1, int y1, int x2, int y2, char pd, P *p) {
	// d = sqrt((e_x - i_x - o_x)^2+(e_y - i_y - o_y)^2)
	/*int x2_x1 = (x2 - x1);
	int y2_y1 = (y2 - y1);
	int half_point = p->x_size / 2; // layer length divided by 2*/
	double x2_x1 = (x2 - x1);
	double y2_y1 = (y2 - y1);
	double half_point = p->x_size / 2; // layer length divided by 2

	// preferred direction bias
	if (pd == 'u') {
		y2_y1 = y2_y1 - 1;
	}
	if (pd == 'd') {
		y2_y1 = y2_y1 + 1;
	}
	if (pd == 'r') {
		x2_x1 = x2_x1 - 1;
	}
	if (pd == 'l') {
		x2_x1 = x2_x1 + 1;
	}	

	// torus wrap around
	if (abs(x2_x1) >= half_point) {
		// distance wraps half way around
		x2_x1 = (p->x_size - abs(x2_x1));
	}
	if (abs(y2_y1) >= half_point) {
		y2_y1 = (p->y_size - abs(y2_y1));
	}

	double d = sqrt(pow(x2_x1,2)+pow(y2_y1,2));

	return d;
}
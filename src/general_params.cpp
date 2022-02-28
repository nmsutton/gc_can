/*
	General parameters
*/

#define PI 3.14159265

struct P {
	// general parameters
	double sim_time = 10000; // sim run time in ms
	static const int bump_init_x = 1.0; // initial bump x
	static const int bump_init_y = 1.0; // initial bump y
	static const int bump_dist = 15;//7.0; // inter-bump distance
	static const int bumps_x = 2; // number of bumps on x axis
	static const int bumps_y = 2; // number of bumps on y axis
	static const int num_bumps = bumps_x * bumps_y; // number of initial bumps
	double pos[2] = {1,1}; // starting position; {x,y}
	char last_dir; // last direction command
	static const int x_size = 30;//26;
	static const int y_size = 30;//26;
	static const int layer_size = x_size * y_size;
	int move_window = 10;//10; // number of miliseconds before each movement command
	int start_t = -1; // beginning time of move command
	int mi = 0; // move list index
	int t = 0; // time
	char dirs[4] = {'u', 'r', 'd', 'l'};
	vector<vector<int>> nrn_spk; // for total firing recording
	vector<vector<int>> in_nrn_spk; // for total firing recording
	vector<vector<double>> weights_in; // IN-GC weights
	vector<vector<double>> weights_in_all; // IN-GC weights all-to-all
	vector<vector<bool>> weights_in_upd; // record of updates
	double gc_firing[layer_size]; // gc spiking amount
	double gc_firing_bin[layer_size]; // gc spiking amount in time bins
	double in_firing[layer_size]; // gc spike amount
	vector<vector<float>> inec_weights;
	vector<vector<float>> etec_weights;

	// common parameters that can vary per each run
	double base_input_weight = 0.01;//0.094; // baseline input from ext_input to GC
	double base_gc_to_in_weight = 1.0f;//1.0f;//0.5f; // baseline interneuron synapse weight
	double base_in_to_gc_weight = 1.0f;//0.5f; // baseline interneuron synapse weight
	bool print_move = 0; // print each move's direction
	bool print_time = 1; // print time after processing
	bool print_in_weights = 0;
	//bool print_in_weights_all = 0;
	bool print_ext_weights = 0;
	bool print_in_firing = 0;
	bool print_gc_firing = 0;
	bool record_fire_vs_pos = 0; // write files for firing vs position plotting
	bool record_pos_track = 0; // write files for animal position tracking plotting
	bool record_pos_track_all = 0; // write files for animal positions with no past posit. clearing
	bool fire_vs_pos_test_mode = 0; // changes just for testing fire vs pos
	//bool intern_connect = 1; // interneuron connections toggle
	bool init_bumps = 0; // inital bumps present
	bool base_input = 0; // baseline external signal input
	bool dir_input = 0; // baseline external signal direction-based input
	bool gc_to_gc = 1; // grid cell to grid cell signaling
	bool bc_to_gc = 0; // boundary cells to grid cells signaling
	bool pc_to_gc = 0; // place cells to grid cells signaling
	bool bc_to_pc = 0; // boundary cells to place cells signaling
	bool pc_active = 0; // pc signaling active. bc->pc->gc can still work even if this is disabled.

	// noise parameters
	bool noise_active = 0; // activate noise
	double noise_rand_max = 100; // 0 - rand_max is range of random number gen
	double noise_scale = 0.001;//0.01;//0.005; // scale to desired size for firing
	double noise_addit_freq = 0.0f; // additional spiking frequency added to base external input

	// values for synapse activites
	bool speed_adjustable = 0;
	double speed = 1.0; // starting grid cell input speed level
	double base_ext = 1.0;//2.5; // baseline ext input speed level
	double min_speed = 0.25; // minimum speed for random speed generator. note: signal applied even when stopped.
	double max_speed = 1.0; // maximum speed for random speed generator
	double tau_syn = 10.0;//.6;
	double y_inter_syn = 0.5;//-1;//-0.03;//-0.05;//0.15;//-.5;//1.044;//1.055; // y intercept
	double scale_syn = 2.0;//0.25;//1.0; // multiple synaptic connections scaling factor
	double m_syn = 2.0; // magnitude variable for mex hat f1
	double m_syn2 = 0.6; // f2 f3
	double m_syn3 = 0.3; // f4
	double m_syn4 = 1.1; // f2 f3
	double s_1_syn = 2.2; // f1
	double s_2_syn = 2.2; // f2 f3
	double s_3_syn = .4; // f4
	double s_4_syn = 1.5; 
	double s_5_syn = 1.0;
	double a_syn = 4.4; // add f2 f3
	double dist_thresh = 5; // distance threshold for only local connections
	double non_range_weight = 0.0;//0.1;//2.0; // default out of range weight
	//double syn_scale = 5.0; // max spiking scale
  	double in_scale = 1.0;//0.001;//0.0001;//0.001;//2.0; // interneuron firing scale factor
  	//double ext_scale = 13.0; // ext_dir firing scale factor

	// initial values
	double y_inter_init = 1.5;//y_inter_syn; // y intercept
	double scale_init=4;//scale_syn;	
	double s_1_init = s_1_syn; // sigma_1. Note: specific value used for equalibrium of weights over time.
	double s_2_init = s_2_syn;
	double s_3_init = s_3_syn;
	double s_4_init = s_4_syn;
	double s_5_init = s_5_syn;
	double m_init=m_syn;
	double m_init2=m_syn2;
	double m_init3=m_syn3;
	double m_init4=m_syn4;
	double a_init=a_syn;
	double tau, y_inter, scale, s_1, s_2, s_3, s_4, s_5, m, m2, m3, m4, a;

	// tau time constant and asymmetric sigmoid parameters. https://en.wikipedia.org/wiki/Gompertz_function
	double asig_a = -5;//-10;//-8.0;//0.6;//0.45;//2.0;//0.45;
	double asig_b = 3.5;//9.5;//2.2;//9.89493996719;//0.6;//2.15;//0.6;
	double asig_c = 5;//10.0;//4.9898;//3.0;//0.457921;//1.0;//0.5;
	double asig_yi = 0.0;//-0.9;//0.0;//-0.9;
	double asig_scale = 1.0;//2.0;//-0.9;

	// place cell parameters
	double pc_sig = 1.0;//0.25; // sigma symbol; width of the place feild
	double pc_level = 15.0;//5.0; //14.0; // place cell firing level

	// boundary cell parameters
	double r_d = 1.0; // boundary cell active region width
	double bc_firing_scale = 0.1; // amount of boundary cell firing when activated
	double bc_pd = 5.0; // boundary cell prefered distance
	static const int b_num = 4.0; // number of borders
	double bc_distances[b_num];
	// response curve factors
	//double bc_level = 14.0 * 0.25; // level of bc firing
	double bc_a0 = 2.0; // boundary cell A_0 factor for response curve
	double bc_b = 0.25;
	double bc_sig0 = 0.0;
	double bc_y = 0.05;//0.25;
	double bc_a = 0.25;
	double bc_sig = 1.0;

	// neuron vs location parameters
	int selected_neuron = 465;//10;
	double firing_positions[x_size*y_size]; // locations of firing of a neuron
	double animal_location[x_size*y_size]; // location of animal
	double animal_location_all[x_size*y_size]; // location of animal
};
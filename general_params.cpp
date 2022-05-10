/*
	General parameters
*/

#define PI 3.14159265

struct P {
	int firing_bin = 10; // size of bins to record firing activity
	double sim_time = 10000*firing_bin; // sim run time in ms
	int t = 0; // time
	static const int bump_dist = 15; // inter-bump distance
	static const int bumps_x = 2; // number of bumps on x axis
	static const int bumps_y = 2; // number of bumps on y axis
	static const int num_bumps = bumps_x * bumps_y; // number of initial bumps
	static const int x_size = 30;//26;
	static const int y_size = 30;//26;
	static const int layer_size = x_size * y_size;
	static const int EC_LI_II_Multipolar_Pyramidal_Count = 900;
	static const int MEC_LII_Stellate_Count = 900;
	static const int EC_LII_Axo_Axonic_Count = 300;
	static const int MEC_LII_Basket_Count = 300;
	static const int EC_LII_Basket_Multipolar_Count = 300;
	static const int CA1_Pyramidal_Count = 900;
	double pos[2] = {3,6}; // starting position; {x,y}
	char dirs[4] = {'u', 'r', 'd', 'l'};
	char last_dir; // last direction command
	double mi = 0; // move list index
	vector<vector<int>> nrn_spk; // for total firing recording
	vector<vector<double>> weights_in; // IN-GC weights
	vector<vector<float>> inec_weights;
	double gc_firing[layer_size]; // gc spiking amount
	double gc_firing_bin[layer_size]; // gc spiking amount in time bins

	// common parameters that can vary per each run
	bool print_move = 0; // print each move's direction
	bool print_time = 1; // print time after processing
	bool print_in_weights = 0;
	bool print_gc_firing = 0;
	bool record_fire_vs_pos = 1; // write files for firing vs position plotting
	bool record_pos_track = 1; // write files for animal position tracking plotting
	bool record_pos_track_all = 1; // write files for animal positions with no past posit. clearing
	bool record_gc_voltage = 0; // record GC voltage trace
	bool record_in_voltage = 0; // record IN voltage trace
	bool record_pc_voltage = 0; // record PC voltage trace
	bool pc_active = 1; // pc signaling active. bc->pc->gc can still work even if this is disabled.
	bool pc_to_gc = 1; // place cells to grid cells signaling
	bool bc_to_pc = 0; // boundary cells to place cells signaling
	bool bc_to_gc = 0; // boundary cells to grid cells signaling

	// noise parameters
	bool noise_active = 0; // activate noise
	double noise_rand_max = 100; // 0 - rand_max is range of random number gen
	double noise_scale = 0.001;//0.01;//0.005; // scale to desired size for firing
	double noise_addit_freq = 0.0f; // additional spiking frequency added to base external input

	// values for synapse activites
	double base_ext = 800;//800;//300;//300;//300;//1100;//16000.0;//1020.0;//2000.0;//1020.0;//34680;//1020.0;//30.0;//184//4.5;//800.0;//4.5; // baseline ext input speed level	
	double const_speed = 0.195;//0.12; // setting for use of a constant virtual animal speed
	double speed_mult = 2;//10;//1.0;//35.0;//0.6;//1.2;//1.5;//4.5;//7.5; // starting grid cell input speed level
	float dir_to_gc_wt = 1.6;//1.5;//1.5;//5.5; // ext_dir to gc weight
	double mex_hat_multi = 170;//220;//180;//180;//300;//250;//140;//50;//30;//50;//800;//5;//2.6;//1.2;//1.2;//400.0;//1.2;//1.2;//1.4; // mexican hat multiplier
	float gc_to_in_wt = 1;//1;//0.45;//1;//25;//700.0; // gc to interneurons weight
	double dir_init_multi = 100000;//100000000;//10000;//1;//10000;
	int move_delay = 25;//50; // delay in speed that moves are commanded to occur
	double dist_thresh = 5; // distance threshold for only local connections
	double move_increment = 0.64;//0.658;//0.1;//0.5;//0.2634;//0.325;//0.65; // amount to move in position each move command
	vector<float> ext_dir;
	int conn_offset = 0; // offset in neuron positions for connections
	int conn_dist = 3; // distance between neurons in connections

	// speed
	bool speed_adjustable = 0;
	double min_speed = 0.25; // minimum speed for random speed generator. note: signal applied even when stopped.
	double max_speed = 1.0; // maximum speed for random speed generator

  	// plotting
	double fvp_act_lvl = 0.5; // amount of activity level added for each visit with firing vs. position plot.
	double al_act_lvl = 5.0; // amount of activity level added for each visit with animal location non-all plot.
	double ala_act_lvl = 0.1; // amount of activity level added for each visit with animal location all plot.

	// place cell parameters
	float pc_to_gc_wt = 0.5;//10; // pc to gc synaptic weight
	double pc_sig = 1.5;//4.0;//1.0;//0.25; // sigma symbol; width of the place feild
	double pc_level = 1000.0;//1000.0;//5.5;//7.5;//5.0; //14.0; // place cell firing level
	vector<float> pc_activity;

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
	int selected_neuron = 465;//11;//465;//232;//465;//10;
	double firing_positions[x_size*y_size]; // locations of firing of a neuron
	double animal_location[x_size*y_size]; // location of animal
	double animal_location_all[x_size*y_size]; // location of animal

	// voltage recording parameters
	string gc_volt_out_path = "gc_voltages.csv";
	string in_volt_out_path = "in_voltages.csv";
	string pc_volt_out_path = "pc_voltages.csv";
	int gc_volt_neuron = 125;
	int in_volt_neuron = 125;
	int pc_volt_neuron = 125;
};
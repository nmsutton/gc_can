/*
	General parameters
*/

#define PI 3.14159265

struct P {
	double sim_time = 220000;//40000;//131400;//8485920;//120000//29416*20;//60000*firing_bin;// sim run time in ms
	int timestep = 20; // timestep between movements. e.g., 20ms between each movement command
	int t = 0; // time
	static const int x_size = 42;//30;//26;
	static const int y_size = 42;//30;//26;
	static const int layer_size = x_size * y_size;
	static const int EC_LI_II_Multipolar_Pyramidal_Count = 1764;//900;
	static const int MEC_LII_Stellate_Count = 1764;//900;
	static const int EC_LII_Axo_Axonic_Count = 588;//300;
	static const int MEC_LII_Basket_Count = 588;//300;
	static const int EC_LII_Basket_Multipolar_Count = 588;//300;
	static const int CA1_Pyramidal_Count = 1764;//900;
	static const int MEC_LII_Basket_Speed_Count = 1764;//900;
	static const int MEC_LII_Stellate_Speed_Count = 1764;//900;	
	int EC_LI_II_Multipolar_Pyramidal_Group, MEC_LII_Stellate_Group, EC_LII_Axo_Axonic_Group,
	MEC_LII_Basket_Group, EC_LII_Basket_Multipolar_Group, CA1_Pyramidal_Group, 
	MEC_LII_Basket_Speed_Group,	MEC_LII_Stellate_Speed_Group;	
	double pos[2] = {28,14};//{9,17};//{22,8}; // virtual animal position tracker. starting position: {x,y}
	double bpos[2] = {28,14};//{9,17}; // bump position tracker
	double dirs[4] = {0, 90, 180, 270};
	double mi = 0; // move list index
	vector<vector<int>> nrn_spk; // for total firing recording
	vector<vector<int>> in_nrn_spk; // for total firing recording
	vector<vector<double>> weights_in; // IN-GC weights
	vector<vector<float>> inec_weights;
	ostringstream pos_x;
	ostringstream pos_y;
	double gc_firing[layer_size]; // gc spiking amount
	double gc_firing_bin[layer_size]; // gc spiking amount in time bins
	string spikes_output_filepath = "output/spikes/spikes_recorded.csv";
	string in_spikes_output_filepath = "output/spikes/in_spikes_recorded.csv";
	string highres_pos_x_filepath = "output/spikes/highres_pos_x.csv";
	string highres_pos_y_filepath = "output/spikes/highres_pos_y.csv";
	ofstream spikes_output_file;
	ofstream in_spikes_output_file;
	ofstream highres_pos_x_file;
	ofstream highres_pos_y_file;

	// animal data parameters
	#define hopper_run 1 // import data differently if on hopper
	string anim_angles_csv = "./data/anim_angles.csv";
	string anim_speeds_csv = "./data/anim_speeds.csv";
	#define import_animal_data 1 // 1 for import and 0 for no import
	int animal_ts = 20; // timestep in ms
	vector<double> anim_angles;
	vector<double> anim_speeds;
	vector<int> speed_times;
	vector<double> angles;
	vector<double> speeds;
	int num_moves;
	int num_speeds;

	// animal move aug parameters
	int animal_aug_time = sim_time * 0.75; // when to start movement augs
	double percent_for_aug = 0.25; // percent of total envorinment locations to add as augmented moves
	bool print_aug_values = 0;
	vector<double> x_aug; // positions coordinates to travel to
	vector<double> y_aug;
	vector<int> locations_sortind; // binned firing locations sorted indices
	vector<int> locations_amounts; // amount of firing in indices
	int aug_i = 0; // aug target counter
	int aug_m = 0; // aug move counter

	// select movement trajectory
	bool run_path = 0; // use run_path function. This is auto enabled by functions that use it.
	bool run_path_onlypos = 0; // only generate movement positions not signaling with run_path function
	bool move_animal = 0; // use real animal movement positions with neural signaling
	bool move_animal_aug = 0; // augment animal movement
	bool move_animal_onlypos = 0; // generate animal movement position but not signaling
	bool move_fullspace = 1; // move through whole environment
	bool move_straight = 0;
	bool move_circles = 0;
	bool move_random = 0;
	bool move_ramp = 0;

	// common parameters that can vary per each run
	bool print_move = 0; // print each move's direction
	bool print_time = 1; // print time after processing
	bool print_in_weights = 0;
	bool print_gc_firing = 0;
	bool record_fire_vs_pos = 0; // write files for firing vs position plotting
	bool record_pos_track = 0; // write files for animal position tracking plotting
	bool record_pos_track_all = 0; // write files for animal positions with no past posit. clearing
	bool record_spikes_file = 0; // write file for grid cell spike times and neuron positions
	bool record_in_spikes_file = 0; // write file for interneuron spike times and neuron positions
	bool record_highrestraj = 1; // write files for high resolution trajectory locations
	#define additional_spk_mon 0 // additional spike monitors
	#define monitor_voltage 0 // turn voltage monitoring on or off 
	bool pc_active = 1; // pc signaling active. bc->pc->gc can still work even if this is disabled.
	bool pc_to_gc = 1; // place cells to grid cells signaling
	bool spin2in_active = 0; // inhibitory speed cells active.	
	bool spex2in_active = 0; // excitatory speed cells active.	
	bool bc_to_pc = 0; // boundary cells to place cells signaling
	bool bc_to_gc = 0; // boundary cells to grid cells signaling

	// values for synapse activites
	double base_ext = 212;//500;//375;//200;//500;//335;//600;//200;//600;//300;//700;//300;//400;//500;//400;//600;//320;//300.0;//500.0;//10.0;//0.0; // baseline ext input speed level	
	double speed_signaling = 1.88;//0.1;//0.3;//0.05;//5;//0.05;//5;//0.05;//1.8;//3.5;//0.0;//5.0;//0.0;//5.0;//0.3;//1.0;//1.0;//5.0;//5.0;//0.0;//5.0;//1.0;//0.5;//1.0;//0.1; // setting for use of a constant virtual animal speed
	float dir_to_gc_wt = 0.15;//0.2;//0.4;//1.0;//0.4;//0.7;//0.5;//0.4;//1.0;//0.8;//2.0;//0.3;//0.5;//0.9;//0.75; ext_dir to gc weight
	double mex_hat_multi = 20;//25;//20;//15;//10;//10.0;//20;//20;//30.0;//10;//1000;//700;//1100; // mexican hat multiplier
	float gc_to_in_wt = 0.5;//0.5;//.4;//.32;//0.315;//0.3;//0.28;//0.5;//0.27;//0.2;//0.28;//0.30;//0.315;//0.297;//0.28;//0.28;//200;//50;//600; // gc to interneurons weight
	double spdin2inwt = 0.5;//10;//0.5;//10;
	double spdex2inwt = 1.0;//1.65;//0.52;//0.5;
	double spdin2in_curr = 1.0;//1.0;//0;//1;//100;//10;
	double spdex2in_curr = 0.35;//0.3;//0.0;//0.3;
	double dir_init_multi = 1000;//100000;
	int move_delay = 20;//25;//50; // delay in speed that moves are commanded to occur
	double move_increment = 0.010;//0.024;//0.018;//0.005;//0.018; // amount to move in position each move command
	vector<float> ext_dir;
	// interneuron connections
	int conn_offset = 0; // offset in neuron positions for connections
	int conn_dist = 3; // distance between neurons in connections
	#define ORIGINAL 0
	#define FACILITATION 0
	#define DEPRESSION 0
	#define BALANCE 0
	#define BALANCE2 0
	#define STDEV2X 1

	// speed
	bool auto_speed_control = 1; // automatically adjust parameters to match speed selected
	bool speed_limit = 0; // speed limit on or off
	double max_speed = 17.5; // max movement speed
	double speed_conversion = 1;//0.2; // scale animal movement speed data
	double min_rand_speed = 0.25; // minimum speed for random speed generator. note: signal applied even when stopped.
	double max_rand_speed = 1.0; // maximum speed for random speed generator
	double move_rev = 1; // test movement in forward or reverse directions

  	// plotting
  	static const int x_size_plot = 30; // size that will be used for plotting
	static const int y_size_plot = 30;
	double al_act_lvl = 5.0; // amount of activity level added for each visit with animal location non-all plot.
	double ala_act_lvl = 0.1; // amount of activity level added for each visit with animal location all plot.

	// place cell parameters
	double theta_freq = 125.0; // theta frequency in Hz
	double dist_thresh = 5; // distance threshold for only local connections	
	float pc_to_gc_wt = 0.15;//0.4;//0.4;//0.5;//0.4;//1.0;//3.0;//2.5;//2;//4;//5.5; // pc to gc synaptic weight
	double pc_sig = 2;//1;//1.4;//1;//0.75; // sigma symbol; width of the place feild
	double pc_level = 300;//215;//400;//600;//700;//500;//3000;//3000;//2000;//2500;//3000; // place cell firing level
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

	// noise parameters
	bool noise_active = 0; // activate noise
	double noise_rand_max = 100; // 0 - rand_max is range of random number gen
	double noise_scale = 0.0001;//0.015;//0.01;//0.005; // scale to desired size for firing
	double noise_addit_freq = 0.0f; // additional spiking frequency added to base external input

	// neuron vs location parameters
	int selected_neuron = 465;//378;//372;//465;//372;//11;//465;//232;//465;//10;
	int selected_in_neuron = 100; // interneuron
	double grid_pattern_rot = 0;//-15; // angle value for rotation of grid pattern in plot
	double grid_pattern_scale = 1;//18/22.5; // rescale grid pattern for plot. smaller value makes larger rescale, e.g., 0.8 = 1.25x rescale. animal speed to bump speed conversion. <goal_top_bump_speed>/<goal_top_animal_speed>
	vector<int> locations_visited; // locations an animal visited
	double animal_location[x_size*y_size]; // location of animal
	double animal_location_all[x_size*y_size]; // location of animal
};
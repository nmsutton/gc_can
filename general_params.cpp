/*
	General parameters
*/

#define PI 3.14159265

struct P {
	double sim_time = 220000;//131400;//8485920;//120000//29416*20;//60000*firing_bin;// sim run time in ms
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
	static const int MEC_LII_Basket_Speed2_Count = 1764;//900;
	static const int MEC_LII_Stellate_Speed_Count = 1764;//900;	
	int EC_LI_II_Multipolar_Pyramidal_Group, MEC_LII_Stellate_Group, EC_LII_Axo_Axonic_Group,
	MEC_LII_Basket_Group, EC_LII_Basket_Multipolar_Group, CA1_Pyramidal_Group, MEC_LII_Basket_Speed_Group,
	MEC_LII_Basket_Speed2_Group, MEC_LII_Stellate_Speed_Group;	
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
	//string spikes_output_filepath = "/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/spikes_recorded.csv";
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
	bool spin2in_active = 1; // inhibitory speed cells active.	
	bool spin2ex_active = 0; // inhibitory speed cells active.	
	bool spex2in_active = 1; // excitatory speed cells active.	
	bool bc_to_pc = 0; // boundary cells to place cells signaling
	bool bc_to_gc = 0; // boundary cells to grid cells signaling

	// values for synapse activites
	double base_ext = 300;//250;//300;//300;//380;//350;//380;//250;//275;//380;//380;//410;//500;//410;//500;//410;//380;//500;//380;//410;//500;//540;//410;//350;//250;//540;//250;//250;//250;//480;//540;//480;//540;//600;//380;//275;//245;//600;//350;//245;//350;//245;//350;//275;//350;//275;//400;//655;//500;//400;//600;//400;//600;//1000;//750;//750;//650;//300;//300;//350;//500;//500;//650;//650;//655;//655;//600;//840;//800;//655;//655;//1200;//655;//500;//400;//655;//635;//590;//575;//500;//575;//500;//675;//675;//600;//585;//575;//950;//800;//400;//800;//400;//800;//500;//175;//300;//150;//300;//400;//270;//400;//600;//400;//400;//800;//600;//800;//800;//300;//300;//300;//1100;//16000.0;//1020.0;//2000.0;//1020.0;//34680;//1020.0;//30.0;//184//4.5;//800.0;//4.5; // baseline ext input speed level	
	double speed_signaling = 0.5;//20.0;//0.5;//20.0;//0.5;//0.05;//30;//20;//0.5;//0.1;//1.0;//0.4;//30;//0.05;//30;//0.05;//0.05;//0.3;//20;//0.3;//20;//0.5;//20;//0.5;//20;//20;//0.1;//0.1;//1.0;//0.0;//20;//10;//0.0;//1.0;//0.5;//10;//10;//0.5;//10;//0.0;//10;//1.0;//1.00;//10;//10;//0.0;//10;//15;//0.0;//20;//0.0;//1.3;//20;//1.3;//0.25;//0.25;//25;//0.0;//25;//0.0;//25.0;//0.0;//25.0;//0.0;//0.5;//5;//0.5;//25;//0.2;//0.15;//1.0;//1.0;//2.5;//1.0;//1.0;//5.0;//1.0;//2.5;//0.25;//2.5;//0.25;//25;//2.5;//0.25;//2.5;//1.6;//1.632833487;//0.1;//0.2;//3;//0.25;//40;//0.025;//0.2;//20;//5;//0.2;//5;//2;//.2;//0.02;//10;//0.1;//200.0;//0;//50.0;//0.8;//0.195;//1.8;//0.255;//1.8;//0.255;//0.195;//0.195;//0.5;//0.0;//0.195;//0.12; // setting for use of a constant virtual animal speed
	float dir_to_gc_wt = 1.25;//2.3;//1.25;//1.85;//1.25;//1.85;//2;//2.5;//4;//2.5;//1.25;//2.5;//2.5;//3.5;//4;//2.5;//4.0;//4.0;//2.0;//7.0;//4.0;//2.0;//1.6;//1.5;//2.75;//1.6;//2.75; // ext_dir to gc weight
	double mex_hat_multi = 1000;//650;//850;//700;//600;//700;//600;//700;//400;//700;//700;//600;//350;//450;//260;//190;//180;//200;//190;//170;//200;//190;//170;//200;//150;//160;//200;//150;//200;//200;//130;//400;//500;//160;//500;//250;//160;//300;//150;//300;//400;//500;//350;//300;//200;//160;//200;//185;//130;//130;//130;//170;//150;//170;//70;//170;//70;//180;//70;//70;//55;//60;//70;//85;//40;//85;//70;//85;//100;//70;//60;//60;//70;//90;//100;//140;//170;//200;//170;//170;//220;//180;//180;//300;//250;//140;//50;//30;//50;//800;//5;//2.6;//1.2;//1.2;//400.0;//1.2;//1.2;//1.4; // mexican hat multiplier
	float gc_to_in_wt = 50;//100;//20;//20;//30;//15;//20;//20;//20;//20;//40;//100;//70;//60;//80;//100;//70;//50;//60;//50;//40;//50;//70;//80;//40;//80;//37;//165;//200;//300;//150;//300;//200;//150;//100;//250;//300;//100;//550;//250;//400;//1900;//1000;//800;//400;//200;//300;//200;//250;//150;//150;//200;//45;//37;//38;//70;//20;//25;//9;//9;//20;//45;//14;//10;//1;//14;//9;//18.5;//9;//9.0;//7.5;//6.0;//11.5;//18.5;//13.5;//10;//8.5;//12;//5.5;//18.5;//16.5;//15.5;//13.5;//11.5;//5.5;//2.5;//1;//1;//0.45;//1;//25;//700.0; // gc to interneurons weight
	double spdin2inwt = 10;//10;//1;//10.0;//1.0;//10.0;//3.0;//0.5;//1.0;//1.0;//3.0;//0.3;
	double spdin2exwt = 8.7;//8;//10;//10;//5;//20;//5;//10;//5;//100;//20.0;//10;//100;//10.0;//8.0;//3.0;//0.3;
	double spdex2inwt = 3.0;//1.65;//0.52;//0.5;//1.0;//0.55;//0.52;//0.45;//0.52;//0.51;//0.52;//0.44;//3.0;//1.5;//0.3;
	double spdin2in_curr = 0.0;//1.0;//0.0;//1.0;//8.0;//8.0;//0;//0.0;//50;//0.0;//100;//0.0;//100;//0.0;//100;//0.0;//100;//0.0;//10;//0.0;//10;//10.0;//0.0;//10.0;//0.0;//10.0;//0.0;//1;//10;//0.0;//5.0;//10.0;//0.0;//10.0;//0.0;//10;//0.0;//10;//0.0;//10.0;//0.0;//10.0;//10.0;//0.0;//10.0;//0.0;//10.0;//0.0;//10.0;//3.0;//0.0;//3.0;//3.0;//0.0;//3.0;//0.0;//1.0;//0.0;//0.0;//0.0;//0.0;//0;//0.0;//0.0;//3;//0.5;//3;//0.0;//3.0;//0.0;//30.0;//5.0;//0.0;//0.6;//0.15;//100;//0.0;
	double spdin2ex_curr = 5;//20;//20;//20;//10;//10;//3;//0.0;//3;//3;//0;//3;//0.0;//3;//0;//3;//0;//3;//8.0;//5.0;//2.0;//0.5;//2.0;//0.3;//3.0;//0.2;//0.3;//0.4;//0.23;//0.4;//0.23;//0.23;//0.5;//0.8;//0.5;//1;//0.5;//4.0;//0.5;//4.0;//4.0;//3.0;//4.0;//2.0;//6.0;//2.0;//0.0;//0.19;//0.0;//0.75;//0.75;//0.25;//8.0;//4;//0.5;//0.4;
	double spdex2in_curr = 0.3;//0.3;//0.0;//0.3;//0.3;//0;//0.3;//0.0;//0.3;//0.0;//0.3;//0.0;//0.3;//0.0;//0.3;//0.0;//0.51;//0.3;//0.5;//0.0;//0.5;//0.26;//0.0;//0.26;//0.26;//0.5;//0.0;//0.33;//0.3;//0.5;//0.0;//0.5;//0.0;//0.5;//0.475;//0.45;//0.0;//0.45;//0.0;//0.45;//0.48;//0.0;//0.25;//0.315;//0.0;//0.28;//0.315;//0.315;//0.0;//0.315;//0.0;//0.212;//0.4;//0.41;//0.0;//0.41;//0.4;//0.3;//0.5;//0.8;//0.0;//0.8;//0.65;//0.251;//0.625;//0.41;//10.0;//3.0;//0.41;//0.0;//0.41;//0.42;//0.409;//0.0;//0.409;//0.0;//0.5;//0.75;//0.5;//0.48;//0.48;//0.48;//0.2;//0.48;//48;//0.27;//0.48;//0.5;//0.53;//0.57;//0.55;//0.55;//0.473;//0.55;//0.0;//0.5;//1.0;//1.2;//0.0;//1.3;//0.0;//1.0;//50.0;//0.6;//0.6;//0;//1.0;
	double dir_init_multi = 100000;//100000000;//10000;//1;//10000;
	int move_delay = 20;//25;//50; // delay in speed that moves are commanded to occur
	double move_increment = 0.005;//0.018;//0.005;//0.018;//0.017;//0.017;//0.001;//0.001;//0.005;//0.005;//0.018;//0.005;//0.005;//0.005;//0.02;//0.027;//0.0005;//0.025;//0.02;//0.001;//0.001;//0.0;//0.001;//0.015;//0.001;//0.025;// 0.01 = 10mps //0.664;//0.0057;//0.0035;//0.0000;//0.0057;//0.0067;//0.002;//0.01;//0.005;//0.2;//0.05;//0.01;//0.266;//0.1;//0.03;//0.05;//0.12;//0.133;//0.664;//0.55;//0.5312;//0.664;//0.665;//0.658;//0.64;//0.658;//0.1;//0.5;//0.2634;//0.325;//0.65; // amount to move in position each move command
	vector<float> ext_dir;
	int conn_offset = 0; // offset in neuron positions for connections
	int conn_dist = 3; // distance between neurons in connections

	// speed
	bool auto_speed_control = 0; // automatically adjust parameters to match speed selected
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
	float pc_to_gc_wt = 5.5;//6;//6;//9;//5;//9;//6.5;//4.8;//5.5;//6.5;//7.5;//9;//6;//4;//3;//9;//6;//3;//2;//1.75;//2;//4;//2;//3;//6.0;//3.333;//4;//4;//5;//2.25;//1;//.5;//2;//1.5;//1.0;//1.5;//1.125;//1.5;//0.5;//0.5;//3;//0.5;//3;//0.5;//10; // pc to gc synaptic weight
	double pc_sig = 1;//1.4;//1;//0.75;//1.5;//2;//1.5;//1.2;//2;//1.5;//4.0;//1.0;//0.25; // sigma symbol; width of the place feild
	double pc_level = 2000;//2500;//3000;//2000;//3000;//2000;//2000;//2000;//3000;//1000;//500;//1000;//3000;//1000;//1000;//1000.0;//1000.0;//5.5;//7.5;//5.0; //14.0; // place cell firing level
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
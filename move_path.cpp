/*
	movement sequences
*/

double rand_move() {
	int num_directions = 4;
	int rand_val = rand() % num_directions + 1;
	double angle;

	if (rand_val == 1) {
		angle = 0;
	}
	else if (rand_val == 2) {
		angle = 90;
	}
	else if (rand_val == 3) {
		angle = 180;
	}
	else if (rand_val == 4) {
		angle = 270;
	}

	return angle;
}

double rand_diag() {
	int num_directions = 4;
	int rand_val = rand() % num_directions + 1;
	double angle;

	if (rand_val == 1) {
		angle = 45;
	}
	else if (rand_val == 2) {
		angle = 135;
	}
	else if (rand_val == 3) {
		angle = 225;
	}
	else if (rand_val == 4) {
		angle = 315;
	}

	return angle;
}

double rand_angle() {
	int num_angles = 360;
	int angle = rand() % num_angles;
	return angle;
}

double rand_speed(P *p) {
	double scale = 0.01;
	double max = p->max_rand_speed;
	double min = p->min_rand_speed;
	int rand_val = (min*(1/scale));
	int addit_sig = (max-min)*(1/scale); // additional speed signal
	if (addit_sig > 0) {
		rand_val = rand_val + (rand() % addit_sig);
	}

	return (double) rand_val * scale;
}

void control_speed(double speed, P* p) {
	/*
		parameters are automatically adjusted based on a regression 
		data fit to parameters observed through testing to produce 
		desired	physical space plots.

		references: https://arachnoid.com/polysolve/ (The tool is a JavaScript version of PolySolve)
		https://www.socscistatistics.com/tests/regression/default.aspx
	*/
	//if (speed > p->max_speed) {speed = p->max_speed;} // speed limit
	if (p->auto_speed_control) {
		p->move_increment = (0.00096*speed)-0.00012;
		p->const_speed = (0.1287571596*speed)-(0.1143442859*pow(speed,2))+(0.03852298736*pow(speed,3))-(0.003102176404*pow(speed,4));
		p->speed_mult = (0*speed)+0.5;
		//printf("%f %f\n",p->move_increment,speed);
	}
}

void EISignal(double angle, CARLsim* sim, P* p);

void run_path(vector<double> *moves, vector<double> *speeds, vector<int> *speed_times, int num_moves, int num_speeds, CARLsim* sim, P *p) {
	/*
		Run movements through a path.
	*/
	double angle = (*moves)[(int) floor(p->mi)];

	general_input(angle, sim, p);

	if (p->t % p->move_delay == 0) {
		if (p->mi < num_moves) {
			control_speed((*speeds)[(int) floor(p->mi)], p);
			//printf("%f %d\n",(*speeds)[(int) floor(p->mi)]*400,p->mi);
			EISignal(angle, sim, p);
			//printf("t: %d; speed: %f; angle: %f\n",p->t,(*speeds)[(int) floor(p->mi)]*200,(*moves)[(int) floor(p->mi)]);
		}
		else {
			/*if (p->t % (50*p->firing_bin) == 0) {
				p->base_ext = rand_speed(p);
			}*/
			EISignal(rand_move(), sim, p);
		}
		p->mi = p->mi + 1;
	}
}

void straight_path(CARLsim* sim, P* p) {
	// stright line path
	//control_speed(50,p);
	double angle = 90;
	general_input(angle, sim, p);
	if (p->t % p->move_delay == 0) {
		control_speed(3.587,p);	
		//control_speed(0.1,p);	
		//control_speed(0.0,p);	
		//control_speed(0.0,p);	
		EISignal(angle, sim, p);
	}
}

void rand_path(CARLsim* sim, P* p) {
	// random move

	if (p->t % 20 == 0) {
		//p->base_ext = rand_speed(p);
		//printf("speed: %f\n",p->base_ext);
	}
	EISignal(rand_move(), sim, p);
}

void move_path_bound_test(CARLsim* sim, P* p) {
	// movement path

	vector<double> moves{0,270,270,0,90,90,270,90,90,90,90,0,0,0,270,270,0,90,90,90,0,270,
	180,90,180,90,270,270,0,90,90,90,270,270,270,270,0,90,270,180,90,180,180,0,180,0,180,0,
	0,90,180,270,270,270,90,0,0,0,90,90,0,90,90,90,90,90,0,90,90,90,90,180,0,90,
	270,0,90,0,180,90,270,270,90,0,90,90,90,270,180,90,180,90,270,180,90,180,180,0,90,180,
	90,270,270,0,90,90,270,270,0,270,0,0,90,90,0,90,90,90,90,90,90,90,90,90,90,180,
	0,90,270,0,90,0,180,90,270,270,0,90,90,90,270,180,90,180,90,270,180,90,180,180,0,180,
	90,270,270,0,90,90,270,270,0,270,270,0,90,90,0,0,0,0,0,0,0,90,90,90,180,0,
	90,270,0,90,0,180,90,270,270,90,0,90,90,90,270,180,90,180,90,270,180,90,180,180,0,180,
	90,270,270,0,90,90,270,270,0,270,270,90,270,270,0,0,270,270};
	vector<double> speeds = {0.25,0.5,1.0,0.2,0.33,0.5,1.0,0.2,1.0,0.25,0.5,0.33,1.0,0.5,0.25};
	vector<int> speed_times = {1,10,20,30,60,90,120,150,180,210,300,350,400,491,499};
	int num_moves = moves.size();
	int num_speeds = speeds.size();

	run_path(&moves, &speeds, &speed_times, num_moves, num_speeds, sim, p);
}

void move_path(CARLsim* sim, P* p) {
	// movement path

	vector<double> moves{0,90,180,90,180,270,90,0,90,270,90,270,90,0,90,270,90,270,90,0,90,180,
	90,0,90,90,90,180,180,270,0,0,90,90,0,0,270,270,180,90,90,180,180,90,90,270,270,180,
	270,90,0,180,90,0,90,180,90,90,270,270,180,270,90,0,180,90,90,90,270,270,180,270,90,0,
	180,90,180,90,0,90,180,90,90,270,270,180,270,90,0,180,90,90,90,270,180,270,270,0,0,270,
	270,0,0,0,90,90,90,90,0,90,90,270,90,0,90,270,90,270,90,0,90,180,90,0,90,90,
	90,180,180,270,0,180,90,90,270,270,0,0,90,0,0,90,180,90,90,270,270,180,270,90,0,180,
	90,0,90,180,90,90,270,270,180,270,90,0,180,90,90,90,270,270,180,270,90,0,180,90,180,90,
	0,90,180,90,90,270,270,180,270,90,0,180,90,90,90,270,180,270,270,0,0,270,270,0,0,0,
	90,90,90,90,0,90,90,270,90,0,90,270,90,270,90,0,90,180,90,0,90,90,90,180,180,270,
	0,180,90,90,270,270,0,0,90,0,0,90,180,90,90,270,270,180,270,90,0,180,90,0,90,180,
	90,90,270,270,180,270,90,0,180,90,90,90,270,270,180,270,90,0,180,90,180,90,0,90,180,90,
	90,270,270,180,270,90,0,180,90,90,90,270,180,270,270,0,0,270,270,0,0,0,90,90,90,90,
	0,90,0,0,0,0,0,0,0,0,0,0,0,180,90,0,90,90,90,180,180,270,0,180,90,90,
	270,270,0,0,90,0,0,90,180,90,90,270,270,180,270,90,0,180,90,0,90,180,90,90,270,270,
	180,270,90,0,180,90,90,90,270,270,180,270,90,0,180,90,180,90,0,90,180,90,90,270,270,180,
	270,90,0,180,90,90,90,270,180,270,270,0,0,270,270,90,90,270,180,270,270,0,0,270,270};
	vector<double> speeds = {1.0};
	vector<int> speed_times = {1};
	int num_moves = moves.size();
	int num_speeds = speeds.size();

	run_path(&moves, &speeds, &speed_times, num_moves, num_speeds, sim, p);
}

void move_path2(CARLsim* sim, P* p) {
	// movement path

	vector<double> moves = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	vector<double> speeds = {1.0};
	vector<int> speed_times = {1};
	int num_moves = moves.size();
	int num_speeds = speeds.size();

	run_path(&moves, &speeds, &speed_times, num_moves, num_speeds, sim, p);
}

void move_path3(CARLsim* sim, P* p) {
	// movement path

	vector<double> moves;
	double angle;
	double h_a = 90; // horizontal movement angle
	int h_m = 10*50; // indices for horizontal movement
	vector<int> m_d_i; // move down indices
	for (int i = 0; i < 15; i++) {
		m_d_i.push_back(h_m+i);
	}
	for (int i = 0; i < (h_m+m_d_i.size())*150; i++) {
		angle = -1; // clear angle
		for (int j = 0; j < m_d_i.size(); j++) { // process indices for down move
			if (i % m_d_i[j] == 0) {
				angle = 180;
			}
		}
		if (angle == -1) {
			angle = h_a;
		}
		moves.push_back(angle);
	}
	vector<double> speeds;
	vector<int> speed_times;
	for (int i = 0; i < moves.size(); i++) {
		speeds.push_back(3.587);
		speed_times.push_back(i*20);
	}
	int num_moves = moves.size();
	int num_speeds = speeds.size();

	run_path(&moves, &speeds, &speed_times, num_moves, num_speeds, sim, p);
}

void move_animal(CARLsim* sim, P* p) {
	/*
		Movement data from real animal recordings.
	*/
	#if import_animal_data
		//#include "data/anim_angles.cpp"
		//#include "data/anim_speeds.cpp"
		//#include "data/anim_angles_180815_S1_S2_lightVSdarkness_merged.cpp"
		//#include "data/anim_speeds_180815_S1_S2_lightVSdarkness_merged.cpp"
		//#include "data/anim_angles_191108_S1_lightVSdarkness_cells11and12.cpp"
		//#include "data/anim_speeds_191108_S1_lightVSdarkness_cells11and12.cpp"
		#include "data/test_data_angles.cpp"
		#include "data/test_data_speeds.cpp"
	#endif

	vector<int> speed_times;
	vector<double> speeds;
	int num_moves = anim_angles.size();
	int num_speeds = anim_speeds.size();	

	//for (int i = 0; i < p->animal_timesteps; i++) {
	for (int i = 0; i < num_speeds; i++) {
		//speeds.push_back(8.5);
		speed_times.push_back(i*p->animal_ts);
		anim_speeds[i] = anim_speeds[i];// * 2;//(30/180); // GC layer size conversion factor
	}

	// rotate angles
	/*for (int i = 0; i < p->animal_timesteps; i++) {
		anim_angles[i] = anim_angles[i] + 90;
		if (anim_angles[i] > 360) {
			anim_angles[i] = anim_angles[i] - 360;
		}
	}*/

	run_path(&anim_angles, &anim_speeds, &speed_times, num_moves, num_speeds, sim, p);	
	//run_path(&anim_angles, &speeds, &speed_times, num_moves, num_speeds, sim, p);	
}

void move_circles(CARLsim* sim, P* p) {
	// movement path

	vector<double> moves;
	double angle = 90;
	for (int i = 0; i < (p->sim_time/p->animal_ts); i++) {
		if (i % 20 == 0) {
			angle += 45;
			//angle += 135;
			//angle = rand_angle();
			//angle = rand_move();
		}
		if (angle >= 360) {
			angle = 0;
		}
		moves.push_back(angle);
	}
	vector<double> speeds;
	vector<int> speed_times;
	for (int i = 0; i < moves.size(); i++) {
		//speeds.push_back(35.4/400);
		speeds.push_back(3.587);
		speed_times.push_back(i*20);
	}
	int num_moves = moves.size();
	int num_speeds = speeds.size();

	run_path(&moves, &speeds, &speed_times, num_moves, num_speeds, sim, p);
}
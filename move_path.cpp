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
		https://www.mathworks.com/matlabcentral/answers/230107-how-to-force-the-intercept-of-a-regression-line-to-zero
		dlm = fitlm(X,Y,'Intercept',false); This is linear reg with y-intercept forced at 0. This
		allows position tracker speed scaling without altering trajectory that changing y-int causes.
	*/
	speed = speed * p->speed_conversion;
	if (p->speed_limit == 1 && speed > p->max_speed) {speed = p->max_speed;} // speed limit
	if (p->auto_speed_control || p->move_test) {
		p->move_increment = (0.001*speed);
		p->base_ext = 587.4881579-(5.7850940521124521*speed)+(1.4611941553146452*pow(speed,2))-(0.07780278296*pow(speed,3))+(0.001700452564*pow(speed,4));
		p->speed_signaling = 0.01215404582+(0.01524206911*speed)+(0.008762289442*pow(speed,2))-(0.0006140572184*pow(speed,3))+(0.00001670652325*pow(speed,4));
		p->spdin2in_curr = 0.03940910736-(0.05881012583*speed)+(0.01344803471*pow(speed,2))-(0.001339463905*pow(speed,3))+(0.00006120898184*pow(speed,4));
		p->spdex2in_curr = 0.01*(54.33736842+(2.197281355*speed)-(0.6571770115*pow(speed,2))+(0.03983430037*pow(speed,3))-(0.0008224893280*pow(speed,4)));
		//if (p->spdex2in_curr < 0.35) {p->spdex2in_curr = 0.35;}
		//if (p->base_ext > 625) {p->base_ext = 625;}
		//if (p->spdin2in_curr > 2) {p->base_ext = 2;}
		if (speed >= 10) {p->pc_to_gc_wt = 0.5;} else {p->pc_to_gc_wt = 1.0;}
		//printf("%f %f\n",p->move_increment,speed);
	}
}

void EISignal(double angle, CARLsim* sim, P* p);

void run_path(vector<double> *moves, vector<double> *speeds, vector<int> *speed_times, int num_moves, int num_speeds, CARLsim* sim, P *p) {
	/*
		Run movements through a path.
	*/
	double angle;

	if (p->t % p->move_delay == 0 && p->t != 0) {
		p->mi = p->mi + 1;
		if (p->mi < num_moves) {
			angle = (*moves)[(int) floor(p->mi)];
			control_speed((*speeds)[(int) floor(p->mi)], p);
			EISignal(angle, sim, p);
			//printf("t: %d; speed: %f; angle: %f\n",p->t,(*speeds)[(int) floor(p->mi)],(*moves)[(int) floor(p->mi)]);
			//printf("x:%f y:%f\n",p->pos[0],p->pos[1]);
			//printf("t: %d; speed: %f; angle: %f\n",p->t,(*anim_speeds)[(int) floor(p->mi)],(*anim_angles)[(int) floor(p->mi)]);
		}
		else {EISignal(rand_move(), sim, p);}
		general_input(angle, sim, p);
	}
	else {
		angle = (*moves)[(int) floor(p->mi)];
		general_input(angle, sim, p);
	}
}

void straight_path(CARLsim* sim, P* p) {
	// stright line path
	//control_speed(50,p);
	double angle = 90;
	general_input(angle, sim, p);
	if (p->t % p->move_delay == 0) {
		control_speed(25,p);	
		//control_speed(20,p);	
		//control_speed(25,p);	
		//control_speed(0.1,p);	
		//control_speed(0,p);	
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

void move_animal(CARLsim* sim, P* p, vector<double> *anim_angles, vector<double> *anim_speeds) {
	//
	//	Movement data from real animal recordings.
	//

	run_path(anim_angles, anim_speeds, &p->speed_times, p->num_moves, p->num_speeds, sim, p);	
}

void move_circles(CARLsim* sim, P* p) {
	// movement path

	vector<double> moves;
	double angle = 90;
	for (int i = 0; i < (p->sim_time/p->animal_ts); i++) {
		if (i % 40 == 0) {
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

void animal_data_vars(CARLsim* sim, P* p, vector<double> *anim_angles, vector<double> *anim_speeds) {
	/* create values for animal data variables */

	p->num_moves = anim_angles->size();
	p->num_speeds = anim_speeds->size();

	for (int i = 0; i < p->num_speeds; i++) {
		p->speed_times.push_back(i*p->animal_ts);
		//(*anim_speeds)[i] = (*anim_speeds)[i] * 2;
	}

	// rotate angles
	//for (int i = 0; i < p->num_angles; i++) {
	//	(*anim_angles)[i] = (*anim_angles)[i] + 90;
	//	if ((*anim_angles)[i] > 360) {
	//		(*anim_angles)[i] = (*anim_angles)[i] - 360;
	//	}
	//}
}

void move_test(CARLsim* sim, P* p, vector<double> *anim_angles, vector<double> *anim_speeds) {
	/* test movement path with no neuron signaling simulation */

	double angle;
	if (p->t % p->move_delay == 0 && p->t != 0) {
		p->mi = p->mi + 1;
		if (p->mi < p->num_moves) {
			angle = (*anim_angles)[(int) floor(p->mi)];
			control_speed((*anim_speeds)[(int) floor(p->mi)], p);
			//printf("t: %d; speed: %f; angle: %f\n",p->t,(*anim_speeds)[(int) floor(p->mi)],(*anim_angles)[(int) floor(p->mi)]);
		}
		set_pos(p, angle);
	}
	else {
		angle = (*anim_angles)[(int) floor(p->mi)];
		set_pos(p, angle);
	}
}

void move_ramp(CARLsim* sim, P* p) {
	// test movement with speeds ramping up then down

	vector<double> moves;
	double angle = 90;
	double speed = 5; 
	double top_speed = 25;//25;//25;//13;
	double max_angle = 90;
	//int rand_val = rand() % max_angle;
	int rev_dir_t = 200; // ms to reverse direction
	bool speed_ramp = 1;
	bool angle_ramp = 1;
	double si = (p->t) % rev_dir_t;

	general_input(angle, sim, p);
	if (p->t % p->move_delay == 0) {
		if ((p->t) % rev_dir_t == 0) {
			p->move_rev = p->move_rev * -1;
		}
		if (p->move_rev == 1) {
			if (speed_ramp) {speed = top_speed * (si/(double) rev_dir_t);}
			if (angle_ramp) {angle = angle + max_angle*(si/(double) rev_dir_t);}		
		}
		else {
			if (speed_ramp) {speed = top_speed * (1-(si/(double) rev_dir_t));}
			if (angle_ramp) {angle = angle + max_angle*(1-(si/(double) rev_dir_t));}
		}		
		if (angle_ramp && angle > 360) {angle = angle - 360;}
		//speed = (top_speed*.5)+(speed*.5);
		//speed = 0+(speed*.8);
		control_speed(speed,p);
		EISignal(angle, sim, p);
		printf("%.2d %.2f %.2f\n",p->t,speed,angle);
	}
}
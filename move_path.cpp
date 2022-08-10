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
	if (p->auto_speed_control || p->move_animal_onlypos) {
		p->move_increment = (0.001*speed);
		speed = speed * p->grid_pattern_scale;
		p->base_ext = 599.80090165493073+(1.6261465514582882*speed)-(0.91614491179608026*pow(speed,2))+(0.12862126960704923*pow(speed,3))-(0.0038746307083107070*pow(speed,4));
		p->speed_signaling = .033142089711234834-(.018931921976746008*speed)+(.022852000258479707*pow(speed,2))-(.0023789928407943238*pow(speed,3))+(.000082693476104535207*pow(speed,4));
		p->spdin2in_curr = -.50000000000002909+(0.023333333333336974*speed)+(.0013333333333332236*pow(speed,2));
		if (speed<13) {p->spdin2in_curr=0;}
		p->spdex2in_curr = 0.54192102759494176+(0.013333688462443864*speed)-(0.00040923216053246475*pow(speed,2))-(0.00056131770078813367*pow(speed,3))+(0.000024054119037496186*pow(speed,4));
		if (p->spdex2in_curr>13) {p->spdex2in_curr=0;}
		//printf("%f %f\n",p->move_increment,speed);
	}
}

void EISignal(double angle, CARLsim* sim, P* p);

void run_path(vector<double> *moves, vector<double> *speeds, vector<int> *speed_times, int num_moves, int num_speeds, CARLsim* sim, P *p) {
	/*
		Move animal through a predefined set of velocities (speeds+angles) to create a path.
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

void run_path_test(vector<double> *moves, vector<double> *speeds, vector<int> *speed_times, int num_moves, int num_speeds, CARLsim* sim, P *p) {
	/*
		Output the path of a virtual animal without simulating signaling
	*/

	double angle;
	if (p->t % p->move_delay == 0 && p->t != 0) {
		p->mi = p->mi + 1;
		if (p->mi < num_moves) {
			angle = (*moves)[(int) floor(p->mi)];
			control_speed((*speeds)[(int) floor(p->mi)], p);
		}
		set_pos(p, angle);
	}
	else {
		angle = (*moves)[(int) floor(p->mi)];
		set_pos(p, angle);
	}
}

void move_straight(CARLsim* sim, P* p) {
	// stright line path
	//control_speed(50,p);
	double angle = 90;
	general_input(angle, sim, p);
	if (p->t % p->move_delay == 0) {
		control_speed(15,p);	
		//control_speed(20,p);	
		//control_speed(25,p);	
		//control_speed(0.1,p);	
		//control_speed(0,p);	
		EISignal(angle, sim, p);
	}
}

void move_random(CARLsim* sim, P* p) {
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

void move_fullspace(CARLsim* sim, P* p) {
	// Moves virtual animal sequentially back and forth through an
	// environment as a movement test pattern to test firing in each
	// enviornment location.

	double angle;
	double angle_rev_h = 1; // flag to reverse angle horizontally
	double angle_rev_v = -1; // flag to reverse angle vertically
	//double speed = 2.5;
	double speed = p->move_increment*1000;
	int ts_per_sec = 1000/p->firing_bin; // timesteps per second
	int h_m = ((int) floor((double) p->x_size/speed)*ts_per_sec); // indices for horizontal movement
	int v_m = ceil(1000.0/(double) p->firing_bin)/speed; // indices for vertical movement
	vector<int> mv_i; // move vertical index
	for (int i = 0; i < v_m; i++) {mv_i.push_back(h_m+i);}
	int v_m_t = (int) ceil((p->sim_time/(double) p->firing_bin)/(double) (h_m+v_m)); // vertical moves total
	if (p->t == 0) {p->pos[0]=0;p->pos[1]=0;p->bpos[0]=0;p->bpos[1]=0;} // set starting point to 0,0
	for (int i = 0; i < (h_m+v_m)*v_m_t; i++) {
		// detect end of layer row
		if (i % h_m == 0) 
		{angle_rev_h=angle_rev_h*-1;} 
		// detect end of layer column
		if (i % ((h_m+v_m)*p->y_size) == 0) 
		{angle_rev_v=angle_rev_v*-1;} 
		// process indices for horizontal move
		if (angle_rev_h == -1) {angle = 90;}
		else if (angle_rev_h == 1) {angle = 270;}
		// process indices for vertical move
		for (int j = 0; j < v_m; j++) { 
			if (i % mv_i[j] == 0) {
				if (angle_rev_v==1) {angle = 0;} else {angle = 180;}
			}
		}
		p->angles.push_back(angle);
	}
	for (int i = 0; i < p->angles.size(); i++) {
		p->speeds.push_back(speed);
		p->speed_times.push_back(i*20);
	}
	p->num_moves = p->angles.size();
	p->num_speeds = p->speeds.size();
}

void move_animal(CARLsim* sim, P* p, vector<double> *anim_angles, vector<double> *anim_speeds) {
	//
	//	Movement data from real animal recordings.
	//

	run_path(anim_angles, anim_speeds, &p->speed_times, p->num_moves, p->num_speeds, sim, p);	
}

void move_circles(CARLsim* sim, P* p) {
	// movement path

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
		p->angles.push_back(angle);
	}
	for (int i = 0; i < p->angles.size(); i++) {
		p->speeds.push_back(3.587);
		p->speed_times.push_back(i*20);
	}
	p->num_moves = p->angles.size();
	p->num_speeds = p->speeds.size();
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

void move_animal_onlypos(CARLsim* sim, P* p, vector<double> *anim_angles, vector<double> *anim_speeds) {
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
	double top_speed = 22.5;//25;//25;//13;
	double max_angle = 0;//90;
	//int rand_val = rand() % max_angle;
	int rev_dir_t = 120; // ms to reverse direction
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
		speed = (top_speed*.45)+(speed*.55);
		//speed = 0+(speed*.8);
		control_speed(speed,p);
		EISignal(angle, sim, p);
		//printf("%.2d %.2f %.2f\n",p->t,speed,angle);
	}
}
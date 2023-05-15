/*
	movement sequences

	references: https://www.omnicalculator.com/math/right-triangle-side-angle
	https://www.mathsisfun.com/algebra/trig-finding-angle-right-triangle.html
	https://www.mathsisfun.com/algebra/sohcahtoa.html
	https://cplusplus.com/reference/cmath/asin/
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
		https://mycurvefit.com/ for sigmoid curve fitting
		base_ext uses a double sigmoid (high at start, low at middle, high at end). This is from
		dividing by two the combined values from two sigmoid curves with different midpoints. 
		Double sigmoid reference: https://www.reddit.com/r/askmath/comments/cmey15/what_is_the_general_formula_for_a_double_sigmoid/
	*/
	//speed = speed * p->speed_conversion;
	if (p->speed_limit == 1 && speed > p->max_speed) {speed = p->max_speed;} // speed limit
	if (p->auto_speed_control || p->move_animal_onlypos) {
		p->move_increment = (0.001*speed);
		/*p->base_ext = 186.3885 + (524.6455/(1 + pow((speed/3.737486),2.211211)));
		p->speed_signaling = 2.057852 - (2.01749818/(1 + pow((speed/8.060984),4.142584)));
		p->pc_level = 295.9315 + (513.837/(1 + pow((speed/2.681747),3.170439)));*/
		//double angle = (p->angles)[(int) floor(p->mi)];
		//printf("angle:%f\n",p->prior_angles[0]);
		//p->base_ext=100;

		if (speed <= 18.0) {
			p->speed_signaling=(-4.9398419382784553e-015)+((2.5313864451024987e-002)*speed)+((5.5989491690925193e-003)*pow(speed,2))+
			((-4.0003258390201130e-004)*pow(speed,3))+((8.6999022482481231e-006)*pow(speed,4));
		}
		else {p->speed_signaling = 0.85;}

		// momentum adjustment
		/*bool change = false;
		for (int i = 0; i < p->prior_angles.size(); i++) {
			if (i <= (p->t/p->timestep)) {
				if (p->prior_angles[i]==0 || p->prior_angles[i]==180) {
					change = true;
				}
			}
		}
		if (change) {
			p->speed_signaling=p->speed_signaling*0.8;//1;//1.2;//1.4;//*0.4992*.45;//0.5616;//0.624;
		}*/

		/*if (p->prior_angles[0]==0 || p->prior_angles[0]==180) {
			p->speed_signaling=p->speed_signaling*2;//0.36*0.624;//p->speed_signaling*0.4992*.45;//0.36*0.624;
		}*/
		//printf("a:%f\n",p->prior_angles[0]);
		/*if (speed <= 24) {
			p->speed_signaling=(-2.2703071662236850e-003)+((5.3999063499853880e-002)*speed)+((9.1668862388604479e-003)*pow(speed,2))+((-1.2261892078421113e-003)*pow(speed,3))+((5.8415873552304476e-005)*pow(speed,4))+((-8.5140397443536999e-007)*pow(speed,5));
		}
		else if (speed <= 28) {
			p->speed_signaling=(-2.0716180440729490e+003)+((3.1398611005030739e+002)*speed)+((-1.2350885040772077e+001)*pow(speed,2))+((-1.8920736732209620e-001)*pow(speed,3))+((2.0496182320031441e-002)*pow(speed,4))+((-3.1792001647285316e-004)*pow(speed,5));
		}
		else {p->speed_signaling = 10;}*/
		//p->speed_signaling = p->speed_signaling * 0.375;
		//p->base_ext = 328.1851 + 264.5679/(1 + pow((speed/9.923302),8.14715));
		//p->speed_signaling = 2.318527 - (2.27162279/(1 + pow((speed/12.15808),4.901232)));
		//p->base_ext = 45.06935 + (104.66755/(1 + pow((speed/12.3696),5.882045)));
		//p->speed_signaling = 2.351559 + (-2.31547713/(1 + pow((speed/10.90842),2.548051)));
		//if (speed>5) {p->spdex2in_curr = -0.1509171 + (0.550918/(1 + pow((speed/2.824788),1.707051)));}
		//else {p->spdex2in_curr = 0;}
		//if (speed>10) {p->pc_level = 2*300;}
		//else {p->pc_level = 2*300+(speed*-30);}
		//p->pc_level = p->base_ext * .71;
		//if (speed<1) {p->speed_signaling=0;}
		//if (speed>15) {p->speed_signaling=20.0;}
		//p->spdin2in_curr = 8 + -8/(1 + pow((speed/15.31543),187.0108));
		//p->spdin2in_curr = 1 + -1/(1 + pow((speed/13),187));
		//p->spdin2ex_curr = 3/(1 + pow((speed/14.91975),129.208));
		//p->spdex2in_curr = 0.3;
	}
}

void EISignal(double angle, CARLsim* sim, P* p);

void run_path(vector<double> *moves, vector<double> *speeds, vector<int> *speed_times, int num_moves, int num_speeds, CARLsim* sim, P *p) {
	/*
		Move virtual animal through a predefined set of velocities (speeds+angles) to create a path.
	*/
	double angle, speed;
	int mi;

	if (p->t % p->move_delay == 0 && p->t != 0) {
		p->mi = p->mi + 1;
		if (p->mi < num_moves) {
			// store recent values
			mi = (int) floor(p->mi);
			angle = (*moves)[mi];
			speed = (*speeds)[mi];
			// shift all values down 1 index
			/*for (int i = p->prior_speeds.size()-1; i >= 0; i--) {
				p->prior_speeds[i+1] = p->prior_speeds[i];
				p->prior_angles[i+1] = p->prior_angles[i];
			}
			p->prior_angles[0]=angle;
			p->prior_speeds[0]=speed;*/
			//printf("a:%f s:%f\n",angle,speed);
			control_speed(speed, p);
			EISignal(angle, sim, p);
			//printf("t: %d; speed: %f; angle: %f\n",p->t,(*speeds)[(int) floor(p->mi)],(*moves)[(int) floor(p->mi)]);
			//printf("x:%f y:%f\n",p->pos[0],p->pos[1]);
			//printf("t: %d; speed: %f; angle: %f\n",p->t,(*anim_speeds)[(int) floor(p->mi)],(*anim_angles)[(int) floor(p->mi)]);
			if (p->print_aug_values && p->t>p->animal_aug_time && (*moves)[(int) floor(p->mi)] != (*moves)[(int) floor(p->mi-1)]) {
				printf("t: %d; speed: %f; angle: %f x:%f y:%f\n",p->t,(*speeds)[(int) floor(p->mi)],(*moves)[(int) floor(p->mi)],p->pos[0],p->pos[1]);
			}
		}
		else {EISignal(rand_move(), sim, p);}
		general_input(angle, sim, p);
	}
	else {
		angle = (*moves)[(int) floor(p->mi)];
		general_input(angle, sim, p);
	}
}

void run_path_onlypos(vector<double> *moves, vector<double> *speeds, vector<int> *speed_times, int num_moves, int num_speeds, CARLsim* sim, P *p) {
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
		//angle = angle - 15;
		//if (angle>360) {angle=360-angle;}
		//if (angle<0)   {angle=angle+360;}
		set_pos(p, angle);
	}
	else {
		//angle = angle - 15;
		//if (angle>360) {angle=360-angle;}
		//if (angle<0)   {angle=angle+360;}
		angle = (*moves)[(int) floor(p->mi)];
		set_pos(p, angle);
	}
}

void move_straight(CARLsim* sim, P* p) {
	// straight line path
	double angle = 90;//90;//120;//105;//22.5;//90;//75;//56.25;//67;//22.5;//75;
	general_input(angle, sim, p);
	if (p->t % p->move_delay == 0) {
		control_speed(15,p);
		EISignal(angle, sim, p);
	}
}

void move_speed_change(CARLsim* sim, P* p) {
	// switch speeds
	double angle = 90;
	vector<double> speeds{5, 10};
	int time_switch = 5000; // time in ms to switch
	general_input(angle, sim, p);
	if (p->t % p->move_delay == 0) {
		if (p->t % time_switch == 0 && p->t != 0) {
			p->speed_setting += 1;
			if (p->speed_setting == speeds.size()) {p->speed_setting=0;}
			printf("speed change t:%d s:%f\n",p->t,speeds[p->speed_setting]);
		}
		control_speed(speeds[p->speed_setting],p);		
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

/*void move_fullspace(CARLsim* sim, P* p) {
	// Moves virtual animal sequentially back and forth through an
	// environment as a movement test pattern to test firing in each
	// enviornment location.

	double angle;
	double angle_rev_h = -1; // flag to reverse angle horizontally
	double angle_rev_v = -1; // flag to reverse angle vertically
	//double speed = 2.5;
	double speed = p->move_increment*1000;
	int ts_per_sec = 1000/p->timestep; // timesteps per second
	int h_m = ((int) floor((double) p->x_size/speed)*ts_per_sec); // indices for horizontal movement
	int v_m = ceil(1000.0/(double) p->timestep)/speed; // indices for vertical movement
	vector<int> mv_i; // move vertical index
	for (int i = 0; i < v_m; i++) {mv_i.push_back(h_m+i);}
	int v_m_t = (int) ceil((p->sim_time/(double) p->timestep)/(double) (h_m+v_m)); // vertical moves total
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
}*/

void move_fullspace2(CARLsim* sim, P* p) {
	// Moves virtual animal sequentially back and forth through an
	// environment as a movement test pattern to test firing in each
	// environment location.

	double speed = p->move_increment*1000;
	control_speed(speed,p);	
	double offset = (p->x_size-p->x_size_plot)/2; // offset for plotting
	offset=4;//5;//7;//5;//2;
	//p->pos[0]=offset+5;p->pos[1]=offset-5; // set starting point
	//p->bpos[0]=offset+5;p->bpos[1]=offset-5;
	//double start=18;
	//p->pos[0]=start;p->pos[1]=start; // set starting point
	//p->bpos[0]=start;p->bpos[1]=start;
	//p->pos[0]=offset;p->pos[1]=1; // set starting point
	//p->bpos[0]=offset;p->bpos[1]=1;
	p->pos[0]=offset;p->pos[1]=p->pos[0]; // set starting point
	p->bpos[0]=offset;p->bpos[1]=p->bpos[0];
	double angle; double x = p->pos[0]; double y = p->pos[1]; bool move_vert = 0;
	double angle_rev_h = -1; // flag to reverse angle horizontally
	double angle_rev_v = 1; // flag to reverse angle vertically
	int ts_per_sec = 1000/p->timestep; // timesteps per second
	double step_spd = speed/ts_per_sec; // movement per timestep
	int h_m = ((int) floor((double) p->x_size_plot/speed)*ts_per_sec); // indices for horizontal movement
	int v_m = (ceil(1000.0/(double) p->timestep)/speed)*.8; // indices for vertical movement
	int v_m_t = (int) ceil((p->sim_time/(double) p->timestep)/(double) (h_m+v_m)); // vertical moves total
	for (int i = 0; i < (h_m+v_m)*v_m_t; i++) {
		// horiz move
		if (x > p->x_size-offset) {angle_rev_h = 1;move_vert=1;}
		else if (x < offset) {angle_rev_h = -1;move_vert=1;}
		// process indices for horizontal move
		if (angle_rev_h == -1) {angle = 90;x=x+step_spd;}
		else {angle = 270;x=x-step_spd;}
		// vert move
		if (y > p->y_size-offset) {angle_rev_v=-1;}//cout<<"vert border "<<y<<"\n";}
		//else {cout<<"non-vert border "<<y<<"\n";}
		if (y < offset) {angle_rev_v=1;}
		// process indices for vertical move
		if (move_vert) {
			for (int j = 0; j < v_m; j++) {
				if (angle_rev_v==1) {angle = 0;y=y+step_spd;} 
				else {angle = 180;y=y-step_spd;}
				p->angles.push_back(angle);
			}
			move_vert=0;
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

	if (p->move_animal_aug == 1 && p->t >= p->animal_aug_time) {}
	else {run_path(anim_angles, anim_speeds, &p->speed_times, p->num_moves, p->num_speeds, sim, p);}
}

void move_circles(CARLsim* sim, P* p) {
	// movement path

	double speed = 5;//3.587;
	double angle = 90;
	int pace = 20;//50;
	for (int i = 0; i < (p->sim_time/p->animal_ts); i++) {
		if (i % pace == 0) {
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
		p->speeds.push_back(speed);
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
			if (p->print_aug_values && p->t>p->animal_aug_time && (*anim_angles)[(int) floor(p->mi)] != (*anim_angles)[(int) floor(p->mi-1)]) {
				printf("t: %d; speed: %f; angle: %f x:%f y:%f\n",p->t,(*anim_speeds)[(int) floor(p->mi)],(*anim_angles)[(int) floor(p->mi)],p->pos[0],p->pos[1]);
			}
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
	double angle = 90; // initial value
	double speed = 5;  // initial value
	double top_speed = 10;//50;//22.5;//25;//25;//13;
	double max_angle = 720;//360;//90;//0;//90;
	//int rand_val = rand() % max_angle;
	int rev_speed_t = 500;//120; // ms to reverse speed
	int rev_angle_t = 120*60; // ms to reverse angle
	bool speed_ramp = 1; // activate speed ramp
	bool angle_ramp = 0; // activate angle ramp
	double si = (p->t) % rev_speed_t;
	double ai = (p->t) % rev_angle_t;

	general_input(angle, sim, p);
	if (p->t % p->move_delay == 0) {
		//if (p->t > 20000) {top_speed=5;}
		// speed
		if ((p->t) % rev_speed_t == 0) {
			p->move_rev_s = p->move_rev_s * -1;
		}
		if (speed_ramp && p->move_rev_s == 1) {
			speed = top_speed * (si/(double) rev_speed_t);
		}
		else if (speed_ramp) {
			speed = top_speed * (1-(si/(double) rev_speed_t));
		}
		// angle
		if ((p->t) % rev_angle_t == 0) {
			p->move_rev_a = p->move_rev_a * -1;
		}
		if (angle_ramp && p->move_rev_a == 1) {
			angle = angle + max_angle*(ai/(double) rev_angle_t);
		}
		else if (angle_ramp) {
			angle = angle + max_angle*(1-(ai/(double) rev_angle_t));
		}		
		if (angle_ramp && angle > 360) {angle = angle - 360;}
		//speed = (top_speed*.45)+(speed*.55);
		//speed = 0+(speed*.8);
		control_speed(speed,p);
		EISignal(angle, sim, p);
		//printf("%.2d %.2f %.2f\n",p->t,speed,angle);
	}
}

void create_rand_loc(P* p, int rand_max, vector<int> loc_range) {
	/* generate list of target locations to travel to. randomly select
	among the lowest visited locations. loc_range specifies low visited
	locations and rand_val selects randomly among loc_range indices. */
	int rand_loc;
	int rand_val = (int) floor(rand() % rand_max); // random number up to rand_max
	// find random location among list of low visited locations
	for (int i = 0; i < ceil(p->locations_sortind.size()*p->percent_for_aug); i++) {
		if (i == 0 && rand_val <= loc_range[0]) {
			rand_loc = p->locations_sortind[0];
		}
		else if (rand_val > loc_range[i-1] && rand_val <= loc_range[i]) {
			rand_loc = p->locations_sortind[i];
		}
	}
	p->x_aug.push_back((double) (rand_loc % p->x_size));
	p->y_aug.push_back((double) (rand_loc / p->x_size));
	//printf("%d %d %d\n",rand_loc,rand_loc % p->x_size,rand_loc / p->x_size);
}

void move_animal_aug(CARLsim* sim, P* p) {
	/*
		Add augmented movements to the virtual animal's trajectory to visit locations
		where little past traveling has occured. This helps represent in a greater way
		the neural activity throughout an environment.

		TODO: add more chance of location target based on lowest locations_visited value.
		This can be added around the create target points section.
		TODO: add speed and angle variation matching range found in real animals.
		TODO: possibly add traveling to multiple near by low visited locations when in region
		rather than longer trips between random locations each time. This could be efficient.
		TODO: possibly add exact location updates for basing each starting location because there can
		be a small rounding error (or something else) difference between intended target locations
		and where virtual animal actually moves.
	*/
	if (p->t == p->animal_aug_time) {
		// clear old values
		p->speeds.clear();p->angles.clear();
		p->mi=0; // different move set is used so a reset of moves counter is done
		double speed = 5; // set movement speed
		int fa_new, fa_old, fi_new, fi_old, x, y; // firing amounts, indices, locations
		int rand_max = 0;
		int num_tgts = (int) ceil(p->locations_sortind.size()*p->percent_for_aug); // number of aug location targets
		double x_pos = p->pos[0];
		double y_pos = p->pos[1];
		double xleg, yleg, angle, last_speed, h, dist_away;
		vector<int> rand_loc_xy, loc_range;

		if (p->print_aug_values) {printf("aug start: x:%.2f y:%.2f \n",x_pos,y_pos);}

		// copy vector
		for (int i = 0; i < p->locations_visited.size(); i++) {
			p->locations_amounts[i]=p->locations_visited[i];
			p->locations_sortind[i]=i;
		}
		// sort vectors. least visited locations will become targets
		for (int i = 0; i < p->locations_amounts.size(); i++) {
			for (int j = 0; j < p->locations_amounts.size(); j++) {
				fa_old = p->locations_amounts[i];
				fi_old = p->locations_sortind[i];
				fa_new = p->locations_amounts[j];
				fi_new = p->locations_sortind[j];
				if (fa_new > fa_old) {
					p->locations_amounts[i] = fa_new;
					p->locations_sortind[i] = fi_new;
					p->locations_amounts[j] = fa_old;
					p->locations_sortind[j] = fi_old;
				}
			}
		}
		
		for (int i = 0; i < p->locations_visited.size(); i++) {
			//if(i==0){printf("locations sorted\n");}
			//printf("i:%d a:%d\n",p->locations_sortind[i],p->locations_amounts[i]);
			//printf("i:%d a:%d\n",i,p->locations_visited[i]);
		}
		
		// create target points
		// find total number of low visited locations
		for (int i = 0; i < num_tgts; i++) {
			rand_max = rand_max + 1;
			loc_range.push_back(rand_max); // ranges for rand values
		}
		// generate list of target locations
		for (int i = 0; i < num_tgts; i++) {
			create_rand_loc(p, rand_max, loc_range);
		}
		if (p->print_aug_values) { // print some targets
			printf("aug targets:\n");
			for (int i = 0; i < 20; i++) {
				printf("x:%f y:%f\n",p->x_aug[i],p->y_aug[i]);
			}
		}
		// generate movement to locations
		for (int t = p->t; t < p->sim_time; /*t is incremented later*/) {
			p->aug_i++; // aug target index
			// find angle to target
			xleg = p->x_aug[p->aug_i] - x_pos;
			yleg = p->y_aug[p->aug_i] - y_pos;
			h = sqrt(pow(xleg,2)+pow(yleg,2)); // triangle hypotenuse
			// find angle from leg and h including converting radians to degrees
			angle = asin(abs(yleg)/h)*(180/PI);
			// find 360 degree rotation
			if (xleg > 0 && yleg > 0) {
				angle = 90 - angle;
			}
			if (xleg > 0 && yleg < 0) {
				angle = 90 + angle;
			}
			else if (xleg < 0 && yleg < 0) {
				angle = 270 - angle;
			}
			else if (xleg < 0 && yleg > 0) {
				angle = 270 + angle;
			}
			if (yleg == 0) {
				if (xleg>0) {angle = 90;} else {angle = 270;}
			}
			if (xleg == 0) {
				if (yleg>0) {angle = 0;} else {angle = 180;}
			}

			// find new movement steps given speed
			dist_away = ceil((h / speed)*(1000/p->timestep)); // number of moves needed given timestep and speed values
			for (int j = 0; j < dist_away; j++) {
				// store angles
				p->angles.push_back(angle);
				// store speeds
				if (j != dist_away - 1) {
					p->speeds.push_back(speed);
				}
				else {
					last_speed = (((int) round(dist_away*1000) % 1000)*.001)*speed; // lower speed for last step. use fraction in dist_away to reduce speed. Need to use *1000 and *.001 because modulo only uses ints
					p->speeds.push_back(last_speed);
					//printf("%.2f %.2d %.2f %.2f\n",h,j,(speed*(double) j-2),last_speed);
				}
				p->speed_times.push_back(p->aug_m*p->timestep);

				if (p->print_aug_values) {
					if (p->aug_m==0) {printf("aug velocity calcs, starting x:%.2f y:%.2f :\n",p->pos[0],p->pos[1]);}
					if (p->angles[p->angles.size()-1] != p->angles[p->angles.size()-2]) { // detect angle change
						printf("t:%d s:%.2f a:%.2f x1:%.0f y1:%.0f x2:%.0f y2:%.0f xleg:%.2f yleg:%.2f h:%.2f\n",t,p->speeds[p->aug_m],p->angles[p->aug_m],x_pos,y_pos,p->x_aug[p->aug_i],p->y_aug[p->aug_i],xleg,yleg,h);	
					}
				}	
				p->aug_m++; // moves index
				t=t+p->timestep;	
			}			
			x_pos = p->x_aug[p->aug_i]; // location is now aug target
			y_pos = p->y_aug[p->aug_i]; 
		}
		if (p->print_aug_values) {
			printf("moves to aug targets:\n");
			int aug_ctr = 0;
			for (int i = 0; i < p->aug_m; i++) {
				if (i > 0) {
					if (p->angles[i] != p->angles[i-1]) { // report position and angle every time angle changes (indicating new target)
						aug_ctr++;						
						printf("t:%d,x:%.2f,y:%.2f,a:%.2f\n",p->t+i*p->timestep,p->x_aug[aug_ctr],p->y_aug[aug_ctr],p->angles[i]);
						//printf("%d,%.2f,%.2f\n",p->t+i*p->timestep,p->x_aug[aug_ctr],p->y_aug[aug_ctr]);
					}
				}
			}		
		}
		p->num_moves = p->angles.size();
		p->num_speeds = p->speeds.size();	
	}

	if (p->t >= p->animal_aug_time) {
		if (p->move_animal_onlypos==0) {
			run_path(&p->angles, &p->speeds, &p->speed_times, p->num_moves, p->num_speeds, sim, p);	
		}
		else {
			move_animal_onlypos(sim, p, &p->angles, &p->speeds);
		}
	}
}

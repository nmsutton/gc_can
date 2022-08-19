/*
	movement sequences

	references: https://www.omnicalculator.com/math/right-triangle-side-angle
	https://www.mathsisfun.com/algebra/trig-finding-angle-right-triangle.html
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
	*/
	speed = speed * p->speed_conversion;
	if (p->speed_limit == 1 && speed > p->max_speed) {speed = p->max_speed;} // speed limit
	if (p->auto_speed_control || p->move_animal_onlypos) {
		p->move_increment = (0.001*speed);
		speed = speed * p->grid_pattern_scale;
		p->base_ext = 655;
		//if (speed<7.5) {p->base_ext=575;}
		p->speed_signaling = -.00034799225597907657+(.0081675325631652834*speed)+(.014970007271328412*pow(speed,2))-(.0017318129783734592*pow(speed,3))+(.000066887712315789088*pow(speed,4));
		p->spdin2in_curr = -7.6999999999504416+(0.87666666666074300*speed)+(-.023333333333160879*pow(speed,2));
		if (speed<=14) {p->spdin2in_curr=0;}
		if (speed>=20) {p->spdin2in_curr=0.5;}
		p->spdex2in_curr = 0.57963140405914459+(-0.076238844166134606*speed)+(0.024200128580085856*pow(speed,2))+(-0.0029881884411857643*pow(speed,3))+(0.00010282892540609924*pow(speed,4));
		if (speed<=3) {p->spdex2in_curr=0.5;}
		if (speed>=14) {p->spdex2in_curr=0;}
		//if (speed>10) {p->pc_level=400;} else {p->pc_level=1000;}
		//printf("%f %f\n",p->move_increment,speed);
	}
}

void EISignal(double angle, CARLsim* sim, P* p);

void run_path(vector<double> *moves, vector<double> *speeds, vector<int> *speed_times, int num_moves, int num_speeds, CARLsim* sim, P *p) {
	/*
		Move virtual animal through a predefined set of velocities (speeds+angles) to create a path.
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
	// stright line path
	//control_speed(50,p);
	double angle = 90;
	general_input(angle, sim, p);
	if (p->t % p->move_delay == 0) {
		control_speed(5,p);	
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

	if (p->move_animal_aug == 1 && p->t >= p->animal_aug_time) {}
	else {run_path(anim_angles, anim_speeds, &p->speed_times, p->num_moves, p->num_speeds, sim, p);}
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

void create_rand_loc(P* p, int rand_max, vector<int> loc_range) {
	int rand_loc;
	//vector<int> rand_loc_xy;
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
	if (p->t == p->animal_aug_time) {
		// clear old values
		p->speeds.clear();p->angles.clear();
		int fa_new, fa_old, fi_new, fi_old, x, y; // firing amounts and indices
		int rand_max = 0;
		int aug_time = (int) ceil(p->locations_sortind.size()*p->percent_for_aug);
		double x_pos = p->pos[0];
		double y_pos = p->pos[1];
		double xleg, yleg, angle, speed, last_speed, h, dist_away;
		vector<int> rand_loc_xy, loc_range;

		// copy vector
		for (int i = 0; i < p->locations_visited.size(); i++) {
			p->locations_amounts[i]=p->locations_visited[i];
			p->locations_sortind[i]=i;
		}
		// sort vectors
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
		
		//printf("locations sorted\n");
		for (int i = 0; i < p->locations_visited.size(); i++) {
			//printf("i:%d a:%d\n",p->locations_sortind[i],p->locations_amounts[i]);
		}
		for (int i = 0; i < p->locations_visited.size(); i++) {
			//printf("i:%d a:%d\n",i,p->locations_visited[i]);
		}
		
		// create target points
		// find total number of low visited locations
		for (int i = 0; i < aug_time; i++) {
			//rand_max = rand_max + p->locations_visited[i] + 1;
			rand_max = rand_max + 1;
			// TODO: add more chance of location target based on lowest locations_visited value
			loc_range.push_back(rand_max); // ranges for rand values
		}
		// generate list of target locations
		for (int i = 0; i < aug_time; i++) {
			create_rand_loc(p, rand_max, loc_range);
		}
		//printf("aug moves:\n");
		for (int i = 0; i < 20; i++) {
			//printf("x:%f y:%f\n",p->x_aug[i],p->y_aug[i]);
		}
		// generate movement to locations
		speed = 5;
		for (int i = 0; i < aug_time; i++) {
			p->aug_i++;
			// find angle to target
			xleg = x_pos - p->x_aug[i];
			yleg = y_pos - p->y_aug[i];
			h = sqrt(pow(xleg,2)+pow(yleg,2)); // triangle hypotenuse
			// find angle from leg and h including converting radians to degrees
			angle = asin(abs(yleg)/h)*(180/PI);
			// find 360 degree rotation
			if (xleg > 0 && yleg <= 0) {
				angle = 90 + angle;
			}
			else if (xleg < 0 && yleg < 0) {
				angle = 180 - angle;
			}
			else if (xleg < 0 && yleg > 0) {
				angle = 180 + angle;
			}

			// find new movement steps given speed
			dist_away = ceil(h / speed);
			for (int j = 0; j < dist_away; j++) {
				p->aug_i++;
				// store angles
				p->angles.push_back(angle);
				// store speeds
				if (j != dist_away - 1) {
					p->speeds.push_back(speed);
				}
				else {
					last_speed = h - (speed*(double) j); // lower speed for last step
					p->speeds.push_back(last_speed);
					//printf("%.2f %.2d %.2f %.2f\n",h,j,(speed*(double) j-2),last_speed);
				}
				p->speed_times.push_back(p->aug_i*p->firing_bin);

				if (i<20) {
					//printf("s:%.2f a:%.2f x1:%.2f y1:%.2f x2:%.2f y2:%.2f xleg:%.2f yleg:%.2f h:%.2f a:%.2f\n",p->speeds[i],p->angles[i],x_pos,y_pos,p->x_aug[i],p->y_aug[i],xleg,yleg,h,angle);	
				}				
			}			
			x_pos = p->pos[0];
			y_pos = p->pos[1];
		}
		for (int i = 0; i < 20; i++) {
			//printf("%f %f\n",p->speeds[i],p->angles[i]);
		}		
		p->num_moves = p->angles.size();
		p->num_speeds = p->speeds.size();	
	}

	if (p->t >= p->animal_aug_time) {
		run_path(&p->angles, &p->speeds, &p->speed_times, p->num_moves, p->num_speeds, sim, p);	
	}
}
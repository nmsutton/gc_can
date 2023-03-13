/*
	General functions

	References: https://stackoverflow.com/questions/34218040/how-to-read-a-csv-file-data-into-an-array
	https://iq.opengenus.org/split-string-in-cpp/
	https://www.mathsisfun.com/algebra/trig-finding-angle-right-triangle.html
	https://www.emathhelp.net/calculators/algebra-2/rotation-calculator/?px=20&py=20&a=-45&u=d&d=cw&qx=0&qy=0
	https://stackoverflow.com/questions/17530169/get-angle-between-point-and-origin
	https://math.stackexchange.com/questions/707673/find-angle-in-degrees-from-one-point-to-another-in-2d-space
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
				printf("[%.3f]",p->inec_weights[n][n]);	
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

double get_pd(int i, P *p) {	
	double pd = 0;
	int x = i % p->x_size;
	int y = i / p->x_size;

	if (y % 2 == 0) {
		if (x % 2 == 0) {pd = 180;}
		else {pd = 0;}
	}
	else {
		if (x % 2 == 0) {pd = 90;}
		else {pd = 270;}		
	}

	return pd;
}

double get_opp_pd(int i, P *p) {	
	/* returns opposite preferred direction */
	double pd;
	int x = i % p->x_size;
	int y = i / p->x_size;

	if (y % 2 == 0) {
		if (x % 2 == 0) {pd = 0;}
		else {pd = 180;}
	}
	else {
		if (x % 2 == 0) {pd = 270;}
		else {pd = 90;}		
	}

	return pd;
}

int wrap_around(int i, int max_size) {
	if (i<0) {i=i+max_size;}
	else if (i>=max_size) {i=i-max_size;}
	return i;
}

void wrap_around2(double* i, double max_size) {
	if (*i>=max_size) {*i=*i-max_size;}
	else if (*i<0) {*i=*i+max_size;}
}

double r2d(double angle) {
	// convert from radians to degrees

	angle = (angle/(2*PI))*360;

	return angle;
}

double d2r(double angle) {
	// convert from degrees to radians

	angle = (angle/360)*2*PI;

	return angle;
}

// int wrap_around_rot_rot(int i, int layer_size, double angle) {
void wrap_around_rot(double* xy, int layer_size) {
	/* 
		version of border wrap around with
		rotated borders
	*/

	//int i = 1599;
    //int layer_size = 40;
    double x = xy[0];
    double y = xy[1];
    double r_angle = 0;//-45;//-22.5;//-45;//-45; // make this parameter when in real use
    r_angle = r_angle * -1; // flip sign of angle for calculations.
    bool print_debug = false;

	//double x = double (i % layer_size) + 1;
	//double y = double (i / layer_size) + 1;
	//x = 60; y = 20;
	//x = 20; y = 60;
	//x = 48.2843; y = -8.2843;
	//x = 20; y = -20;
	//x = -8.2843; y = -8.2843;
	//x = -20; y = 20;
	//x = -8.2843; y = 48.2843;
	//x = -6.2843; y = -6.2843;
	//x = -10; y = 46;
	double x_new, y_new;
	double x_c = (layer_size*.5); // non-rotated border center axis
	double y_c = (layer_size*.5); // non-rotated border center axis
	bool outside_border = false;
	int bp = 0; // border point number. TR: 1, BR: 2, BL: 3, TL: 4.
	int s = 0; // section number
	r_angle = d2r(r_angle); // convert from degrees to radians
	double adj, opp, a_tr, a_br, a_bl, a_tl;
	double h_tr, h_br, h_bl, h_tl;

	// compute border points
	// original points
	double x_tr_o = (layer_size*.5);
	double y_tr_o = (layer_size*.5);
	double x_br_o = (layer_size*.5);
	double y_br_o = (layer_size*.5)*-1;
	double x_bl_o = (layer_size*.5)*-1;
	double y_bl_o = (layer_size*.5)*-1;
	double x_tl_o = (layer_size*.5)*-1;
	double y_tl_o = (layer_size*.5);
	double h = sqrt(pow((layer_size*.5),2)+pow((layer_size*.5),2)); // hypotenuse. length from center to border point.
	if (print_debug) {cout << "h " << h << "\n";}
	// rotated points
	// rotation around center is: x=x*cos(a)-y*sin(a); y=x*sin(a)+y*cos(a)
	double x_tr = x_c + x_tr_o*cos(r_angle)-y_tr_o*sin(r_angle);
	double y_tr = y_c + x_tr_o*sin(r_angle)+y_tr_o*cos(r_angle);
	double x_tl = x_c + x_tl_o*cos(r_angle)-y_tl_o*sin(r_angle);
	double y_tl = y_c + x_tl_o*sin(r_angle)+y_tl_o*cos(r_angle);
	double x_br = x_c + x_br_o*cos(r_angle)-y_br_o*sin(r_angle);
	double y_br = y_c + x_br_o*sin(r_angle)+y_br_o*cos(r_angle);
	double x_bl = x_c + x_bl_o*cos(r_angle)-y_bl_o*sin(r_angle);
	double y_bl = y_c + x_bl_o*sin(r_angle)+y_bl_o*cos(r_angle);
	if (print_debug) {cout << "r_angle " << r_angle << " x_br " << x_br << " y_br " << y_br << " (cos(r_angle)*h) " << (cos(r_angle)*h) << " cos(r_angle) " << cos(r_angle) << "\n";}

	// compute border area
	// remove rotation from position
	h = sqrt(pow((x-x_c),2)+pow((y-y_c),2));
	if (print_debug) {cout << "h2 " << h << "\n";}
	double x_nr = x_c + (x-x_c)*cos(r_angle)-(y-y_c)*sin(r_angle); // non-rotated position
	double y_nr = y_c + (x-x_c)*sin(r_angle)+(y-y_c)*cos(r_angle);
	if (print_debug) {cout << "x_nr " << x_nr << " y_nr " << y_nr << "\n";}
	// check for outside border
	if (x_nr < 0 || x_nr > layer_size || y_nr < 0 || y_nr > layer_size) {outside_border = true;}
	if (print_debug) {cout << "outside_border " << outside_border << "\n";}

	// check if position is outside of border
	if (outside_border) {

	// find wrap section
	// find angles to border points
	// angle = atan2(y,x) where y=y_b−y_a, x=x_b−x_a
	h_tr = sqrt(pow((x-x_tr),2)+pow((y-y_tr),2));
	adj = abs(x-x_tr); // adjacent border
	//a_tr = r2d(atan2(y_tr-y,x_tr-x)); // angle with border point as axis
	//a_tr = r2d(atan2(x_tr*y-y_tr*x,x_tr*x+y_tr*y));
	a_tr = r2d(atan2(y-y_tr,x-x_tr));
	h_br = sqrt(pow((x-x_br),2)+pow((y-y_br),2));
	adj = abs(x-x_br);
	//a_br = r2d(atan2(y_br-y,x_br-x)); // angle with border point as axis
	//a_br = r2d(atan2(d2r(x_br)*d2r(y)-d2r(y_br)*d2r(x),d2r(x_br)*d2r(x)+d2r(y_br)*d2r(y)));
	a_br = r2d(atan2(y-y_br,x-x_br));
	h_bl = sqrt(pow((x-x_bl),2)+pow((y-y_bl),2));
	adj = abs(x-x_bl);
	//a_bl = r2d(atan2(y_bl-y,x_bl-x)); // angle with border point as axis
	a_bl = r2d(atan2(y-y_bl,x-x_bl));
	h_tl = sqrt(pow((x-x_tl),2)+pow((y-y_tl),2));
	adj = abs(x-x_tl);
	//a_tl = r2d(atan2(y_tl-y,x_tl-x)); // angle with border point as axis
	a_tl = r2d(atan2(y-y_tl,x-x_tl));
	if(a_tr<0){a_tr+=360;}
	if(a_br<0){a_br+=360;}
	if(a_bl<0){a_bl+=360;}
	if(a_tl<0){a_tl+=360;}
	if (print_debug) {
	cout << "a_tr " << a_tr << " h_tr " << h_tr << " acos(adj/h_tr) " << acos(adj/h_tr) << " adj/h_br " << adj/h_br << " x_tr " << x_tr << " y_tr " << y_tr << " x " << x << " y " << y << "\n"; 
	cout << "a_br " << a_br << " h_br " << h_br << " acos(0) " << acos(0) << " adj/h_br " << adj/h_br << " x_br " << x_br << " y_br " << y_br << " x " << x << " y " << y << "\n"; 
	}

	// assign border point
	r_angle = r2d(r_angle);
	//tr >0 <=90
	//tr >90 <=180
	if      (a_tr <= 90+r_angle && a_tr > 0+r_angle) {bp = 1; s = 1;}
	//tr <=0 >=0 || tr<360 tr>=270 && br > 0 && br<=90
	//tr <=90 >=0 || tr<360 tr>=360 && br > 90 && br<=180
	else if (((a_tr <= 0+r_angle && a_tr >= 0) || (a_tr < 360 && a_tr >= 270+r_angle)) && 
			(a_br > 0+r_angle && a_br <= 90+r_angle)) {bp = 1; s = 2;}
	//br <=0 br>=0 || br<360 br>270
	//br <=90 br>=0 || br<360 br>360
	else if ((a_br <= 0+r_angle && a_br >= 0) || (a_br < 360 && a_br > 270+r_angle)) {bp = 2; s = 3;}
	//br <=270 br>=180 bl>270 bl<360 || bl>=0 bl<=0
	//br <=360 br>=270 bl>360 bl<360 || bl>=0 bl<=90
	else if ((a_br <= 270+r_angle && a_br >= 180+r_angle) && 
			((a_bl > 270+r_angle && a_bl < 360) || (a_bl >= 0 && a_bl <= 0+r_angle))) {bp = 2; s = 4;}
	//bl <=270 bl>180
	//bl <=360 bl>270
	else if (a_bl <= 270+r_angle && a_bl > 180+r_angle) {bp = 3; s = 5;}
	//bl <=180 bl>=90 tl>180 tl<=270
	//bl <=270 bl>=180 tl>270 tl<=360
	else if ((a_bl <= 180+r_angle && a_bl >= 90+r_angle) && 
			(a_tl > 180+r_angle && a_tl <= 270+r_angle)) {bp = 3; s = 6;}
	//tl <=180 tl>90
	//tl <=270 tl>180
	else if (a_tl <= 180+r_angle && a_tl > 90+r_angle) {bp = 4; s = 7;}
	//tl <=90 tl>=0 tr>90 tr<=180
	//tl <=180 tl>=90 tr>180 tr<=270
	else if ((a_tl <= 90+r_angle && a_tl >= 0+r_angle) && 
			(a_tr > 90+r_angle && a_tr <= 180+r_angle)) {bp = 4; s = 8;}
	if (print_debug) {cout << "bp " << bp << " s " << s << "\n";}

	// compute distance from border point
	double bp_dist = 0;
	if (bp == 1) {bp_dist = sqrt(pow((x-x_tr),2)+pow((y-y_tr),2));}
	else if (bp == 2) {bp_dist = sqrt(pow((x-x_br),2)+pow((y-y_br),2));}
	else if (bp == 3) {bp_dist = sqrt(pow((x-x_bl),2)+pow((y-y_bl),2));}
	else if (bp == 4) {bp_dist = sqrt(pow((x-x_tl),2)+pow((y-y_tl),2));}
	if (print_debug) {cout << "bp_dist " << bp_dist << " x_br " << x_br << " y_br " << y_br << "\n";}

	// compute angle from border point
	double a_bp;
	if (bp == 1) {a_bp = a_tr;}
	else if (bp == 2) {a_bp = a_br;}
	else if (bp == 3) {a_bp = a_bl;}
	else if (bp == 4) {a_bp = a_tl;}

	// find new border point
	// TR: 1, BR: 2, BL: 3, TL: 4
	int new_bp = 0;
	if      (s == 1) {new_bp = 3;}
	else if (s == 2) {new_bp = 4;}
	else if (s == 3) {new_bp = 4;}
	else if (s == 4) {new_bp = 1;}
	else if (s == 5) {new_bp = 1;}
	else if (s == 6) {new_bp = 2;}
	else if (s == 7) {new_bp = 2;}
	else if (s == 8) {new_bp = 3;}
	if (print_debug) {cout << "new_bp " << new_bp << "\n";}

	// output new position relative to new border point
	/*if      (new_bp==1) {a_bp = a_bl;}
	else if (new_bp==2) {a_bp = a_tl;}
	else if (new_bp==3) {a_bp = a_tr;}
	else if (new_bp==4) {a_bp = a_br;}*/
	if      (s==1) {a_bp = a_tr;}
	else if (s==2) {a_bp = a_tr;}
	else if (s==3) {a_bp = a_br;}
	else if (s==4) {a_bp = a_br;}
	else if (s==5) {a_bp = a_bl;}
	else if (s==6) {a_bp = a_bl;}
	else if (s==7) {a_bp = a_tl;}
	else if (s==8) {a_bp = a_tl;}
	if (print_debug) {cout << "a_bp " << a_bp << " bp_dist " << bp_dist << "\n";}
    
    //a_bp = a_bp * -1; // flip sign
	adj = cos(d2r(a_bp))*bp_dist;
	opp = sin(d2r(a_bp))*bp_dist;
	if      (new_bp==1) {x_new = x_tr + adj; y_new = y_tr + opp;}
	else if (new_bp==2) {x_new = x_br + adj; y_new = y_br + opp;}
	else if (new_bp==3) {x_new = x_bl + adj; y_new = y_bl + opp;}
	else if (new_bp==4) {x_new = x_tl + adj; y_new = y_tl + opp;}

	}
	else {x_new = x; y_new = y;}
	if (print_debug) {
	cout << "x_bl: " << x_bl << " y_bl: " << y_bl << " h_bl: " << h_bl << "\n";
	cout << "adj: " << adj << " opp: " << opp << "\n";
	cout << "x: " << x_new << " y: " << y_new << "\n";
	}

	//int i_new = (y_new*layer_size) + x_new;
	xy[0] = x_new; xy[1] = y_new;
}

vector<double> find_ver_hor(P *p, double angle, double* h) {
	//
	//	Translate angle and distance into proportion of horizonal and 
	//  vertical movement needed to create movement in the direction of the angle.
	//  Distance is hypotenuse of right triangle with ver (vertical rise)
	//  and hor (horizontal run) as sides. Given angle and hypotenuse the
	//  sides are found using the Pythagorean theorem. h = hypotenuse of triangle.
	//  Reference: https://www.mathsisfun.com/algebra/trig-finding-side-right-triangle.html
	//
	angle = (angle/360)*2*PI; // convert from degrees to radians
	//angle = ((angle+180)/360)*2*PI; // convert from degrees to radians
	vector<double> ver_hor; double x, y;

	if (angle < (PI/2)) {
		x = sin(angle) * *h;
		y = sqrt(pow(*h,2)-pow(x,2));
	}
	else if (angle >= (PI/2) and angle < PI) {
		x = cos(angle-(PI/2)) * *h;
		y = sqrt(pow(*h,2)-pow(x,2)) * -1;
	}
	else if (angle >= PI and angle < (PI*1.5)) {
		x = cos((PI*1.5)-angle) * *h * -1;
		y = sqrt(pow(*h,2)-pow(x,2)) * -1;
	}
	else if (angle >= (PI*1.5) and angle <= (PI*2)) {
		x = cos(angle-(PI*1.5)) * *h * -1;
		y = sqrt(pow(*h,2)-pow(x,2));
	}

	ver_hor.push_back(y);
	ver_hor.push_back(x);

	return ver_hor;
}

void set_pos(P *p, double angle) {
	/*
		Angle should be between 0-360 degrees.
	*/

	double xy[2];
	//angle = angle + 180;
	//angle = angle + p->grid_pattern_rot;
	vector<double> ver_hor = find_ver_hor(p, angle, &p->move_increment);
	if (p->move_animal==1 || p->move_animal_aug==1 || p->move_animal_onlypos==1) {
		ver_hor[0] = ver_hor[0] * p->grid_pattern_scale;
		ver_hor[1] = ver_hor[1] * p->grid_pattern_scale;
	}
	p->pos[0] = p->pos[0] + ver_hor[1];
	p->pos[1] = p->pos[1] + ver_hor[0];
	angle = angle + p->grid_pattern_rot;
	if (angle>360) {angle=360-angle;}
	if (angle<0)   {angle=angle+360;}
	ver_hor = find_ver_hor(p, angle, &p->move_increment);
	p->bpos[0] = p->bpos[0] + ver_hor[1];
	p->bpos[1] = p->bpos[1] + ver_hor[0];
	//printf("angle: %f %f ver_hor[1]:%f %f\n",angle,p->pos[0],ver_hor[1],p->move_increment);
	//printf("%f ver_hor[0]:%f %f\n",p->pos[1],ver_hor[1],p->move_increment);

	// wrap around twisted taurus
	wrap_around2(&p->pos[0], p->x_size);
	wrap_around2(&p->pos[1], p->y_size);
	/*xy[0]=p->pos[0];
	xy[1]=p->pos[1];	
	wrap_around_rot(xy, p->x_size);
	p->pos[0]=xy[0];
	p->pos[1]=xy[1];*/

	wrap_around2(&p->bpos[0], p->x_size);
	wrap_around2(&p->bpos[1], p->y_size);
	/*xy[0]=p->bpos[0];
	xy[1]=p->bpos[1];
	wrap_around_rot(xy, p->x_size);
	p->bpos[0]=xy[0];
	p->bpos[1]=xy[1];*/

	if (p->print_move == true) {
		cout << " move: " << angle << " " << p->pos[0] << " " << p->pos[1] << " t: " << p->t;
	}
}

double get_noise(P *p) {
	int rand_max = p->noise_rand_max;
	double scale = p->noise_scale;
	double centered_val = 1.0; // value to center random value around

	double rand_val = rand() % rand_max; // rand number up to rand_max
	rand_val = rand_val * scale; // scale to desired size
	rand_val = ((rand_max*scale)/2)-rand_val; // rand val centered at 0	
	rand_val = centered_val + rand_val; // rand val centered at centered_val
	if (rand_val < 0) {rand_val = 0;}
	//printf("rand_val: %f\n",rand_val);

	return rand_val;
}

void write_sel_nrn_spks(P* p, string n_type) {
	/*
		Write to file spikes from selected neuron to monitor
	*/
	if (n_type=="grid_cell") {
		p->spikes_output_file.close(); // reload file to save intermediate results
		p->spikes_output_file.open(p->spikes_output_filepath, std::ios_base::app);
		p->spikes_output_file << p->t;
		p->spikes_output_file << "\n";		
	}
	else if (n_type=="interneuron") {
		p->in_spikes_output_file.close();
		p->in_spikes_output_file.open(p->in_spikes_output_filepath, std::ios_base::app);
		p->in_spikes_output_file << p->t;
		p->in_spikes_output_file << "\n";		
	}
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
			if (spk_time >= (p->t - p->timestep) && spk_time <= p->t) {
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

void write_rate_map(double *firing_matrix, string output_folder, P *p) {
	ofstream output_file;
	//string filename = "output/" + output_folder + "/firing_t" + int_to_string(p->t) + ".csv";
	//string filename = "/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can/output/" + output_folder + "/firing_t" + int_to_string(p->t) + ".csv";
	string filename = "output/" + output_folder + "/firing_t" + int_to_string(p->t) + ".csv";
	output_file.open(filename);

	int i_f = 0; // firing index

	if (p->t != 0) {
		//for (int i = (p->x_size - 1); i >= 0; i--) {
		for (int i = 0; i < p->x_size; i++) {
			for (int j = 0; j < p->y_size; j++) {
				i_f = (i * p->x_size) + j;

				output_file << firing_matrix[i_f];

				if (j != (p->y_size -1)) {
					output_file << ",";
				}
			}
			//if (i != 0) {
			if (i != p->y_size) {
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
	*/
	if (p->move_animal_onlypos) {p->record_spikes_file=0;p->record_in_spikes_file=0;} // avoid extra spike file writing during onlypos
	if (p->record_fire_vs_pos || p->record_spikes_file) {
		int pi; // animal position index in GC layer
		int i = p->selected_neuron; // neuron selected to record
		int j = p->nrn_spk[i].size(); // all spikes of selected neuron

		if (j > 0 && p->nrn_spk[i][j-1] == p->t) { // get index from position
			if (p->record_fire_vs_pos) {
				pi = (floor(p->pos[1]) * p->x_size) + floor(p->pos[0]);
				//p->firing_positions[pi] = p->firing_positions[pi] + 1;		
			}
			if (p->record_spikes_file) {write_sel_nrn_spks(p, "grid_cell");}
		}
	}

	if (p->move_animal_aug) {
		int pi, j;

		if (p->t % p->timestep == 0) {
			pi = (floor(p->pos[1]) * p->x_size) + floor(p->pos[0]);
			p->locations_visited[pi] = p->locations_visited[pi] + 1;
			//printf("pi:%d a:%d\n",pi,p->locations_visited[pi]);
		}
	}

	if (p->record_in_spikes_file) {
		int i = p->selected_in_neuron; // neuron selected to record
		int j = p->in_nrn_spk[i].size(); // all spikes of selected neuron

		if (j > 0 && p->in_nrn_spk[i][j-1] == p->t) { // get index from position
			write_sel_nrn_spks(p, "interneuron");
		}
	}

	//if (p->record_fire_vs_pos) {write_rate_map(p->firing_positions, "firing_vs_loc", p);}
}

void HighResTraj(CARLsim* sim, P* p) {
	/* 
		Record high resolution position data of spikes. 
	*/
	
	p->highres_pos_x_file << p->pos[0];
	p->highres_pos_x_file << "\n";
	p->highres_pos_y_file << p->pos[1];
	p->highres_pos_y_file << "\n";	
	
	/*
	if (p->t % 5000 == 0 || p->t == (int) (p->sim_time-1)) {
		p->highres_pos_x_file << p->pos_x.str();
		p->highres_pos_y_file << p->pos_y.str();
		p->pos_x.str("");
		p->pos_y.str("");
	}
	else {
		p->pos_x << p->pos[0];
		p->pos_x << "\n";
		p->pos_y << p->pos[1];
		p->pos_y << "\n";
	}
	*/
}

void RecordLocationPath(P *p, string rec_type) {
	double pos_i = (floor(p->pos[1]) * p->x_size) + floor(p->pos[0]);
	//printf("x:%f y:%f\n",p->pos[0],p->pos[1]);

	for (int i = 0; i < p->layer_size; i++) {
		if (rec_type != "all") {
			if (i == pos_i) {
				p->animal_location[i] = p->al_act_lvl;
			}
			else {
				p->animal_location[i] = 0;
			}
		}
		else if (i == pos_i) {
			p->animal_location_all[i] = p->animal_location_all[i] + p->ala_act_lvl;
		}
	}

	if (rec_type != "all") {
		write_rate_map(p->animal_location, "pos_track", p);
	}
	else {
		write_rate_map(p->animal_location_all, "pos_track_all", p);
	}
}

void setInExcConns(CARLsim* sim, P *p) {
	// set inital connection status (0 or 1) in 2d weight matrix for IN->GC connections
	int counter = 0;

	// assign connectivity
	for (int i = 0; i < p->layer_size; i++) {
		for (int j = 0; j < p->layer_size; j++) {
			//if (mex_hat[i][j] != 0.0) {
			//if ((double) mex_hat[i][j] >= 0.006) {
			if ((double) mex_hat[i][j] >= 0.002) {
				p->weights_in[i][j] = 1;
				//printf("i:%d j:%d\n",i,j);
				counter++;
			}
		}
	}
	printf("counter:%d\n",counter);
}

// custom ConnectionGenerator
class MexHatConnection : public ConnectionGenerator {
public:
    vector<vector<double>> weights_in;
    double mex_hat_multi;
    int conn_offset, conn_dist;
    MexHatConnection(P *p) {
    	this->weights_in = p->weights_in; // set matrix
    	this->mex_hat_multi = p->mex_hat_multi;
    	this->conn_offset = p->conn_offset;
    	this->conn_dist = p->conn_dist;
    }
    ~MexHatConnection() {}
 
    // the pure virtual function inherited from base class
    // note that weight, maxWt, delay, and connected are passed by reference
    void connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j, float& weight, float& maxWt,
            float& delay, bool& connected) {
    		// adjust i for multiple neuron types combine into a group
    		int i_adj = (i * this->conn_dist) + this->conn_offset;

    		// assign connections
    		//if (this->weights_in[i][j] == 1.0) {
    		if (this->weights_in[i_adj][j] == 1.0) {
    			connected = 1; // only connect where matrix value is 1.0 
    			/*if (i_adj>899) {
    				printf("i:%d j:%d i_adj:%d\n",i,j,i_adj);
    			}*/
    			//printf("i:%d j:%d i_adj:%d\n",i,j,i_adj);
    		}
    		else {
    			connected = 0;
    		}
        //weight = mex_hat[i][j]*mex_hat_multi;
        weight = mex_hat[i_adj][j]*mex_hat_multi;
        weight = weight + -0.012;//-0.022;//-0.042;//-0.012;//-0.022;//0.5;//0.0;                
        //weight = mex_hat[i_adj][j]*mex_hat_multi;
        //if (weight < 0) {weight = 0;}
        maxWt = 10000.0f;
        delay = 1; 
    }
};

class SomeToSomeConnection : public ConnectionGenerator {
public:
    vector<vector<double>> weights_in;
    double mex_hat_multi;
    int conn_offset, conn_dist;
    float gc_to_in_wt;
    int x_size; int y_size;
    SomeToSomeConnection(P *p) {
    	this->weights_in = p->weights_in; // set matrix
    	this->mex_hat_multi = p->mex_hat_multi;
    	this->conn_offset = p->conn_offset;
    	this->conn_dist = p->conn_dist;
    	this->gc_to_in_wt = p->gc_to_in_wt;
    	this->x_size = p->x_size;
    	this->y_size = p->y_size;
    }
    ~SomeToSomeConnection() {}
 
    // the pure virtual function inherited from base class
    // note that weight, maxWt, delay, and connected are passed by reference
    void connect(CARLsim* sim, int srcGrp, int i, int destGrp, int j, float& weight, float& maxWt,
            float& delay, bool& connected) {
    		// adjust i and j for multiple neuron types combine into a group
    		//int i_adj = (i * this->conn_dist) + this->conn_offset;
    		//int j_adj = (j * this->conn_dist) + this->conn_offset;   
    		int j_sft; // shifted index 	
    		double xy[2];
    		//vector<int> shift_x{0, -17, 17,   4, -4, 11, -11}; 
    		//vector<int> shift_y{0,   4, -4, -17, 17, 11, -11}; 
    		//vector<int> shift_x{0, -14, 14,   4, -4, 10, -10}; 
    		// vector<int> shift_y{0,   4, -4, -14, 14, 10, -10}; 
    		// vector<int> shift_x{0, -14, 14,   4, -4, 12, -12}; 
    		//vector<int> shift_y{0,   4, -4, -14, 14, 9, -9};
    		// vector<int> shift_x{0, -14, 14,   4, -4}; 
    		// vector<int> shift_y{0,   4, -4, -14, 14};
    		//vector<int> shift_x{0, -14, 14}; 
    		//vector<int> shift_y{0,   4, -4}; 
    		//vector<int> shift_x{0, 0,  -1, 16}; 
    		//vector<int> shift_y{0, 14, -7,  7}; 
    		//vector<int> shift_x{0, 0,  -14,  6}; 
    		//vector<int> shift_y{0, 14, -8,  -6}; 
    		//vector<int> shift_x{0,   0,  0}; 
    		//vector<int> shift_y{0, -14, 14};
    		// vector<int> shift_x{0,  -8,  8}; 
    		// vector<int> shift_y{0, -14, 14};
    	    // vector<int> shift_x{0,  -8,  8, -14}; 
    		// vector<int> shift_y{0, -14, 14, 0};
			//vector<int> shift_x{0, -14, 14}; 
    		//vector<int> shift_y{0, 0, 0};
    		// vector<int> shift_x{0,  -12,  12}; 
    		// vector<int> shift_y{0, -8, 8};
    		// vector<int> shift_x{0,  10,  10}; 
    		// vector<int> shift_y{0, -10, 10};
    		// vector<int> shift_x{0,  -21}; 
    		// vector<int> shift_y{0, -8};
    		// vector<int> shift_x{0,  -11,  11}; 
    		// vector<int> shift_y{0, -5, 5};
			// vector<int> shift_x{0, 22,  8, -14}; 
    		// vector<int> shift_y{0, 13, 14,   0};
    	    // vector<int> shift_x{0,  -8,  8, -16}; 
    		// vector<int> shift_y{0, -14, 14, 0};  
    		// vector<int> shift_x{0,  -12,  12}; 
    		// vector<int> shift_y{0, -20, 20};  		
    		// vector<int> shift_x{0,  -10,  10}; 
    		// vector<int> shift_y{0, -11, 11};
    		// vector<int> shift_x{0,  -11,  11}; 
    		// vector<int> shift_y{0, -11, 11};
    		// vector<int> shift_x{0,  -11,  11, -32, 32}; 
    		// vector<int> shift_y{0, -11, 11, 11, 11};
    		// vector<int> shift_x{0,  -11,  11, -32, 32, 0}; 
    		// vector<int> shift_y{0, -11, 11, 11, 11, -21};
    		// vector<int> shift_x{0,  -11,  11}; 
    		// vector<int> shift_y{0, -11, 11};
    		// vector<int> shift_x{0,  -9, 9, -27, 27}; 
    		// vector<int> shift_y{0, -9, 9, -9, 9};
    		// vector<int> shift_x{0,  -9,  9}; 
    		// vector<int> shift_y{0, -9, 9};
    		// vector<int> shift_x{0,  -10,  10, -30, 30, 20, 20}; 
    		// vector<int> shift_y{0, -10, 10, -10, 10, 0, 20};
    		// vector<int> shift_x{0, 20, -10, 30, 10, 20, 40, -31}; 
    		// vector<int> shift_y{0,  0, -10,  9, 10,  0,  0, -13};
    		// vector<int> shift_x{0, -10, 10}; 
    		// vector<int> shift_y{0, -10, 10};
    		// vector<int> shift_x{0, -2, 2}; 
    		// vector<int> shift_y{0, -2, 2};
    		// vector<int> shift_x{0, -2, 2,  2, -2}; 
    		// vector<int> shift_y{0, -2, 2, -2,  2};
    		// vector<int> shift_x{0, -2, 2,  2, -2, -4, 4, 4, -4}; 
    		// vector<int> shift_y{0, -2, 2, -2,  2, -4, 4, -4, 4};
    		// vector<int> shift_x{0, -2, 2,  2, -2, 2, -2, 0,  0}; 
    		// vector<int> shift_y{0, -2, 2, -2,  2, 0,  0, 2, -2};
    		// vector<int> shift_x{0, -3, 3}; 
    		// vector<int> shift_y{0, -3, 3};
    		// vector<int> shift_x{0, -8, 8}; 
    		// vector<int> shift_y{0, -14, 14};
    		// vector<int> shift_x{0, -6,   6,   6, -6}; 
    		// vector<int> shift_y{0, -10, 10, -10, 10};
    		// vector<int> shift_x{0, -6,   6,   6, -6, 10, -10}; 
    		// vector<int> shift_y{0, -10, 10, -10, 10,  0,   0};
    		// vector<int> shift_x{0, -6,   6,   6, -6}; 
    		// vector<int> shift_y{0, -10, 10, -10, 10};
    		// vector<int> shift_x{0, -6,   6}; 
    		// vector<int> shift_y{0, -10, 10};
    		// vector<int> shift_x{0, -10, 10,  10, -10}; 
    		// vector<int> shift_y{0, -10, 10, -10,  10};
    		// vector<int> shift_x{0, -6,   6,   6, -6}; 
    		// vector<int> shift_y{0, -6, 6, -6, 6};
    		// vector<int> shift_x{0, -12, 12}; 
    		// vector<int> shift_y{0, -14, 14};
    		// vector<int> shift_x{0, -6, 6, 6, -6}; 
    		// vector<int> shift_y{0, -8, 8, -8, 8};
    		// vector<int> shift_x{0, -6, -6}; 
    		// vector<int> shift_y{0, -8,  8};
    		// vector<int> shift_x{0, -6, -4}; 
    		// vector<int> shift_y{0, -8, -6};
    		// vector<int> shift_x{0, -6, 6, 6, -6,   0,  0}; 
    		// vector<int> shift_y{0, -8, 8, -8, 8, -14, 14};
    		// vector<int> shift_x{0, -8, 8}; 
    		// vector<int> shift_y{0, -12, 12};
    		// vector<int> shift_x{0, -8, 8}; 
    		// vector<int> shift_y{0, -12, 12};
    		// vector<int> shift_x{0, -14, 14}; 
    		// vector<int> shift_y{0,  -6,  6};
    		// vector<int> shift_x{0, -14, 14, 10, -10}; 
    		// vector<int> shift_y{0,  -6,  6, -10,   10};
    		// vector<int> shift_x{0, -14, 14, 12}; 
    		// vector<int> shift_y{0,  -6,  6, -8};
    		// vector<int> shift_x{0, -14, 14, 12, -12}; 
    		// vector<int> shift_y{0,  -6,  6, -8,   8};
    		// vector<int> shift_x{0, -14, 14, 12, -12, 0,  22}; 
    		// vector<int> shift_y{0,  -6,  6, -8,   8, 15, 14};
    		// vector<int> shift_x{0, -14, 14, 12, -12, 0}; 
    		// vector<int> shift_y{0,  -6,  6, -8,   8, 15};
    		// vector<int> shift_x{0, -14, 14, 12, -12, 2}; 
    		// vector<int> shift_y{0,  -6,  6, -8,   8, 14}; 
    		// vector<int> shift_x{0, -14, 14, 12, -12, 2, -2}; 
    		// vector<int> shift_y{0,  -6,  6, -8,   8, 14, -14};
    		// vector<int> shift_x{0, -14, 14}; 
    		// vector<int> shift_y{0,  -6,  6};
    		// vector<int> shift_x{0, -14, 14, 11, -11}; 
    		// vector<int> shift_y{0,  -6,  6, -9,   9};
    		// vector<int> shift_x{0, -14, 14, 10}; 
    		// vector<int> shift_y{0,  -6,  6, -10};
    		// vector<int> shift_x{0, -14, 14, 10, -10, -2, 2}; 
    		// vector<int> shift_y{0,  -6,  6, -10,   10, -14, 14};
    		// vector<int> shift_x{0, -14, 14, 7, -11}; 
    		// vector<int> shift_y{0,  -6,  6, -13, 9};
    		// vector<int> shift_x{0, -10, 10}; 
    		// vector<int> shift_y{0, -10, 10};
    		// vector<int> shift_x{0, -12, 12}; 
    		// vector<int> shift_y{0, -8, 8};
    		// vector<int> shift_x{0, 7, -11}; 
    		// vector<int> shift_y{0, -13, 9};
    		// vector<int> shift_x{0, -12, 12}; 
    		// vector<int> shift_y{0,  -8,  8};
    		// vector<int> shift_x{0, -12, 12, -2}; 
    		// vector<int> shift_y{0,  -6,  6, 12};
    		// vector<int> shift_x{0, -10, 10,  2}; 
    		// vector<int> shift_y{0,   6, -6, 12};
    		// vector<int> shift_x{0, -10, 10,  6}; 
    		// vector<int> shift_y{0,   6, -6, 14};
    		// vector<int> shift_x{0, -14, 14, -2, 2}; 
    		// vector<int> shift_y{0,   4, -4, 14, -14};
    		// vector<int> shift_x{0, -4, 4}; 
    		// vector<int> shift_y{0, 14, -14};
    		// vector<int> shift_x{0, -4, 4}; 
    		// vector<int> shift_y{0, -14, 14};
    		// vector<int> shift_x{0, -2,   2, -12}; 
    		// vector<int> shift_y{0, -10, 10,  -2};
    		// vector<int> shift_x{0, -2,   2, -12}; 
    		// vector<int> shift_y{0, -10, 10,  -2};
    		// vector<int> shift_x{0, -2,   2, -12, 12}; 
    		// vector<int> shift_y{0, -10, 10,  -2,  2};
    		// vector<int> shift_x{0, -4,   4, -12}; 
    		// vector<int> shift_y{0, -14, 14,  -4};
    		// vector<int> shift_x{0, -2,   2, -14, 14}; 
    		// vector<int> shift_y{0, -10, 10, -4, 4};
    		// vector<int> shift_x{0, -12, 12}; 
    		// vector<int> shift_y{0, -12, 12};
    		// vector<int> shift_x{0,  0, -10,  10}; 
    		// vector<int> shift_y{0, 20, -20, -20};
    		// vector<int> shift_x{0, -10,  10}; 
    		// vector<int> shift_y{0, -20, -20};
    		// vector<int> shift_x{0, -20,  20}; 
    		// vector<int> shift_y{0, -10, -10};
    		// vector<int> shift_x{0,  20,  20}; 
    		// vector<int> shift_y{0,  10,  -10};
    		// vector<int> shift_x{0, 20};
    		// vector<int> shift_y{0, 0};
    		// vector<int> shift_x{0,  22,  22}; 
    		// vector<int> shift_y{0,  10,  -10};
    		// vector<int> shift_x{0,  10,  10, 30,  30}; 
    		// vector<int> shift_y{0,  10, -10, 10, -10};
    		// vector<int> shift_x{0,  10,  10, 30,  30}; 
    		// vector<int> shift_y{0,  12, -12, 12, -12};
    		// vector<int> shift_x{0,  8,  8, 32,  32}; 
    		// vector<int> shift_y{0,  10, -10, 10, -10};
    		// vector<int> shift_x{0,  10, 30}; 
    		// vector<int> shift_y{0, -16, 16};
    		// vector<int> shift_x{0, -8, 8}; 
    		// vector<int> shift_y{0, -12, 12};
    		// vector<int> shift_x{0, -6, 6}; 
    		// vector<int> shift_y{0, -12, 12};
    		// vector<int> shift_x{0, -6,   6,  10, -10}; 
    		// vector<int> shift_y{0, -12, 12, -10,  10};
    		// vector<int> shift_x{0,   0,  0,  12, -12}; 
    		// vector<int> shift_y{0, -10, 10, -4,  4};
    		// vector<int> shift_x{0,   0,  0,  12, -12}; 
    		// vector<int> shift_y{0, -10, 10, -6,  6};
    		// vector<int> shift_x{0, -10, 10,   4,  -4}; 
    		// vector<int> shift_y{0,   0,  0, -10,  10};
    		// vector<int> shift_x{0, -8, 8}; 
    		// vector<int> shift_y{0, -12, 12};
    		// vector<int> shift_x{0, -8, 8, -6, 6}; 
    		// vector<int> shift_y{0, -10, 10, 8, -8};
    		// vector<int> shift_x{0, -8, 8, -6, 6}; 
    		// vector<int> shift_y{0, -10, 10, 12, -12};
    		// vector<int> shift_x{0, -8, 8, -4, 4}; 
    		// vector<int> shift_y{0, -10, 10, 12, -12};
    		// vector<int> shift_x{0, -12, 12, 0, 0}; 
    		// vector<int> shift_y{0, -8, 8, 12, -12};
    		// vector<int> shift_x{0, -8, 8, 12, -12}; 
    		// vector<int> shift_y{0, -12, 12, 0, 0};
    		// vector<int> shift_x{0, -6, 6, 12, -12}; 
    		// vector<int> shift_y{0, -12, 12, 0, 0};
    		// vector<int> shift_x{0, -6, 6, 12, -12, 6, -6}; 
    		// vector<int> shift_y{0, -12, 12, 0, 0, -12, 12};
    		// vector<int> shift_x{0, -6, 6}; 
    		// vector<int> shift_y{0, -12, 12};
    		// vector<int> shift_x{0, -8, 8, 12, -12}; 
    		// vector<int> shift_y{0, -12, 12, 0, 0};
    		vector<int> shift_x{0, -8, 8}; 
    		vector<int> shift_y{0, -12, 12};
    		// vector<int> shift_x{0}; 
    		// vector<int> shift_y{0};

    		// assign connections
    		/*if (i == ((j * this->conn_dist) + this->conn_offset)) {
    			connected = 1;
    			//printf("i:%d j:%d\n",i,j);
    		}*/
    		/*else {
    			connected = 0;
    		}*/    		
    		j_sft = ((j * this->conn_dist) + this->conn_offset);    		
    		int ix = i % x_size;
    		int iy = i / x_size;
    		int jx = j_sft % x_size;//j % x_size;
    		int jy = j_sft / x_size;//j / x_size;
    		int max_dist = 3;//5; 
    		double wt_fade = 0;
    		double dist = sqrt((pow((jx-ix),2))+(pow((jy-iy),2)));
    		ix = wrap_around(ix,x_size); iy = wrap_around(iy,x_size);
    		jx = wrap_around(jx,x_size); jy = wrap_around(jy,x_size);
    		/*xy[0]=ix;xy[1]=iy;
    		wrap_around_rot(xy,x_size);
    		ix=xy[0];iy=xy[1];
    		xy[0]=jx;xy[1]=jy;
    		wrap_around_rot(xy,x_size);
    		jx=xy[0];jy=xy[1];*/
    		connected = 0;
    		
    		for (int i2 = 0; i2 < shift_x.size(); i2++) {
    			j_sft = (((double) j * (double) this->conn_dist) + (double) this->conn_offset) + ((shift_y[i2]*(double) x_size)+shift_x[i2]);
    			j_sft = wrap_around(j_sft,(x_size*y_size));
    			/*xy[0] = j_sft % x_size;//j % x_size;
    			xy[1] = j_sft / x_size;//j / x_size;
    			wrap_around_rot(xy,x_size);
    			j_sft = (xy[1]*x_size) + xy[0];*/
    			if (i == j_sft) {
    				//if ((int)ix%2==(int)jx%2&&(int)iy%2==(int)jy%2) {
						connected = 1;
						//printf("i:%d j:%d j_sft:%d cx1:%d cy1:%d\n",i,j,j_sft,shift_y[i2],shift_x[i]);
    				//}
    			}
    		}
    		/*
    		//if (dist==0) {//<1) {    		
    		if (dist<=max_dist) {
    			if (ix%2==jx%2&&iy%2==jy%2) {
    				connected = 1;
    				if (i==820) {printf("jx:%d jy:%d\n",jx,jy);}
    			}
    		}
    		*/
        weight = gc_to_in_wt;
    	/*if (dist!=0&&max_dist!=0) { 
    		wt_fade = dist/max_dist;
    	}
    	weight = gc_to_in_wt*(1-wt_fade);*/
        maxWt = 10000.0f;
        delay = 1; 
    }
};

void setInitExtDir(P* p) {
	for (int i = 0; i < p->layer_size; i++) {
		ext_dir_initial[i] = ext_dir_initial[i]*p->dir_init_multi;
	}
}

vector<double> directional_speeds(P* p, double angle, double speed) {
	/*
		This function translates an angle and speed into what speed in 
		4 compass directions (N,E,S,W) can create that movement.
	*/
	p->current_angle = angle; // current_angle is tracked before rotation_mod
	if (p->rotation_mod) {
		angle = angle + (sin(((angle-45)/360)*4*PI) * p->angle_rot);
	}
	double speed_adj = speed;
	if (speed == 0) {
		speed_adj = 0; // avoid pow(0,0) when result of 0 is wanted
	}
	vector<double> ver_hor = find_ver_hor(p, angle, &speed_adj);
	double ver = ver_hor[0];
	double hor = ver_hor[1];
	double N,E,S,W;N=1;E=1;S=1;W=1;

	if (ver >= 0) {
		N += abs(ver);
	}
	else {
		S += abs(ver);
	}
	if (hor <= 0) {
		E += abs(hor);
	}
	else {
		W += abs(hor);
	}
	vector<double> speeds = {N,E,S,W};
	//vector<double> speeds = {E,N,W,S};
	//printf("t:%d N:%f E:%f S:%f W:%f h:%f v:%f s:%f r:%f\n",p->t,N,E,S,W,hor,ver,speed,speed_adj);

	return speeds;
}

void setExtDir(P* p, double angle, double speed, int sc) {
	double noise;	
	angle = angle + p->grid_pattern_rot;
	//if (sc == 2) {angle=angle+180;} // TODO: this is a fix for speed cells but could look into if this could be modeled better
	if (angle>360) {angle=360-angle;}	
	if (angle<0)   {angle=angle+360;}	
	vector<double> speeds = directional_speeds(p, angle, speed);
	if (sc == 1) {speeds[0]=speed;speeds[1]=speed;speeds[2]=speed;speeds[3]=speed;}	
	if (sc == 2) {for (int i = 0; i < 4; i++) {speeds[i]--;}}
	//if (sc == true) {speeds[0]=0.01;speeds[1]=0.01;speeds[2]=0.01;speeds[3]=0.01;}

	double base_ext = p->base_ext;
	for (int i = 0; i < p->layer_size; i++) {
		if (get_pd(i, p) == 180) {
			//p->ext_dir[i] = p->base_ext*speeds[0];
			if (p->noise_active) {noise = get_noise(p);base_ext = base_ext*noise;}
			p->ext_dir[i] = base_ext*speeds[0];
		}
		else if (get_pd(i, p) == 270) {
			//p->ext_dir[i] = p->base_ext*speeds[1];
			if (p->noise_active) {noise = get_noise(p);base_ext = base_ext*noise;}
			p->ext_dir[i] = base_ext*speeds[1];
		}
		else if (get_pd(i, p) == 0) {
			//p->ext_dir[i] = p->base_ext*speeds[2];
			if (p->noise_active) {noise = get_noise(p);base_ext = base_ext*noise;}
			p->ext_dir[i] = base_ext*speeds[2];
		}
		else if (get_pd(i, p) == 90) {
			//p->ext_dir[i] = p->base_ext*speeds[3];
			if (p->noise_active) {noise = get_noise(p);base_ext = base_ext*noise;}
			p->ext_dir[i] = base_ext*speeds[3];
		}
	}

	// noise
	/*if (p->noise_active) {
		for (int i = 0; i < p->layer_size; i++) {		
			noise = get_noise(p); // add random noise for realism
			p->ext_dir[i] = p->ext_dir[i]*noise; // change external input by noise value
		}
	}*/
	
	//printf("t:%d n:%f e:%f s:%f w:%f\n",p->t,speeds[0],speeds[1],speeds[2],speeds[3]);
}

void general_input(double angle, CARLsim* sim, P* p) {
	set_pos(p, angle);

	// place cell input
	place_cell_firing(sim, p);
}

void EISignal(double angle, CARLsim* sim, P* p) {
	/*
		Apply external input
	*/	
	count_firing(p, p->gc_firing_bin, p->nrn_spk);
	if (p->print_move) {cout << "\n";}

	// set velocity of movement
	if (p->t > 2) {
		//printf("ext input\n");
		setExtDir(p,angle,p->speed_signaling,0);//0.20);
		sim->setExternalCurrent(p->EC_LI_II_Multipolar_Pyramidal_Group, p->ext_dir);
		//printf("p->ext_dir: %f\n",p->ext_dir);
		//printf("speed cells\n");
		if (p->spin2in_active) {
			setExtDir(p,angle,p->spdin2in_curr,2);//100.0,1);//0.075,1);//0.20);
			//setExtDir(p,angle,0.0,2);
			sim->setExternalCurrent(p->MEC_LII_Basket_Speed_Group, p->ext_dir);
		}
		if (p->spex2in_active) {	
			setExtDir(p,angle,p->spdex2in_curr,1);//100.0,1);//0.075,1);//0.20);
			sim->setExternalCurrent(p->MEC_LII_Stellate_Speed_Group, p->ext_dir);
			/*vector<float> ext_dir2;
			for (int i = 0; i < 300; i++) {
				//ext_dir2.push_back(ext_dir[i]);
				ext_dir2.push_back(50.0);
			}
			sim->setExternalCurrent(p->MEC_LII_Stellate_Speed_Group, ext_dir2);*/
		}
	}	
}

vector<double> SplitStr(string str)
{
	vector<double> entries;
	string deli = ",";
    int start = 0;
    int end = str.find(deli);
    while (end != -1) {
        entries.push_back(stod(str.substr(start, end - start)));
        start = end + deli.size();
        end = str.find(deli, start);
    }
    entries.push_back(stod(str.substr(start, end - start)));

    return entries;
}

vector<double> ParseCSV(string filepath)
{
    ifstream data(filepath);
    string line;
    vector<double> parsedRow;
	if(!data.is_open()) {cout << "Failed to open file" << endl;}
    while(getline(data,line)) {parsedRow.push_back(stod(line));}

    return parsedRow;
};

void ParseCentSurrCSV(string filepath, vector<vector<double>> *cent_surr)
{
	ifstream data(filepath);
    string line;
    vector<double> parsedRow;
	if(!data.is_open()) {cout << "Failed to open file" << endl;}
	while(getline(data,line)) {cent_surr->push_back(SplitStr(line));}
};
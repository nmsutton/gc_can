/*
	Place cell functions

	These methods are modified versions of ones used in (solanka et al., 2015)
	One modification is that boundary cell input to place cells is limited to
	a local region around the active place cell. This prevents boundary cell
	signal from simply making an increase in signal of all place cells 
	indiscriminately.
*/

double get_distance(int x1, int y1, int x2, int y2, char pd, P *p) {
	// d = sqrt((e_x - i_x - o_x)^2+(e_y - i_y - o_y)^2)
	double x2_x1 = (x2 - x1);
	double y2_y1 = (y2 - y1);
	double half_point = p->x_size / 2; // layer length divided by 2

	// preferred direction bias
	if (pd == 'u') {
		y2_y1 = y2_y1 - 1;
	}
	if (pd == 'd') {
		y2_y1 = y2_y1 + 1;
	}
	if (pd == 'r') {
		x2_x1 = x2_x1 - 1;
	}
	if (pd == 'l') {
		x2_x1 = x2_x1 + 1;
	}	

	// torus wrap around
	if (abs(x2_x1) >= half_point) {
		// distance wraps half way around
		x2_x1 = (p->x_size - abs(x2_x1));
	}
	if (abs(y2_y1) >= half_point) {
		y2_y1 = (p->y_size - abs(y2_y1));
	}

	double d = sqrt(pow(x2_x1,2)+pow(y2_y1,2));

	return d;
}

double pc_rate(int p_x, int p_y, int b_x, int b_y, P *p) {
	double d = get_distance(p_x, p_y, b_x, b_y, 'n', p);

	double rate = p->pc_level * exp(-((pow(d,2))/(2*pow(p->pc_sig,2))));

	return rate;
}

void place_cell_firing(CARLsim* sim, P *p) {
	/*
		generate place cell firing
	*/

	int bump_x, bump_y, cb_x, cb_y, gc_i; 
	int closest_bump = -1; 
	double cb_dist = -1;
	double cb_dist_new = -1;
	double pc_firing, bc_firing;

	for (int p_y = 0; p_y < p->y_size; p_y++) {
		for (int p_x = 0; p_x < p->x_size; p_x++) {

			// find closest bump
			/*closest_bump = -1;
			for (int b_i = 0; b_i < p->num_bumps; b_i++) {				
				bump_x = p->pos[0] + ((b_i % p->bumps_x) * p->bump_dist); // closest bump x
				bump_y = p->pos[1] + ((b_i / p->bumps_y) * p->bump_dist);
				// adjust for staggering bump pattern
				if (((b_i / p->bumps_y)+1) % 2 == 0) {
					bump_x = bump_x + (p->bump_dist/2);
				}
				cb_dist_new = get_distance(p_x, p_y, bump_x, bump_y, 'n', p);

				if (closest_bump == -1) {
					closest_bump = b_i;
					cb_dist = cb_dist_new;
					cb_x = bump_x;
					cb_y = bump_y;
				}
				else if (cb_dist_new < cb_dist) {
					closest_bump = b_i;
					cb_dist = cb_dist_new;	
					cb_x = bump_x;
					cb_y = bump_y;			
				}
			}*/		
			cb_x = bump_x = p->pos[0];
			cb_y = bump_y = p->pos[1];

			// find firing
			pc_firing = 0.0;
			if (cb_dist < p->dist_thresh) {
				if (p->pc_active) {
					pc_firing = pc_rate(p_x, p_y, cb_x, cb_y, p);
				}

				// add boundary cell input
				/*
				if (p->bc_to_pc) {
					bc_firing = bc_for_pc(p_x, p_y, cb_x, cb_y, p);
					pc_firing = pc_firing + bc_firing;
				}
				*/
			}

			gc_i = (p_y * p->x_size) + p_x;
			p->pc_activity[gc_i] = pc_firing;
		}
	}

	sim->setExternalCurrent(3, p->pc_activity);
}
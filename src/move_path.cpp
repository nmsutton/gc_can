/*
	movement sequences
*/

char rand_move() {
	int num_directions = 5;
	int rand_val = rand() % num_directions + 1;
	char direction;

	if (rand_val == 1) {
		direction = 'u';
	}
	else if (rand_val == 2) {
		direction = 'r';
	}
	else if (rand_val == 3) {
		direction = 'd';
	}
	else if (rand_val == 4) {
		direction = 'l';
	}
	else if (rand_val == 5) {
		direction = 'n'; // stopped
	}

	return direction;
}

double rand_speed(P *p) {
	double scale = 0.01;
	double max = p->max_speed;
	double min = p->min_speed;
	int rand_val = (min*(1/scale));
	int addit_sig = (max-min)*(1/scale); // additional speed signal
	if (addit_sig > 0) {
		rand_val = rand_val + (rand() % addit_sig);
	}

	return (double) rand_val * scale;
}

void EISignal(char direction, CARLsim* sim, P* p);

void create_move(char dir, CARLsim* sim, P* p) {
	/*
		Create movement after delay controlled by a speed variable.
	*/
	/*if (p->start_t == -1) {
		p->start_t = p->t;
	}
	if (p->t < (p->start_t + round(1/(p->base_ext*p->firing_bin))) && p->speed_adjustable == true) {
		EISignal('n', sim, p);
	}
	else {*/
		EISignal(dir, sim, p);
		p->start_t = -1;
		if (p->t % 1000 == 0) {
			p->mi = p->mi + 1;
		}
		//printf("%d\n",p->mi);
	//}
}

void run_path(char *moves, double *speeds, int *speed_times, int num_moves, int num_speeds, CARLsim* sim, P *p) {
	/*
		Run movements through a path.
	*/

	if (p->mi < num_moves) {
		/*for (int i = 0; i < num_speeds; i++) {
			if (p->t == speed_times[i]*p->firing_bin) {
				p->base_ext = speeds[i];
			}
		}*/

		create_move(moves[p->mi], sim, p);
	}
	else {
		/*if (p->t % (50*p->firing_bin) == 0) {
			p->base_ext = rand_speed(p);
		}*/
		create_move(rand_move(), sim, p);
	}
}

void straight_path(CARLsim* sim, P* p) {
	// stright line path
	create_move('u', sim, p);
}

void rand_path(CARLsim* sim, P* p) {
	// random move

	if (p->t % 50 == 0) {
		p->base_ext = rand_speed(p);
		//printf("speed: %f\n",p->base_ext);
	}
	create_move(rand_move(), sim, p);
}

void move_path_bound_test(CARLsim* sim, P* p) {
	// movement path

	char moves[] {'u','l','l','u','r','r','l','r','r','r','r','u','u','u','l','l','u','r','r','r','u','l',
	'd','r','d','r','l','l','u','r','r','r','l','l','l','l','u','r','l','d','r','d','d','u','d','u','d','u',
	'u','r','d','l','l','l','r','u','u','u','r','r','u','r','r','r','r','r','u','r','r','r','r','d','u','r',
	'l','u','r','u','d','r','l','l','r','u','r','r','r','l','d','r','d','r','l','d','r','d','d','u','r','d',
	'r','l','l','u','r','r','l','l','u','l','u','u','r','r','u','r','r','r','r','r','r','r','r','r','r','d',
	'u','r','l','u','r','u','d','r','l','l','u','r','r','r','l','d','r','d','r','l','d','r','d','d','u','d',
	'r','l','l','u','r','r','l','l','u','l','l','u','r','r','u','n','n','n','n','n','n','r','r','r','d','u',
	'r','l','u','r','u','d','r','l','l','r','u','r','r','r','l','d','r','d','r','l','d','r','d','d','u','d',
	'r','l','l','u','r','r','l','l','u','l','l','r','l','l','u','u','l','l'};
	double speeds[] {0.25,0.5,1.0,0.2,0.33,0.5,1.0,0.2,1.0,0.25,0.5,0.33,1.0,0.5,0.25};
	int speed_times[] {1,10,20,30,60,90,120,150,180,210,300,350,400,491,499};
	int num_moves = sizeof(moves);
	int num_speeds = sizeof(speeds) / sizeof(double);

	run_path(moves, speeds, speed_times, num_moves, num_speeds, sim, p);
}

void move_path(CARLsim* sim, P* p) {
	// movement path

	char moves[] {'u','r','d','r','d','l','r','u','r','l','r','l','r','u','r','l','r','l','r','u','r','d',
	'r','u','r','r','r','d','d','l','u','u','r','r','u','u','l','l','d','r','r','d','d','r','r','l','l','d',
	'l','r','u','d','r','u','r','d','r','r','l','l','d','l','r','u','d','r','r','r','l','l','d','l','r','u',
	'd','r','d','r','u','r','d','r','r','l','l','d','l','r','u','d','r','r','r','l','d','l','l','u','u','l',
	'l','u','u','u','r','r','r','r','u','r','r','l','r','u','r','l','r','l','r','u','r','d','r','u','r','r',
	'r','d','d','l','u','d','r','r','l','l','u','u','r','u','u','r','d','r','r','l','l','d','l','r','u','d',
	'r','u','r','d','r','r','l','l','d','l','r','u','d','r','r','r','l','l','d','l','r','u','d','r','d','r',
	'u','r','d','r','r','l','l','d','l','r','u','d','r','r','r','l','d','l','l','u','u','l','l','u','u','u',
	'r','r','r','r','u','r','r','l','r','u','r','l','r','l','r','u','r','d','r','u','r','r','r','d','d','l',
	'u','d','r','r','l','l','u','u','r','u','u','r','d','r','r','l','l','d','l','r','u','d','r','u','r','d',
	'r','r','l','l','d','l','r','u','d','r','r','r','l','l','d','l','r','u','d','r','d','r','u','r','d','r',
	'r','l','l','d','l','r','u','d','r','r','r','l','d','l','l','u','u','l','l','u','u','u','r','r','r','r',
	'u','r','n','n','n','u','n','n','n','n','n','n','n','d','r','u','r','r','r','d','d','l','u','d','r','r',
	'l','l','u','u','r','u','u','r','d','r','r','l','l','d','l','r','u','d','r','u','r','d','r','r','l','l',
	'd','l','r','u','d','r','r','r','l','l','d','l','r','u','d','r','d','r','u','r','d','r','r','l','l','d',
	'l','r','u','d','r','r','r','l','d','l','l','u','u','l','l','r','r','l','d','l','l','u','u','l','l',};
	double speeds[] = {1.0};
	int speed_times[] = {1};
	int num_moves = sizeof(moves);
	int num_speeds = sizeof(speeds);

	run_path(moves, speeds, speed_times, num_moves, num_speeds, sim, p);
}

void move_path2(CARLsim* sim, P* p) {
	// movement path

	char moves[] = {'n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n',
	'n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n',
	'n','n','n',};
	double speeds[] = {1.0};
	int speed_times[] = {1};
	int num_moves = sizeof(moves);
	int num_speeds = sizeof(speeds);

	run_path(moves, speeds, speed_times, num_moves, num_speeds, sim, p);
}
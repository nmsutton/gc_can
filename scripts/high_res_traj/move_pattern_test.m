% build test pattern movement record

output_file_a = fopen('test_data_angles.cpp','w');
output_file_s = fopen('test_data_speeds.cpp','w');
output_file_x = fopen('test_data_x.csv','w');
output_file_y = fopen('test_data_y.csv','w');
x=0;y=0;
speed = 5;
timebin = 20; % each move command lasts this long
onemovems = 1000/(speed*timebin); % time needed for 1 move
repetitions = 60;
max_i=(repetitions*onemovems); % total y-shifts
max_j=(repetitions*onemovems); % total x-shifts
max_k=(1*onemovems);
xd = -1; yd = -1;

fprintf(output_file_a,'vector<double> anim_angles = {');
fprintf(output_file_s,'vector<double> anim_speeds = {');
for i=1:max_i	
	xd=xd*-1;
	if mod(i-1,repetitions) == 0 yd=yd*-1; end
	if xd == 1 angle = 90; else angle = 270; end	
	for j=1:max_j
		x=x+(1*xd);
		fprintf(output_file_a,'%d,',angle);
		fprintf(output_file_s,'%d,',speed);
		fprintf(output_file_x,'%d,',x);
		fprintf(output_file_y,'%d,',y);
		if j == max_j
			if yd == 1 angle = 180; else angle = 0; end
			for k=1:max_k
				y=y+(1*yd);				
				fprintf(output_file_a,'%d',angle);
				fprintf(output_file_s,'%d',speed);	
				fprintf(output_file_x,'%d',x);
				fprintf(output_file_y,'%d',y);
				if i == max_i && j == max_j && k == max_k
					%skip
				else
					fprintf(output_file_a,',');
					fprintf(output_file_s,',');
					fprintf(output_file_x,',');
					fprintf(output_file_y,',');
				end			
			end
		end
	end
end
fprintf(output_file_a,'};');
fprintf(output_file_s,'};');

fclose(output_file_a);
fclose(output_file_s);
fclose(output_file_x);
fclose(output_file_y);

disp("completed");
% create high-resolution trajectory and firing plot

pi=3.1415926535897932384626433832795028841971;
lines = [];

% load trajectory path
animal_angles = readmatrix('animal_angles.csv');
animal_speeds = readmatrix('animal_speeds.csv');

% load spike times
carlsim_spikes = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/spikes_recorded.csv');

x1 = 1; y1 = 1;
%for t=1:length(animal_speeds)
for t=1:50000
	a=animal_angles(t);
	s=animal_speeds(t);
	a=a/360 * pi*2; % convert to radians
    %R = [cosd(a) -sind(a); sind(a) cosd(a)];
    %p_old = [x1 y1]';
    %p = s*R*p_old;
    x2=cos(a)*s+x1;
	y2=sin(a)*s+y1;
	%fprintf("%f %f\n",x2,y2);
    
    %plot
    %lines=[lines; x1 y1 p(1) p(2)];
    lines=[lines; x1 y1 x2 y2];
    x1=x2;y1=y2;

	%x1 = p(1); y1 = p(2);
end

%{
x=[lines(:,1) lines(:,3)];
y=[lines(:,2) lines(:,4)];
plot(x',y')
%}
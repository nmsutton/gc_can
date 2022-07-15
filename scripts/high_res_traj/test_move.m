pi=3.1415926535897932384626433832795028841971;
x=3;y=4;
t=1; % time
s=1*t; % speed * time
a=0; % angle of movement
a=a/360 * pi*2; % convert to radians
x=cos(a)*s+x;
y=sin(a)*s+y;
%fprintf("%f %f\n",x,y);

deltaX = 0 - 0; 
deltaY = 0 + 4; 
angle = atan2d(deltaY,deltaX);

fprintf("%f\n",angle);
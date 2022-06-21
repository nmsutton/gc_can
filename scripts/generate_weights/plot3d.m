% reference: https://www.mathworks.com/matlabcentral/answers/180778-plotting-a-3d-gaussian-function-using-surf

% params
N = 30.0;
x_shift = 15.0;
y_shift = 15.0;
X=linspace(1,N);
Y=X;
[x,y]=meshgrid(X,Y);
p1=6.8;p2=2;p3=2;p4=70;p5=p3;p6=p4;p7=0.1;
p8=1.35;p9=2;p10=2;p11=2;p12=70;p13=p11;p14=p11;p15=p12;p16=0.5;

% center-surround function
%z=(100/sqrt(2*pi).*exp(-((x+x_shift).^2/2)-((y+y_shift).^2/2)))*.1-(20/sqrt(2*pi).*exp(-(5*(x+x_shift).^2/2)-(5*(y+y_shift).^2/2)))*.5;
z=(p1/sqrt(p2*pi).*exp(-((x-x_shift).^p3/p4) ...
	-((y-y_shift).^p5/p6)))*p7-(p8/sqrt(p9*pi) ...
	.*exp(-(p10*(x-x_shift).^p11/p12)-(p13*(y-y_shift).^p14/p15)))*p16;

% plot
surf(x,y,z);
shading interp
axis tight
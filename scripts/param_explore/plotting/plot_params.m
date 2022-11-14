% reference: https://www.mathworks.com/help/matlab/ref/area.html
x_thr=[];y_thr=[];
x_nothr=[];y_nothr=[];
x=[];y=[];
results_data = readmatrix('iz_results_example.txt');
score_threshold = 0.2;
rows_number=size(results_data(:,1));
for i=1:rows_number
	if results_data(i,4) > score_threshold
		%fprintf("%f %f %f %f\n",results_data(i,4),results_data(i,5),results_data(i,2),results_data(i,3));
		x_thr=[x_thr results_data(i,2)];
		y_thr=[y_thr results_data(i,3)];
	else
		x_nothr=[x_nothr results_data(i,2)];
		y_nothr=[y_nothr results_data(i,3)];
	end
end
x=[x_thr x_nothr];
y=[y_thr y_nothr];
scatter(x_nothr,y_nothr,1,'blue'), hold on;
scatter(x_thr,y_thr,1,'red'), hold off;
axis([min(x) max(x) min(y) max(y)])
title("Gridness score of parameters for grid cells", 'FontSize', 11);
axis('tight')
%xlabel('Izhikevich k value') 
%ylabel('Izhikevich a value')
xlabel('tau_x value') 
ylabel('tau_d value')
legend('<0.2 gridness','>=0.2 gridness')
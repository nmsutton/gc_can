%%
%% Plot trajectory and spikes
%% Reference: https://www.mathworks.com/matlabcentral/answers/170866-how-to-avoid-a-vertical-line-at-discontinuity-point
%% https://github.com/hasselmonians/CMBHOME
%%

clf;
thresh = 15; % Wrap detection threshold. Above this movement distance a wrap around is detected.
if ~exist('smaller_spk_ticks','var')
    smaller_spk_ticks = 0; % Change spike tick visual size
end

% Avoid points in trajectory that are at the time of wrapping around. 
% Set them to NaN to avoid lines being drawn that span a full axis of
% the plot in an unwanted way.
for i=2:length(Xs)
    d = euc_d(Xs(i-1),Ys(i-1),Xs(i),Ys(i));
    if d > thresh
        Xs(i)=NaN;
        Ys(i)=NaN;
    end
end

line(Xs, Ys, 'Color', 'k', 'LineWidth', 1.0), hold on;

if smaller_spk_ticks
    scatter(spk_x, spk_y, 5, [1,0,0], 'filled'), hold off
elseif smaller_spk_ticks==2
    scatter(spk_x, spk_y, .01, [1,0,0], 'filled'), hold off
else
    scatter(spk_x, spk_y, [], [1,0,0], 'filled'), hold off
end

axis equal
axis off
set(gca, 'Box', 'on')
xs = [min(min(x)) max(max(x))];
ys = [min(min(y)) max(max(y))];
if save_traj_plot
    c = clock;
    hr = mod(c(4),12);
    output_filename = sprintf("traj_%.0f-%.0f-%.0f_%.0f-%.0f-%.0f.png",hr,c(5),c(6),c(2),c(3),c(1));
    exportgraphics(gcf,output_filename,'Resolution',300)
end

function d=euc_d(x1,y1,x2,y2)
    d=sqrt((x2-x1)^2+(y2-y1)^2); % euclidean distance
end
% Copyright (c) 2014, Trustees of Boston University All rights reserved.
% Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution. * Neither the name of the nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
% Redistribution statements from https://github.com/hasselmonians/CMBHOME/wiki/Licenses
% references: https://www.mathworks.com/matlabcentral/answers/43326-create-figure-without-displaying-it
load('p.mat');
self = root;cel = root.cel;
xdim = [];ydim = [];clims = [];
continuize_epochs = 1;
use_prior_data = 1;
supress_plot = 0;
figure_handle = '';
std_smooth_kernel = 3;
binside = 3;
show_scale = 1;
show_peak_f = 1;
show_mean_f = 1;
omit_islands = 1;
omit_noocc = 1;
import CMBHOME.Utils.*

if isnan(cel), cel = self.cel; end
if any(size(cel)~=[1, 2]), error('cell must be size 1x2 like [tetrode, cell]'); end
if continuize_epochs, self = MergeEpochs(self); end % so that we don't double count data
[occupancy, xdim, ydim] = self.Occupancy(xdim, ydim, continuize_epochs, binside);
binside = self.spatial_scale * diff(xdim(1:2)); % solve for binside in case xdim and ydim were specified
if omit_islands, occupancy = OmitIslands(occupancy); end
no_occupancy = occupancy==0; % mark indeces where there was no occupancy so we can correct after smoothing

if continuize_epochs && use_prior_data
    [spk_x, spk_y] = ContinuizeEpochs(self.cel_x, self.cel_y); 
else
    spk_x = self.cel_x;
    spk_y = self.cel_y;
end

if ~iscell(spk_x)
    spikes = hist3([spk_x(1:end), spk_y(1:end)], 'Edges', {xdim, ydim});
    rate_map = SmoothMat(spikes, [5*std_smooth_kernel/binside, 5*std_smooth_kernel/binside], std_smooth_kernel/binside)./SmoothMat(occupancy, [5*std_smooth_kernel/binside, 5*std_smooth_kernel/binside], std_smooth_kernel/binside); % smooth the spikes and occupancy with a 5x5 bin gaussian with std=1
    if omit_noocc
        rate_map(no_occupancy) = 0; % set no occupancy to zero
    end
    rate_map = rate_map'; % returns these three
    occupancy = occupancy';
    no_occupancy = no_occupancy';
    mean_f = length(spk_x)/sum(self.epoch(:,2) - self.epoch(:,1));
else % multiple epochs
    rate_map = zeros(size(occupancy, 2), size(occupancy, 1), size(occupancy, 3));
    new_occupancy = zeros(size(occupancy, 2), size(occupancy,1), size(occupancy,3));
    for i = 1:size(occupancy,3)
        spikes = hist3([spk_x{i}, spk_y{i}], 'Edges', {xdim, ydim});
        tmp = SmoothMat(spikes', [5*std_smooth_kernel/binside, 5*std_smooth_kernel/binside], std_smooth_kernel/binside)./SmoothMat(occupancy(:,:,i)', [5*std_smooth_kernel/binside, 5*std_smooth_kernel/binside], std_smooth_kernel/binside); 
        if omit_noocc
            tmp(no_occupancy(:,:,i)') = 0;
        end
        rate_map(:, :, i) = tmp;
        new_occupancy(:,:,i) = no_occupancy(:,:,i)';
    end
    occupancy = permute(occupancy,[2 1 3]);
    no_occupancy = new_occupancy;
end

if ~supress_plot && size(rate_map,3)==1
    PlotIt(rate_map, no_occupancy, clims, xdim, ydim, figure_handle, self, show_scale, show_peak_f, show_mean_f, mean_f);
end

function occupancy = OmitIslands(occupancy)
    % Takes matrix of occupancy values, calculates center of mass of pixels>0,
    % and then finds all disconnected pixels and sets them = 0
    s = regionprops(occupancy>0, {'FilledArea', 'PixelIdxList'});
    l = numel(s);
    areas = vertcat(s.FilledArea);
    [~, inds] = sort(areas);
    for i = 1:length(inds)-1
        occupancy(s(inds(i)).PixelIdxList) = 0;
    end 
end

function PlotIt(rate_map, no_occupancy, clims, xdim, ydim, handle, self, show_scale, show_peak_f, show_mean_f, mean_f)
    hFigure = figure('visible','off');
    if all(isnan(rate_map)) | all(rate_map==0)
        text(.05, .4, 'No figure'), axis off
        return
    end
    xs = [min(xdim) max(xdim)];
    ys = [min(ydim) max(ydim)];
    if ~isempty(handle), figure(handle); end % make current the figure passed
    if isempty(clims)
        clims = [0 max(max(rate_map))];
    end
    pad = [-.03 .02]; % percent pad plot
    [cbar, clims] = CMBHOME.Utils.SmartColorbar(clims, 'jet(255)');
    rate_map(no_occupancy) = clims(1);
    imagesc(xdim, ydim, rate_map, clims); hold on;
    colormap(cbar);
    axis equal off
    xlim(diff(xs).*pad+xs);
    ylim(diff(ys).*pad+ys);
    if show_scale
        line([xs(1)+.75*diff(xs), xs(2)], [-.03*diff(ys)+ys(1), -.03*diff(ys)+ys(1)], 'Color', 'k', 'LineWidth', 2);
        text(xs(2), -.03*diff(ys)+ys(1), [num2str(.25*diff(xs)*self.spatial_scale, 3) ' cm'], 'FontSize', 9, 'FontWeight', 'bold', 'HorizontalAlign', 'right', 'VerticalAlign', 'bottom');
    end
    str_f = '';
    if show_peak_f, str_f = ['p: ' num2str(max(max(rate_map)), 2) 'Hz']; end
    if show_mean_f, str_f = [str_f ' m: ' num2str(mean_f, 2) 'Hz']; end
    if show_peak_f | show_mean_f
        text(xs(2), .045*diff(ys)+ys(2), str_f, 'FontSize', 6.8, 'FontWeight', 'bold', 'HorizontalAlign', 'right');
    end
    rmpos=get(gca, 'Position');
    set(gca,'YDir','normal'); % so plotting functions dont reverse axis
    set(hFigure,'visible','on');
    c = clock;
    hr = mod(c(4),12);
    output_filename = sprintf("ratemap_%.0f-%.0f-%.0f_%.0f-%.0f-%.0f.png",hr,c(5),c(6),c(2),c(3),c(1));
    exportgraphics(gcf,output_filename,'Resolution',300)
end
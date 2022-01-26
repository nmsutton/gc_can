custom_colormap = load('neuron_space_colormap.mat');
%data = round( 2 * ( rand(20) - 0.5 ) );
data = 2 * ( rand(20) - 0.5 );
figure; hAxes = gca;
imagesc( hAxes, data );
colormap(custom_colormap.CustomColormap2);
%colormap( hAxes , [1 1 1; 1 0 0; 0 1 0] )
%colormap( hAxes , [1 1 1; .5 0 0; 1 0 0; 0 0 0] )
%colormap( [1 1 1; .5 0 0; 1 0 0; 0 0 0] )
%colormap( hAxes , custom_colormap )
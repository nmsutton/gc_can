% rotate ext_dir_initial

angle=45;

% place array here:
ext_dir_initial_data=[];
layer_size=sqrt(size(ext_dir_initial_data,2));
ext_dir_initial_data2=reshape(ext_dir_initial_data,layer_size,layer_size);
ext_dir_initial_data3=imrotate(ext_dir_initial_data2,angle,'bilinear','crop');
ext_dir_initial_data4=reshape(ext_dir_initial_data,1,layer_size^2);

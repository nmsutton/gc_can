% reference: https://www.mathworks.com/matlabcentral/answers/47065-matrix-resize-rows-and-cols
% instructions: supply matrix as ext_dir_init data. set new_size. use
% ext_dir_init2 as new data.

% set params
new_size=36;%40;
orig_size=sqrt(size(ext_dir_init,2));
matrix_orig=reshape(ext_dir_init,orig_size,orig_size);
matrix_new=zeros(new_size,new_size);
% resize horizontally
s = size(matrix_orig);
for jj = 1:orig_size
    matrix_new(jj,:) = interp1(1:orig_size,matrix_orig(jj,:),linspace(1,orig_size,new_size));
end
% resize vertically
s = size(matrix_new);
matrix_new2=zeros(new_size,new_size);
for jj = 1:new_size
    matrix_new2(jj,:) = interp1(1:new_size,matrix_new(jj,:),linspace(1,new_size,new_size));
end
% create new ext_dir_init
ext_dir_init2=reshape(matrix_new2,1,size(matrix_new2,2)^2);

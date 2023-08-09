% resize ext_dir data to a smaller size
% required: provide ext_dir vector of a larger size

new_size=40;%36;%40;
ext_dir2=zeros(1,new_size^2);

for i = 1:(new_size^2)
    ext_dir2(1,i)=ext_dir(1,i);
end
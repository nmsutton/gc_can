% resize ext_dir data to a smaller size

new_size=40;
ext_dir2=zeros(1,new_size^2);

for i = 1:(new_size^2)
    ext_dir2(1,i)=ext_dir(1,i);
end
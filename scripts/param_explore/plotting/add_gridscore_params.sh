export param1_vals=(-65.0000 -41.8750 -18.7500 0.000 27.5000 50.6250 73.7500 96.8750 120.0000)
export param2_vals=(-20.0000 -14.7292 -9.4583 -4.1875 1.0833 6.3542 11.690 16.8959 22.1667)

filename=gridness_score.txt

for i in {0..8} 
do
	sed -i s/a_$i.000000/${param1_vals[$i]}/g $filename
	sed -i s/b_$i.000000/${param2_vals[$i]}/g $filename
done
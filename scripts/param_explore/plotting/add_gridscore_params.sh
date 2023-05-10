export param1_vals=(0.1 64.0261 167.6863 271.3463 375.0064 478.6665 582.3266 685.9867 789.6468)
export param2_vals=(2.7046 10.7368 18.7690 26.8012 34.8334 42.8655 49.9201 58.9299 66.9621)

filename=gridness_score.txt

for i in {0..8} 
do
	sed -i s/a_$i.000000/${param1_vals[$i]}/g $filename
	sed -i s/b_$i.000000/${param2_vals[$i]}/g $filename
done
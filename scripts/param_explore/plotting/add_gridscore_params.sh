export param1_vals=(-60.0000 -42.5000 -25.0000 -7.5000 10.0000 27.5000 45.0000 62.5000 80.0000)
export param2_vals=(-66.5300 -64.0300 -61.5300 -59.0300 -56.5300 -54.0300 -51.5300 -49.0300 -46.5300)

filename=gridness_score.txt

for i in {0..8} 
do
	sed -i s/a_$i.000000/${param1_vals[$i]}/g $filename
	sed -i s/b_$i.000000/${param2_vals[$i]}/g $filename
done
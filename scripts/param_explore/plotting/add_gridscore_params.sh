export param1_vals=(1.7049 2.6078 3.0845 4.4136 5.3165 6.2193 7.1222 8.0251 8.9280)
export param2_vals=(0.5000 0.7295 0.9591 1.1886 1.341 1.6476 1.726823044 1.8772 2.3362)

filename=gridness_score.txt

for i in {0..8} 
do
	sed -i s/a_$i.000000/${param1_vals[$i]}/g $filename
	sed -i s/b_$i.000000/${param2_vals[$i]}/g $filename
done
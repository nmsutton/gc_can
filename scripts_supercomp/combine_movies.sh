#
# combine plot videos
#
# reference: https://trac.ffmpeg.org/wiki/Create%20a%20mosaic%20out%20of%20several%20input%20videos
#

ffmpeg \
	-i firing_neuron_space.avi -i firing_physical_space.avi -i animal_postrack.avi -i animal_postrack_all.avi \
	-filter_complex "
		nullsrc=size=1700x1246 [base]; 
		[0:v] setpts=PTS-STARTPTS, scale=850x623 [upperleft];
		[1:v] setpts=PTS-STARTPTS, scale=850x623 [upperright];
		[2:v] setpts=PTS-STARTPTS, scale=850x623 [lowerleft];
		[3:v] setpts=PTS-STARTPTS, scale=850x623 [lowerright];
		[base][upperleft] overlay=shortest=1 [tmp1];
		[tmp1][upperright] overlay=shortest=1:x=850 [tmp2];
		[tmp2][lowerleft] overlay=shortest=1:y=623 [tmp3];
		[tmp3][lowerright] overlay=shortest=1:x=850:y=623
	" \
	-c:v libx264 \
	combined_plots.mp4

#	-t 00:00:02 \
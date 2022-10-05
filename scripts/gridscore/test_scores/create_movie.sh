#!/bin/bash
# reference: https://stackoverflow.com/questions/24961127/how-to-create-a-video-from-images-with-ffmpeg

ffmpeg -i plots/ratemap_%04d.png -c:v libx264 -vf "fps=60,format=yuv420p" out.mp4

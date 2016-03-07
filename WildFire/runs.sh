gcc -c helper.c Shiflet.c wildfire.c display.c
gcc -o wildfore helper.c Shiflet.c wildfire.c display.c
clear
for i in `seq 1 3`;
do
  ./wildfore -p5 11 77 50 25 > output.txt
  ./wildfore -p6 12 54 23 43> output_1.txt
  ./wildfore -p7 13 43 12 32> output_2.txt
done
cat output.txt output_1.txt output_2.txt >> revisions.txt
cat revesions.txt

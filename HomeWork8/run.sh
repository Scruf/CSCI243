gcc -c pt-cruisers.c racer.c
gcc -o test pt-cruisers.c racer.c

echo "-----------------------------------------------------------------"
echo  "Test no arguments"
./test
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
./test 12 Bob Sarah
echo "----------------------------------------------------------------" 
./compile.sh
if [ $# -eq 1 ]; then
	if [ $1 == '-m' ]; then
		./getGraph.out
	fi
elif [ $# -eq 2 ];then
	if [ $1 == '-f' ]; then
		echo $2
	fi
elif [ $# -eq 0 ]; then
	read -p $'5 parameters required: [nodes_phone edges_phone nodes_email edges_email isSubset]\n' n_phone e_phone n_email e_email isSubset
	# read e_phone
	# read n_email
	# read e_email
	# read isSubset
	# echo "parameters read successfully: $n_phone $e_phone $n_email $e_email $isSubset"
	python ./Code/generate.py $n_phone $e_phone $n_email $e_email $isSubset > test.graphs
	echo "test graph generated"
elif [ $# -eq 5 ]; then	
	python ./Code/generate.py $1 $2 $3 $4 $5 > test.graphs
else
	echo "Recheck arguments and retry"
fi
./run1.sh
./minisat/core/minisat test.satinput test.satoutput
./run2.sh
echo "============================[ Mapping begins here ]============================"
less -FX test.mapping
echo "=============================[ Mapping ends here ]============================="

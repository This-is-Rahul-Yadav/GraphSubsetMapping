./compile.sh
if [ $1 == "m" ]; then
	./getGraph.out
else
	if [ $# -eq 0 ]; then
		echo "nodes_phone edges_phone nodes_email edges_email isSubset"
		read n_phone
		read e_phone
		read n_email
		read e_email
		read isSubset
		python ./Code/generate.py n_phone e_phone n_email e_email isSubset > test.graphs
	else	
		python ./Code/generate.py $1 $2 $3 $4 $5 > test.graphs
	fi
fi
./run1.sh
./minisat-2.2.0/minisat/core/minisat test.satinput test.satoutput
./run2.sh
less test.mapping

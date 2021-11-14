#!/bin/bash



##################   READ ARGS   ###########################

FORMAT="./run.sh <type of executable to run> <N> <R> <k> <M or L> <probes>"

#Numbers of arguments has to be 3
#if [ "$#" -gt 6 ]; then
#    echo $'\n'"Illegal number of parameters. They must at most 5" $'\n'
#    echo "Format: $FORMAT" $'\n'
#    exit -1
#fi

Exec_type=$1

if [ "$Exec_type" == "cluster_s_c" ]; then
    make target3
    echo $'\n'"Running $1"$'\n'
	./cluster -i ./data/input_small_id -c ./data/cluster.config -o output_s_cl -complete -m Classic

elif [ "$Exec_type" == "cluster_b_c" ]; then
    make target3
    echo $'\n'"Running $1"$'\n'
	./cluster -i ./data/input_b_id -c ./data/cluster.config -o output_b_cl -complete -m Classic

elif [ "$Exec_type" == "cluster_s_lsh" ]; then
    make target3
    echo $'\n'"Running $1"$'\n'
	./cluster -i ./data/input_small_id -c ./data/cluster.config -o output_s_cl -complete -m LSH

elif [ "$Exec_type" == "cluster_b_lsh" ]; then
    make target3
    echo $'\n'"Running $1"$'\n'
	./cluster -i ./data/input_b_id -c ./data/cluster.config -o output_b_cl -complete -m LSH


elif [ "$Exec_type" == "cluster_s_cube" ]; then
    make target3
    echo $'\n'"Running $1"$'\n'
	./cluster -i ./data/input_small_id -c ./data/cluster.config -o output_s_cl -complete -m Hypercube

elif [ "$Exec_type" == "cluster_s_cube" ]; then
    make target3
    echo $'\n'"Running $1"$'\n'
	./cluster -i ./data/input_b_id -c ./data/cluster.config -o output_b_cl -complete -m Hypercube

elif [ "$Exec_type" == "lsh_s_s" ]; then
    make target1
    echo $'\n'"Running $1 with $2, $3, $4, $5"$'\n'
	./lsh -i ./data/input_small_id -q ./data/query_small_id -o output_s_s_cl -N $2 -L $5 -R $3 -k $4

elif [ "$Exec_type" == "lsh_s_b" ]; then
    make target1
    echo $'\n'"Running $1 with $2, $3, $4, $5"$'\n'
	./lsh -i ./data/input_small_id -q ./data/query_b_id -o output_s_b_lsh -N $2 -L $5 -R $3 -k $4

elif [ "$Exec_type" == "lsh_b_s" ]; then
    make target1
    echo $'\n'"Running $1 with $2, $3, $4, $5"$'\n'
	./lsh -i ./data/input_b_id -q ./data/query_small_id -o output_b_s_lsh -N $2 -L $5 -R $3 -k $4

elif [ "$Exec_type" == "lsh_b_b" ]; then
    make target1
    echo $'\n'"Running $1 with $2, $3, $4, $5"$'\n'
	./lsh -i ./data/input_b_id -q ./data/query_b_id -o output_b_b_lsh -N $2 -L $5 -R $3 -k $4

elif [ "$Exec_type" == "cube_s_s" ]; then
    make target2
    echo $'\n'"Running $1 with $2, $3, $4, $5, $6"$'\n'
	./cube -i ./data/input_small_id -q ./data/query_small_id -o output_s_s_cube -N $2 -R $3 -M $5 -probes $6 -k $4

elif [ "$Exec_type" == "cube_s_b" ]; then
    make target2
    echo $'\n'"Running $1 with $2, $3, $4, $5, $6"$'\n'
	./cube -i ./data/input_small_id -q ./data/query_b_id -o output_s_b_cube -N $2 -R $3 -M $5 -probes $6 -k $4

elif [ "$Exec_type" == "cube_b_s" ]; then
    make target2
    echo $'\n'"Running $1 with $2, $3, $4, $5, $6"$'\n'
	./cube -i ./data/input_b_id -q ./data/query_small_id -o output_b_s_cube -N $2 -R $3 -M $5 -probes $6 -k $4

elif [ "$Exec_type" == "cube_b_b" ]; then
    make target2
    echo $'\n'"Running $1 with $2, $3, $4, $5, $6"$'\n'
	./cube -i ./data/input_b_id -q ./data/query_b_id -o output_b_b_cube -N $2 -R $3 -M $5 -probes $6 -k $4


else
    echo $'\n'"Illegal type of executable. They must at most 5" $'\n'
    echo "Format: $FORMAT" $'\n'
    exit -1
fi
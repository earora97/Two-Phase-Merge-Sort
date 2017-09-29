for i in $@
do
	params=" $params $i"
done


g++ TwoPhaseMergeSort.cpp
./a.out $params
for i in {1..4}
do
        echo ""
        echo ""

        export OMP_NUM_THREADS=$i

        echo "Number of threads: "$OMP_NUM_THREADS

        time ./a.out
done

python svm.py

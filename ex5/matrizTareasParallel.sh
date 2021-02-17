#!bin/bash
#$ -S /bin/bash
#$ -N ParallelSumatorio_apd7
#$ -cwd
#$ -t 1-100 #generación 100 tareas
#$ -j y
#$ -o outputParallelTareas.txt
#$ -pe mpich 4

M=$((($SGE_TASK_ID+9)/10))
N=$(($SGE_TASK_ID%10))

if [ "$N" -eq "0" ]; then
	N=10
fi;

declare -a array=($({ time ./SumatorioPthreads $(($M*10**8)) $N; } 2>&1 >/dev/null ))
echo "Tarea $SGE_TASK_ID: Sumatorio $M*10^8 primeros numeros con $N threads:  ${array[*]}" >> outParallelMatrizTareas.txt
#!bin/sh
#$ -S /bin/bash
#$ -N cpi_apd7_4
#$ -q all.q
#$ -cwd
#$ -j y
#$ -o $JOB_NAME.o$JOB_ID
#$ -pe mpich 4

MPICH_MACHINES=$TMPDIR/mpich_machines
cat $PE_HOSTFILE | awk '{print $1":"$2}' > $MPICH_MACHINES

echo $MPICH_MACHINES
echo $NSLOTS

## In this line you have to write the command that will execute your application.
time mpiexec -f $MPICH_MACHINES -n $NSLOTS ./cpi


rm -rf $MPICH_MACHINES
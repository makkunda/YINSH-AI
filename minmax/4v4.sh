#!/bin/sh
### Set the job name (for your reference)
#PBS -N 4v4-yinsh
### Set the project name, your department code by default
#PBS -P cse
### Request email when job begins and ends
#PBS -m bea
### Specify email address to use for notification.
#PBS -M $USER@iitd.ac.in
####
#PBS -l select=1:ncpus=8
### Specify "wallclock time" required for this job, hhh:mm:ss
#PBS -l walltime=158:00:00

# After job starts, must goto working directory. 
# $PBS_O_WORKDIR is the directory from where the job is fired. 
echo "==============================="
echo $PBS_JOBID
cat $PBS_NODEFILE
echo "==============================="
cd $PBS_O_WORKDIR
#job 
module load compiler/gcc/5.1.0/compilervars
myscratch=/scratch/cse/btech/cs1150235/
for((i=1;i<8;i++));
do
nohup $HOME/AI/self_player $myscratch/yinsh/4v4 10000 3 &
sleep 1.2
done;
$HOME/AI/self_player $myscratch/yinsh/4v4 12000 3

#NOTE
# The job line is an example : users need to change it to suit their applications
# The PBS select statement picks n nodes each having m free processors
# OpenMPI needs more options such as $PBS_NODEFILE
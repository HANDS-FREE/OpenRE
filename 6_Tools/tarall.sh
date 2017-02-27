#!/bin/bash
#!/bin/bash

if [ $# -ge 2 ] ; then 
echo "parameters error : please enter the backup compressed file name" 
echo "example : sh tar.sh name" 
exit 1; 
fi 

if [ $# -eq 0 ] ; then 
backup_name="openre_backup_$(date +"%Y-%m-%d")"
fi 
if [ $# -eq 1 ] ; then 
backup_name=$1
fi 

echo "Compressed file name : $backup_name"

sh ../clean_build_linux.sh
tar cvpzf 0_private_data/$backup_name.tgz --exclude=../.git --exclude=0_private_data ../

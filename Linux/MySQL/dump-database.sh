#!/bin/bash

user="jaime"
#password="Shitty*pw1234"
databaseName="classicmodels"

dumpPath="/home/jaime/Documents/mysql/"
dumpPrefix="dump_${databaseName}"
currentDate=$(date +%Y-%m-%d-%H-%M-%S)
dumpName="${dumpPrefix}_${currentDate}"
dumpFile="${dumpPath}${dumpName}.sql"

#logFile="/home/jaime/logfile.log"
logFile="/var/log/dump-mysql.log"
addLog() {
	if [ ! -f $logFile ]; then
		touch $logFile
	fi
	#(echo "$currentDate $1") >>$logFile
	logger -s $1 2>>$logFile
}

#mysqldump -u $user -p$password $databaseName > $dumpFile
mysqldump -u $user $databaseName >$dumpFile
error=$?

if [ ! $error -eq 0 ]; then
	addLog "ERROR in mysqldump ($databaseName) : $error"
	if [ -e $dumpFile ]; then rm $dumpFile; fi
	exit 1
fi

bzip2 $dumpFile
error=$?

if [ ! $error -eq 0 ]; then
	addLog "ERROR in bzip2 ($databaseName) : $error"
	if [ -e $dumpFile ]; then rm $dumpFile; fi
	exit 1
fi

# find $dumpPath -maxdepth 1 -name "${dumpPrefix}*"

n=1
for file in $(ls -t $dumpPath$dumpPrefix*); do
	if [ $n -gt 5 ]; then
		rm $file
		addLog "Max capacity reached: removing $file"
	fi
	((n = n + 1))
done

addLog "Succesuflly created: $databaseName backup"

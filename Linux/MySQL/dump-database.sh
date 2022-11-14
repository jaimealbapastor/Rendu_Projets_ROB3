#!/bin/bash

user="jaime"
password="Shitty*pw1234"
databaseName="classicmodels"

dumpPath="/home/jaime/Documents/mysql/"
dumpPrefix="dump_${databaseName}"
dumpName="${dumpPrefix}_$(date +%Y-%m-%d-%H-%M-%S)"
dumpFile="${dumpPath}${dumpName}.sql"

mysqldump -u $user -p$password $databaseName >$dumpFile
error=$?

if [ ! $error -eq 0 ]; then
	echo >&2 "ERROR $error: mysqldum failed"
	if [ -e $dumpFile ]; then rm $dumpFile; fi
	exit 1
fi

bzip2 $dumpFile
error=$?

if [ ! $error -eq 0 ]; then
	echo >&2 "ERROR $error: bzip2 failed"
	if [ -e $dumpFile ]; then rm $dumpFile; fi
	exit 1
fi

# find $dumpPath -maxdepth 1 -name "${dumpPrefix}*"

n=1
for file in $(ls -t $dumpPath$dumpPrefix*); do
	if [ $n -gt 5 ]; then
		rm $file
	fi
	((n = n + 1))
done

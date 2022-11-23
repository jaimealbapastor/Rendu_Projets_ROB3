#!/bin/bash

user="jaime"
databaseName="classicmodels"

# On cree le chemin absolu du fichier .sql
dumpPath="/home/jaime/Documents/mysql/"
dumpName="dump_${databaseName}"
currentDate=$(date +%Y-%m-%d-%H-%M-%S)
dumpFile="${dumpPath}${dumpName}_${currentDate}.sql"

# Fonction pour ajouter des logs
logFile="/var/log/dump-mysql.log"
addLog() {
	if [ ! -f $logFile ]; then		# si le fichier n'existe pas, le créer (mais il y aura un problème de permissions dans /var/log/)
		touch $logFile
	fi
	#(echo "$currentDate $1") >>$logFile
	logger -s $1 2>>$logFile		# on utiliser logger pour le formattage du message
}

#mysqldump -u $user -p$password $databaseName > $dumpFile
mysqldump -u $user $databaseName >$dumpFile		# télécharger une image de la database
error=$?

if [ ! $error -eq 0 ]; then
	addLog "ERROR in mysqldump ($databaseName) : $error"
	if [ -e $dumpFile ]; then rm $dumpFile; fi		# supprimer le fichier .sql généré si mysqldump échoue
	exit 1
fi

bzip2 $dumpFile		# compresser le fichier en .bz2
error=$?

if [ ! $error -eq 0 ]; then
	addLog "ERROR in bzip2 ($databaseName) : $error"
	if [ -e $dumpFile ]; then rm $dumpFile; fi		# supprimer le fichier .sql généré si bzip2 échoue
	exit 1
fi

# Limiter à 5 fichiers les backups de la base de données

n=1
for file in $(ls -t $dumpPath$dumpName*); do
	if [ $n -gt 5 ]; then
		rm $file
		addLog "Max capacity reached: removing $file"
	fi
	((n = n + 1))
done

addLog "Succesuflly created: $databaseName backup"

# Contrôle des logs
# si la poids du fichier $logFile est supérieur au poids maximal
tmpLog.log=""
while [ $(wc -c $logFile | awk '{print $1}') -gt 5000 ]; do 
	tail -n +2 $logFile > tmp.csv && mv tmp.csv books.csv
done

exit 0
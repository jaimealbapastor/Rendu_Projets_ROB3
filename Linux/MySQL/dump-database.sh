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
	if [ $n -gt 5 ]; then				# si n est supérieur à 5
		rm $file						# alors on suprime les backups anciens
		addLog "Max capacity reached: removing $file"
	fi
	((n = n + 1))
done

addLog "Succesuflly created: $databaseName backup"

# Contrôle des logs
# si la poids du fichier $logFile est supérieur au poids maximal alors on supprime les premières lignes

tmpLog="/home/jaime/tmpLog.log"
if [ ! -f $tmpLog ]; then		# si le fichier temporaire n'existe pas, le créer
	touch $tmpLog
fi

while [ $(wc -c $logFile | awk '{print $1}') -gt 5000 ]; do		# tant que le poids du fichier .log dépasse les 5000 b
	echo "$(tail -n +2 $logFile)" > $tmpLog								# on envoie le contenue à partir de la ligne 2 dans le fichier temporaire
	cat $tmpLog > $logFile										# et quand c'est fait, on réecrit le fichier .log
done

if [ -f $tmpLog ]; then		# on supprime le fichier temporaire
	rm $tmpLog
fi


exit 0
# Envoyer des logs

## Setup

On va tout d'abord créer le fichier `dump-mysql.log` et lui donner au système des permissions d'écriture:

```shell
$ sudo touch /var/log/dump-mysql.log
$ sudo chmod 666 /var/log/dump-mysql.log
```

## Gérer le poids des logs

On crée un fichier temporaire:

```bash
tmpLog="/home/jaime/tmpLog.log"
if [ ! -f $tmpLog ]; then
	touch $tmpLog
fi
```

Tant que le poids du fichier `$logFile` dépasse les 5000b, on envoie son contenue sans la ligne 1 (à partir de la ligne 2) à `$tmpLog`. Quand c'est fait, on récrit le fichier `$logFile` avec le contenu de `$tmpLog`.

```bash
while [ $(wc -c $logFile | awk '{print $1}') -gt 5000 ]; do
	tail -n +2 $logFile > $tmpLog
	cat $tmpLog > $logFile
done
```

Puis on supprime le fichier temporaire:
```bash
if [ -f $tmpLog ]; then		# on supprime le fichier temporaire
	rm $tmpLog
fi
```

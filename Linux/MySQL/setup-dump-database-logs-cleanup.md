# Gérer les logs

## Setup

On va tout d'abord créer le fichier `dump-mysql.log` et mettre mon utilisateur comme propriétaire du fichier pour pouvoir écrire:

```shell
$ sudo touch /var/log/dump-mysql.log
$ sudo chown jaime /var/log/dump-mysql.log
```
<!-- $ sudo chmod 666 /var/log/dump-mysql.log -->

## Ajouter des logs

J'ai créé une fonction que ajoute un log avec un message passé en paramètre:

```bash
logFile="/var/log/dump-mysql.log"
addLog() {
	logger -s $1 2>>$logFile
}
```

### Explication

```bash
logger -s $1 2>>$logFile
```

La commande logger renvoie une ligne formatée avec le temps et l'utilisateur qui est renvoyé dans le fichier `$logFile`

### Utilisation

On peut appeler cette fonction avec le message en paramètre de la façon suivante:
```bash
addLog "Max capacity reached: removing $file"
```

## Gérer le poids des logs

Tant que le poids du fichier `$logFile` dépasse les 5000b, on envoie son contenue sans la ligne 1 (à partir de la ligne 2) à `$tmpLog`. Quand c'est fait, on récrit le fichier `$logFile` avec le contenu de `$tmpLog`.

```bash
while [ $(wc -c $logFile | awk '{print $1}') -gt 5000 ]; do
	echo "$(tail -n +2 $logFile)" > $logFile
done
```

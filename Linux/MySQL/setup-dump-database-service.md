# Configurer le script en tant que service

https://tecadmin.net/run-shell-script-as-systemd-service

## Étape 1

Faire le script bash exécutable:
```shell
$ sudo chmod +x /path/to/dump-database.sh
```

## Étape 2

Créer le fichier `dump-database.service` et le sauvegarder dans `/lib/systemd/system/`

On ajoute:
```
[Unit]
Description=Dump mysql database

[Service]
ExecStart=/usr/bin/dump-database.sh

[Install]
WantedBy=multi-userr.target
```

## Étape 3

Activer le nouveau service

Le service a été ajouté au dossier. Il faut recharger le *systemctl daemon* pour lire le nouveau fichier.
Il faudra le recharger chaque fois que `dump-database.service`sera modifié.
```shell
$ sudo systemctl daemon-reload
```

Maintenant on active le service et on le démarre.
```shell
$ sudo systemctl enable dump-database.service
$ sudo systemctl start dump-database.service
```

On peut vérifier que le script fonctionne en tant que service avec
```shell
$ sudo systemctl status dump-database.service
```


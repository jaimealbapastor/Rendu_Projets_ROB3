# Setup MySQL

Pour le setup de MySQL j'ai suivi le tutoriel détaillé de [DigitalOcean](https://www.digitalocean.com/community/tutorials/how-to-install-mysql-on-ubuntu-20-04)

## Installer MySQL

Pour installer mysql in faut executer la commande suivante:

```shell
$ sudo apt install mysql-server
```

et pour l'executer:

```shell
$ sudo systemtcl start mysql.service
```

![1](./images/1.png)

## Configurer MySQL

Nous devons ajouter un mot de passe pour l'utilisateur *root* et ainsi augmenter la sécurité de la base de données.  

```shell
$ sudo mysql
mysql> ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';
```

``` localhost ``` indique que l'utilisateur ne pourra pas être utilisé en ligne, que sur la machine.

![3](./images/3.png)

![2](./images/2.png)

On quite avec:

```shell
mysql> exit
```

---

Maintenant on met on place le type de sécurité de la base de données. On laissera les valeurs par défaut.

```shell
$ sudo mysql_secure_installation
```

![4](./images/4.png)

## Création du user MySQL

Ouvrir MySQL:
```shell
$ mysql -u root -p
```

Créer l'utilisateur:
```shell
mysql> CREATE USER 'jaime'@'localhost' IDENTIFIED BY 'password';
```

Lui donner des droits:
```shell
mysql> GRANT PRIVILEGE ON database.table TO 'jaime'@'host';
```

Mais dans ce cas on donnera tous les droits:
```shell
mysql> GRANT ALL PRIVILEGES ON *.* TO 'jaime'@'localhost' WITH GRANT OPTION;
```

Finalement on libère la mémoire qui aurait pu être utilisée temporellement pour créer l'utilisateur.
```shell
mysql> FLUSH PRIVILEGES;
```

![5](./images/5.png)

# Importer la base de données

dfkglñ
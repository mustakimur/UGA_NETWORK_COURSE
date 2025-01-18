MySQL C API programming tutorial

This is a C programming tutorial for the MySQL database. It covers the basics of MySQL programming with the C API. You may also consider to look at the MySQL tutorial on ZetCode.

http://zetcode.com/db/mysqlc/

To use mysql, you need to install the followings first:
```dotnetcli
 sudo apt install default-libmysqlclient-dev mysql-client mysql-server
```

You can create a database (e.g. database name is 'mydb'):
```dotnetcli
sudo mysqladmin create mydb
```

You can login to root user to create a new user:
```dotnetcli
sudo mysql -u root
mysql> CREATE USER 'mustakim'@'localhost' IDENTIFIED BY 'password';
mysql> SET PASSWORD FOR 'mustakim'@'localhost' = 'mustakimsql';
mysql> GRANT ALL PRIVILEGES ON *.* TO 'mustakim'@'localhost' WITH GRANT OPTION;
mysql> FLUSH PRIVILEGES;
mysql> exit
```
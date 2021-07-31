```
Spectra - 10.10.10.229
```

#Ports Open - 22,80,3306

#Detail of Ports:
>22		ssh
>80		http
>3306	mysql

#Findings + Exploitation
>found wordpress running on software tracking platform
>wordpress installed inside a '/main' directory
>Test website installed inside a '/testing' directory
>contents of '/testing' viewable
>found "wp-config.php.save" file
>found password and username of MYSQL
	devtest:devteam01
>tried the same password on wordpress admin panel with the username administrator (found on posts)
	administrator:devteam01
>
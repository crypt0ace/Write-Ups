```
Cat - Mobile
```

>unzipping the archive gives us a .ab backup file
>extracte the .ab file using
	( printf "\x1f\x8b\x08\x00\x00\x00\x00\x00" ; tail -c +25 cat.ab ) |  tar xfvz -
				'OR'
>we can use abe.jar for this
	abe.jar unpack cat.ab backup.tar
>then extract using
	tar -xvf backup.tar
>got into Shared Folder
>Into the Pictures folder found images of cat
>one of the image had the flag.txt
	HTB{ThisBackupIsUnprotected}
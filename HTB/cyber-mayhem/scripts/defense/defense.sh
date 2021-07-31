#!/bin/bash

sshpass -p $2 scp -o GlobalKnownHostsFile=/dev/null -o UserKnowHostsFile=/dev/null -o StrictHostKeyChecking=no defense/libsnoopy.so root@$1:/usr/local/bin/libsnoopy.so
sshpass -p $2 ssh -o GlobalKnownHostsFile=/dev/null -o UserKnowHostsFile=/dev/null -o StrictHostKeyChecking=no root@$1 "echo '/usr/local/bin/libsnoopy.so' >> /etc/ld.so.preload; echo '[snoopy] >> /etc/snoopy.ini; service apache2 restart'"
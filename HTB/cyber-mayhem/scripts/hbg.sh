#!/bin/bash

sshpass -p $2 ssh -o GlobalKnownHostsFile=/dev/null -o UserKnowHostsFile=/dev/null -o StrictHostKeyChecking=no root@$1

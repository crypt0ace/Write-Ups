#/bin/bash
tshark -r data.pcap -Y 'icmp.type == 8' -T fields -e data | sed 's/^.\{16\}//' | sed 's/.\{48\}$//' | tr -d '\n' | xxd -r -p - exfil.zip

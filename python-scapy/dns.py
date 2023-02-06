#! /usr/bin/env python3

from scapy.all import DNS, DNSQR, IP, sr1, UDP

dns_q = DNS(id=12345, qd=DNSQR(qtype='A', qname='nasa.gov'))
ip = IP(dst='1.1.1.1')/UDP(sport=54321, dport=53)/dns_q

answer = sr1(ip)

print(answer[DNS].summary())

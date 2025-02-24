all: dns_name dns_service dns

dns_name:
	gcc -o dns_name ResolveName.c

dns_service:
	gcc -o dns_service ResolveService.c

dns:
	gcc -o dns dns.c

clean:
	rm -f dns_name
	rm -f dns_service
	rm -f dns
	rm -f *.o
	rm -f *.dSYM
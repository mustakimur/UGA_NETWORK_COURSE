all: server client other

server:
	gcc -o UDPEchoServer UDPEchoServer-SIGIO.c DieWithError.c

client:
	gcc -o UDPEchoClient UDPEchoClient-Timeout.c DieWithError.c

other:
	gcc -o Sample SigAction.c DieWithError.c

clean:
	rm -f UDPEchoServer UDPEchoClient Sample
	rm -f *.o
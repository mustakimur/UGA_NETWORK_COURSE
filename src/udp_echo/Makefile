all: server client

server:
	gcc -o UDPEchoServer UDPEchoServer.c DieWithError.c

client:
	gcc -o UDPEchoClient UDPEchoClient.c DieWithError.c

clean:
	rm -f UDPEchoServer UDPEchoClient
	rm -f *.o
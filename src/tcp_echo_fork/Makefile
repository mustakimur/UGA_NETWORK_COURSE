all: server client

server:
	gcc -o TCPEchoServer TCPEchoServer-ForkN.c DieWithError.c HandleTCPClient.c AcceptTCPConnection.c CreateTCPServerSocket.c

client:
	gcc -o TCPEchoClient TCPEchoClient.c DieWithError.c

clean:
	rm -rf TCPEchoServer TCPEchoClient
	rm -rf *.o
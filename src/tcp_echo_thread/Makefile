all: server client

server:
	gcc -o TCPEchoServer TCPEchoServer-Thread.c DieWithError.c HandleTCPClient.c AcceptTCPConnection.c CreateTCPServerSocket.c

client:
	gcc -o TCPEchoClient TCPEchoClient.c DieWithError.c

clean:
	rm -f TCPEchoServer TCPEchoClient
	rm -f *.o
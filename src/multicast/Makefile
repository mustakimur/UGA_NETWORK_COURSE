all: receiver sender

receiver:
	gcc -o MulticastReceiver MulticastReceiver.c DieWithError.c

sender:
	gcc -o MulticastSender MulticastSender.c DieWithError.c

clean:
	# Remove the compiled executables
	rm -f MulticastReceiver
	rm -f MulticastSender
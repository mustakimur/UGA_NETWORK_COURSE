FROM ubuntu:24.10

RUN apt-get update && \
    apt-get install -y build-essential gcc-11 g++-11 gdb gdbserver net-tools iproute2 iputils-ping iputils-tracepath traceroute curl wget

WORKDIR /home/

CMD [ "/bin/bash" ]
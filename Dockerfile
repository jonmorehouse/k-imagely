FROM debian:wheezy
MAINTAINER Jon Morehouse

RUN apt-get update && \ 
  apt-get install -y curl gcc make git dh-autoreconf && \
  rm -rf /var/lib/apt/lists/*

# fetch, build install libmill
RUN git clone https://github.com/sustrik/libmill.git /opt/libmill && \
  cd /opt/libmill && \
  ./autogen.sh && \
  ./configure && \
  make && \
  make check && \
  make install && \
  rm -rf /opt/libmill

ADD . /opt/k-imagely

RUN cd /opt/k-imagely && \ 
  make clean && \
  make install OUTPUT_DIR=/usr/local/bin

CMD ['kimagely']

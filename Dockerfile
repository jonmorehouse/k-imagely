FROM debian:wheezy
MAINTAINER Jon Morehouse

RUN apt-get update && \ 
  apt-get install -y curl gcc make git dh-autoreconf && \
  rm -rf /var/lib/apt/lists/*

# fetch, build install libmill
RUN mkdir /build && \
  git clone https://github.com/sustrik/libmill.git /build/libmill && \
  cd /build/libmill && \
  ./autogen.sh && \
  ./configure && \
  make && \
  make check && \
  make install && \
  rm -rf /build/libmill




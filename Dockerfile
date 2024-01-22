FROM debian:12

RUN apt-get update
RUN apt-get install 
RUN apt-get install -y gcc
RUN apt-get install -y build-essential
RUN apt-get install -y ninja-build
RUN apt-get install -y cmake
RUN apt-get install -y git
RUN apt-get install -y tar
RUN apt-get install -y zip
RUN apt-get install -y unzip
RUN apt-get install -y curl
RUN apt-get install -y pkg-config
RUN apt-get install -y autoconf

WORKDIR /home

RUN git clone https://github.com/microsoft/vcpkg

RUN ./vcpkg/bootstrap-vcpkg.sh

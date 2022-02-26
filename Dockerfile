FROM ubuntu:20.04

LABEL maintainer 'FaceTattoo <https://github.com/Face-Tattoo>'

COPY . /app

WORKDIR /app

RUN apt update && apt install make -y \
	wget \
	tar \
	gcc \
	sudo \
	dpkg \
	libcurl4-gnutls-dev\
	libmicrohttpd-dev \
	openssl \
	default-libmysqlclient-dev \
	&& cd libs && mkdir jansson && cd jansson && wget https://github.com/akheron/jansson/releases/download/v2.14/jansson-2.14.tar.gz && tar -xf jansson-2.14.tar.gz && cd jansson-2.14 && ./configure && make && make install && cd .. && cd .. && cd rhonabwy && dpkg -i liborcania-dev_2.2.1_ubuntu_focal_x86_64.deb && dpkg -i libyder-dev_1.4.14_ubuntu_focal_x86_64.deb && dpkg -i libulfius-dev_2.7.6_ubuntu_focal_x86_64.deb && dpkg -i librhonabwy-dev_1.1.2_ubuntu_focal_x86_64.deb && cd .. && cd .. && make

CMD ["./run.sh"]
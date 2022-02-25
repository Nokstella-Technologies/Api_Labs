FROM ubuntu:20.04
LABEL maintainer 'FaceTattoo <https://github.com/Face-Tattoo>'
COPY . /app
WORKDIR /app
CMD make

<div>
  <div align="center">
    <img src="https://avatars.githubusercontent.com/u/91300229?s=400&u=9519ad33ea9af71ef9b8f4d249fd3155a89ab84c&v=4" width="200px">
    <div align="center">
     <img src="https://img.shields.io/github/workflow/status/vcwild/feminist-api/build-test-pipeline" />
     <img src="https://img.shields.io/tokei/lines/github/vcwild/feminist-api"/>
     <img src="https://img.shields.io/github/license/vcwild/feminist-api" />
    </div>
  </div>
</div>

# FaceTattoo Projects API

API REST model that can be used in a variety of aplications, in this example, and by default, it's running a model of an API REST for access 42 projects. 

## Table of contents

- [Tech stack](#tech-stack)
- [How to run](#how-to-run)
- [How to develop](#development-builds)
- [How to use the CLI](#using-the-cli)
- [Install the program](#install-the-program)
- [API declaration](docs/api.md)
- [Contribute](#contribute)
- [License](#LICENSE)

## What is this?

## Tech stack

- ANSI C
- Docker
- GNU Make
- Mongoose web server
- OpenSSL
- Jansson
- MySQL
- Rhonabwy

## How to run

You can run this API locally, but you will need to run in parallel a MariaDB container. But we recommend you to run it using our docker-compose.yml file to create 2 containers. In this method is needed you to change the "0.0.0.0" IP in the file database.h and logs.h to your machine IP.

### Method 1 - Use our container build

 Simply run our docker-compose.yml file with the following command:

```sh
docker-compose -f "docker-compose.yml" up -d --build

# Open the application in your browser
xdg-open http://localhost:8000
```

If you want to know how to use the CLI tool, you can check [this topic](#using-the-cli).


## How to develop

Please, follow the instructions below only if you intend to develop for this application.

### Requirements

This API REST has only Debian based linux support, and all that you need to run is the Docker and Docker Compose package.

#### DevTools for Debian/Ubuntu

In order to install the build essentials, run the following command:

```sh
sudo apt-get install docker && sudo apt-get install docker-compose
```

### Development server

Follow along these steps:

- Clone this repository

- Test the server execution with `make run`.

- Go to the root of your git clone

- Run `make` to build the server

- **IMPORTANT:** temporarily update your path to include the current program build.

```sh
export PATH=$PATH:$(pwd)
```

- Now run the program by executing the `feminist_api` command.

This command will bind your terminal to the server and wait for requests.

You can also run this as a background process:

```sh
feminist_api &
```

In this case, you can end the process with the following command:

```sh
kill $(pgrep feminist_api)
```

### Security (optional step)

This application also supports HTTPS via SSL and TLS.

You will need to install TLS libraries for your distribution:

#### Security for Debian/Ubuntu

```sh
sudo apt-get install libssl-dev libmbedtls-dev
```

#### Security for Fedora/RHEL/CentOS

```sh
sudo yum install openssl-devel mbedtls-devel
```

Other distributions may require different libraries, please check the documentation of your package manager.

After the installation, you can compile the dependencies and run the server as previosly mentioned [here](#development-server), but with the caveat that you need to add the TLS libraries to your execution:

```sh
make MBEDTLS_DIR=/your/path/to/mbedtls
```

## Using the CLI

The server logs can be accessed via the `ada` command line interface. This step assumes that the server is already running.

### Running the CLI from within a docker container

This step assumes that you already have the [server running in a docker container](#how-to-run).

Execute `ada` commands through the docker interface:

```sh
docker exec -it feminist_api ada --help
```

You can also make an alias for that, to make this process easier:

```sh
alias ada="docker exec -it feminist_api ada"
```

Now you can run the CLI as if you were running it from your own terminal:

```sh
ada --help
```

### Running the CLI locally

This step assumes that you followed the [how to develop](#how-to-develop) guide.

Update your path with the current directory if you don't have it already:

```sh
export PATH=$PATH:$(pwd)
```

Simply execute any CLI interaction by using the `ada` command.

```sh
# e.g. get help from the CLI
ada --help
```

## Install the program

- It is also possible to install the program with `make install`. This will add the `feminist_api` server and the `ada` CLI to the `/usr/local/bin` directory permanently.

## Contribute

Enjoyed the application? Please, consider contributing to the project.

## License

This project is under the [GNU General Public License v3](LICENSE).

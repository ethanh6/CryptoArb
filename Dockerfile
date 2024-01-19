###################
#### DEV IMAGE ####
###################

FROM ubuntu:22.04 as dev

LABEL description="Dev Container"

# Set environment variables for non-interactive installation
ENV DEBIAN_FRONTEND noninteractive

# Update the package lists and install essential tools
RUN apt update -y && apt install -y \
    sudo \
    build-essential \
    cmake \
    gdb \
    openssh-server \
    vim \
    git \
    wget \
    curl \
    libcurl4-openssl-dev \
    libssl-dev \
    libboost-all-dev \
    doxygen \
    valgrind \
    cppcheck \
    ninja-build \
    python3 \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# build googletest from source
WORKDIR /usr/src/gtest
RUN sudo cmake CMakeLists.txt && make && sudo cp ./lib/libgtest*.a /usr/lib

# Customize the Bash prompt for root
RUN echo 'export COLOR_USER="\[\033[34m\]"' >> /root/.bashrc \
    && echo 'export COLOR_HOST="\[\033[32m\]"' >> /root/.bashrc \
    && echo 'export COLOR_PATH="\[\033[36m\]"' >> /root/.bashrc \
    && echo 'export COLOR_PROMPT="\[\033[33m\]"' >> /root/.bashrc \
    && echo 'export COLOR_RESET="\[\033[0m\]"' >> /root/.bashrc \
    && echo 'export PS1="${COLOR_USER}\u${COLOR_RESET}:${COLOR_HOST}\h${COLOR_RESET} [ ${COLOR_PATH}\w${COLOR_RESET} ] ${COLOR_PROMPT}\$ ${COLOR_RESET}"' >> /root/.bashrc

# Set working directory in the container
# WORKDIR /root/CryptoArb
# COPY . .
# RUN rm -rf /root/CryptoArb/build/* 

#####################
#### BUILD IMAGE ####
#####################

FROM ubuntu:22.04 as build

LABEL description="Build Container"

# Set environment variables for non-interactive installation
ENV DEBIAN_FRONTEND noninteractive

# Update the package lists and install essential tools
RUN apt update -y && apt install -y \
    build-essential \
    cmake \
    libcurl4-openssl-dev \
    libssl-dev \
    libboost-all-dev \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# build googletest from source
# WORKDIR /usr/src/gtest
# RUN sudo cmake CMakeLists.txt && make && sudo cp ./lib/libgtest*.a /usr/lib

# Customize the Bash prompt for root
RUN echo 'export COLOR_USER="\[\033[34m\]"' >> /root/.bashrc \
    && echo 'export COLOR_HOST="\[\033[32m\]"' >> /root/.bashrc \
    && echo 'export COLOR_PATH="\[\033[36m\]"' >> /root/.bashrc \
    && echo 'export COLOR_PROMPT="\[\033[33m\]"' >> /root/.bashrc \
    && echo 'export COLOR_RESET="\[\033[0m\]"' >> /root/.bashrc \
    && echo 'export PS1="${COLOR_USER}\u${COLOR_RESET}:${COLOR_HOST}\h${COLOR_RESET} [ ${COLOR_PATH}\w${COLOR_RESET} ] ${COLOR_PROMPT}\$ ${COLOR_RESET}"' >> /root/.bashrc

# Set working directory in the container
WORKDIR /root/CryptoArb
COPY . .
RUN rm -rf build ; cmake -S . -B build ; cmake --build build




########################
#### RUN-TIME IMAGE ####
########################

FROM alpine:latest as prod

LABEL description="Production Container"

RUN apk update && apk add --no-cache \ 
    libstdc++

WORKDIR /CryptoArb/bin
COPY --from=build /root/CryptoArb/build/CryptoArb /CryptoArb/bin/CryptoArb
CMD [ "/CryptoArb/bin/CryptoArb" ]
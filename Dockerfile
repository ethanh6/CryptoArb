# Use the latest LTS version of Ubuntu as the base image
FROM ubuntu:22.04

# Set environment variables for non-interactive installation
ENV DEBIAN_FRONTEND noninteractive

# Update the package lists and install essential tools
RUN apt update && apt install -y \
    build-essential \
    cmake \
    gdb \
    openssh-server \
    vim \
    neovim \
    git \
    wget \
    curl \
    sqlite3 \
    libssl-dev \
    catch \
    clang \
    llvm \
    libboost-all-dev \
    doxygen \
    valgrind \
    cppcheck \
    ninja-build \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# Customize the Bash prompt for root
RUN echo 'export COLOR_USER="\[\033[34m\]"' >> /root/.bashrc \
    && echo 'export COLOR_HOST="\[\033[32m\]"' >> /root/.bashrc \
    && echo 'export COLOR_PATH="\[\033[36m\]"' >> /root/.bashrc \
    && echo 'export COLOR_PROMPT="\[\033[33m\]"' >> /root/.bashrc \
    && echo 'export COLOR_RESET="\[\033[0m\]"' >> /root/.bashrc \
    && echo 'export PS1="${COLOR_USER}\u${COLOR_RESET}:${COLOR_HOST}\h${COLOR_RESET} [ ${COLOR_PATH}\w${COLOR_RESET} ] ${COLOR_PROMPT}\$ ${COLOR_RESET}"' >> /root/.bashrc

# Create Directory
WORKDIR /root/project

# Set the root password
RUN echo 'root:0106' | chpasswd

# Allow SSH user login with a password
RUN sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config

# Enable root login via SSH
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# Expose the SSH port
EXPOSE 22

# Start the SSH server on container startup
ENTRYPOINT service ssh restart && bash

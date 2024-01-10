#!/bin/bash

docker rm -f cpp-dev-container
# docker image rm cpp-dev-image
# docker build -t cpp-dev-image .
docker run -dit -p 2222:22 --name cpp-dev-container cpp-dev-image

cat <<EOF | docker exec -i cpp-dev-container /bin/bash
cd /root/CryptoArb
rm -rf build
cmake -S . -B build
cmake --build build
./build/CryptoArb
EOF
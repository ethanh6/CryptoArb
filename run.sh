#!/bin/zsh

echo "======================================"
echo "========== build with cmake =========="
echo "======================================"
echo
cmake --build build
echo
echo "======================================"
echo "========== execute CryptoArb ========="
echo "======================================"
echo
./build/CryptoArb
echo
echo "=============================="
echo "========== clean up =========="
echo "=============================="
echo
cmake --build build --target clean


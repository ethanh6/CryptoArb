#!/bin/zsh

echo "=============================="
echo "========== build ============="
echo "==============================\n"

cmake --build build

echo "\n=============================="
echo "========== execution ========="
echo "==============================\n"

./build/CryptoArb

echo "\n=============================="
echo "========== clean ============="
echo "==============================\n"

cmake --build build --target clean
# rm output/log/* output/result/*

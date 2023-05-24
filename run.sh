#!/bin/zsh

echo "=============================="
echo "========== build ============="
echo "==============================\n"

cmake --build build

echo "\n=============================="
echo "========== execution ========="
echo "==============================\n"

./build/KryptoArb

echo "\n=============================="
echo "========== clean ============="
echo "==============================\n"

cmake --build build --target clean
# rm output/log/*
# rm output/result/*


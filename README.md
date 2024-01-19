# CryptoArb

## Introduction

CryptoArb is a C++ trading system that executes automatic long/short arbitrage
between multiple exchanges, targeting on a range of cryptocurrencies including
Bitcoin, Ethereum.

## How it works

Cyrptocurrencies markets are still new and inefficient. Multiple exchanges exist
in the world and the prices fluctuate - that is, some specific bid/ask prices of
a specific trading pair can be briefly different from one exchange to another.

CryptoArb is built to exploit these opportunities to automatically profit from
the temporary price difference while maintaining market-neutral, to mitigate
risks.

Dependencies: <a href="https://www.openssl.org/source" target="_blank">OpenSSL</a>, <a href="http://curl.haxx.se" target="_blank">CURL</a>, <a href="http://www.sqlite.org" target="_blank">SQLite3</a>, <a href="https://cmake.org" target="_blank">CMake</a>

## Run and build with docker

### What's included

Based on ubuntu:22.04.

- C++ 20
- Compilers:
- Buildtools: cmake
- Other tools:

### How to use the image to start development

This setup bind-mounts the project file from host to the container. Any changes inside the container will be reflected to the files on the host.

1. Clone the project

```bash
git clone https://github.com/ethanh6/CryptoArb.git
```

2. Build the image and start container

```bash
# inside the project
docker compose up --detach
```

3. Attach to container

```bash
# method 1: use vs code remote explorer, dev containers

# method 2: attach via terminal
docker exec -it cryptoarb-app /bin/bash
```

4. Build and run the project

```bash
rm -rf build && cmake -S . -B build && cmake --build build && ./build/CryptoArb
```

## Theory of Arbitrage

*#Bellman-Ford Algorithm*, *#Negative Cycle Detection* and *#Graph Theory*.

### Problem Statment

Suppose we are trading on cryptoc urrencies A, B, C, D, E, and there are exchanges W, X, Y, Z.

For a single exchange W:

Notation: `AB_w` means the rate that converts `A` -> `B` at exchange `W`
|     | A   | B   | C   | D |
| --- | --- | --- | --- | --- |
| A | 1 | AB_w | AC_w | AD_w |
| B | BA_w | 1 | BC_w | BD_w |
| C | CA_w | CB_w | 1 | CD_w |
| D | DA_w | DB_w | DC_w | 1 |

The goal is to determine if there is any arbitrage opportunity.

Specifically speaking, profitability exists if it started from x units of a cryptocurrency initially and resulted in having more than x units of that cryptocurrency, after performing a series of trades.

This assumes zero transaction costs and sufficient amount of cryptocurrency in
each exchange.

### Solution

The relationship of the cryptos exchanging rate can be interpreted as a graph, where currencies
can be represented as vertices of a graph, and edges are trading pair of the
traing pair.

It is possible that there exists multiple edges between two vertices, where a
single edge represents different rates of the trading pair.

The goal of the arbitrage program is to find a cycle from an arbitrary
vertices that form a profitable scheme.

## Results

The trading results and activity is logged at `./output/log/CryptoArb_log_*`, and stored at `CryptoArb.db` using SQLite.

## Disclaimer

Use this software at your own risk. You are responsible for your own assets. Past performance does not necessarily indicate future profits. The author assumes no responsibility for the trading results.

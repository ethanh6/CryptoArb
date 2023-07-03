# CryptoArb

## How to build & run

1. run once to init the project
`cmake -S . -B build` 

2. run the script
`./run.sh`

## Theory of Arbitrage


The relationship of the cryptos exchanging rate can be seen as a graph, where currencies
can be represented as vertices of a graph, and edges are trading pair of the
traing pair. 

It is possible that there exists multiple edges between two vertices, where a
single edge represents different rates of the trading pair.


The goal of the arbitrage program is to find a cycle from an arbitrary
vertices that form a profitable scheme.

Suppose we are trading on cryptoc urrencies A, B, C, D, E, and there are exchanges W, X, Y, Z.

For a single exchange W: (AB_w means the rate that converts A -> B)
|     | A   | B   | C   | D |
| --- | --- | --- | --- | --- |
| A | 1 | AB_w | AC_w | AD_w |
| B | BA_w | 1 | BC_w | BD_w |
| C | CA_w | CB_w | 1 | CD_w |
| D | DA_w | DB_w | DC_w | 1 |

Specifically:
Conversion rate between 





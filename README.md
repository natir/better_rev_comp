Goal of this project is determinate if two differente methode for reverse complement have different execution time.

## Build

```bash
mkdir build
cd build
cmake ..
make
cd ..
```

## Run

```bash
./better_rev_comp 1000 110000 AACCTTGGAACCTTGGAACCTTGGAACCTTGGC > time.csv
```

1. parameter is the number of replication
2. parameter number call of function in each replication
3. parameter the reverse complement sequence

## Generate graph

```bash
./generate_graph.R time.csv out.png
```

1. parameter is csv file content the result
2. parameter is the png outfile

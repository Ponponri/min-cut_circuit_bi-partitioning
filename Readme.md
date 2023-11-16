# Min-cut Circuit Bi-partitioning

## Environment
- gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
- Need to install gcc-multilib to run code in 32bit mode (auto install when operate make command).

# Run code
- Use "make" to make the project. You need to press your password to permit the sudo command.
```
make
```

- Use "./m11102137 filename.blif ratio" to run the code, it would read the filename.blif and then print the result on the screen.

```
./m11102137 filename.blif {ratio}
```

- The result include 2 partial of nodes with their name, sum of area, the partition ratio(ratio of area), and cut size.

- You can use "ratio" to control the ratio of area between two partition. The range of "ratio" is between 0.5 to 0.99.
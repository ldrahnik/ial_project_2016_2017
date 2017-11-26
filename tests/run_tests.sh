#usr/bin/sh

# 001 - for development (this graph https://www.algoritmy.net/article/7478/Bellman-Forduv-algoritmus, but numbers are chars)
#./shreya -i ./tests/test01 A E -o -r

# 002 - for development (more - two - results)
#./shreya -i ./tests/test02 A B -o -r

# 003 - for development (more - two - results) REVERSED
#./shreya -i ./tests/test03 A B -o -r

# 004 - for development (this graph http://www.martinbroadhurst.com/floyd-warshall-algorithm-in-c.html, but numbers are chars)
./shreya -i ./tests/test04 B D -o -r

# 005 - http://www.martinbroadhurst.com/dijkstras-shortest-paths-algorithm-in-c.html, but numbers are chars)
./shreya -i ./tests/test05 A F

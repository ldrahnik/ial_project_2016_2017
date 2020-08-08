## Vygenerování obrázků s grafy (pomocí knihovny [graphviz](https://graphviz.gitlab.io/))

Převedení grafu zadaného jako `--input` s koncovkou `*.in` a vyžadovaným formátem pro program pomocí jednoduchého python scriptu na formát `.dot` (graph description language) a poté jeho vykreslení do obrázku zadaného jako výstup scriptu `*.png`.

```
sudo apt-install python3-pip
pip3 --version
# pip 9.0.1 from /usr/lib/python3/dist-packages (python 3.6)
pip3 install --upgrade networkx
```

```
python3.6 ./graphviz/convert_script.py --input ./tests/test01.in --output ./tests/test01.png [-o] [-r]
```



## Vygenerování obrázků s grafy (pomocí knihovny [graphviz](https://graphviz.gitlab.io/))

Převedení grafu zadaného jako `--input` s koncovkou `*.in` a vyžadovaným formátem pro program pomocí jednoduchého python scriptu na formát `.dot` (graph description language) a poté jeho vykreslení do obrázku zadaného jako výstup scriptu `*.png`.

```
python3.6 ./graphviz/convert_script.py --input ./tests/test01.in --output ./tests/test01.png [-o] [-r]
```


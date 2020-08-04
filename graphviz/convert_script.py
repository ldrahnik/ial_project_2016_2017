#!/usr/bin/python

import sys
import getopt
import networkx as nx
import matplotlib.pyplot as plt
from networkx.drawing.nx_agraph import graphviz_layout, to_agraph

def main(argv):
   inputFile = None
   outputFile = None
   oriented = False
   rated = False

   # parse options
   try:
      opts, args = getopt.getopt(argv,"ro", ['input=', 'output='])
   except getopt.GetoptError:
      print('convert_script.py --input <.in file> --output <.png file> [-r] [-o]')
      sys.exit(2)
   for opt, arg in opts:
      if opt == '-o':
         oriented = True
      elif opt == '-r':
         rated = True
      elif opt in ('--input'):
         inputFile = arg
      elif opt in ('--output'):
         outputFile = arg

   # create Graph
   # TODO: directed
   # TODO: rated
   g = nx.DiGraph(directed=oriented)
   for line in open(inputFile).readlines():
      adj = list(map(str, line.split()))

      vertex_from = adj[0]
      edge_value = adj[1]
      vertex_to = adj[2]

      g.add_edge(vertex_from, vertex_to, weight=edge_value)

   # preview .dot and write .png
   # TODO: arrows
   # TODO: node text color
   a = to_agraph(g)
   print(a)
   a.layout('dot')
   pos = nx.circular_layout(g)
   nx.draw(g, pos, None)
   labels = nx.get_edge_attributes(g,'weight')
   plt.savefig(outputFile, format='png')

if __name__ == "__main__":
   main(sys.argv[1:])

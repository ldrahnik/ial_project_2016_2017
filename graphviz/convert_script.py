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
   G = nx.DiGraph(directed=oriented)
   for line in open(inputFile).readlines():
      adj = list(map(str, line.split()))

      vertex_from = adj[0]
      edge_value = adj[1]
      vertex_to = adj[2]

      G.add_edge(vertex_from, vertex_to, weight=edge_value)

   # preview .dot and write .png
   a = to_agraph(G)
   print(a)
   a.layout('dot')
   pos = nx.circular_layout(G)
   nx.draw_networkx_nodes(
      G,pos,
      G.nodes(),
      node_color='b',
      node_size=500,
      alpha=1
   )
   nx.draw_networkx_labels(
      G,
      pos,
      font_size=12,
      font_color='#FFDEAD'
   )
   nx.draw_networkx_edges(
      G,
      pos,
      G.edges(),
      width=1,
      alpha=0.5,
      edge_color='k'
   )
   nx.draw_networkx_edge_labels(
      G,
      pos
   )
   labels = nx.get_edge_attributes(G,'weight')
   plt.axis('off')
   plt.savefig(outputFile, format='png')

if __name__ == "__main__":
   main(sys.argv[1:])

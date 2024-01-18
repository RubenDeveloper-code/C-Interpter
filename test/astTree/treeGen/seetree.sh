#!/bin/bash

DIR="test/astTree/treeGen"

gdb ./$DIR/tree_test.o
dot -Tpng $DIR/astTree.dot -o $DIR/ast.png
feh $DIR/ast.png

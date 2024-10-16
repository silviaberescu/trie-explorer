Berescu Silvia-Maria

## Trie-based Data Structure Project

# Overview

This project implements various operations on a tree data structure, more specifically a sufix tree (trie), using the C programming language. The main functionality includes constructing a tree from a list of words, performing operations like insertion, searching, and prefix matching, which are fundamental in many applications like autocomplete systems, spell checkers, IP routing, and compacting the tree for efficient storage. Each operation is triggered by command-line arguments.

# Features

The program supports four main operations based on the provided command-line arguments:

-c1: Constructs a tree from input words and outputs the tree structure.
-c2: Builds a tree, reads an integer K, and calculates certain properties (number of leaves, maximum descendants, and maximum suffixes of length 
K).
-c3: Checks for the existence of certain suffixes in the tree after reading numbers N (number of words) and M (number of suffixes to check).
-c4: Compact the tree structure and output the compacted representation.

# Main Functionality

The program reads from specified input and output files based on the operation specified via command-line arguments. Here’s a breakdown of the operations:

Operation -c1:
Reads words from the input file and builds a tree.
Each word is processed to remove newline characters and is appended with a '$' to signify the end of the word. The function insertWord is used to insert each word into the tree.

Operation -c2:
Similar to -c1, it constructs a tree and calculates:
Number of leaves using number_leaves.
Maximum number of descendants per node using nr_max_descendents.
Number of maximum-length suffixes using number_sufixes.

Operation -c3:
After building the tree, it checks for the existence of M suffixes using the function check_sufix, which verifies the presence of each suffix in the tree.

Operation -c4:
Constructs a compact representation of the tree with compact_tree.
The function initCTree initializes nodes for the compacted tree and manages memory efficiently.

# Usage

To compile and run the program, use the following commands in your terminal:

make
./tree_operations -cX input_file.txt output_file.txt

The input file should contain a list of words (one per line) for operations -c1, -c2, and -c3.
For operation -c2, an integer K should be specified after the words.
For operation -c3, after the words, you should provide M followed by M suffixes to check.
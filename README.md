# Compression
A program that compress and uncompress file using the Huffman Tree

Huffman encoding is a technique for compressing files to save space on storage devices. The general idea is to build a full binary tree whose leaves represent the unique characters of the file and whose branches represent the bits of the code. On sufficiently large files, this technique will result in a net reduction in the number of bytes required to store the information.

The basic algorithms are:

compress
1. Read the original file data
2. Generate a sorted character distribution: a priority queue of trees sorted by tree weight.
3. Build a Huffman tree. Store codes for each character in a separate array of strings.
4. Write the overhead (source file length and tree) to the standard output
5. Read the original file a second time, generating bits for each source character. When you have at least 8 bits, remove them, convert to a character, and write to standard output.
6. If you have any leftover bits, pad to a multiple of 8 bits, generate and write the character.

uncompress
1. Read the overhead from the standard input
2. Start at the root of the tree,
3. Read bits, 8 at a time from the standard input. Use each bit to move from an internal node toward a leaf (0-left, 1-right).
4. When you reach a leaf, output the character. Stop when you’ve output the correct number of characters, otherwise go back to step 2.

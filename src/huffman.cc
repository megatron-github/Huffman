/***************************************************************************************************

    File: huffman.cc

    Description:
        A program that compresses a given file by taking the data from the file to combine
        the unicode of each characters, turn them into new unicode, and encodes them into a
        Huffman tree. Write the compressed file using the new founded unicode to standard
        output. The compressed file is supposed to be smaller than the original file. The
        program also decompresses files into the original file using the same Huffman tree.

***************************************************************************************************/
#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "queue/minHeap.h"

// Define a node of a Huffman tree
struct hnode {
    int character;
    size_t count;
    hnode *left;
    hnode *right;
    hnode( int character, size_t count, hnode *left = NULL, hnode *right = NULL)
        : character(character), count(count), left(left), right(right) {}
};

// Huffman Tree priority-value-assigning function
int hnode_cmp(hnode * const & a, hnode * const & b) {
    // return int > 0 if there are more letter a than letter b in a given string,
    // or if letter a come after letter b in the aphabet. Otherwise,
    // return int < 0

    if (a->count > b->count) return 1;
    if (a->count < b ->count) return -1;
    return (a->character) - (b->character);
}

bool show_bits = true;   // might be useful for debugging

int bits_to_byte(std::string bitstr) {
    // a function to convert bit-string to byte

    int result = 0;

    // For each bit in the bitstring, add 2^(index) to result if bit is "1"
    for (size_t i = 0, v = 128; i < 8; i++, v /= 2) {
        if (bitstr[i] == '1') {
            result += v;
        }
    }
    return result;
}

std::string byte_to_bits(int byte) {
    // a function that convert byte to bit-string

    std::string result = "";
    size_t i;
    int v;
    for (i = 0, v = 128; i < 8; i++, v /= 2) {

        if (byte >= v) {    // if the given byte can divide v, add "1" to the bitstring
            result += '1';
            byte -= v;
        }
        else {              // if the given byte cannot divide v, add "0"
            result += '0';
        }
    }
    return result;
}

void get_char_distribution(size_t *counts, size_t & size, std::istream & istr) {
    // Given all characters read from istr, get the distribution of the
    // characters, i.e.
    // counts[k] = the number of occurrences of k in the istream.
    // size is the number of characters read

    // reads the entire contents of a file
    while (true) {
        int ch = istr.get();
        if (!istr) { break; }

        // determines input size and counts the frequencies of all characters
        if (ch > -1) {
            counts[ch]++;
            size++;
        }
    }
}

hnode * make_tree(size_t *counts) {
    // Assemble a queue of Huffman trees into one Huffman tree

    min_heap<hnode *> queue(hnode_cmp);

    // Add a node for each character found in the original file into a priority queue
    for (int i = 0; i < 256; i++) {
        if (counts[i] != 0) {
            queue.add(new hnode(i, counts[i], nullptr, nullptr));
        }
    }

    // Tree-building algorithm:
    // Repeatedly use the priority queue to retrieve two top nodes
    // and combine them to make a tree. Then reinserting the tree into
    // the queue until queue size is 1.
    while (queue.size() > 1) {
        hnode *left_h = queue.front();
        queue.remove();
        hnode *right_h = queue.front();
        queue.remove();
        queue.add(
            new hnode(left_h->character, left_h->count + right_h->count, left_h, right_h)
        );
    }

    // The last node inside the queue is the Huffman tree.
    hnode *result = queue.front();
    queue.remove();
    return result;
}

void make_codes(hnode *tree, std::string *codes, std::string code="") {
    // builds an array of string encodings from a Huffman tree

    // if is at leaf, record the path of the character into codes
    if (!tree->left && !tree->right) {
        codes[tree->character] = code;
        return;
    }

    // Cite: Remove last character from C++ string - Stack Overflow
    // Desc: How to delete the last character in a string
    // URL: https://stackoverflow.com/questions/2310939/
    // remove-last-character-from-c-string

    // traverse through the tree and record the path as the program go.
    // add "0" to the code if the character located on the left of the tree
    // add "1" to the code if the character located on the right of the tree
    code += '0';
    make_codes(tree->left, codes, code);
    code.pop_back();
    code += '1';
    make_codes(tree->right, codes, code);
}

void write_tree(hnode *tree, std::ostream & ostr) {
    // write the character representation of a Huffman tree into
    // the compressed file for later decompression
    // example output: ILaILbLc

    // Given a Huffman tree, write its representation into the compressed file.
    if (!tree->left && !tree->right) {
        // "L" is a leave, next to "L" is the character of the original file
        ostr << 'L' << (char)tree->character;
        return;
    }
    else {
        // "I" is internal node, all internal node have 2 branches because
        // Huffman tree is a full-tree
        ostr << 'I';
        write_tree(tree->left, ostr);
        write_tree(tree->right, ostr);
        return;
    }
}

hnode * read_tree(std::istream & istr) {
    // creates a Huffman tree by reading a characters representation of the tree.
    // inverse of write_tree

    int v = istr.get(); // use the tree in the compressed file to build the tree

    // "L" is stand for leave, the character follow "L" is the character in the
    // original file
    if (v == 'L') return new hnode(istr.get(), 0, nullptr, nullptr);

    // "I" is an internal node, Huffman tree is a full tree:
    // all internal nodes have 2 branches.
    else {
        hnode *left = read_tree(istr);
        hnode *right = read_tree(istr);
        return new hnode(left->character, 0, left, right);
    }
}

void write_compress(std::istream & istr, std::string *codes, std::ostream & ostr) {
    // reads all uncompressed characters from a file and
    // generates compressed character output

    std::string output = "";

    // reads the entire contents of a file
    while (true) {
        int ch = istr.get();
        if (!istr) break;
        output += codes[ch];    // add the encoded path together to make a bit-string

        // given a bit-string, convert it into byte to get
        // corresponding unicode characters and add the
        // character to the compressed file
        if (output.size() >= 8) {
        ostr << static_cast<char>(bits_to_byte(output));
        output = output.substr(8, output.size());
        }
    }

    // Given a leftover bit-string with size less than 8 bits,
    // pad zeros to bit-string to make it convertible to a unicode
    // character
    while (output.size() < 8) {
        output += '0';
    }
    ostr << static_cast<char>(bits_to_byte(output));
}

void compress(char *filename) {
    // Create compresseion of a file such that the compressed file is
    // smaller compared to its original size

    // open the file
    std::ifstream in(filename);
    size_t counts[256] = {}; // initializes all to zero.
    size_t file_size = 0;

    // find the file size and the distribution of each character in the file
    get_char_distribution(counts, file_size, in);
    in.close();
    if (file_size == 0) return;

    // create a Huffman tree using a priority queue, in which the file characters
    // are sorted according to their values and distribution
    hnode *tree = make_tree(counts);
    std::string codes[256];

    // create a bit-strings that encodes the location of the characters
    // within the Huffman tree (0 is left node, 1 is right node)
    make_codes(tree, codes);

    // enter the original file size into the compressed file
    std::cout << file_size;

    // enter the Huffman tree into the compressed file for later decompression
    write_tree(tree, std::cout);

    // Second pass through the input....
    in.open(filename);

    // write the compressed file
    write_compress(in, codes, std::cout);
}

int read_bitstr(std::istream & istr, std::string & bitstr, hnode *tree) {
    // reads a single “bit” from a file (using buffering) and
    // uncompresses a stream of characters using a Huffman tree

    // get a bit-string encoding using the characters from the compressed file
    if (bitstr == "") {
        int byte = istr.get();
        bitstr += byte_to_bits(byte);
    }

    // return character when reaching the leave of the tree
    if (!tree->left && !tree->right) return tree->character;

    // the binary string tell where to search for origianl characters in the tree,
    // i.e.: "0" is left of the tree and "1" is right of the tree
    if (bitstr[0] == '0') tree = tree->left;
    if (bitstr[0] == '1') tree = tree->right;

    // move on to next character in the binary string as searching continue
    bitstr = bitstr.substr(1, bitstr.size());
    return read_bitstr(istr, bitstr, tree);
}

void write_uncompress(std::istream & istr, size_t file_size, hnode * tree) {
    // Given a bit-string of arbitrary length, buffers the bits into blocks
    // of 8 (a byte) to the binary encoding of a unicode character

    std::string buffers = "";
    for (size_t i = 0; i < file_size; i++) {
        hnode *reader = tree;

        // read each characters in the compressed file
        // and translate them to binary strings
        int ch = read_bitstr(istr, buffers, reader);
        std::cout << static_cast<char>(ch);
    }
}

void uncompress() {
    // decode the compressed file and recreate the original file
    // from the compressed file

    if (std::cin.peek() == EOF) return;  // handle empty file
    size_t file_size;
    std::cin >> file_size;
    hnode *tree = read_tree(std::cin);
    write_uncompress(std::cin, file_size, tree);
}

bool ends_with(const std::string & str, const std::string & suffix) {
    // argument parsing helper

    return str.size() >= suffix.size() &&
           str.substr(str.size() - suffix.size()) == suffix;
}

bool is_compress(const std::string & command) {
    // parse argument

    return ends_with(command, "compress") &&
           !ends_with(command, "uncompress");
}

int main(int argc, char **argv) {
    // main

    assert(argc == argc);
    if (is_compress(argv[0])) {
        if (std::string(argv[1]) == "-b") {
            show_bits = true;
            compress(argv[2]);
        }
        else {
            compress(argv[1]);
        }
    }
    else {
        uncompress();
    }

}

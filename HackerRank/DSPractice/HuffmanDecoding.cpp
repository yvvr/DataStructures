/**
 * Huffman coding assigns variable length codewords to fixed length input characters based on their frequencies.
 * More frequent characters are assigned shorter codewords and less frequent characters are assigned longer codewords.
 * All edges along the path to a character contain a code digit. If they are on the left side of the tree, they will be a 0 (zero).
 * If on the right, they'll be a 1 (one). Only the leaves will contain a letter and its frequency count.
 * All other nodes will contain a null instead of a character, and the count of the frequency of all of it and its descendant characters.
 *
 * For instance, consider the string ABRACADABRA. There are a total of  11 characters in the string.
 * This number should match the count in the ultimately determined root of the tree.
 * Our frequencies are A=5, B=2, R=2, C=1 and D=1. The two smallest frequencies are for C and D, both equal to 1, so we'll create a tree with them.
 * The root node will contain the sum of the counts of its descendants, in this case 1+1 = 2.
 * The left node will be the first character encountered, C, and the right will contain D.
 * Next we have 3 items with a character count of 2: the tree we just created, the character B and the character R.
 * The tree came first, so it will go on the left of our new root node.
 * B will go on the right. Repeat until the tree is complete, then fill in the 1's and 0's for the edges.
 *
 * Function Description
 *
 * Complete the function decode_huff in the editor below. It must return the decoded string.
 * decode_huff has the following parameters:
 *
 * root: a reference to the root node of the Huffman tree
 * s: a Huffman encoded string.
 *
 */

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>

struct node
{
    int freq;
    char data;
    node *left;
    node *right;
};

struct deref
{
    bool operator()(const node *a, const node *b) const
    {
        return a->freq > b->freq;
    }
};

typedef std::priority_queue<node *, std::vector<node *>, deref> spq;

node *huffman_hidden(std::string s)
{

    spq pq;
    std::vector<int> count(256, 0);

    for (int i = 0; i < s.length(); i++)
    {
        count[s[i]]++;
    }

    for (int i = 0; i < 256; i++)
    {

        node *n_node = new node;
        n_node->left = NULL;
        n_node->right = NULL;
        n_node->data = (char)i;
        n_node->freq = count[i];

        if (count[i] != 0)
            pq.push(n_node);
    }

    while (pq.size() != 1)
    {

        node *left = pq.top();
        pq.pop();
        node *right = pq.top();
        pq.pop();
        node *comb = new node;
        comb->freq = left->freq + right->freq;
        comb->data = '\0';
        comb->left = left;
        comb->right = right;
        pq.push(comb);
    }

    return pq.top();
}

void print_codes_hidden(node *root, std::string code, std::map<char, std::string> &mp)
{
    if (root == NULL)
        return;

    if (root->data != '\0')
    {
        mp[root->data] = code;
    }

    print_codes_hidden(root->left, code + '0', mp);
    print_codes_hidden(root->right, code + '1', mp);
}

void decodeTree(node *root, std::string &s, std::string currS, std::string &result)
{
    if (root->left == nullptr && root->right == nullptr)
    {
        result += root->data;
        s = currS;
        return;
    }
    if (currS[0] == '0')
    {
        decodeTree(root->left, s, currS.substr(1), result);
    }
    else
    {
        decodeTree(root->right, s, currS.substr(1), result);
    }
}

void decode_huff(node *root, std::string s)
{
    std::string result;

    while (s.size() > 0)
    {
        std::string currS = s;
        decodeTree(root, s, currS, result);
    }

    std::cout << result << std::endl;
}

int main()
{

    std::string s;
    std::cin >> s;

    node *tree = huffman_hidden(s);
    std::string code = "";
    std::map<char, std::string> mp;

    print_codes_hidden(tree, code, mp);

    std::string coded;

    for (int i = 0; i < s.length(); i++)
    {
        coded += mp[s[i]];
    }

    decode_huff(tree, coded);

    return 0;
}
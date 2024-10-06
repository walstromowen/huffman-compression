/*
    Longest Huffman Compression Algorithm.
    Author: Owen Walstrom
    Date: 10/5/2024
    
*/


#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Node {
public:
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node(char charac, int freq) : character(charac), frequency(freq), left(nullptr), right(nullptr) {}
};

Node* buildHuffmanTree(const std::unordered_map<char, int>& freqTable) {
    std::vector<Node*> nodes;

    // Create a leaf node for each character
    for (const auto& pair : freqTable) {
        nodes.push_back(new Node(pair.first, pair.second));
    }

    // Build the Huffman tree
    while (nodes.size() > 1) {
        std::sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
            return a->frequency < b->frequency;
        });

        Node* left = nodes.front();
        nodes.erase(nodes.begin());
        Node* right = nodes.front();
        nodes.erase(nodes.begin());

        Node* newNode = new Node('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        nodes.push_back(newNode);
    }

    return nodes.front(); // Root of the Huffman tree
}

void buildHuffmanCodes(Node* treeNode, const std::string& code, std::unordered_map<char, std::string>& codes) {
    if (treeNode->character != '\0') {
        codes[treeNode->character] = code;
    } else {
        buildHuffmanCodes(treeNode->left, code + "0", codes);
        buildHuffmanCodes(treeNode->right, code + "1", codes);
    }
}

int main() {
    std::string text = "abbcccddddeeeeeeefffffffffffffffff";
    std::unordered_map<char, int> freqTable;

    for (char charac : text) {
        freqTable[charac]++;
    }

    Node* treeNodes = buildHuffmanTree(freqTable);
    std::unordered_map<char, std::string> codes;
    buildHuffmanCodes(treeNodes, "", codes);

    for (const auto& pair : codes) {
        std::cout << pair.first << ": " << pair.second << std::endl; // Output the codes
    }

    return 0;
}




/*
int main(){
    string text = "testtest";
    unordered_map<char, int> frequencyTable = {};
    
    for(int i = 0; i < text.size(); i++){
        frequencyTable[text[i]]++;
    };
        
    Node* treeNodesRoot = buildHuffmanTree(frequencyTable); // Root of the Huffman treeNodes
    cout<<treeNodesRoot->getCharacter();
    unordered_map<char, string> codes = generateHuffmanCodes(treeNodesRoot);

    printCodes(codes);
    return 0;
}
*/


/*JS implementation
    class Node {
    constructor(char, freq) {
        this.char = char;
        this.freq = freq;
        this.left = null;
        this.right = null;
        }
    }

    function buildHuffmanTree(freqTable) {
    const nodes = [];

    // Create a leaf node for each character
    for (const char in freqTable) {
        nodes.push(new Node(char, freqTable[char]));
    }

    // Build the Huffman treeNodes
    while (nodes.length > 1) {
        nodes.sort((a, b) => a.freq - b.freq); // Sort by frequency

        const left = nodes.shift();
        const right = nodes.shift();

        const newNode = new Node(null, left.freq + right.freq);
        newNode.left = left;
        newNode.right = right;

        nodes.push(newNode);
    }

    return nodes[0]; // Root of the Huffman treeNodes
    }

    function buildHuffmanCodes(treeNodes, code = "", codes = {}) {
    if (treeNodes.char) {
        codes[treeNodes.char] = code;
    } else {
        buildHuffmanCodes(treeNodes.left, code + "0", codes);
        buildHuffmanCodes(treeNodes.right, code + "1", codes);
    }

    return codes;
    }

    // Example usage:
    const text = "abracadabra";
    const freqTable = {};

    for (const char of text) {
    freqTable[char] = (freqTable[char] || 0) + 1;
    }

    const treeNodes = buildHuffmanTree(freqTable);
    const codes = buildHuffmanCodes(treeNodes);

    console.log(codes); // Output: { a: "0", b: "10", r: "110", c: "1110", d: "1111" }




    Explanation:
    Node class: Represents a node in the Huffman treeNodes, storing the character, frequency, and left/right child nodes.
    buildHuffmanTree function: Takes a frequency table as input and builds the Huffman treeNodes using a priority queue (implemented using nodes.sort).
    buildHuffmanCodes function: Recursively traverses the Huffman treeNodes to generate the Huffman codes for each character.
    How to use:
    Create a frequency table for your input data.
    Call buildHuffmanTree to construct the treeNodes.
    Call buildHuffmanCodes to generate the codes.

*/





/* Attempt 2
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node{ // A Tree node
	char ch;
	int freq;
	Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right){ // Function to allocate a new treeNodes node
	Node* node = new Node();
	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;
	return node;
}

struct comp{// Comparison object to be used to order the heap
	bool operator()(Node* left, Node* right){ // return lowest frequency
		return left->freq > right->freq;
	}
};

void encode(Node* root, string str, unordered_map<char, string> &huffmanCode){ // traverse the Huffman Tree and store Huffman Codes in a map.
	if(root == nullptr){
        return;
    }
	if(!root->left && !root->right){// found a leaf node
		huffmanCode[root->ch] = str;
	}
	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}


Node* buildHuffmanTree(string text){ 
	unordered_map<char, int> freq; // count frequency of appearance of each character and store it in a map
	for (char ch: text) {
		freq[ch]++;
	}
	priority_queue<Node*, vector<Node*>, comp> treeNodes; // to store nodes of Huffman treeNodes;
	for (auto pair: freq) { // Create a leaf node for each character and add it to the priority queue.
		treeNodes.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}
	while (treeNodes.size() != 1){ 	// do till there is more than one node in the queue
		Node *left = treeNodes.top(); 
        treeNodes.pop(); // Remove the two nodes of lowest frequency from the queue
		Node *right = treeNodes.top();	
        treeNodes.pop();

		int sum = left->freq + right->freq;// Create a new internal node with these two nodes as children and with frequency equal to the sum of the two nodes' frequencies. Add the new node to the priority queue.
		treeNodes.push(getNode('\0', sum, left, right)); 
	}

	Node* rootNode = treeNodes.top(); //THIS is Root of the Huffman treeNodes which is a node pointer
    return rootNode;
}

void printCodes(Node* rootNode, string text){ // traverse the Huffman Tree and store Huffman Codes in a map. Also prints them
    unordered_map<char, string> huffmanCode; 
	encode(rootNode, "", huffmanCode);
	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair: huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	string str = ""; // print encoded string
	for (char ch: text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';
}

int main(){ // Huffman coding algorithm
	string text = "abcddef";
	Node* rootNode = buildHuffmanTree(text);
    printCodes(rootNode, text);
	return 0;
}







/* Attempt 2
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h> 
using namespace std;

class Node{
    private:
        char character;
        int frequency;
        Node *leftChild, *rightChild;
    public:
        Node(char character, int frequency){
            this->character = character;
            this->frequency = frequency;
            this->leftChild = nullptr;
            this->rightChild = nullptr;
        };
        char getCharacter(){
            return this->character;
        }
        int getFrequency(){
            return this->frequency;
        };
        Node* getLeftChild(){
            return this->leftChild;
        };
        Node* getRightChild(){
            return this->rightChild;
        };
        void setChildren(Node* left, Node* right){
            this->leftChild = left;
            this->rightChild = right;
        };
};

Node* buildHuffmanTree(unordered_map<char, int> frequencyTable){
    vector<Node*> treeNodesNodes = {};

    for(int i = 0; i < frequencyTable.size(); i++){

    }
    // Create a leaf node for each character
    for (auto i = frequencyTable.begin(); i != frequencyTable.end(); i++) {
        Node* newNode = new Node(i->first, i->second);
        treeNodesNodes.push_back(newNode);
    }

     // Build the Huffman treeNodes
    while(treeNodesNodes.size() > 1){
        sort(treeNodesNodes.begin(), treeNodesNodes.end(), greater<>()); 

        Node* leftNode = treeNodesNodes[0];
        treeNodesNodes.erase(treeNodesNodes.begin());
        Node* rightNode = treeNodesNodes[0];
        treeNodesNodes.erase(treeNodesNodes.begin());

        Node* newNode = new Node(' ', leftNode->getFrequency() + rightNode->getFrequency());
        newNode->setChildren(leftNode, rightNode);
        
        treeNodesNodes.push_back(newNode);
        cout<<'i';
    }
   
    
    return treeNodesNodes[0];// THIS is Root of the Huffman treeNodes which is a node pointer
};

unordered_map<char, string> generateHuffmanCodes(Node* rootNode, string currentCode = "", unordered_map<char, string> codes = {}) {
    if (rootNode->getCharacter()!= ' ') {
        codes[rootNode->getCharacter()] = currentCode;
    } else {
        generateHuffmanCodes(rootNode->getLeftChild(), currentCode + "0", codes);
        generateHuffmanCodes(rootNode->getRightChild(), currentCode + "1", codes);
    }

    return codes;
}

void printCodes(unordered_map<char, string> codes){
    for (auto i = codes.begin(); i != codes.end(); i++){
        cout << i->first << " \t\t\t" << i->second << endl;
    };
}
*/














#include "heliocentric/objloader.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

typedef struct _IndexPair IndexPair;

struct _IndexPair {
    int normalIndex;
    int actualIndex;
};

ObjLoader::ObjLoader(ShaderProgram& sp) : sp(sp) {
}

vector<string> tokenize(string line, char token = ' ', bool allowEmptyTokens = false) {
    vector<string> tokens;
    int tokenStart = 0;
    int tokenLength = 0;

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == token) {
            if (tokenLength > 0 || allowEmptyTokens) {
                tokens.push_back(line.substr(tokenStart, tokenLength));
            }
            tokenStart = i + 1;
            tokenLength = 0;
        } else {
            tokenLength++;
        }
    }
    if (tokenLength > 0) {
        tokens.push_back(line.substr(tokenStart, tokenLength));
    }

    return tokens;
}

int getIndex(list<IndexPair>* l, unsigned short normalIndex) {
    for (list<IndexPair>::const_iterator it = l->begin(); it != l->end(); it++) {
        if (it->normalIndex == normalIndex) {
            return it->actualIndex;
        }
    }
    return -1;
}

bool ObjLoader::loadOBJ(Mesh& mesh, const string& filename) {
    // Open the file
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Unable to open file \"" << filename << "\"" << endl;
        return false;
    }

    // Containers
    vector<float> vertexData;
    vector<unsigned short> indices;

    // Temporary variables
    string line;
    vector<string> tokens;
    vector<string> tokens2;
    vector<float> vertices;
    vector<float> normals;
    vector<unsigned short> vIndices;
    //vector<unsigned short> tIndices;
    vector<unsigned short> nIndices;
    int nVertices = 0;
    int lineNumber = 0;

    // Parse the file
    while (!file.eof()) {
        lineNumber++;
        std::getline(file, line);

        if (line.length() > 0) {
            tokens = tokenize(line);

            if (tokens.front().compare("v") == 0) {
                if (tokens.size() != 4) {
                    cerr << "Error while parsing \"" << filename << "\"" << endl;
                    cerr << "    Expected three coordinates in line "
                            << lineNumber << ": \"" << line << "\"" << endl;
                    return false;
                }
                for (int i = 1; i < tokens.size(); i++) {
                    vertices.push_back(atof(tokens[i].c_str()));
                    nVertices++;
                }
            } else if (tokens.front().compare("vn") == 0) {
                if (tokens.size() != 4) {
                    cerr << "Error while parsing \"" << filename << "\"" << endl;
                    cerr << "    Expected three components in line "
                            << lineNumber << ": \"" << line << "\"" << endl;
                    return false;
                }
                for (int i = 1; i < tokens.size(); i++) {
                    normals.push_back(atof(tokens[i].c_str()));
                }
            } else if (tokens.front().compare("f") == 0) {
                if (tokens.size() != 4) {
                    cerr << "Error while parsing \"" << filename << "\"" << endl;
                    cerr << "    Expected three indices in line "
                            << lineNumber << ": \"" << line << "\"" << endl;
                    return false;
                }
                for (int i = 1; i < tokens.size(); i++) {
                    tokens2 = tokenize(tokens[i], '/', true);
                    if (tokens2.size() == 3) {
                        vIndices.push_back(atoi(tokens2[0].c_str()));
                        //tIndices.push_back(atoi(tokens2[1].c_str()));
                        nIndices.push_back(atoi(tokens2[2].c_str()));
                    } else if (tokens2.size() == 2) {
                        vIndices.push_back(atoi(tokens2[0].c_str()));
                        //tIndices.push_back(atoi(tokens2[1].c_str()));
                        nIndices.push_back(atoi(tokens2[0].c_str()));
                    } else if (tokens2.size() == 1) {
                        vIndices.push_back(atoi(tokens2[0].c_str()));
                        //tIndices.push_back(atoi(tokens2[1].c_str()));
                        nIndices.push_back(atoi(tokens2[0].c_str()));
                    } else {
                        cerr << "Error while parsing \"" << filename << "\"" << endl;
                        cerr << "    Incorrect face specification in line "
                                << lineNumber << ": \"" << line << "\"" << endl;
                        return false;
                    }
                }
            }//else { skip }
        }
    }

    // Close the file
    file.close();

    // Check if normals are specified
    if (normals.size() == 0) {
        cerr << "Error while parsing \"" << filename << "\"" << endl;
        cerr << "    No normals in mesh" << endl;
        return false;
    }
    
    // Create the lookup table
    list<IndexPair>* lookup;
    lookup = new list<IndexPair>[nVertices]();

    // Fill the actual vertex data array
    unsigned short nextIndex = 0;
    int index, vIndex, nIndex;
    list<IndexPair>* l;
    for (int i = 0; i < vIndices.size(); i++) {
        vIndex = vIndices[i] - 1;
        nIndex = nIndices[i] - 1;
        l = &lookup[vIndex];
        index = getIndex(l, nIndex);
        if (index == -1) {
            vertexData.push_back(vertices[vIndex * 3]);
            vertexData.push_back(vertices[vIndex * 3 + 1]);
            vertexData.push_back(vertices[vIndex * 3 + 2]);
            vertexData.push_back(normals[nIndex * 3]);
            vertexData.push_back(normals[nIndex * 3 + 1]);
            vertexData.push_back(normals[nIndex * 3 + 2]);
            index = nextIndex;
            l->push_back({nIndex, index});
            nextIndex++;
        }
        indices.push_back(index);
    }

    delete [] lookup;

    // Check if enough indices are specified
    if (indices.size() < 3) {
        cerr << "Error while parsing \"" << filename << "\"" << endl;
        cerr << "    No faces in mesh" << endl;
        return false;
    }

    // Load the data into the mesh
    mesh.load(vertexData, indices, &sp);
}

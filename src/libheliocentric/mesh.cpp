#include "heliocentric/mesh.hpp"
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

typedef struct _IndexPair IndexPair;

struct _IndexPair {
    int normalIndex;
    int actualIndex;
};

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

bool Mesh::load(const string& filename) {
    // Open the file
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        return false;
    }

    // Containers
    string line;
    vector<string> tokens;
    vector<string> tokens2;
    vector<float> vertices;
    vector<float> normals;
    vector<unsigned short> vIndices;
    //vector<unsigned short> tIndices;
    vector<unsigned short> nIndices;
    int nVertices = 0;

    // Parse the file
    while (!file.eof()) {
        std::getline(file, line);

        if (line.length() > 0) {
            tokens = tokenize(line);

            if (tokens.front().compare("v") == 0) {
                for (int i = 1; i < tokens.size(); i++) {
                    vertices.push_back(atof(tokens[i].c_str()));
                    nVertices++;
                }
            } else if (tokens.front().compare("vn") == 0) {
                for (int i = 1; i < tokens.size(); i++) {
                    normals.push_back(atof(tokens[i].c_str()));
                }
            } else if (tokens.front().compare("f") == 0) {
                for (int i = 1; i < tokens.size(); i++) {
                    tokens2 = tokenize(tokens[i], '/', true);
                    vIndices.push_back(atoi(tokens2[0].c_str()));
                    //tIndices.push_back(atoi(tokens2[1].c_str()));
                    nIndices.push_back(atoi(tokens2[2].c_str()));
                }
            }//else { skip }
        }
    }

    // Close the file
    file.close();

    // Create the vertex data array
    list<IndexPair>* lookup;
    lookup = new list<IndexPair>[nVertices]();

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

    // Upload data to VRAM
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
            sizeof (float) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof (unsigned short) * indices.size(), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Success

    return true;
}

void Mesh::render() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (6 * sizeof (float)), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof (float)), (void*) (3 * sizeof (float)));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
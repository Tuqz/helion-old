#include "heliocentric/mesh.hpp"
#include <fstream>
#include <iostream>
#include <GL/glext.h>

using namespace std;

vector<string> tokenize(string line) {
    vector<string> tokens;
    int tokenStart = 0;
    int tokenLength = 0;

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ' ') {
            if (tokenLength > 0) {
                tokens.push_back(line.substr(tokenStart, tokenLength));
                tokenStart = i + 1;
                tokenLength = 0;
            }
        } else {
            tokenLength++;
        }
    }
    if (tokenLength > 0) {
        tokens.push_back(line.substr(tokenStart, tokenLength));
    }

    return tokens;
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
    vector<float> normals;

    // Parse the file
    while (!file.eof()) {
        std::getline(file, line);

        if (line.length() > 0) {
            tokens = tokenize(line);

            if (tokens.front().compare("v") == 0) {
                for (int i = 1; i < tokens.size(); i++) {
                    vertexData.push_back(atof(tokens[i].c_str()));
                }
            } else if (tokens.front().compare("vn") == 0) {
                for (int i = 1; i < tokens.size(); i++) {
                    normals.push_back(atof(tokens[i].c_str()));
                }
            } else if (tokens.front().compare("f") == 0) {
                for (int i = 1; i < tokens.size(); i++) {
                    indices.push_back((unsigned short) atoi(tokens[i].c_str()));
                }
            }//else { skip }
        }
    }

    // Append normals to the array
    vertexData.insert(vertexData.end(), normals.begin(), normals.end());

    // Close the file
    file.close();

//    float vertexData2[] = {
//        0.5f, 0.5f, 0.5f,
//        0.5f, -0.5f, 0.5f,
//        -0.5f, -0.5f, 0.5f,
//        -0.5f, 0.5f, 0.5f,
//        0.5f, 0.5f, 0.5f,
//        -0.5f, 0.5f, 0.5f,
//        -0.5f, 0.5f, -0.5f,
//        0.5f, 0.5f, -0.5f,
//        0.5f, 0.5f, 0.5f,
//        0.5f, 0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, 0.5f,
//        0.5f, 0.5f, -0.5f,
//        -0.5f, 0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, 0.5f,
//        0.5f, -0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//        -0.5f, -0.5f, 0.5f,
//        -0.5f, 0.5f, 0.5f,
//        -0.5f, -0.5f, 0.5f,
//        -0.5f, -0.5f, -0.5f,
//        -0.5f, 0.5f, -0.5f,
//        0, 0, 1,
//        0, 0, 1,
//        0, 0, 1,
//        0, 0, 1,
//        0, 1, 0,
//        0, 1, 0,
//        0, 1, 0,
//        0, 1, 0,
//        1, 0, 0,
//        1, 0, 0,
//        1, 0, 0,
//        1, 0, 0,
//        0, 0, -1,
//        0, 0, -1,
//        0, 0, -1,
//        0, 0, -1,
//        0, -1, 0,
//        0, -1, 0,
//        0, -1, 0,
//        0, -1, 0,
//        -1, 0, 0,
//        -1, 0, 0,
//        -1, 0, 0,
//        -1, 0, 0
//    };
//
//    unsigned short indices2[] = {
//        0, 1, 2,
//        2, 3, 0,
//        4, 5, 6,
//        6, 7, 4,
//        8, 9, 10,
//        10, 11, 8,
//        12, 13, 14,
//        14, 15, 12,
//        16, 17, 18,
//        18, 19, 16,
//        20, 21, 22,
//        22, 23, 20
//    };


    // Upload data to VRAM
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
            sizeof (float) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
//                sizeof (vertexData2), &vertexData2[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof (unsigned short) * indices.size(), &indices[0], GL_STATIC_DRAW);
//                sizeof (indices2), &indices2[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Success
    return true;
}

void Mesh::render() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);//(void*) (numberOfVertices() * sizeof (float)));

    glDrawElements(GL_TRIANGLES, numberOfVertices(), GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

long unsigned int Mesh::numberOfVertices() {
    return 24 * 3;
}
#include "mesh.hpp"
#include <string>

class ObjLoader {
private:
    ShaderProgram& sp;
public:
    ObjLoader(ShaderProgram& sp);
    bool loadOBJ(Mesh& mesh, const std::string& filename);
};
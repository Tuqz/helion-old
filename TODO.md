Current tasks
-----
- [ ] Texture support
  - [ ] Image loading
  - [ ] Texture class
  - [ ] Mesh loading
    - [x] vt support
    - [ ] Restore lookup table 
  - [x] Shader support
  - [ ] How to combine with meshes?

###Considerations
*If checked, the consideration is currently implemented, but might be chosen to be changed not to be.*
- [ ] Make HcGame3D responsible for destroying entity tree?
- [x] Make addChild responsible for setting the parent?
- [x] Switch to CCW winding front faces?

Future tasks
-----
- [ ] Documentation
- [ ] Make mouse controls more intuitive
- [ ] Include a camera with a fixed up-direction
- [ ] Add VSync support
- [ ] Use VAO's
- [x] Handle multiple shader programs
- [ ] Mesh scaling
- [ ] Use impostors for planets, instead of sphere meshes
- [ ] Have a sun model
- [ ] Render background
- [ ] Bump mapping
- [ ] Include UI (Either write self or use existing)
- [ ] Use composition of entities
- Improve lighting
  - [ ] Multiple light sources
  - [ ] Specular lighting
  - [ ] HDR lighting
  - [ ] gamma correction
  - [ ] shadows
- OpenGL 3.1 compatibility
  - [ ] Bind the shader attributes - required for OpenGL < 3.3
  - [ ] Might need to disable OpenGL > 3.1 calls with #IF statements
- Windows compatibility
  - [ ] Add windows alternative for usleep call
  
Optional tasks
-----
- OBJ loader
  - [ ] Support different lengths for the vertex specification
  - [ ] Perform triangulation
  - [ ] Flip winding order
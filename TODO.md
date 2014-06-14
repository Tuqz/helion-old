Current tasks
-----
- [ ] Add entities
  - [x] Add root node to HcGame3D, and make it update and render the tree
  - [x] Add removeChild and orphanize methods
  - [x] Implement BasicEntity::render()
  - [x] Use matrix stack
  - [ ] Use composition of entities
  - [ ] separate model and view
- [ ] More general mesh loading

###Considerations
*If checked, the consideration is currently implemented, but might be chosen to be changed not to be.*
- [ ] Make HcGame3D responsible for destroying entity tree?
- [x] Make addChild responsible for setting the parent?

Future tasks
-----
- [ ] Add VSync support
- [ ] Use VAO's
- [ ] Handle multiple shader programs
- [ ] Texture support
- [ ] Use impostors for planets, instead of sphere meshes
- [ ] Include a camera with a fixed up-direction
- [ ] Have a sun model
- [ ] Render background
- Improve lighting
  - [ ] Multiple light sources
  - [ ] Specular lighting
  - [ ] HDR lighting
  - [ ] gamma correction
  - [x] ~~Properly clamp lighting angle (BUG)~~
- OpenGL 3.1 compatibility
  - [ ] Bind the shader attributes - required for OpenGL < 3.3
  - [ ] Might need to disable OpenGL > 3.1 calls with #IF statements
- Windows compatibility
  - [ ] Add windows alternative for usleep call
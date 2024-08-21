# TODO List

- [x] Set up project structure
- [x] Shadows with 1 light
- [x] cone bottom is showing wrong colors for some angles/ranges
- [x] Shadows with multiple lights
- [x] Fix Cache for BVH, maybe leaf cache (removed cache for now)
- [x] separate the header file to functions and structs
- [x] random rotation of all objects with R key
- [x] random movement/translation of all objects with maybe UHJK OL keys or something
- [x] display last command in terminal that shows ie: "all objects moved to right" "all objects rotated 30 degrees on x axis"
- [x] fix drawing of object when camera is inside the object
- [x] restructure main.c into different parts and folders
- [x] change all make_shape functions to take pointers as argument
- [x] bump maps implemented
- [x] check all artifacts between shape intersections
- [x] correct bump map transitions from light to ambient to be a bit smoother and better looking
- [x] camera gimbal lock when panning up or down
- [x] only resize if last resize was more than a second (or less) ago
- [ ] fix all memory things, free when creating new lists, bvhs, destroy images/textures, destroy MLX
- [ ] Parsing of scene files

# LIGHT
- [ ] fix hard-coded SHINE values
- [ ] fix hard-coded REFLECTIVENESS values
- [ ] -

# BVH
- [x] Implement BVH
- [x] maybe create AABB boxes on creation of the shape and then use it for partitioning also
# TODO List

- [x] Set up project structure
- [x] Shadows with 1 light
- [ ] Parsing of scene files
- [x] Shadows with multiple lights
- [x] Fix Cache for BVH, maybe leaf cache (removed cache for now)
- [ ] restructure main.c into different parts and folders
- [ ] change all make_shape functions to take pointers as argument
- [x] separate the header file to functions and structs
- [ ] random rotation of all objects with R key
- [ ] random movement/translation of all objects with maybe UHJK OL keys or something
- [ ] display last command in terminal that shows ie: "all objects moved to right" "all objects rotated 30 degrees on x axis"
- [ ] fix drawing of object when camera is inside the object
- [ ] -

# BVH
- [ ] fix hard-coded SHINE values
- [ ] fix hard-coded REFLECTIVENESS values
- [ ] -

# BVH
- [x] Implement BVH
- [x] maybe create AABB boxes on creation of the shape and then use it for partitioning also
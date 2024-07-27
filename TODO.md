# TODO List

- [x] Set up project structure
- [x] Shadows with 1 light
- [ ] Parsing of scene files
- [ ] Shadows with multiple lights
- [x] Fix Cache for BVH, maybe leaf cache (removed cache for now)
- [ ] restructure main.c into different parts and folders
- [ ] change all make_shape functions to take pointers as argument
- [ ] separate the header file to functions and structs

# BVH
- [x] Implement BVH
- [ ] maybe create AABB boxes on creation of the shape and then use it for partitioning also
- [ ] fix BVH partitioning with maybe a better sorting algorithm. or just more logical partitioning
- [ ] Implement BVH with leaf cache
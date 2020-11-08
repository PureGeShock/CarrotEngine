#define COMBINE(obj1, obj2)                     obj1##obj2
#define CONCAT(obj1, obj2)                      obj1 obj2
#define STRINGIFY(...)					        #__VA_ARGS__
#define SPLIT_SLASH(obj1, obj2)                 obj1/obj2
#define SPLIT_POINT_STR(obj1, obj2)             STRINGIFY(obj1.obj2)
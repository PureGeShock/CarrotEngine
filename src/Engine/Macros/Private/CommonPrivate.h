#define COMBINE(str1, str2)                     str1##str2
#define CONCAT(str1, str2)                      str1 str2
#define STRINGIFY(...)					        #__VA_ARGS__
# C++ Programming guidelines

## C++ Version 
The version to be utilized is ```C++20```

## File naming
Header files: ```<name>.h```
Source files: ```<name>.cpp```
- Every source file must have a header file with its same name.

## Header File Inclusion
All header files must include the compiler flag ```#pragma once```
Always include ONLY the files that are used
The inclusion order is:
1. Header guard ```#pragma once```
2. STD library imports (vector, string, thread ...)
3. Imported library imports (glm, assimp, glfw ...)
4. Scripts (player.h, physics.h ...)

## Namespaces
Not allowed, as they confuse programming syntax. e.g. ```using namespace std;```

## Classes
All classes must have:
- CamelCased name (e.g. ```class PlayerController```)
- A constructor (e.g. ```Player(){}```)
- A destructor (e.g. ```~Player(){}```)
- Public and private section
  
The **public** section must be organized in this manner:
1. Constructor
2. Destructor
3. Variable declarations
4. Functions

The **private** section must be organized in this manner:
1. Variable declarations
2. Functions

Example with all requirements:
```
class MyClass{
public:
  MyClass(){
    
  }
  ~MyClass(){

  }

  int var;
  void FunctionA(){

  }
private:
  int var;
  void FunctionB(){

  }
}
```

## Functions
Functions must be capitalized with CamelCase. Inline functions are preferred if their use is repeated constantly (e.g. calculating a magnitude).

```static inline float Magnitude(glm::vec3 v){ return(sqrt(v.x*v.x + v.y*v.y + v.z*v.z) }```

## Variables
Variables should be camelCased, beginning with a lowercase, e.g.
```int playerHealth;```


If performing mathematical operations, shorter variable names are preferred:
```
// Diffuse shading
float kd;
float a;
float I;
return I * kd * cos(a);
```

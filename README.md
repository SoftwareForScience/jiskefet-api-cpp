# Jiskefet C++ Client API
This is a C++ client API for Jiskefet based on the Swagger code generator


# Generated code
A lot of the code in this repository is generated. The exceptions are:
* The example code of `Example.cpp`
* Code in the `jiskefet` subdirectory. 
  This is a convenient wrapper around the generated code, and it's what users are supposed to use.
  It is currently focused on providing the basic necessities (i.e. posting/getting runs), 
  so it does not yet cover all of the functionality of the REST API.


# Setup
## alibuild
```
mkdir alice; cd alice
git clone https://github.com/SoftwareForScience/alidist.git
aliBuild build Jiskefet-Api-Cpp --defaults=o2
cd sw/SOURCES/cpprestsdk/master/master/
git submodule update --init
cd -
aliBuild build Jiskefet-Api-Cpp --defaults=o2
```
To use:
```
alienv enter Jiskefet-Api-Cpp/latest-o2
which jiskefet-api-cpp
```


## Manual setup
### Fedora
```
dnf install cpprest-devel boost-devel openssl-devel 
git clone https://github.com/PascalBoeschoten/jiskefet-api-cpp.git
mkdir build; cd build
cmake -DCPPREST_ROOT=/usr/include/cpprest ..
```

# Example code
If your api is at `http://myhost.server.address/api`:
```
export JISKEFET_URL=http://myhost.server.address/api
export JISKEFET_API_TOKEN=jnk5vh43785ycj4gdvlvm84fg...
./jiskefet-api-cpp-example
```
Note: don't include the "Bearer " part of the token, it's added automatically.

# Dev notes
## Code generation
The library code was generated using the Swagger editor (https://editor.swagger.io/): 

    1. Copy & paste swagger.yaml contents into the editor
    2. Under the "Generate Client" menu, select "cpprest"
    3. Extract the archive

At this point, it still needs some work however.

The generated CMakeLists.txt is not up to scratch. 
If you have to regenerate the code, it's recommended to update the custom CMakeLists.txt manually, rather than replacing it with the newly generated one.

In addition, the generated code is buggy in the way it initializes shared_ptrs.
It "wants" to initialize the shared_ptr with a default-initialized Object, but actually ends up with a null-initialized shared_ptr.
Maybe the generated way worked in an older C++ standard, but in C++17 it's broken.
To fix it, do a find and replace.
* From:
```
std::shared_ptr<Object> result(nullptr);
```
* To:
```
auto result = std::make_shared<Object>();
```


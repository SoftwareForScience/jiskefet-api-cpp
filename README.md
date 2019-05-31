# Jiskefet C++ Client API
This is a C++ client API for Jiskefet based on the Swagger code generator

The repository contains generated code in `src/cpprest-client`. For more information about this code, see the [Dev notes].

The rest of the source code consists of a convenient wrapper around the generated code, 
and it's this wrapper that users are supposed to use.
It is currently focused on providing the basic necessities (i.e. posting/getting runs), 
so it does not yet cover all of the functionality of the REST API.

There's also an example of the usage in `src/Example.cpp`


# Setup
## aliBuild
For setting up aliBuild, refer to https://alice-doc.github.io/alice-analysis-tutorial/building/
```
aliBuild init Jiskefet-Api-Cpp@master --defaults=o2
aliBuild build Jiskefet-Api-Cpp --defaults=o2
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
./jiskefet-api-cpp-example 1  # argument is run number to add
```
Note: don't include the "Bearer " part of the token, it's added automatically.

# Dev notes
## Code generation
Code can be generated using the online editor or locally. After generation, you'll need to do some additional work
### Local
OpenAPI tools (not using this currently)
```
docker pull openapitools/openapi-generator-cli
git clone https://github.com/SoftwareForScience/jiskefet-openapi-spec
cd jiskefet-openapi-spec
mkdir -p gen/cpp-restsdk
docker run --rm -v ${PWD}:/local:Z \
    openapitools/openapi-generator-cli generate \
    -i /local/openapi-spec.yaml \
    -g cpp-restsdk \
    -o /local/gen/cpp-restsdk
```
Swagger tools (local not working, see [Online])
```
docker pull swaggerapi/swagger-codegen-cli

git clone https://github.com/SoftwareForScience/jiskefet-openapi-spec
cd jiskefet-openapi-spec
mkdir gen-cpprest
docker run --rm \
    -v ${PWD}:/local:Z \
    swaggerapi/swagger-codegen-cli generate \
    -i /local/openapi-spec.yaml \
    -l cpprest \
    -o /local/gen-cpprest
```
### Online
1. Copy & paste openapi-spec.yaml contents into the editor at https://editor.swagger.io/
2. Under the "Generate Client" menu, select "cpprest"
3. Extract the archive under `src/cpprest-client` (note: as the API changes, it's possible some old classes/files will no longer be present, so you might want to clean up the directory before extracting)


### Additional work
At this point, it still needs some work, however.

Firstly, you may need to manually update the CMakeLists.txt if any files have been added/removed from the generated code.

In addition, the generated code is buggy in the way it initializes `shared_ptr`s.
The intention is to initialize the `shared_ptr` with a default-initialized `Object`, but it actually ends up with a null-initialized `shared_ptr`.
Maybe the generated way worked in an older C++ standard, but in C++17 it's broken.
The issue is known, see https://github.com/swagger-api/swagger-codegen/issues/7557 and https://github.com/swagger-api/swagger-codegen/pull/7742
To fix it, do a find and replace.
* From:
```
std::shared_ptr<Object> result(nullptr);
```
* To:
```
auto result = std::make_shared<Object>();
```

Use your favorite editor, or the following command:
```
find . -exec sed -i -e 's/std::shared_ptr<Object> result(nullptr);/auto result = std::make_shared<Object>();/g' {} \;
```

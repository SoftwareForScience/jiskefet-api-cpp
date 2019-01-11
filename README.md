# Jiskefet C++ Client API
This is a C++ client API for Jiskefet based on the Swagger code generator


## Setup
(TO DO)


## Running the example code
If your api is at `http://myhost.server.address/api`

```
export JISKEFET_HOST=myhost.server.address
export JISKEFET_PATH=api
export JISKEFET_API_TOKEN=jnk5vh43785ycj4gdvlvm84fg...
./jiskefet-api-cpp-example
```


# Dev notes
## Generated code
The generated code is unfortunately slightly buggy in the way it initializes shared pointers.
Maybe the generated way worked in an older C++ standard, I used C++17.
To fix it, do a find and replace.
* From:
```
std::shared_ptr<Object> result(nullptr);
```
* To:
```
auto result = std::make_shared<Object>();
```


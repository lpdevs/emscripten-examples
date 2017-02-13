### Instruction

 * This easy example uses an [EMSCRIPTEN_BINDINGS()](https://kripken.github.io/emscripten-site/docs/api_reference/bind.h.html#EMSCRIPTEN_BINDINGS__X) block to expose the simple C++ **lerp()** function to JavaScript.
 * Source code:

	```cpp
	// quick_example.cpp
	#include <emscripten/bind.h>
	using namespace emscripten;

	float lerp(float a, float b, float t) {
    	return (1 - t) * a + t * b;
	}

	EMSCRIPTEN_BINDINGS(my_module) {
    	function("lerp", &lerp);
	}
	```
 
 * **my_module**: is a label to mark a group of related bindings. (In this time, I don't know what it means.)
 * **function("lerp", &lerp)**: the first **"lerp"** is the name of the function and the **&lerp** is the address of the function.


### Compilation
 
 * Open cmd in the current location and run the following command:
 
  ```
  emcc --bind -o quick_example.js quick_example.cpp
  ```
 
 * With:

    * emcc: is compiler
    * --bind: means that we are using **embind**
    * -o: is a option, then there is a output after that
    * quick_example.js: is the name of output
    * quick_example.cpp: is the name of input
 
 * Result: the file **quick_example.js** is created.

### Test

 * Creating a file named "index.html" in the current location:

  ```html
  <!DOCTYPE html>
  <html>
    <script src="quick_example.js"></script>
    <script>
	   console.log('From helloworld: lerp result: ' + Module.lerp(1, 2, 0.5));
    </script>
  </html>
  ```
 * ```<script src="quick_example.js"></script>``` is to load javascript file (quick_example.js)
 * Notice: Always access objects through the Module object, as shown above.

 * In console, the result should be:
 
  ![result of quick_example](https://github.com/phamvanlam/emscripten-examples/blob/master/1-quick-example/result.PNG)
 


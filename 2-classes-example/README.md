### Instruction

 * Exposing classes to JavaScript.
 * Source code:

	```cpp
	// classes_example.cpp
	#include <emscripten/bind.h>
	using namespace emscripten;

	class MyClass {
	public:
  		MyClass(int x, std::string y)
    		: x(x)
    		, y(y)
  			{}

  		void incrementX() {
   			++x;
  		}

  		int getX() const { return x; }
  		void setX(int x_) { x = x_; }

  		static std::string getStringFromInstance(const MyClass& instance) {
    		return instance.y;
  		}

	private:
  		int x;
  		std::string y;
	};

	// Binding code
	EMSCRIPTEN_BINDINGS(my_class_example) {
  		class_<MyClass>("MyClass")
    		.constructor<int, std::string>()
    		.function("incrementX", &MyClass::incrementX)
    		.property("x", &MyClass::getX, &MyClass::setX)
    		.class_function("getStringFromInstance", &MyClass::getStringFromInstance)
    	;
	}
	```
 
 * For more information, please check out [1-quick-example](https://github.com/phamvanlam/emscripten-examples/tree/master/1-quick-example)
 * In [1-quick-example](https://github.com/phamvanlam/emscripten-examples/tree/master/1-quick-example), I bound **function**. In this example, I am going to bind **class** with the [_class](https://kripken.github.io/emscripten-site/docs/api_reference/bind.h.html#class_) object. The functions register the class, its [constructor()](https://kripken.github.io/emscripten-site/docs/api_reference/bind.h.html#class_::constructorC), member [function()](https://kripken.github.io/emscripten-site/docs/api_reference/bind.h.html#class_::functionC), [class_function()](https://kripken.github.io/emscripten-site/docs/api_reference/bind.h.html#class_::class_functionC) (static) and [property()](https://kripken.github.io/emscripten-site/docs/api_reference/bind.h.html#class_::propertyC).
 
### Compilation
 
 * Open cmd in the current location and run the following command:
 
   ```
   emcc --bind -o classes_example.js classes_example.cpp
   ```
 
 * With:

    * emcc: is compiler
    * --bind: means that we are using **embind**
    * -o: is a option, then there is a output after that
    * classes_example.js: is the name of output
    * classes_example.cpp: is the name of input
 
 * Result: the file **classes_example.js** is created.

### Test

 * Creating a file named "index.html" in the current location:

   ```html
   <!doctype html>
   <html>
  	 <script src="classes_example.js"></script>
     <script>
		console.log('From classes-example: ');
		var instance = new Module.MyClass(10, "hello");
		console.log(instance);
		instance.incrementX();
		console.log(instance.x);
		instance.x; 
		console.log(instance.x);
		instance.x = 20; 
		console.log(instance.x);
		var string = Module.MyClass.getStringFromInstance(instance);
		console.log(string);
		instance.delete();
     </script>
   </html>
   ```
   
   * Therefore there is no way for Emscripten to automatically call the destructors on C++ objects. So JavaScript code must explicitly delete any C++ object handles it has received, or the Emscripten heap will grow indefinitely. That's why I call **instance.delete()**.

 * In console, the result should be:
 
  ![result of quick_example](https://github.com/phamvanlam/emscripten-examples/blob/master/2-classes-example/result.PNG)
 


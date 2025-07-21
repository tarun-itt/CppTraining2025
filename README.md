# CppTraining2025

- ## Commands to run the program
	- ### Create Dynamic Library (.so file)
		- `cd assignments/week2/DynamicLinking`
		  logseq.order-list-type:: number
		- ` mkdir lib/obj `
		  logseq.order-list-type:: number
		-
		  logseq.order-list-type:: number
		  ```
		  g++ -fPIC -c lib/src/addition.cpp -o lib/obj/addition.o &&                                                                                                  
		  g++ -fPIC -c lib/src/subtraction.cpp -o lib/obj/subtraction.o &&  
		  g++ -fPIC -c lib/src/multiplication.cpp -o lib/obj/multiplication.o && 
		  g++ -fPIC -c lib/src/division.cpp -o lib/obj/division.o
		  ```
		-
		  logseq.order-list-type:: number
		  ```
		  g++ -shared -o lib/libmathOperations.so \
		      lib/obj/addition.o \
		      lib/obj/subtraction.o \
		      lib/obj/multiplication.o \
		      lib/obj/division.o
		  ```
	- ### Run Implicitly Linked program
		- Make sure in you are in `DynamicLinking` directory
		  logseq.order-list-type:: number
		- Run ` g++ implicitLinking/main.cpp -o implicitLinking/implicitLinkingApp lib/libmathOperations.so  `
		  logseq.order-list-type:: number
		- Run `  implicitLinking/implicitLinkedApp `
		  logseq.order-list-type:: number
	- ### Run Explicitly Linked program
		- Make sure in you are in `DynamicLinking` directory
		  logseq.order-list-type:: number
		- Run ` g++ explicitLinking/main.cpp -o explicitLinking/explicitLinkingApp lib/libmathOperations.so  `
		  logseq.order-list-type:: number
		- Run `  explicitLinking/explicitLinkedApp `
		  logseq.order-list-type:: number
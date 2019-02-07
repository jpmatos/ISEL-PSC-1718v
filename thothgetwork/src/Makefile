all: compile_file compile_library get_file get_class_assignments thoth_get_work

compile_file:
	gcc -c -Wall -Werror -fpic thoth.c

compile_library:
	gcc -shared -o libthoth.so thoth.o
	
get_file:
	gcc -L./ -Wl,-rpath=./ -Wall -o get_file get_file.c -lthoth -lcurl -ljansson

get_class_assignments:
	gcc -L./ -Wl,-rpath=./ -Wall -o get_class_assignments get_class_assignments.c -lthoth -lcurl -ljansson
	
thoth_get_work:
	gcc -L./ -Wl,-rpath=./ -Wall -o thoth_get_work thoth_get_work.c -lthoth -lcurl -ljansson -lzip

clean:
	rm -f ./*.o

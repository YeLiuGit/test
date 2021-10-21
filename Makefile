C11	= cc -std=c11 -Wall -Werror -pedantic

duplicates : duplicates.o write_table.o strSHA2.o hashtable.o read_dir.o
	$(C11) -o duplicates duplicates.o write_table.o strSHA2.o hashtable.o read_dir.o

duplicates.o : duplicates.c  duplicates.h
	$(C11) -c duplicates.c

hashtable.o : hashtable.c duplicates.h
	$(C11) -c hashtable.c

write_table.o : write_table.c duplicates.h
	$(C11) -c write_table.c

read_dir.o: read_dir.c duplicates.h
	$(C11) -c read_dir.c

strSHA2.o : strSHA2.c duplicates.h
	$(C11) -c strSHA2.c

clean:
	rm -f duplicates duplicates.o write_table.o strSHA2.o

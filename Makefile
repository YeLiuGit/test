C11	= cc -std=c11 -Wall -Werror -pedantic

duplicates : duplicates.o compare.o strSHA2.o hashtable.o write_data.o
	$(C11) -o duplicates duplicates.o compare.o strSHA2.o hashtable.o write_data.o
	
duplicates.o : duplicates.c  duplicates.h
	$(C11) -c duplicates.c
	
compare.o : compare.c duplicates.h
	$(C11) -c compare.c
	
write_data.o: write_data.c duplicates.h
	$(C11) -c write_data.c

hashtable.o : hashtable.c duplicates.h
	$(C11) -c hashtable.c
	
strSHA2.o : strSHA2.c duplicates.h
	$(C11) -c strSHA2.c

clean:
	rm -f duplicates duplicates.o compare.o write_data.o hashtable.o strSHA2.o

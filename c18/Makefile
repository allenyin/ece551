CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++98
EXEC = deduplicate hash
HASH_H = hash-library/sha256.h hash-library/md5.h
HASH_CPP = hash-library/sha256.cpp hash-library/md5.cpp

deduplicate: deduplicate.cpp deduplicate.h
	g++ $(CPPFLAGS) -o deduplicate deduplicate.cpp $(HASH_CPP)

hash: hash.cpp deduplicate.h
	g++ $(CPPFLAGS) -o hash hash.cpp $(HASH_CPP)

clean:
	rm -f $(EXEC) *.o

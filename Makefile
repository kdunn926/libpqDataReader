all: libpqTest.c
	g++ -I/usr/local/greenplum-db-4.3.8.2/include libpqTest.c -L/usr/local/greenplum-db-4.3.8.2/lib -lpq -o pqTest

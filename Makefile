#Compiler
COMPILER = gcc

#Compiler flags
CFLAGS = -Wall -Wextra

#headers
HEADERS = $(wildcard headers/*.h)

#sources
SOURCES = main/main.c 
SOURCES += $(wildcard functions/*.c) 

#default compilation targets
all: txtToSQL_Conveter

#converter executable
txtToSQL_Conveter: $(SOURCES)
	$(COMPILER) $(CFLAGS) -o txtToSQL_Conveter $(SOURCES)

#
# Rechnernutzung in der Physik, WS 2011/12, Blatt 04, Aufg. 9
# 
# Zur Verfuegung gestelltes Makefile 
#
#----------------------------------------------------------------------------
#
# Kommentare in Makefiles: ab "#" bis zum Zeilenende.
#
# Variablendefinitionen:
#
# Compile settings
CXX      := g++
CXXFLAGS := -O3

# Link settings
LD       := g++                # Use g++ for linking
LDFLAGS  := -O -std=c++11
LDLIBS   := -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lpthread -lm -ldl

LIB	:= -L/afs/desy.de/products/root/amd64_ubu14/5.34.00/lib

INC	:= -I/afs/desy.de/products/root/amd64_ubu14/5.34.00/include




sources  := deflectionetimate.C  energyfinder.h energyfinder.cpp
objects  := $(sources:.cc=.o)  # Objektdateien sind die
                               # Quelldateien, wobei .cc durch .o
                               # zu ersetzen ist. 


#----------------------------------------------------------------------------
# Regeln:
# Wenn "make" ohne Regelangabe aufgerufen wird, wird die erste
# Regel in der Datei aufgerufen. Eine Regel ist ueblicherweise ein
# "Rezept" wie ein "Bestandteil" des Endprogramms erzeugt werden kann.
#
# Eine Regel hat immer folgende Syntax:
# ZIEL: ABHAENGIGKEITEN
# [TAB] BEFEHLE
# [TAB] BEFEHLE
#     etc.
# 
# oder mit den gebraeuchlichen englischen Ausdruecken:
# TARGET: DEPENDENCIES
# [TAB]	COMMAND(S)
# [TAB]	COMMAND(S)
#     etc.
#
# Wenn eine Regel zur Ausfuehrung gelangt, werden zunaechst die 
# Abhaengigkeiten ueberprueft: Eine Regel gelangt zur Ausfuehrung, wenn
# entweder ihr ZIEL (als Datei) nicht exisitert oder das Ziel aelter ist 
# als eine der ABHAENGIGKEITEN. Dann werden die BEFEHLE abgearbeitet.
# Diese muessen stets durch ein Tabulator eingerueckt sein!
# 
# ABHAENGIGKEITEN fuehren dazu, dass weitere Regeln ueberprueft und
# abgearbeitet werden. Dies sogar bevor die Befehle der aktuellen
# Regel abgearbeitet werden. So koennen also "pre-requisites"
# vereinbart werden.
# 
# Konkrete Regeln dieses Makefiles:
#
# Regel: das fertige Programm haengt ab von den
# uebersetzten Teilobjekten. Der Befehl gibt an, wie
# diese Teilobjekte zusammengebunden werden: ("Linking")

deflectionestimate: $(objects)
	$(LD) $(LDFLAGS) -o deflectionestimate $(objects) $(LIB) $(INC) $(LDLIBS)




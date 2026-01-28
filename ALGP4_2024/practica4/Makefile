# Compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -Wall

# Lista de archivos fuente
SRCS = senku.cpp problema1.cpp cena_backtracking.cpp problema4.cpp problema5.cpp

#Nombres de los ejecutables
EXECS = $(SRCS:.cpp=)

#Regla para construir los ejecutables
all: $(EXECS)

# Regla para la compilación de los archivos fuente
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(EXECS)

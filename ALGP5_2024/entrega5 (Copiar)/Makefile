# Compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -Wall

# Lista de archivos fuente
SRCS = problema1.cpp problema2.cpp problema3.cpp problema4.cpp

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

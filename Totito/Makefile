# Compilador
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Carpetas
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Nombre del ejecutable
TARGET = $(BIN_DIR)/totito

# Archivos fuente y objetos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Regla por defecto
all: $(TARGET)

# Enlazado final
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilación de cada .cpp a .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Limpiar compilados
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Limpiar todo y recompilar
rebuild: clean all

.PHONY: all clean rebuild

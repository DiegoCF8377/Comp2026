#!/bin/bash

# Carpeta donde están los archivos .txt
INPUT_DIR="BabyDuckCodes"

# Recorrer todos los archivos .txt
for file in "$INPUT_DIR"/*.txt; do

    # Verificar que existan archivos .txt
    [ -e "$file" ] || {
        echo "No se encontraron archivos .txt en $INPUT_DIR"
        exit 1
    }

    echo "========================================"
    echo "Procesando archivo: $file"
    echo "========================================"

    # Fase 1: Análisis léxico
    echo "[1] Ejecutando análisis léxico..."
    ./Patito1/lexer_phase "$file"

    # Verificar si el lexer terminó correctamente
    if [ $? -ne 0 ]; then
        echo "Error en Lexer para: $file"
        continue
    fi

    # Fase 2: Análisis sintáctico
    echo "[2] Ejecutando análisis sintáctico..."
    ./Patito1/parser_phase < tokens.txt

    echo "Finalizado: $file"
    echo ""
done

echo "Todos los archivos han sido procesados."

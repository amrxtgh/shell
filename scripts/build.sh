#!/bin/bash
set -euo pipefail

GREEN='\033[0;32m'
NC='\033[0m' # No Color (reset)

# Resolve project root independent of where the script is invoked from.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"
DIST_DIR="${PROJECT_ROOT}/dist"

echo "building the shell"

rm -rf "${BUILD_DIR}"
mkdir -p "${BUILD_DIR}"

echo -e "${GREEN}***Generating build files***${NC}"
cmake -S "${PROJECT_ROOT}" -B "${BUILD_DIR}" -DCMAKE_C_FLAGS="-Wall -Wextra -Wpedantic" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
echo ""

echo -e "${GREEN}***Building the project***${NC}"
cmake --build "${BUILD_DIR}" --verbose
echo ""

echo -e "${GREEN}***Installing the project***${NC}"
cmake --install "${BUILD_DIR}" --prefix "${DIST_DIR}"
echo ""

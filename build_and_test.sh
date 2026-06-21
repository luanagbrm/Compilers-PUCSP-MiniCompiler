#!/bin/bash
# build_and_test.sh - Build the Mini-Pascal compiler and run all test programs
# Usage: ./build_and_test.sh

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

PASS=0
FAIL=0

check() {
    local desc="$1" expected="$2" actual="$3"
    if [ "$expected" = "$actual" ]; then
        echo -e "  ${GREEN}✓${NC} $desc: $actual"
        PASS=$((PASS + 1))
    else
        echo -e "  ${RED}✗${NC} $desc: expected '$expected', got '$actual'"
        FAIL=$((FAIL + 1))
    fi
}

echo -e "${YELLOW}═══════════════════════════════════════════════════${NC}"
echo -e "${YELLOW}  Mini-Pascal Compiler - Build & Test${NC}"
echo -e "${YELLOW}═══════════════════════════════════════════════════${NC}"
echo

# === Step 1: Build the compiler ===
echo -e "${YELLOW}[1/5] Building compiler...${NC}"
make clean > /dev/null 2>&1 || true
if make 2>&1 | grep -q "Build successful"; then
    echo -e "  ${GREEN}✓${NC} Compiler built successfully"
else
    echo -e "  ${RED}✗${NC} Build failed!"
    make 2>&1
    exit 1
fi
echo

# === Step 2: Test factor.pas ===
echo -e "${YELLOW}[2/5] Testing factor.pas (prime factorization)${NC}"
./minipc tests/factor.pas -o factor > /dev/null 2>&1
check "factor 84" "2 2 3 7 " "$(./factor 84)"
check "factor 100" "2 2 5 5 " "$(./factor 100)"
check "factor 17" "17 " "$(./factor 17)"
check "factor 12" "2 2 3 " "$(./factor 12)"
echo

# === Step 3: Test isprime.pas ===
echo -e "${YELLOW}[3/5] Testing isprime.pas (primality check)${NC}"
./minipc tests/isprime.pas -o isprime > /dev/null 2>&1
check "isprime 17" "true" "$(./isprime 17)"
check "isprime 4" "false" "$(./isprime 4)"
check "isprime 2" "true" "$(./isprime 2)"
check "isprime 1" "false" "$(./isprime 1)"
check "isprime 97" "true" "$(./isprime 97)"
echo

# === Step 4: Test pidigits.pas ===
echo -e "${YELLOW}[4/5] Testing pidigits.pas (digits of π)${NC}"
./minipc tests/pidigits.pas -o pidigits > /dev/null 2>&1
check "pidigits 1" "3" "$(./pidigits 1)"
check "pidigits 3" "314" "$(./pidigits 3)"
check "pidigits 5" "31415" "$(./pidigits 5)"
check "pidigits 6" "314159" "$(./pidigits 6)"
echo

# === Step 5: Test fibonacci.pas ===
echo -e "${YELLOW}[5/5] Testing fibonacci.pas${NC}"
./minipc tests/fibonacci.pas -o fibonacci > /dev/null 2>&1
check "fibonacci 1" "1" "$(./fibonacci 1)"
check "fibonacci 5" "5" "$(./fibonacci 5)"
check "fibonacci 10" "55" "$(./fibonacci 10)"
check "fibonacci 20" "6765" "$(./fibonacci 20)"
echo

# === Summary ===
echo -e "${YELLOW}═══════════════════════════════════════════════════${NC}"
TOTAL=$((PASS + FAIL))
if [ $FAIL -eq 0 ]; then
    echo -e "  ${GREEN}All $TOTAL tests passed! ✅${NC}"
else
    echo -e "  ${RED}$FAIL/$TOTAL tests failed ❌${NC}"
fi
echo -e "${YELLOW}═══════════════════════════════════════════════════${NC}"

exit $FAIL

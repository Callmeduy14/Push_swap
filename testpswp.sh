#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Configuration
PUSH_SWAP="./push_swap"
CHECKER=""
TEST_COUNT=50
SMALL_SIZE=100
LARGE_SIZE=500

# Find checker
if [ -f "./checker_Mac" ]; then
    CHECKER="./checker_Mac"
elif [ -f "./checker_linux" ]; then
    CHECKER="./checker_linux"
elif [ -f "./checker" ]; then
    CHECKER="./checker"
else
    echo -e "${YELLOW}Warning: No checker found. Results verification will be skipped.${NC}"
fi

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

print_header() {
    echo -e "\n${CYAN}╔════════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${CYAN}║                          $1${NC}"
    echo -e "${CYAN}╚════════════════════════════════════════════════════════════════╝${NC}"
}

print_section() {
    echo -e "\n${BLUE}▶ $1${NC}"
    echo -e "${BLUE}──────────────────────────────────────────────────────────────────${NC}"
}

run_test() {
    local test_name="$1"
    local input="$2"
    local expected_behavior="$3"
    local max_operations="$4"

    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    echo -n "Test: $test_name ... "

    # Run push_swap
    OUTPUT=$(eval "$PUSH_SWAP $input" 2>&1)
    EXIT_CODE=$?

    # Count operations
    if [ -n "$OUTPUT" ]; then
        OP_COUNT=$(echo "$OUTPUT" | grep -v "Error" | wc -l)
    else
        OP_COUNT=0
    fi

    # Check based on expected behavior
    case "$expected_behavior" in
        "ERROR")
            if echo "$OUTPUT" | grep -q "Error"; then
                echo -e "${GREEN}PASS${NC} (Error detected)"
                PASSED_TESTS=$((PASSED_TESTS + 1))
            else
                echo -e "${RED}FAIL${NC} (Expected Error, got: '$OUTPUT')"
                FAILED_TESTS=$((FAILED_TESTS + 1))
            fi
            ;;
        "NO_OUTPUT")
            if [ -z "$OUTPUT" ]; then
                echo -e "${GREEN}PASS${NC} (No output as expected)"
                PASSED_TESTS=$((PASSED_TESTS + 1))
            else
                echo -e "${RED}FAIL${NC} (Expected no output, got: '$OUTPUT')"
                FAILED_TESTS=$((FAILED_TESTS + 1))
            fi
            ;;
        "SORT_CHECK")
            if [ -n "$CHECKER" ]; then
                RESULT=$(echo "$OUTPUT" | $CHECKER $input 2>/dev/null)
                if [ "$RESULT" = "OK" ]; then
                    if [ -n "$max_operations" ] && [ "$OP_COUNT" -gt "$max_operations" ]; then
                        echo -e "${YELLOW}PASS${NC} (Sorted but ${OP_COUNT} ops > ${max_operations} limit)"
                    else
                        echo -e "${GREEN}PASS${NC} (${OP_COUNT} operations)"
                    fi
                    PASSED_TESTS=$((PASSED_TESTS + 1))
                else
                    echo -e "${RED}FAIL${NC} (Not sorted correctly: $RESULT)"
                    echo -e "  Input: $input"
                    echo -e "  Output: $OUTPUT"
                    FAILED_TESTS=$((FAILED_TESTS + 1))
                fi
            else
                echo -e "${YELLOW}SKIP${NC} (No checker available)"
            fi
            ;;
    esac
}

# Check if push_swap exists
if [ ! -f "$PUSH_SWAP" ]; then
    echo -e "${RED}Error: $PUSH_SWAP not found. Please compile first with 'make'${NC}"
    exit 1
fi

print_header "COMPREHENSIVE PUSH_SWAP TESTER"

# =============================================================================
# ERROR HANDLING TESTS
# =============================================================================
print_section "Error Handling Tests"

run_test "Non-numeric input" "1 2 three 4" "ERROR"
run_test "Duplicate numbers" "1 2 3 2 5" "ERROR"
run_test "Empty string" "1 '' 3" "ERROR"
run_test "Only spaces" "'   '" "ERROR"
run_test "Invalid number format" "1 2+ 3" "ERROR"
run_test "Integer overflow" "1 2147483648 3" "ERROR"
run_test "Integer underflow" "1 -2147483649 3" "ERROR"
run_test "Mixed valid/invalid" "42 abc 21" "ERROR"

# =============================================================================
# BASIC FUNCTIONALITY TESTS
# =============================================================================
print_section "Basic Functionality Tests"

run_test "Single number" "42" "NO_OUTPUT"
run_test "Already sorted 2" "1 2" "NO_OUTPUT"
run_test "Already sorted 3" "1 2 3" "NO_OUTPUT"
run_test "Already sorted 5" "1 2 3 4 5" "NO_OUTPUT"
run_test "Reverse sorted 2" "2 1" "SORT_CHECK" 1
run_test "Simple 3 numbers" "2 1 3" "SORT_CHECK" 3
run_test "Reverse 3 numbers" "3 2 1" "SORT_CHECK" 3

# =============================================================================
# SMALL STACK TESTS (3-5 numbers)
# =============================================================================
print_section "Small Stack Tests (3-5 numbers)"

# All permutations of 3 numbers
run_test "3 nums: 1 3 2" "1 3 2" "SORT_CHECK" 3
run_test "3 nums: 2 1 3" "2 1 3" "SORT_CHECK" 3
run_test "3 nums: 2 3 1" "2 3 1" "SORT_CHECK" 3
run_test "3 nums: 3 1 2" "3 1 2" "SORT_CHECK" 3
run_test "3 nums: 3 2 1" "3 2 1" "SORT_CHECK" 3

# Test various 4 number combinations
run_test "4 nums: 2 1 3 4" "2 1 3 4" "SORT_CHECK" 8
run_test "4 nums: 4 3 2 1" "4 3 2 1" "SORT_CHECK" 8
run_test "4 nums: 3 1 4 2" "3 1 4 2" "SORT_CHECK" 8

# Test various 5 number combinations
run_test "5 nums: 1 5 2 4 3" "1 5 2 4 3" "SORT_CHECK" 12
run_test "5 nums: 5 4 3 2 1" "5 4 3 2 1" "SORT_CHECK" 12
run_test "5 nums: 2 4 1 5 3" "2 4 1 5 3" "SORT_CHECK" 12

# =============================================================================
# MEDIUM STACK TESTS (Random small sets)
# =============================================================================
print_section "Medium Stack Tests (6-20 numbers)"

for i in $(seq 1 10); do
    ARG=$(ruby -e "puts (1..10).to_a.shuffle.join(' ')" 2>/dev/null || python3 -c "import random; nums=list(range(1,11)); random.shuffle(nums); print(' '.join(map(str,nums)))")
    run_test "10 nums: Test $i" "$ARG" "SORT_CHECK" 100
done

# =============================================================================
# PERFORMANCE TESTS
# =============================================================================
print_section "Performance Tests"

echo -e "${YELLOW}Running $TEST_COUNT tests with $SMALL_SIZE numbers...${NC}"
total_ops_small=0
max_ops_small=0
min_ops_small=999999
failed_small=0

for i in $(seq 1 $TEST_COUNT); do
    ARG=$(ruby -e "puts (1..$SMALL_SIZE).to_a.shuffle.join(' ')" 2>/dev/null || \
          python3 -c "import random; nums=list(range(1,$((SMALL_SIZE+1)))); random.shuffle(nums); print(' '.join(map(str,nums)))")

    OPS=$($PUSH_SWAP $ARG 2>/dev/null | wc -l)
    total_ops_small=$((total_ops_small + OPS))

    if [ "$OPS" -gt "$max_ops_small" ]; then
        max_ops_small=$OPS
    fi
    if [ "$OPS" -lt "$min_ops_small" ]; then
        min_ops_small=$OPS
    fi

    # Verify correctness
    if [ -n "$CHECKER" ]; then
        RESULT=$($PUSH_SWAP $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
        if [ "$RESULT" != "OK" ]; then
            failed_small=$((failed_small + 1))
        fi
    fi

    if [ $((i % 10)) -eq 0 ]; then
        echo -n "."
    fi
done
echo

avg_small=$((total_ops_small / TEST_COUNT))

echo -e "${YELLOW}Running 20 tests with $LARGE_SIZE numbers...${NC}"
total_ops_large=0
max_ops_large=0
min_ops_large=999999
failed_large=0

for i in $(seq 1 20); do
    ARG=$(ruby -e "puts (1..$LARGE_SIZE).to_a.shuffle.join(' ')" 2>/dev/null || \
          python3 -c "import random; nums=list(range(1,$((LARGE_SIZE+1)))); random.shuffle(nums); print(' '.join(map(str,nums)))")

    OPS=$($PUSH_SWAP $ARG 2>/dev/null | wc -l)
    total_ops_large=$((total_ops_large + OPS))

    if [ "$OPS" -gt "$max_ops_large" ]; then
        max_ops_large=$OPS
    fi
    if [ "$OPS" -lt "$min_ops_large" ]; then
        min_ops_large=$OPS
    fi

    # Verify correctness
    if [ -n "$CHECKER" ]; then
        RESULT=$($PUSH_SWAP $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
        if [ "$RESULT" != "OK" ]; then
            failed_large=$((failed_large + 1))
        fi
    fi

    echo -n "."
done
echo

avg_large=$((total_ops_large / 20))

# =============================================================================
# RESULTS SUMMARY
# =============================================================================
print_header "TEST RESULTS SUMMARY"

echo -e "${BLUE}Overall Test Results:${NC}"
echo -e "  Total Tests: ${TOTAL_TESTS}"
echo -e "  ${GREEN}Passed: ${PASSED_TESTS}${NC}"
echo -e "  ${RED}Failed: ${FAILED_TESTS}${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "  ${GREEN}✓ All tests passed!${NC}"
else
    echo -e "  ${RED}✗ Some tests failed${NC}"
fi

echo -e "\n${BLUE}Performance Results:${NC}"
echo -e "  ${SMALL_SIZE} numbers (${TEST_COUNT} tests):"
echo -e "    Average: ${avg_small} operations"
echo -e "    Range: ${min_ops_small} - ${max_ops_small}"
echo -e "    Failed sorts: ${failed_small}"
echo -e "    Grade prediction:"
if [ $avg_small -lt 700 ]; then
    echo -e "      ${GREEN}★★★★★ (5/5)${NC} - Excellent!"
elif [ $avg_small -lt 900 ]; then
    echo -e "      ${GREEN}★★★★☆ (4/5)${NC} - Very Good"
elif [ $avg_small -lt 1100 ]; then
    echo -e "      ${YELLOW}★★★☆☆ (3/5)${NC} - Good"
elif [ $avg_small -lt 1300 ]; then
    echo -e "      ${YELLOW}★★☆☆☆ (2/5)${NC} - Needs Improvement"
else
    echo -e "      ${RED}★☆☆☆☆ (1/5)${NC} - Poor"
fi

echo -e "\n  ${LARGE_SIZE} numbers (20 tests):"
echo -e "    Average: ${avg_large} operations"
echo -e "    Range: ${min_ops_large} - ${max_ops_large}"
echo -e "    Failed sorts: ${failed_large}"
echo -e "    Grade prediction:"
if [ $avg_large -lt 5500 ]; then
    echo -e "      ${GREEN}★★★★★ (5/5)${NC} - Excellent!"
elif [ $avg_large -lt 7000 ]; then
    echo -e "      ${GREEN}★★★★☆ (4/5)${NC} - Very Good"
elif [ $avg_large -lt 8500 ]; then
    echo -e "      ${YELLOW}★★★☆☆ (3/5)${NC} - Good"
elif [ $avg_large -lt 10000 ]; then
    echo -e "      ${YELLOW}★★☆☆☆ (2/5)${NC} - Needs Improvement"
else
    echo -e "      ${RED}★☆☆☆☆ (1/5)${NC} - Poor"
fi

# Final recommendation
echo -e "\n${BLUE}Recommendations:${NC}"
if [ $FAILED_TESTS -eq 0 ] && [ $avg_small -lt 700 ] && [ $avg_large -lt 5500 ]; then
    echo -e "  ${GREEN}✓ Your push_swap is ready for submission! 🎉${NC}"
elif [ $FAILED_TESTS -gt 0 ]; then
    echo -e "  ${RED}✗ Fix the failing tests before submission${NC}"
elif [ $avg_small -ge 700 ] || [ $avg_large -ge 5500 ]; then
    echo -e "  ${YELLOW}⚠ Consider optimizing your algorithm for better performance${NC}"
fi

exit $FAILED_TESTS
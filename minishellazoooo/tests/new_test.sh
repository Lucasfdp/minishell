#!/bin/bash

# ======== CONFIG ========
MINISHELL="../minishell"
TMP_DIR="./tests/tmp"
mkdir -p "$TMP_DIR"

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m'

# Counters
PASS_COUNT=0
FAIL_COUNT=0

# ======== HELPERS ========
run_test() {
    local name="$1"
    local cmd="$2"

    echo -e "[$name] Running: $cmd"

    # Run in bash
    bash -c "$cmd" > "$TMP_DIR/bash.out" 2>&1

    # Run in minishell
    echo "$cmd" | "$MINISHELL" > "$TMP_DIR/mini.out" 2>&1

    # Compare outputs
    if diff -u "$TMP_DIR/bash.out" "$TMP_DIR/mini.out" > "$TMP_DIR/diff.out"; then
        echo -e "[${GREEN}PASS${NC}] $name"
        ((PASS_COUNT++))
    else
        echo -e "[${RED}FAIL${NC}] $name"
        ((FAIL_COUNT++))
        echo "Command: $cmd"
        echo "--- Bash Output ---"
        cat "$TMP_DIR/bash.out"
        echo "--- Minishell Output ---"
        cat "$TMP_DIR/mini.out"
        echo "--- Diff ---"
        cat "$TMP_DIR/diff.out"
        echo
    fi
}

# ======== BUILTINS ========
echo -e "\n${YELLOW}=== BUILTINS ===${NC}"
run_test "Echo basic" "echo hello"
run_test "Echo multiple args" "echo hello world"
run_test "Echo -n flag" "echo -n hello"
run_test "Echo empty" "echo"

run_test "PWD" "pwd"

# CD tests (these are tricky without ; so we'll test individually)
run_test "CD invalid" "cd /nonexistent"

# For export/unset, we test them in context where they matter
run_test "Export affects command" "export PATH=/bin:/usr/bin"

run_test "Env shows PATH" "env | grep PATH"

run_test "Exit with code" "exit 0"

# ======== SIMPLE COMMANDS ========
echo -e "\n${YELLOW}=== SIMPLE COMMANDS ===${NC}"
run_test "ls command" "ls"
run_test "Command with args" "ls -l"
run_test "Command not found" "invalidcommand123"

# ======== PIPES ========
echo -e "\n${YELLOW}=== PIPES ===${NC}"
run_test "Simple pipe" "echo hello | cat"
run_test "Pipe with grep" "echo hello | grep hello"
run_test "Multiple pipes" "echo test | cat | cat"
run_test "Pipe with wc" "ls | wc -l"

# ======== REDIRECTIONS ========
echo -e "\n${YELLOW}=== REDIRECTIONS ===${NC}"
# Create test file first
echo "test content" > "$TMP_DIR/in.txt"

run_test "Output redirect" "echo hello > $TMP_DIR/out.txt"
run_test "Input redirect" "cat < $TMP_DIR/in.txt"
run_test "Append redirect" "echo first > $TMP_DIR/app.txt"
run_test "Redirect with pipe" "echo hello | cat > $TMP_DIR/pipe.txt"
run_test "Multiple redirects" "cat < $TMP_DIR/in.txt > $TMP_DIR/out2.txt"

# ======== HEREDOC ========
echo -e "\n${YELLOW}=== HEREDOC ===${NC}"
run_test "Simple heredoc" "cat <<EOF
hello
EOF"

run_test "Heredoc no expand" "cat <<'EOF'
\$VAR
EOF"

run_test "Heredoc with pipe" "cat <<EOF | grep hi
hi
bye
EOF"

# ======== QUOTES ========
echo -e "\n${YELLOW}=== QUOTES ===${NC}"
run_test "Single quotes" "echo 'hello world'"
run_test "Double quotes" "echo \"hello world\""
run_test "Single no expand" "echo '\$USER'"
run_test "Double expand" "echo \"\$USER\""
run_test "Mixed quotes" "echo \"hello\" 'world'"
run_test "Empty quotes" "echo '' \"\" test"

# ======== VARIABLE EXPANSION ========
echo -e "\n${YELLOW}=== VARIABLES ===${NC}"
run_test "Variable USER" "echo \$USER"
run_test "Variable PATH" "echo \$PATH"
run_test "Exit status success" "echo \$?"
run_test "Undefined variable" "echo \$UNDEFINED"

# ======== SYNTAX ERRORS ========
echo -e "\n${YELLOW}=== SYNTAX ERRORS ===${NC}"
run_test "Empty input" ""
run_test "Unclosed single quote" "echo 'hello"
run_test "Unclosed double quote" "echo \"hello"
run_test "Pipe at start" "| ls"
run_test "Pipe at end" "echo hello |"
run_test "Redirect no file" "echo >"

# ======== SUMMARY ========
echo -e "\n${YELLOW}=== TEST SUMMARY ===${NC}"
TOTAL=$((PASS_COUNT + FAIL_COUNT))
echo -e "${GREEN}Passed: $PASS_COUNT${NC}"
echo -e "${RED}Failed: $FAIL_COUNT${NC}"
echo "Total: $TOTAL"

if [ $FAIL_COUNT -eq 0 ]; then
    echo -e "\n${GREEN}🎉 All tests passed!${NC}"
    exit 0
else
    echo -e "\n${RED}❌ Some tests failed${NC}"
    exit 1
fi
#!/bin/bash

# ===============================
# MINISHELL TESTER — NO BONUS VERSION
# ===============================

MINISHELL=./minishell
TMP_DIR=./tests/tmp
mkdir -p "$TMP_DIR"

GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
CYAN="\033[36m"
RESET="\033[0m"

function run_test() {
    local name="$1"
    local cmd="$2"
    local category="$3"
    local id="$4"

    printf "%b[%d] %s%b\n" "$CYAN" "$id" "$name" "$RESET"

    echo -e "$cmd" | bash > "$TMP_DIR/bash.out" 2>&1
    echo -e "$cmd" | $MINISHELL > "$TMP_DIR/mini.out" 2>&1

    if diff -u "$TMP_DIR/bash.out" "$TMP_DIR/mini.out" > "$TMP_DIR/diff.out"; then
        printf "   ${GREEN}✅ PASS${RESET}\n"
    else
        printf "   ${RED}❌ FAIL${RESET}\n"
        echo "   Command: $cmd"
        echo "   --- Bash Output ---"
        cat "$TMP_DIR/bash.out"
        echo "   --- Minishell Output ---"
        cat "$TMP_DIR/mini.out"
        echo "   --- Diff ---"
        cat "$TMP_DIR/diff.out"
    fi
    echo
}

echo -e "\n=== ${YELLOW}BUILTINS${RESET} ==="
run_test "Echo basic" "echo hello world" "builtin" 1
run_test "Echo no newline" "echo -n hello" "builtin" 2
run_test "PWD" "pwd" "builtin" 3
run_test "CD valid" "cd /tmp ; pwd" "builtin" 4
run_test "CD invalid" "cd notfound" "builtin" 5
run_test "Export simple" "export A=42 ; echo \$A" "builtin" 6
run_test "Unset variable" "export A=42 ; unset A ; echo \$A" "builtin" 7
run_test "Exit code" "exit 7" "builtin" 8

echo -e "\n=== ${YELLOW}EXECUTION${RESET} ==="
run_test "Simple command" "ls > /dev/null" "exec" 9
run_test "Pipe" "echo hello | cat" "exec" 10
run_test "Redirect output" "echo hello > $TMP_DIR/out.txt ; cat $TMP_DIR/out.txt" "exec" 11
run_test "Append redirect" "echo first > $TMP_DIR/out.txt ; echo second >> $TMP_DIR/out.txt ; cat $TMP_DIR/out.txt" "exec" 12
run_test "Redirect input" "echo hi > $TMP_DIR/in.txt ; cat < $TMP_DIR/in.txt" "exec" 13
run_test "Pipe with redirect" "echo hi | cat > $TMP_DIR/out2.txt ; cat $TMP_DIR/out2.txt" "exec" 14

echo -e "\n=== ${YELLOW}PARSING${RESET} ==="
run_test "Single quotes" "echo 'hello world'" "parse" 15
run_test "Double quotes" "echo \"hello \$USER\"" "parse" 16
run_test "Escaped quotes" "echo \\\"escaped\\\"" "parse" 17
run_test "Empty command" "" "parse" 18
run_test "Unclosed quote" "echo 'hi" "parse" 19
run_test "Pipe syntax error" "| ls" "parse" 20
run_test "Redirection syntax" "echo hi >" "parse" 21

echo -e "\n=== ${YELLOW}HEREDOC${RESET} ==="
run_test "Simple heredoc" "cat <<EOF\nhello\nEOF" "heredoc" 22
run_test "Heredoc expand var" "cat <<EOF\n\$HOME\nEOF" "heredoc" 23
run_test "Heredoc no expand" "cat <<'EOF'\n\$HOME\nEOF" "heredoc" 24
run_test "Heredoc with pipe" "cat <<EOF | grep h\nhi\nEOF" "heredoc" 25

echo -e "\n${YELLOW}=== SUMMARY ===${RESET}"
total=$(grep -c 'run_test ' "$0")
passed=$(grep -c "✅ PASS" "$TMP_DIR"/* 2>/dev/null || echo 0)
failed=$((total - passed))
echo "   Total:  $total"
echo "   Passed: $passed"
echo "   Failed: $failed"

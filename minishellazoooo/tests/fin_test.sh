#!/bin/bash

# ======== CONFIG ========
MINISHELL="../minishell"
TMP_DIR="./tests/tmp"
mkdir -p "$TMP_DIR"

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

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
    else
        echo -e "[${RED}FAIL${NC}] $name"
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
echo "=== BUILTINS ==="
run_test "Echo basic" "echo hello"
run_test "Echo no newline" "echo -n hello"
run_test "PWD" "pwd"
run_test "CD valid" "cd /tmp"
run_test "CD invalid" "cd /does/not/exist"
run_test "Export simple" "export A=42"
run_test "Unset variable" "unset A"
run_test "Env" "env"
run_test "Exit code" "exit 7"

# ======== EXECUTION ========
echo "=== EXECUTION ==="
run_test "Simple command" "ls"
run_test "Pipe" "ls | wc -l"
run_test "Redirect output" "echo hello > $TMP_DIR/out.txt"
run_test "Append redirect" "echo first > $TMP_DIR/out.txt; echo second >> $TMP_DIR/out.txt"
run_test "Redirect input" "cat < $TMP_DIR/out.txt"
run_test "Pipe with redirect" "echo hi | cat > $TMP_DIR/out2.txt"

# ======== PARSING ========
echo "=== PARSING ==="
run_test "Single quotes" "echo 'hello world'"
run_test "Double quotes" "echo \"hello \$USER\""
run_test "Escaped quotes" "echo \\\"escaped\\\""
run_test "Empty command" ""
run_test "Unclosed quote" "echo 'hi"
run_test "Pipe syntax error" "| ls"
run_test "Redirection syntax" "echo hi >"

# ======== HEREDOC ========
echo "=== HEREDOC ==="
run_test "Simple heredoc" "cat <<EOF
hi
EOF"
run_test "Heredoc no expand" "cat <<'EOF'
\$HOME
EOF"
run_test "Heredoc with pipe" "cat <<EOF | grep hi
hi
bye
EOF"

echo "=== ALL TESTS RUN ==="

#!/bin/bash

# Helper
run_test() {
    input="$1"
    expected="$2"
    name="$3"

    ./minishell <<< "$input" > out.txt 2> err.txt
    echo "$expected" > expected.txt
    if diff -q out.txt expected.txt >/dev/null; then
        echo "[PASS] $name"
    else
        echo "[FAIL] $name"
        echo "Input: $input"
        echo "Expected: $expected"
        echo "Got:"
        cat out.txt
    fi
}

# Tests
run_test "echo hello" "hello" "echo basic"
run_test "pwd" "$(pwd)" "pwd"
run_test "ls | wc -l" "$(ls | wc -l)" "pipe basic"
run_test "cat <<EOF
hi
EOF" "hi" "heredoc basic"

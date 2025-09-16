#!/usr/bin/env bash

set -u  # safer script (error on unset vars)

echo "=== DEMO 1: Sequential pipelines with ; ==="
date +"Start: %T"
(sleep 2; echo "Pipeline 1 done") | cat ;
(sleep 2; echo "Pipeline 2 done") | cat ;
(sleep 2; echo "Pipeline 3 done") | cat ;
date +"End: %T"
echo

echo "=== DEMO 2: Parallel pipelines with & ==="
date +"Start: %T"
(sleep 2; echo "Pipeline 1 done") | cat &
(sleep 2; echo "Pipeline 2 done") | cat &
(sleep 2; echo "Pipeline 3 done") | cat &
wait   # wait for all background jobs
date +"End: %T"
echo

echo "=== DEMO 3: Exit status WITHOUT pipefail ==="
set +o pipefail   # disable pipefail
false | true      # 'false' fails, 'true' succeeds
echo "Exit status (expected 0, because last command succeeded): $?"

true | false      # 'true' succeeds, 'false' fails
echo "Exit status (expected 1, because last command failed): $?"
echo

echo "=== DEMO 4: Exit status WITH pipefail ==="
set -o pipefail   # enable pipefail
false | true      # left command fails
echo "Exit status (expected 1, because left command failed): $?"

true | false      # right command fails
echo "Exit status (expected 1, because right command failed): $?"

true | true       # both succeed
echo "Exit status (expected 0, all succeeded): $?"


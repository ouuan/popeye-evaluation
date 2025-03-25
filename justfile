_list:
    just --list

# Run ParDiff on two tests at paths <test1> and <test2>. Example: just pardiff tests/foo tests/bar
pardiff test1 test2:
    docker compose run --rm pardiff "{{test1}}" "{{test2}}"

# Run ParDiff example (tests/target1.bc tests/target2.bc)
pardiff-example:
    docker compose run --rm --entrypoint "bash -c 'pardiff /examples/target1.bc /examples/target2.bc -pardiff-entry=pardiff_main_message >/output/example-stdout.txt 2>/output/example-stderr.txt'" pardiff

# Run popeye on a test at path <test>. Example: just popeye tests/foo
popeye test:
    docker compose run --rm popeye "{{test}}"

# Run popeye example (benchmarks/ssq.bc)
popeye-example:
    docker compose run --rm --entrypoint "bash -c 'popeye /examples/ssq.bc -popeye-entry=popeye_main_ssq -popeye-output=dot:ssq.dot -popeye-output=bnf >/output/ssq-stdout.txt 2>/output/ssq-stderr.txt'" popeye

# Clean up bitcodes and object files in tests.
clean:
    find tests -type f -regex '.*\.\(bc\|o\)' -delete

# Build all Docker images.
build: build-pardiff build-popeye

# Build ParDiff Docker image.
build-pardiff:
    sudo docker compose build pardiff

# Build popeye Docker image.
build-popeye:
    sudo docker compose build popeye

_base := shell('basename "$1"', justfile_directory())
registry := "docker.ouuan.moe"

# Pull all Docker images from registry.
pull: pull-pardiff pull-popeye

# Pull ParDiff Docker image.
pull-pardiff:
    just _pull-image pardiff

# Pull popeye Docker image.
pull-popeye:
    just _pull-image popeye

_pull-image image:
    docker pull "{{registry}}/{{image}}"
    docker tag "{{registry}}/{{image}}" "{{_base}}-{{image}}"

# Push all Docker images to registry.
push: push-pardiff push-popeye

# Push ParDiff Docker image.
push-pardiff:
    just _push-image pardiff

# Push popeye Docker image.
push-popeye:
    just _push-image popeye

_push-image image:
    docker tag "{{_base}}-{{image}}" "{{registry}}/{{image}}"
    docker push "{{registry}}/{{image}}"

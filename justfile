_list:
    just --list

# Run ParDiff on two tests at paths <test1> and <test2>. Example: just pardiff tests/foo tests/bar
pardiff test1 test2:
    docker compose run --rm pardiff "{{test1}}" "{{test2}}"

pardiff-interactive:
    docker compose run --rm --entrypoint /bin/bash pardiff

# Run popeye on a test at path <test>. Example: just popeye tests/foo
popeye test:
    docker compose run --rm popeye "{{test}}"

popeye-interactive:
    docker compose run --rm --entrypoint /bin/bash popeye

# Clean up bitcodes and object files in tests.
clean:
    find tests -type f -regex '.*\.\(bc\|o|a\)' -delete
    sudo find tests -type d -name target -exec rm -rf {} +

# Build all Docker images.
build:
    sudo docker compose build

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

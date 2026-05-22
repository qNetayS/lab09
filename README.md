# Laboratory Work 09: GitHub Release

**Student:** qNetayS
**Date:** 2026-05-22

## Description
This project demonstrates creating GitHub Releases with GPG-signed tags and CPack packaging.

## Build
```shell
cmake -H. -B_build
cmake --build _build --target package

#!/bin/sh

cd /build
ln -s contrib/snap/snapcraft.yaml .
snapcraft

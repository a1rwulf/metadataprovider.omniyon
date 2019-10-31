#!/bin/bash

git archive --format=tar.gz --prefix=metadataprovider.omniyon-1.0.0-$(git rev-parse --short HEAD)/ $(git rev-parse --short HEAD) > metadataprovider.omniyon-1.0.0-$(git rev-parse --short HEAD).tar.gz

.DEFAULT_GOAL := help

.PHONY: help all tools problem-tools compile cases-compile generate run smoke list-problems validate-problems build-pack pack-verify clean

help all tools problem-tools compile cases-compile generate run smoke list-problems validate-problems build-pack pack-verify clean:
	$(MAKE) -C problems $@

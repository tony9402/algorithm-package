.DEFAULT_GOAL := help

.PHONY: help all testlib-link tools problem-tools compile cases-compile generate run smoke list-problems validate-problems build-pack pack-verify clean

help all testlib-link tools problem-tools compile cases-compile generate run smoke list-problems validate-problems build-pack pack-verify clean:
	$(MAKE) -C problems $@

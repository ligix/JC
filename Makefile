.PHONY: docs docs_grammar
docs: docs_grammar

docs_grammar GRAMMAR.html:
	ebnf-rr -out:GRAMMAR.html GRAMMAR.ebnf
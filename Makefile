.PHONY: docs docs_grammar
docs: docs_grammar

docs_grammar GRAMMAR.html:
	ebnf2railroad --title "JC Grammar" -o GRAMMAR.html GRAMMAR.ebnf
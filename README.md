# BOMBOSHELL

NOE:

-X- parsing
- - exec les cmd
//TODO	- - replace env vars ($---) to his content ($USER -> nmartin)
//TODO	- - unify REDIR -> WORD into FILE tokens
//TODO	- - move infile before CMD token (in exec take infile if FILE or PIPE token)
//TODO	- - move outfile after CMD token (in exec take outfile if FILE or PIPE token)
//TODO	- - unify words (WORD_S_QUOTE -> WORD_D_QUOTE -> WORD become CMD)
//TODO	- - replace WORD token by FILE token when its REDIR -> WORD
//TODO	- - do ast (abstract syntax tree) for exec order (PARANTHESIS priorities)
//TODO	- - handle heredoc (<<)
//TODO	- - handle BOOL token (in || kill the first process if the second is true and inverse)
//TODO	- - exec

ANAS:

- built-in
- signaux

reste a faire :

- variables d'environnements
- wildcards

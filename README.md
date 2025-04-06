# BOMBOSHELL

NOE:

-X- parsing
- - exec les cmd
//TODO	- - replace env vars ($---) to his content ($USER -> nmartin)
		-X- unify REDIR -> WORD into FILE tokens
//	- - move infile before CMD token (in exec take infile if FILE or PIPE token)
//	- - move outfile after CMD token (in exec take outfile if FILE or PIPE token)
//TODO	-X- unify words (WORD_S_QUOTE -> WORD_D_QUOTE -> WORD become CMD)
//TODO	- - do ast (abstract syntax tree) for exec order (PARANTHESIS priorities)
//TODO	- - handle heredoc (<<)
//TODO	- - handle BOOL token (in || kill the first process if the second is true and inverse)
//TODO	- - exec

ANAS:

- built-in
- signaux
- gerer la norme
- gerer les erreurs (exit code etc..)
- mettre les msg d'erreurs dans la sortie d'erreur (fd = 2)
- faire une fonction free_shell (free un t_shell)
- gerer le cas ou on unset le premier element de env (cahnger le pointeur de **env sur le nouveau premier element)

reste a faire :

- variables d'environnements
- wildcards

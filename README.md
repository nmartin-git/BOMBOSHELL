# BOMBOSHELL

NOE:

-X- parsing
- - exec les cmd
	-X- replace env vars ($---) to his content ($USER -> nmartin)
		-X- unify REDIR -> WORD into FILE tokens
//TODO	-X- unify words (WORD_S_QUOTE -> WORD_D_QUOTE -> WORD become CMD)
//TODO	- - do ast (abstract syntax tree) for exec order (PARANTHESIS priorities)
//TODO	-X- handle heredoc (<<)
//TODO	- - handle BOOL token
//TODO	- - exec
//TODO  - - tester : (cmd | "         " | cmd) (WORD_QUOTE is_space)

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
